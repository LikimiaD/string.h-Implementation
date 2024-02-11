#include <math.h>
#include <stdarg.h>

#include "../include/custom_string.h"
typedef struct {
  int left_align;
  int show_sign;
  int space_prefix;
  int width;
  int precision;
  int count_white_spaces;
  char length;
  char specifier;
  int zero;
  int hashtag;
  int custom_presicion;
} FormatSpec;

int is_negative_nan(long double value) {
  if (isnan(value)) {
    long double neg_value = -value;
    return isnan(neg_value) && (neg_value != value);
  }
  return 0;
}

long double custom_fabsl(long double x) {
  long double long_x = (long double)x;
  if (long_x < 0.0) {
    long_x *= -1;
  }
  return long_x;
}

long double round_long_double(long double value, int precision) {
  long double rounder = 0.5L;
  for (int i = 0; i < precision; i++) {
    if (precision >= 0)
      rounder /= 10.0L;
    else
      rounder *= 10.0L;
  }
  if (value < 0) rounder = -rounder;
  value = value + rounder;
  return value;
}

void int_to_char(char *buffer, long long value, FormatSpec parser) {
  int index = 0;
  int is_negative = value < 0;

  if (is_negative) {
    buffer[index++] = '-';
    value = -value;
  } else if (parser.show_sign == 1) {
    buffer[index++] = '+';
  } else if (parser.space_prefix == 1) {
    buffer[index++] = ' ';
  }

  if (value == 0) {
    buffer[index++] = '0';
  } else {
    int start = index;
    while (value > 0) {
      buffer[index++] = (char)(value % 10 + '0');
      value /= 10;
    }

    for (int i = start, j = index - 1; i < j; i++, j--) {
      char temp = buffer[i];
      buffer[i] = buffer[j];
      buffer[j] = temp;
    }
  }

  buffer[index] = '\0';
}

void uint_to_char(char *buffer, unsigned long long value) {
  int index = 0;

  if (value == 0) {
    buffer[index++] = '0';
  } else {
    int start = index;
    while (value > 0) {
      buffer[index++] = (char)(value % 10 + '0');
      value /= 10;
    }

    for (int i = start, j = index - 1; i < j; i++, j--) {
      char temp = buffer[i];
      buffer[i] = buffer[j];
      buffer[j] = temp;
    }
  }

  buffer[index] = '\0';
}

void double_part_to_char(char *buffer, int start_index, long double value,
                         FormatSpec parser) {
  for (int i = 0; i < parser.precision; i++) {
    value *= 10;
    int digit = (int)(value);
    buffer[start_index++] = digit + '0';
    value -= digit;
  }
  buffer[start_index] = '\0';
}

void pointer_to_hex(char *buffer, void *ptr) {
  unsigned long long address = (unsigned long long)ptr;
  int index = 0;
  if (address == 0) {
    buffer[index++] = '0';
  } else {
    while (address > 0) {
      int rem = address % 16;
      if (rem < 10) {
        buffer[index++] = '0' + rem;
      } else {
        buffer[index++] = 'a' + (rem - 10);
      }
      address /= 16;
    }
  }
  buffer[index] = '\0';
  for (int i = 0, j = index - 1; i < j; i++, j--) {
    char temp = buffer[i];
    buffer[i] = buffer[j];
    buffer[j] = temp;
  }
}

int is_number(char sym) { return ((sym >= 48) && (sym <= 57)) ? 1 : 0; }

int handle_character(char **str, va_list *args, FormatSpec parser) {
  char input = (char)va_arg(*args, int);
  int added_chars = 0;

  int padding =
      parser.count_white_spaces > 1 ? parser.count_white_spaces - 1 : 0;

  if (!parser.left_align && padding > 0) {
    char fill_char = parser.zero ? '0' : ' ';
    for (int i = 0; i < padding; i++) {
      *(*str)++ = fill_char;
      added_chars++;
    }
  }

  **str = input;
  (*str)++;
  added_chars++;

  if (parser.left_align && padding > 0) {
    for (int i = 0; i < padding; i++) {
      *(*str)++ = ' ';
      added_chars++;
    }
  }

  return added_chars;
}

