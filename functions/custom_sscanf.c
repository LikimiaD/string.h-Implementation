#include "../include/custom_sscanf.h"

int custom_sscanf(const char *str, const char *format, ...) {
  int result = *str ? 0 : -1;
  va_list ap;
  va_start(ap, format);

  char *s_str = (char *)str;
  char *start = s_str;
  char *f_str = (char *)format;
  while (*s_str && *f_str && result != -1) {
    if (*f_str == '%') {
      f_str++;
      if (*f_str != '%') {
        specifier opt = scan_specifier(&f_str);
        result += scan(opt, &s_str, ap, &result, start);
      } else {
        if (*s_str == '%') {
          s_str++;
          f_str++;
        } else {
          result = -1;
        }
      }
    } else {
      if (*s_str == *f_str) {
        s_str++;
        f_str++;
      } else if (*f_str == ' ') {
        f_str++;
      } else {
        break;
      }
    }
  }
  if (*f_str == '%' && *(f_str + 1) == 'n') {
    *va_arg(ap, long int *) = s_str - start;
  }

  va_end(ap);

  return result;
}

specifier scan_specifier(char **format) {
  specifier res = {0};
  if (**format == '*') {
    res.skip = 1;
    (*format)++;
  }

  if (is_digit(**format, 10)) {
    res.width = scan_width(format);
  }

  if (**format == 'l') {
    res.len = len_l;
    (*format)++;
    if (**format == 'l') {
      res.len = len_L;
      (*format)++;
    }
  } else if (**format == 'h') {
    res.len = len_h;
    (*format)++;
  } else if (**format == 'L') {
    res.len = len_L;
    (*format)++;
  } else {
    res.len = len_none;
  }
  const char *opt_str = "cdieEfgGosuxXpn";
  char *pos = custom_strchr(opt_str, **format);
  if (pos) {
    res.opt = (options)(pos - opt_str);
  } else {
    res.opt = opt_unknown;
  }
  (*format)++;
  return res;
}

int scan_width(char **f_str) {
  int res = 0;
  while (is_digit(**f_str, 10)) {
    res = res * 10 + (**f_str - '0');
    (*f_str)++;
  }
  return res;
}

int is_digit(char c, int base) {
  int res;
  if (base <= 10) {
    res = c >= '0' && c < '0' + base;
  } else {
    res = (c >= '0' && c <= '9') || (c >= 'A' && c < 'A' + base - 10) ||
          (c >= 'a' && c < 'a' + base - 10);
  }
  return res;
}

custom_size_t to_digit(char c, int base) {
  custom_size_t res = 0;
  if (base <= 10) {
    res = c - '0';
  } else {
    if (c <= '9') {
      res = c - '0';
    } else if (c <= 'A' + base - 10) {
      res = c - 'A' + 10;
    } else {
      res = c - 'a' + 10;
    }
  }
  return res;
}

char chr_lower(char c) {
  if (c >= 'A' && c <= 'Z') {
    c += 'a' - 'A';
  }
  return c;
}

int strstr_icase(char **str, char *pat) {
  int res = 0;
  char *s = *str;
  while (*s && chr_lower(*s) == chr_lower(*pat)) {
    s++;
    pat++;
  }
  if (*pat == '\0') {
    *str = s;
    res = 1;
  }
  return res;
}

int scan(specifier opt, char **str, va_list ap, int *res, char *start) {
  int result = 0;
  while (**str == ' ') {
    (*str)++;
  }
  if (**str) {
    switch (opt.opt) {
      case opt_c:
        result = parse_string(opt, str, ap);
        break;
      case opt_d:
        result = parse_int(opt, str, ap);
        break;
      case opt_i:
        result = parse_i_uint(opt, str, ap);
        break;
      case opt_e:
        result = parse_float(opt, str, ap);
        break;
      case opt_E:
        result = parse_float(opt, str, ap);
        break;
      case opt_f:
        result = parse_float(opt, str, ap);
        break;
      case opt_g:
        result = parse_float(opt, str, ap);
        break;
      case opt_G:
        result = parse_float(opt, str, ap);
        break;
      case opt_o:
        result = parse_oct(opt, str, ap, 0);
        break;
      case opt_s:
        result = parse_string(opt, str, ap);
        break;
      case opt_u:
        result = parse_uint(opt, str, ap, 0);
        break;
      case opt_x:
        result = parse_hex(opt, str, ap, 0);
        break;
      case opt_X:
        result = parse_hex(opt, str, ap, 0);
        break;
      case opt_p:
        result = parse_ptr(opt, str, ap);
        break;
      case opt_n:
        *va_arg(ap, long int *) = *str - start;
        break;
      case opt_unknown:
        *res = -1;
        break;
      default:
        *res = -1;
        break;
    }
  } else {
    *res = -1;
  }
  return result;
}

