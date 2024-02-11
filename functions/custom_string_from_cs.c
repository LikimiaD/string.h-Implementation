#include "../include/custom_string.h"

// WARNING: Dinamic memory allocated!
void *custom_to_lower(const char *str) {
  if (str == NULL_VALUE) {
    return NULL_VALUE;
  }
  custom_size_t length = custom_strlen(str);
  char *buffer = (char *)malloc(length + 1);
  if (buffer == NULL_VALUE) {
    return NULL_VALUE;
  }
  for (custom_size_t count = 0; count < length; count++) {
    if (str[count] >= 'A' && str[count] <= 'Z') {
      buffer[count] = (char)(str[count] + ('a' - 'A'));
    } else {
      buffer[count] = str[count];
    }
  }
  buffer[length] = '\0';
  return (void *)buffer;
}

// WARNING: Dinamic memory allocated!
char *custom_insert(const char *src, const char *str, size_t start_index) {
  if (src == NULL_VALUE || str == NULL_VALUE ||
      start_index > custom_strlen(src)) {
    return NULL_VALUE;
  }
  custom_size_t new_length = custom_strlen(src) + custom_strlen(str);
  char *result = (char *)malloc(new_length + 1);
  if (result == NULL_VALUE) {
    return NULL_VALUE;
  }
  custom_strncpy(result, src, start_index);
  custom_strcpy(result + start_index, str);
  custom_strcpy(result + start_index + custom_strlen(str), src + start_index);
  return result;
}

// WARNING: Dinamic memory allocated!
char *custom_trim(const char *src, const char *trim_chars) {
  if (src == NULL_VALUE || trim_chars == NULL_VALUE) {
    return NULL_VALUE;
  }
  const char *start = src + custom_strspn(src, trim_chars);
  const char *end = src + custom_strlen(src) - 1;
  while (end > start && custom_strchr(trim_chars, *end)) {
    end--;
  }
  custom_size_t length = (end >= start) ? (size_t)(end - start) + 1 : 0;
  char *result = (char *)malloc(length + 1);
  if (result == NULL_VALUE) {
    return NULL_VALUE;
  }
  custom_strncpy(result, start, length);
  result[length] = '\0';
  return result;
}