int handle_integer(char **str, va_list *args, FormatSpec parser) {
  long long int input = 0;
  if (parser.length == 'h') {
    input = (short int)va_arg(*args, int);
  } else if (parser.length == 'l') {
    input = va_arg(*args, long int);
  } else if (parser.length == 'L') {
    input = va_arg(*args, long long int);
  } else {
    input = va_arg(*args, int);
  }

  char buffer[long_long_int_max_len];
  int_to_char(buffer, input, parser);

  int len = custom_strlen(buffer);
  int added_chars = 0;

  int num_zeros = parser.precision > len ? parser.precision - len : 0;
  if (parser.zero) {
    num_zeros = parser.count_white_spaces - len;
  } else if (parser.precision > 0) {
    if ((input < 0 || parser.show_sign || parser.space_prefix) &&
        (parser.precision - len > -1)) {
      num_zeros += 1;
    }
  }

  int total_length = len + num_zeros;
  int padding = parser.count_white_spaces > total_length
                    ? parser.count_white_spaces - total_length
                    : 0;

  if (!parser.left_align && padding > 0) {
    for (int i = 0; i < padding; i++) {
      *(*str)++ = parser.zero == 1 ? '0' : ' ';
      added_chars++;
    }
  }

  if (input < 0) {
    *(*str)++ = '-';
    added_chars++;
  } else if (parser.show_sign) {
    *(*str)++ = '+';
    added_chars++;
  } else if (parser.space_prefix && input > 0) {
    *(*str)++ = ' ';
    added_chars++;
  }

  for (int i = 0; i < num_zeros; i++) {
    *(*str)++ = '0';
    added_chars++;
  }

  for (int i = (input < 0 || parser.show_sign || parser.space_prefix) ? 1 : 0;
       i < len; i++) {
    *(*str)++ = buffer[i];
    added_chars++;
  }

  if (parser.space_prefix != 0) {
    padding += parser.space_prefix;
  }

  if (parser.left_align && padding > 0) {
    for (int i = 0; i < padding; i++) {
      *(*str)++ = ' ';
      added_chars++;
    }
  }

  return added_chars;
}

int handle_float(char **str, va_list *args, FormatSpec parser) {
  long double input = (parser.length == 'L') ? va_arg(*args, long double)
                                             : va_arg(*args, double);

  char buffer[double_max_len];
  custom_memset(buffer, 0, double_max_len);

  int added_chars = 0;

  if (isnan(input) || isinf(input)) {
    parser.hashtag = 0;
    char specialValue[5];
    int current_index = 0;

    if (isinf(input) && input > 0.0 && parser.show_sign) {
      specialValue[current_index++] = '+';
    }

    custom_strcpy(&specialValue[current_index], isinf(input) ? "inf" : "NaN");

    int specialLen = custom_strlen(specialValue);
    int padding = parser.count_white_spaces - specialLen;

    if (!parser.left_align && padding > 0) {
      char fill_char = parser.zero ? '0' : ' ';
      for (int i = 0; i < padding; i++) {
        *(*str)++ = fill_char;
        added_chars++;
      }
    }

    custom_strcpy(*str, specialValue);
    *str += specialLen;
    added_chars += specialLen;

    if (parser.left_align && padding > 0) {
      for (int i = 0; i < padding; i++) {
        *(*str)++ = ' ';
        added_chars++;
      }
    }
  } else {
    input = round_long_double(input, parser.precision);

    long long int_part = (long long)input;
    long double fractional_part = custom_fabsl(input - (long double)int_part);

    int_to_char(buffer, int_part, parser);
    int current_index = custom_strlen(buffer);

    if (parser.precision > 0 || (parser.hashtag && parser.precision == 0)) {
      buffer[current_index++] = '.';
      double_part_to_char(buffer, current_index, fractional_part, parser);
      current_index += custom_strlen(buffer);
    }

    int len = custom_strlen(buffer);
    int padding = parser.count_white_spaces - len;

    if (!parser.left_align && padding > 0) {
      char fill_char = parser.zero ? '0' : ' ';
      for (int i = 0; i < padding; i++) {
        *(*str)++ = fill_char;
        added_chars++;
      }
    }

    for (int i = 0; i < len; i++) {
      *(*str)++ = buffer[i];
      added_chars++;
    }

    if (parser.left_align && padding > 0) {
      for (int i = 0; i < padding; i++) {
        *(*str)++ = ' ';
        added_chars++;
      }
    }
  }

  return added_chars;
}