int parse_string(specifier opt, char **str, va_list ap) {
  int result = 0;
  char *d = va_arg(ap, char *);
  if (opt.width == 0) {
    if (opt.opt == opt_c) {
      opt.width = 1;
    } else {
      opt.width = INT_MAX;
    }
  }
  while (**str && opt.width > 0 && **str != ' ') {
    *d++ = **str;
    (*str)++;
    opt.width--;
  }
  if (opt.opt == opt_s) {
    *d = '\0';
  }
  result = 1;

  return result;
}

int parse_int(specifier opt, char **str, va_list ap) {
  long long res = 0;
  int result = scan_int(str, opt.width, &res);
  result &= !opt.skip;
  if (result) {
    switch (opt.len) {
      case len_none:
        *(va_arg(ap, int *)) = (int)res;
        break;
      case len_h:
        *(va_arg(ap, short *)) = (short)res;
        break;
      case len_l:
        *(va_arg(ap, long *)) = (long)res;
        break;
      case len_L:
        *(va_arg(ap, long long *)) = (long long)res;
        break;
    }
  }
  return result;
}

int parse_based_uint(specifier opt, char **str, va_list ap, int base, int neg) {
  unsigned long long res = 0;
  int result = scan_based_uint(str, opt.width, &res, base, neg) || neg;
  result &= !opt.skip;
  if (result) {
    switch (opt.len) {
      case len_none:
        *(va_arg(ap, unsigned int *)) = (unsigned int)res;
        break;
      case len_h:
        *(va_arg(ap, unsigned short *)) = (unsigned short)res;
        break;
      case len_l:
        *(va_arg(ap, unsigned long *)) = (unsigned long)res;
        break;
      case len_L:
        *(va_arg(ap, unsigned long long *)) = (unsigned long long)res;
        break;
    }
  }
  return result;
}

int parse_uint(specifier opt, char **str, va_list ap, int neg) {
  int res = 0;
  int f = 1;
  if (**str == '-') {
    if (!neg) {
      (*str)++;
      opt.width--;
      neg = 1;
    } else {
      f = 0;
    }
  } else if (**str == '+') {
    (*str)++;
    opt.width--;
  }
  if (f) {
    res |= parse_based_uint(opt, str, ap, 10, neg);
  }
  return res;
}

int parse_hex(specifier opt, char **str, va_list ap, int neg) {
  int res = neg;
  if (**str == '-' && !neg) {
    (*str)++;
    opt.width--;
    neg = 1;
  } else if (**str == '+') {
    (*str)++;
    opt.width--;
  }
  if (**str == '0' && ((*(*str + 1) == 'x') || *(*str + 1) == 'X')) {
    *str += 2;
    res |= 1;
  }
  res |= parse_based_uint(opt, str, ap, 16, neg);
  return res;
}

int parse_oct(specifier opt, char **str, va_list ap, int neg) {
  int res = neg;
  if (**str == '-' && !neg) {
    neg = 1;
    (*str)++;
    opt.width--;
  } else if (**str == '+') {
    (*str)++;
    opt.width--;
  }
  if (**str == '0') {
    (*str)++;
    opt.width--;
    res |= 1;
  }
  res |= parse_based_uint(opt, str, ap, 8, neg);
  return res;
}

int parse_i_uint(specifier opt, char **str, va_list ap) {
  int neg = 0;
  if (**str == '-') {
    neg = 1;
    (*str)++;
    opt.width--;
  } else if (**str == '+') {
    (*str)++;
    opt.width--;
  }
  int res = 0;
  if (**str == '0') {
    (*str)++;
    if (**str == 'x') {
      (*str)++;
      res = parse_hex(opt, str, ap, neg);
    } else {
      res = parse_oct(opt, str, ap, neg);
    }
  } else {
    res = parse_uint(opt, str, ap, neg);
  }
  return res;
}

