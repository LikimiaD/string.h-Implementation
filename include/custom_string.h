#ifndef CUSTOM_STRING_H_
#define CUSTOM_STRING_H_

#include <stdio.h>
#include <stdlib.h>

#define custom_size_t unsigned long
#define NULL_VALUE 0

#define integer_max_len 13
#define unsigned_int_max_len 11
#define short_int_max_len 8
#define unsigned_short_int_max_len 6
#define long_int_max_len 22
#define long_long_int_max_len 22
#define unsigned_long_int_max_len 21
#define unsigned_long_long_int_max_len 21

#define unsigned_integer_max_len 12

#define double_max_len 321

custom_size_t custom_strlen(const char *str);
char *custom_strcpy(char *str1, const char *str2);
void *custom_memcpy(void *dest, const void *src, custom_size_t n);
int custom_strncmp(const char *str1, const char *str2, custom_size_t n);
int custom_memcmp(const void *str1, const void *str2, custom_size_t n);
void *custom_memset(void *str, int c, custom_size_t n);
void *custom_memchr(const void *str, int c, custom_size_t n);
char *custom_strchr(const char *str, int symbol);
char *custom_strstr(const char *str1, const char *str2);
char *custom_strtok(char *str, const char *delim);
char *custom_strncat(char *str1, const char *str2, custom_size_t n);
char *custom_strncpy(char *str1, const char *str2, custom_size_t n);
char *custom_strpbrk(const char *str1, const char *str2);
custom_size_t custom_strcspn(const char *str1, const char *str2);
char *custom_strerror(int errnum);
void *custom_to_upper(const char *str);
void *custom_to_lower(const char *str);
char *custom_insert(const char *src, const char *str, size_t start_index);
char *custom_trim(const char *src, const char *trim_chars);
custom_size_t custom_strspn(const char *str1, const char *str2);
int custom_sprintf(char *str, const char *format, ...);

#endif