int handle_gfloat(char **str, long double arg, FormatSpec parser) {
  long double input = arg;

  char buffer[double_max_len];
  custom_memset(buffer, 0, double_max_len);

  int added_chars = 0;

  if (isnan(input) || isinf(input)) {
    parser.hashtag = 0;
    char specialValue[5];
    int current_index = 0;

    if (isinf(input) && input > 0.0 && parser.show_sign) {
      specialValue[current_index++] = '+';
    }

    custom_strcpy(&specialValue[current_index], isinf(input) ? "inf" : "NaN");

    int specialLen = custom_strlen(specialValue);
    int padding = parser.count_white_spaces - specialLen;

    if (!parser.left_align && padding > 0) {
      char fill_char = parser.zero ? '0' : ' ';
      for (int i = 0; i < padding; i++) {
        *(*str)++ = fill_char;
        added_chars++;
      }
    }

    custom_strcpy(*str, specialValue);
    *str += specialLen;
    added_chars += specialLen;

    if (parser.left_align && padding > 0) {
      for (int i = 0; i < padding; i++) {
        *(*str)++ = ' ';
        added_chars++;
      }
    }
  } else {
    int ilen = 0;
    for (long double val = input; fabsl(val) >= 1; val /= 10) {
      ilen++;
    }
    parser.precision -= ilen;
    input = round_long_double(input, parser.precision);

    long long int_part = (long long)input;
    long double fractional_part = custom_fabsl(input - (long double)int_part);

    int_to_char(buffer, int_part, parser);
    int current_index = custom_strlen(buffer);

    if (parser.precision > 0) {
      int fraction_index = current_index;
      buffer[current_index++] = '.';
      double_part_to_char(buffer, current_index, fractional_part, parser);
      current_index += parser.precision;

      while (current_index > fraction_index + 1 &&
             buffer[current_index - 1] == '0') {
        current_index--;
      }
      if (buffer[current_index - 1] == '.') {
        current_index--;
      }
    } else if (parser.hashtag && parser.precision == 0) {
      buffer[current_index++] = '.';
    }

    int len = custom_strlen(buffer);
    int padding = parser.count_white_spaces - len;

    if (!parser.left_align && padding > 0) {
      char fill_char = parser.zero ? '0' : ' ';
      for (int i = 0; i < padding; i++) {
        *(*str)++ = fill_char;
        added_chars++;
      }
    }

    for (int i = 0; i < len; i++) {
      *(*str)++ = buffer[i];
      added_chars++;
    }

    if (parser.left_align && padding > 0) {
      for (int i = 0; i < padding; i++) {
        *(*str)++ = ' ';
        added_chars++;
      }
    }
  }

  return added_chars;
}

int handle_string(char **str, va_list *args, FormatSpec parser) {
  const char *input = va_arg(*args, const char *);
  int len = custom_strlen(input);
  int added_chars = 0;
  if (!parser.left_align) {
    for (int i = len; i < parser.count_white_spaces; i++) {
      *(*str)++ = parser.zero == 1 ? '0' : ' ';
      added_chars++;
    }
  }
  while (*input) {
    *(*str)++ = *input++;
    added_chars++;
  }
  if (parser.left_align) {
    for (int i = len; i < parser.count_white_spaces; i++) {
      *(*str)++ = ' ';
      added_chars++;
    }
  }

  return added_chars;
}