int parse_ptr(specifier opt, char **str, va_list ap) {
  opt.len = len_l;
  return parse_hex(opt, str, ap, 0);
}

int parse_float(specifier opt, char **str, va_list ap) {
  int res = 0;
  if (opt.width == 0) {
    opt.width = INT_MAX;
  }
  long double res_d = 0;
  res = scan_float(str, opt.width, &res_d);
  res &= !opt.skip;
  if (res) {
    switch (opt.len) {
      case len_none:
        *(va_arg(ap, float *)) = (float)res_d;
        break;
      case len_h:  // это уб
        *(va_arg(ap, float *)) = (float)res_d;
        break;
      case len_l:
        *(va_arg(ap, double *)) = (double)res_d;
        break;
      case len_L:
        *(va_arg(ap, long double *)) = res_d;
        break;
      default:
        break;  // impossible
    }
  }
  return res;
}

int scan_int(char **str, int width, long long *dest) {
  int flag = 0, find = 0, neg = 0;
  if (width == 0) {
    width = INT_MAX;
  }
  long long res = 0;
  if (**str == '-') {
    neg = 1;
    (*str)++;
    width--;
  } else if (**str == '+') {
    (*str)++;
    width--;
  }
  if (is_digit(**str, 10)) {
    find = 1;
  } else if (neg) {
    (*str)--;
  }
  if (find) {
    while (is_digit(**str, 10) && width--) {
      if (res > (LLONG_MAX - (**str - '0')) / 10) {  // overflow
        find = 0;
        flag = 1;
        res = LLONG_MAX;
        if (neg) res = -res - 1;
        while (**str && width--) (*str)++;
        break;
      }
      res = res * 10 + (**str - '0');
      (*str)++;
    }
  }
  if (find && neg) {
    res = -res;
  }
  if (find || flag) {
    *dest = res;
  }
  return find || flag;
}

int scan_based_uint(char **str, int width, unsigned long long *dest, int base,
                    int neg) {
  int find = 0;
  if (width == 0) width = INT_MAX;
  unsigned long long res = 0;
  if (is_digit(**str, base)) {
    find = 1;
  }
  if (find) {
    while (is_digit(**str, base) && width--) {
      if (res > (ULLONG_MAX - to_digit(**str, base)) / base) {
        res = ULLONG_MAX;
        while (**str && width--) (*str)++;
      } else {
        res = res * base + to_digit(**str, base);
        (*str)++;
      }
    }
    if (neg) res = -res;
    *dest = res;
  }
  return find;
}

int scan_float(char **str, int width, long double *dest) {
  int find = 0;
  int neg = 0;
  long double res = 0;
  if (**str == '-') {
    neg = 1;
    (*str)++;
    width--;
  } else if (**str == '+') {
    (*str)++;
    width--;
  }
  if (nan_inf(str, &res)) {
    find = 1;
  } else if (is_digit(**str, 10) || **str == '.') {
    find = 1;
    if (**str == '.') {
      find = 0;
      if (is_digit(*(*str + 1), 10)) {
        find = 1;
      }
    }
    res = custom_atof(str, &width);
    scientific(str, &width, &res);
  } else if (neg) {
    (*str)--;
  }
  if (find) {
    if (neg) res = -res;
    *dest = res;
  }
  return find;
}

int nan_inf(char **str, long double *dest) {
  int res = 0;
  if (strstr_icase(str, "nan")) {
    res = 1;
    *dest = NAN;
  } else if (strstr_icase(str, "inf")) {
    res = 1;
    *dest = INFINITY;
  }
  return res;
}

long double custom_atof(char **str, int *width) {
  long double res = 0;
  while (is_digit(**str, 10) && width) {
    res = res * 10 + (**str - '0');
    (*str)++;
    (*width)--;
  }
  if (**str == '.') {
    (*str)++;
    (*width)--;
    long double frac_coef = 1;
    int frac_width = 0;
    while (is_digit(*(*str + frac_width), 10) && (*width)--) frac_width++;
    while (frac_width--) {
      frac_coef /= 10;
      res += frac_coef * (**str - '0');
      (*str)++;
    }
  }
  return res;
}

int scientific(char **str, int *width, long double *res) {
  long long exp = 0;
  int find = 0;

  if (**str == 'e' || **str == 'E') {
    (*str)++;
    (*width)--;
    find = scan_int(str, *width, &exp);
  }

  *res *= pow(10, exp);
  return find;
}