int handle_unsigned_integer(char **str, va_list *args, FormatSpec parser) {
  unsigned long long input = 0;
  int input_len = unsigned_long_long_int_max_len;

  if (parser.length == 'h') {
    input = (unsigned short)va_arg(*args, unsigned int);
    input_len = unsigned_short_int_max_len;
  } else if (parser.length == 'l') {
    input = va_arg(*args, unsigned long);
    input_len = unsigned_long_int_max_len;
  } else if (parser.length == 'L') {
    input = va_arg(*args, unsigned long long);
  } else {
    input = va_arg(*args, unsigned int);
    input_len = unsigned_int_max_len;
  }

  char buffer[input_len];
  uint_to_char(buffer, input);
  int len = custom_strlen(buffer);

  int zero_padding = (parser.custom_presicion && parser.precision > len)
                         ? (parser.precision - len)
                         : 0;

  int total_padding = parser.count_white_spaces - (len + zero_padding);
  int added_chars = 0;

  if (!parser.left_align) {
    for (int i = 0; i < total_padding; i++) {
      *(*str)++ = parser.zero == 1 ? '0' : ' ';
      added_chars++;
    }
  }

  for (int i = 0; i < zero_padding; i++) {
    *(*str)++ = '0';
    added_chars++;
  }

  for (int i = 0; i < len; i++) {
    *(*str)++ = buffer[i];
    added_chars++;
  }

  if (parser.left_align) {
    for (int i = 0; i < total_padding; i++) {
      *(*str)++ = ' ';
      added_chars++;
    }
  }

  return added_chars;
}

int handle_percent(char **str, FormatSpec parser) {
  int added_chars = 0;
  if (!parser.left_align) {
    for (int i = 0; i < parser.count_white_spaces - 1; i++) {
      *(*str)++ = parser.zero == 1 ? '0' : ' ';
      added_chars++;
    }
  }
  **str = '%';
  (*str)++;
  added_chars++;
  if (parser.left_align) {
    for (int i = 1; i < parser.count_white_spaces; i++) {
      *(*str)++ = ' ';
      added_chars++;
    }
  }
  return added_chars;
}

int handle_oct(char **str, va_list *args, FormatSpec parser) {
  unsigned long long n = 0;

  if (parser.length == 'h') {
    n = (unsigned short)va_arg(*args, unsigned int);
  } else if (parser.length == 'l') {
    n = va_arg(*args, unsigned long);
  } else if (parser.length == 'L') {
    n = va_arg(*args, unsigned long long);
  } else {
    n = va_arg(*args, unsigned int);
  }

  char buffer[100];
  int buf_index = 0;

  if (n == 0) {
    buffer[buf_index++] = '0';
  } else {
    for (unsigned long long temp = n; temp != 0; temp /= 8) {
      buffer[buf_index++] = '0' + (temp % 8);
    }
  }

  int len = buf_index;
  int added_chars = 0;

  int zero_padding = 0;
  if (parser.custom_presicion && parser.precision > len) {
    zero_padding = parser.precision - len;
  }

  int total_padding = parser.count_white_spaces - (len + zero_padding);

  if (parser.hashtag == 1 && n != 0 && parser.zero != 1 &&
      parser.left_align != 1) {
    *(*str)++ = '0';
    added_chars++;
    total_padding--;
  }

  if (!parser.left_align) {
    for (int i = 0; i < total_padding; i++) {
      *(*str)++ = ' ';
      added_chars++;
    }
  }

  for (int i = 0; i < zero_padding; i++) {
    *(*str)++ = '0';
    added_chars++;
  }

  while (--buf_index >= 0) {
    *(*str)++ = buffer[buf_index];
    added_chars++;
  }

  if (parser.left_align) {
    for (int i = 0; i < total_padding; i++) {
      *(*str)++ = ' ';
      added_chars++;
    }
  }

  return added_chars;
}

// Число в шестнадцатеричную
void uint_to_hex(char *buffer, unsigned long long number, int uppercase) {
  const char *digits = uppercase ? "0123456789ABCDEF" : "0123456789abcdef";
  char temp[17];
  int i = 0;

  if (number == 0) {
    temp[i++] = '0';
  } else {
    while (number != 0) {
      temp[i++] = digits[number % 16];
      number /= 16;
    }
  }

  int j = 0;
  while (i > 0) {
    buffer[j++] = temp[--i];
  }
  buffer[j] = '\0';
}

int handle_hex(char **str, va_list *args, FormatSpec parser, int is_upper) {
  unsigned long long input = 0;
  if (parser.length == 'h') {
    input = (unsigned short)va_arg(*args, unsigned int);
  } else if (parser.length == 'l') {
    input = va_arg(*args, unsigned long);
  } else if (parser.length == 'L') {
    input = va_arg(*args, unsigned long long);
  } else {
    input = va_arg(*args, unsigned int);
  }

  char buffer[17];
  uint_to_hex(buffer, input, is_upper);
  int len = custom_strlen(buffer);

  int zero_padding = (parser.custom_presicion && parser.precision > len)
                         ? (parser.precision - len)
                         : 0;

  int prefix_len = (parser.hashtag == 1 && input != 0) ? 2 : 0;
  int total_padding =
      parser.count_white_spaces - (len + zero_padding + prefix_len);
  int added_chars = 0;

  if (!parser.left_align) {
    for (int i = 0; i < total_padding; i++) {
      *(*str)++ = ' ';
      added_chars++;
    }
  }

  if (parser.hashtag == 1 && input != 0) {
    *(*str)++ = '0';
    *(*str)++ = is_upper ? 'X' : 'x';
    added_chars += 2;
  }

  for (int i = 0; i < zero_padding; i++) {
    *(*str)++ = '0';
    added_chars++;
  }

  for (int i = 0; i < len; i++) {
    *(*str)++ = buffer[i];
    added_chars++;
  }

  if (parser.left_align) {
    for (int i = 0; i < total_padding; i++) {
      *(*str)++ = ' ';
      added_chars++;
    }
  }

  return added_chars;
}

int handle_hex_lower(char **str, va_list *args, FormatSpec parser) {
  return handle_hex(str, args, parser, 0);
}

int handle_hex_upper(char **str, va_list *args, FormatSpec parser) {
  return handle_hex(str, args, parser, 1);
}

int handle_pointer(char **str, va_list *args, FormatSpec parser) {
  void *ptr = va_arg(*args, void *);
  char buffer[20];
  int added_chars = 0;

  if (ptr == NULL_VALUE) {
    custom_strcpy(buffer, "(nil)");
  } else {
    custom_strcpy(buffer, "0x");
    pointer_to_hex(buffer + 2, ptr);
  }

  int len = custom_strlen(buffer);
  int padding = parser.count_white_spaces - len;

  if (!parser.left_align && padding > 0) {
    char fill_char = parser.zero ? '0' : ' ';
    for (int i = 0; i < padding; i++) {
      *(*str)++ = fill_char;
      added_chars++;
    }
  }

  custom_strcpy(*str, buffer);
  *str += len;
  added_chars += len;

  if (parser.left_align && padding > 0) {
    for (int i = 0; i < padding; i++) {
      *(*str)++ = ' ';
      added_chars++;
    }
  }

  return added_chars;
}

void local_int_to_char(char *buffer, int value) {
  int index = 0;
  if (value == 0) {
    buffer[index++] = '0';
  } else {
    int is_negative = value < 0;
    if (is_negative) {
      value = -value;
      buffer[index++] = '-';
    }

    int start_index = index;
    while (value > 0) {
      buffer[index++] = (value % 10) + '0';
      value /= 10;
    }

    for (int i = start_index, j = index - 1; i < j; i++, j--) {
      char temp = buffer[i];
      buffer[i] = buffer[j];
      buffer[j] = temp;
    }
  }

  buffer[index] = '\0';
}

int handle_e(char **str, va_list *args, FormatSpec parser, int uppercase) {
  long double value = (parser.length == 'L') ? va_arg(*args, long double)
                                             : va_arg(*args, double);
  char buffer[double_max_len];  // Ensure this is large enough
  int added_chars = 0;
  int current_index = 0;
  int remove = 0;
  int is_negative_zero = (value == 0.0 && 1.0 / value < 0.0);

  if (isinf(value)) {
    if (value < 0 || is_negative_zero) {
      buffer[added_chars++] = '-';
      current_index++;
      remove++;
    }
    const char *infStr = uppercase ? "INF" : "inf";
    for (int i = 0; infStr[i] != '\0'; i++) {
      buffer[added_chars++] = infStr[i];
      current_index++;
      remove++;
    }
  } else if (isnan(value)) {
    if (is_negative_nan(value)) {
      buffer[added_chars++] = '-';
      current_index++;
      remove++;
    }
    const char *nanStr = uppercase ? "NAN" : "nan";
    for (int i = 0; nanStr[i] != '\0'; i++) {
      buffer[added_chars++] = nanStr[i];
      current_index++;
      remove++;
    }
  } else {
    int degree = 0;
    long double mantissa = value < 0 ? -value : value;
    if (mantissa != 0) {
      while (mantissa >= 10) {
        mantissa /= 10;
        degree++;
      }
      while (mantissa < 1) {
        mantissa *= 10;
        degree--;
      }
    }

    double rounder = 0.5;
    for (int i = 0; i < parser.precision; i++) {
      rounder /= 10;
    }
    mantissa += rounder;

    if (mantissa >= 10) {
      mantissa /= 10;
      degree++;
    }

    if (value < 0 || is_negative_zero) {
      buffer[current_index++] = '-';
    } else if (parser.show_sign) {
      buffer[current_index++] = '+';
    } else if (parser.space_prefix) {
      buffer[current_index++] = ' ';
    }

    int mantissa_int = (int)mantissa;
    char mantissa_str[20];
    local_int_to_char(mantissa_str, mantissa_int);
    int mantissa_len = custom_strlen(mantissa_str);
    for (int i = 0; i < mantissa_len; i++) {
      buffer[current_index++] = mantissa_str[i];
    }

    if (parser.precision > 0 || parser.hashtag == 1) {
      buffer[current_index++] = '.';
    }
    if (parser.precision > 0) {
      double fractional_part = mantissa - mantissa_int;
      double_part_to_char(buffer, current_index, fractional_part, parser);
      current_index += parser.precision;
    } else if (parser.hashtag == 1 && parser.precision == 0) {
      buffer[current_index++] = '0';
    }

    buffer[current_index++] = uppercase ? 'E' : 'e';
    if (degree < 0) {
      buffer[current_index++] = '-';
      degree = -degree;
    } else {
      buffer[current_index++] = '+';
    }
    char degree_str[20];
    local_int_to_char(degree_str, degree);
    int degree_len = custom_strlen(degree_str);
    if (degree_len == 1) {
      buffer[current_index++] = '0';
    }
    for (int i = 0; i < degree_len; i++) {
      buffer[current_index++] = degree_str[i];
    }
  }

  int len = current_index;
  if (!parser.left_align) {
    for (int i = len; i < parser.count_white_spaces; i++) {
      *(*str)++ = parser.zero ? '0' : ' ';
      added_chars++;
    }
  }

  for (int i = 0; i < len; i++) {
    *(*str)++ = buffer[i];
    added_chars++;
  }

  if (parser.left_align) {
    for (int i = len; i < parser.count_white_spaces; i++) {
      *(*str)++ = ' ';
      added_chars++;
    }
  }

  return added_chars - remove;
}

int handle_ge(char **str, long double arg, FormatSpec parser, int uppercase) {
  long double value = arg;
  char buffer[double_max_len];
  int added_chars = 0;
  int current_index = 0;
  int remove = 0;
  int is_negative_zero = (value == 0.0 && 1.0 / value < 0.0);

  if (isinf(value)) {
    if (value < 0 || is_negative_zero) {
      buffer[added_chars++] = '-';
      current_index++;
      remove++;
    }
    const char *infStr = uppercase ? "INF" : "inf";
    for (int i = 0; infStr[i] != '\0'; i++) {
      buffer[added_chars++] = infStr[i];
      current_index++;
      remove++;
    }
  } else if (isnan(value)) {
    if (is_negative_nan(value)) {
      buffer[added_chars++] = '-';
      current_index++;
      remove++;
    }
    const char *nanStr = uppercase ? "NAN" : "nan";
    for (int i = 0; nanStr[i] != '\0'; i++) {
      buffer[added_chars++] = nanStr[i];
      current_index++;
      remove++;
    }
  } else {
    int degree = 0;
    long double mantissa = value < 0 ? -value : value;
    if (mantissa != 0) {
      while (mantissa >= 10) {
        mantissa /= 10;
        degree++;
      }
      while (mantissa < 1) {
        mantissa *= 10;
        degree--;
      }
    }

    double rounder = 0.5;
    for (int i = 0; i < parser.precision; i++) {
      rounder /= 10;
    }
    mantissa += rounder;

    if (mantissa >= 10) {
      mantissa /= 10;
      degree++;
    }

    if (value < 0 || is_negative_zero) {
      buffer[current_index++] = '-';
    } else if (parser.show_sign) {
      buffer[current_index++] = '+';
    } else if (parser.space_prefix) {
      buffer[current_index++] = ' ';
    }

    int mantissa_int = (int)mantissa;
    char mantissa_str[20];
    local_int_to_char(mantissa_str, mantissa_int);
    int mantissa_len = custom_strlen(mantissa_str);
    for (int i = 0; i < mantissa_len; i++) {
      buffer[current_index++] = mantissa_str[i];
    }

    if (parser.precision > 0) {
      double fractional_part = mantissa - mantissa_int;
      double_part_to_char(buffer, current_index, fractional_part, parser);
      int end = current_index + parser.precision;
      while (end > current_index && buffer[end - 1] == '0') {
        end--;
      }

      if (end > current_index) {
        buffer[current_index++] = '.';
        current_index = end;
      }
    } else if (parser.hashtag == 1 && parser.precision == 0) {
      buffer[current_index++] = '.';
      buffer[current_index++] = '0';
    }

    buffer[current_index++] = uppercase ? 'E' : 'e';
    if (degree < 0) {
      buffer[current_index++] = '-';
      degree = -degree;
    } else {
      buffer[current_index++] = '+';
    }
    char degree_str[20];
    local_int_to_char(degree_str, degree);
    int degree_len = custom_strlen(degree_str);
    // Add leading zero for degree if necessary
    if (degree_len == 1) {
      buffer[current_index++] = '0';
    }
    for (int i = 0; i < degree_len; i++) {
      buffer[current_index++] = degree_str[i];
    }
  }

  int len = current_index;
  if (!parser.left_align) {
    for (int i = len; i < parser.count_white_spaces; i++) {
      *(*str)++ = parser.zero ? '0' : ' ';
      added_chars++;
    }
  }

  for (int i = 0; i < len; i++) {
    *(*str)++ = buffer[i];
    added_chars++;
  }

  if (parser.left_align) {
    for (int i = len; i < parser.count_white_spaces; i++) {
      *(*str)++ = ' ';
      added_chars++;
    }
  }

  return added_chars - remove;
}

int handle_g(char **str, va_list *args, FormatSpec parser, int uppercase) {
  long double value = (parser.length == 'L') ? va_arg(*args, long double)
                                             : va_arg(*args, double);

  int use_e_format = 0;
  int degree = 0;
  long double mantissa = (value < 0) ? -value : value;

  if (mantissa != 0.0) {
    while (mantissa >= 10.0) {
      mantissa /= 10.0;
      degree++;
    }
    while (mantissa < 1.0) {
      mantissa *= 10.0;
      degree--;
    }
  }

  if ((degree < -4 || degree >= parser.precision) && degree != 0) {
    use_e_format = 1;
  }

  if (use_e_format) {
    return handle_ge(str, value, parser, uppercase);
  } else {
    return handle_gfloat(str, value, parser);
  }
}

int handle_n(int written_so_far, int *arg) {
  *arg = written_so_far;
  return 0;
}

int custom_sprintf(char *str, const char *format, ...) {
  int current_len = 0;
  va_list args;
  va_start(args, format);
  int tmp = 0;

  for (const char *ptr = format; *ptr != '\0'; ptr++) {
    if (*ptr == '%') {
      FormatSpec parser = {0};
      parser.precision = -1;
      ptr++;
      parser.count_white_spaces = 0;
      if (*ptr == '0' && *(ptr - 1) == '%') {
        parser.zero = 1;
        ptr++;
      }
      while (is_number(*ptr)) {
        parser.count_white_spaces =
            parser.count_white_spaces * 10 + (*ptr - '0');
        ptr++;
      }
      while (*ptr != 'c' && *ptr != 'd' && *ptr != 'f' && *ptr != 's' &&
             *ptr != 'u' && *ptr != '%' && *ptr != 'o' && *ptr != 'x' &&
             *ptr != 'X' && *ptr != 'p' && *ptr != 'e' && *ptr != 'E' &&
             *ptr != 'g' && *ptr != 'G' && *ptr != 'F' && *ptr != 'n') {
        switch (*ptr) {
          case '+':
            parser.show_sign = 1;
            ptr++;
            if (*ptr == '0') {
              parser.zero = 1;
              ptr++;
            }
            while (is_number(*ptr)) {
              parser.count_white_spaces =
                  parser.count_white_spaces * 10 + (*ptr - '0');
              ptr++;
            }
            ptr--;
            break;
          case ' ':
            parser.space_prefix = 1;
            if (is_number(*(ptr + 1))) {
              while (is_number(*(ptr + 1))) {
                parser.count_white_spaces =
                    parser.count_white_spaces * 10 + (*(ptr + 1) - '0');
                ptr++;
              }
            }
            break;
          case '.':
            ptr++;
            if (*ptr == '*') {
              tmp = va_arg(args, int);
              parser.precision = tmp;
            } else {
              parser.precision = 0;
              while (is_number(*ptr) == 1) {
                parser.precision = parser.precision * 10 + (*ptr - '0');
                ptr++;
              }
              ptr--;
            }
            parser.custom_presicion = 1;
            break;
          case '-':
            parser.left_align = 1;
            ptr++;
            parser.count_white_spaces = 0;
            while (is_number(*ptr) == 1) {
              parser.count_white_spaces =
                  parser.count_white_spaces * 10 + (*ptr - '0');
              ptr++;
            }
            ptr--;
            break;
          case '*':
            tmp = va_arg(args, int);
            if (tmp < 0) {
              parser.left_align = 1;
              tmp = -tmp;
            }
            parser.count_white_spaces = tmp;
            break;
          case 'l':
          case 'h':
          case 'L':
            parser.length = *ptr;
            break;
          case '0':
            parser.zero = 1;
            break;
          case '#':
            ptr++;
            parser.count_white_spaces = 0;
            while (is_number(*ptr) == 1) {
              parser.count_white_spaces =
                  parser.count_white_spaces * 10 + (*ptr - '0');
              ptr++;
            }
            ptr--;
            parser.hashtag = 1;
            break;
          default:
            break;
        }
        ptr++;
      }
      switch (*ptr) {
        case 'c':
          current_len += handle_character(&str, &args, parser);
          break;
        case 'd':
        case 'i':
          current_len += handle_integer(&str, &args, parser);
          break;
        case 'n':
          int *arg_ptr = va_arg(args, int *);
          handle_n(current_len, arg_ptr);
          break;
        case 'f':
        case 'F':
          if (parser.precision == -1) {
            parser.precision = 6;
          }
          current_len += handle_float(&str, &args, parser);
          break;
        case 's':
          current_len += handle_string(&str, &args, parser);
          break;
        case 'u':
          current_len += handle_unsigned_integer(&str, &args, parser);
          break;
        case '%':
          current_len += handle_percent(&str, parser);
          break;
        case 'o':
          current_len += handle_oct(&str, &args, parser);
          break;
        case 'x':
          current_len += handle_hex_lower(&str, &args, parser);
          break;
        case 'X':
          current_len += handle_hex_upper(&str, &args, parser);
          break;
        case 'p':
          current_len += handle_pointer(&str, &args, parser);
          break;
        case 'e':
          current_len += handle_e(&str, &args, parser, 0);
          break;
        case 'E':
          current_len += handle_e(&str, &args, parser, 1);
          break;
        case 'g':
          current_len += handle_g(&str, &args, parser, 0);
          break;
        case 'G':
          current_len += handle_g(&str, &args, parser, 1);
          break;
      }
    } else {
      *str++ = *ptr;
      current_len++;
    }
  }
  va_end(args);
  *str = '\0';
  return current_len;
}