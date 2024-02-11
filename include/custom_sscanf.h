#ifndef CUSTOM_SSCANF_H_
#define CUSTOM_SSCANF_H_

#include <math.h>
#include <stdarg.h>

#include "custom_string.h"

#define LLONG_MAX 0x7fffffffffffffff
#define LLONG_MIN (-LLONG_MAX - 1LL)
#define ULLONG_MAX 0xffffffffffffffff
#define INT_MAX 0x7fffffff

typedef enum {
  opt_c,        // 0 Symbol
  opt_d,        // 1 Signed decimal integer
  opt_i,        // 2 Signed integer (can be decimal, octal or
                // hexadecimal)
  opt_e,        // 3 Decimal floating point number or scientific notation
                // (mantissa/exponent)
  opt_E,        // 4 Decimal floating point number or scientific notation
                // (mantissa/exponent)
  opt_f,        // 5 Decimal floating point number or scientific notation
                // (mantissa/exponent)
  opt_g,        // 6 Decimal floating point number or scientific notation
                // (mantissa/exponent)
  opt_G,        // 7 Decimal floating point number or scientific notation
                // (mantissa/exponent)
  opt_o,        // 8 Беззнаковое восьмеричное число
  opt_s,        // 9 Character string
  opt_u,        // 10 Unsigned decimal integer
  opt_x,        // 11 Unsigned hexadecimal integer (any letters)
  opt_X,        // 12 Unsigned hexadecimal integer (any letters)
  opt_p,        // 13 Pointer address
  opt_n,        // 14 Number of characters read before %n appears
  opt_unknown,  // 15 Unknown specifier
} options;

typedef enum lens {
  len_none,  // 0
  len_h,     // 1
  len_l,     // 2
  len_L,     // 3
} lens;

typedef struct {
  options opt;
  int width;
  lens len;
  int skip;
} specifier;

int custom_sscanf(const char *str, const char *format, ...);

specifier scan_specifier(char **format);
int scan_width(char **f_str);

int is_digit(char c, int base);
custom_size_t to_digit(char c, int base);
char chr_lower(char c);
int strstr_icase(char **str, char *pat);

int scan(specifier opt, char **str, va_list ap, int *res, char *start);

int parse_string(specifier opt, char **str, va_list ap);
int parse_int(specifier opt, char **str, va_list ap);
int parse_based_uint(specifier opt, char **str, va_list ap, int base, int neg);
int parse_uint(specifier opt, char **str, va_list ap, int neg);
int parse_hex(specifier opt, char **str, va_list ap, int neg);
int parse_oct(specifier opt, char **str, va_list ap, int neg);
int parse_i_uint(specifier opt, char **str, va_list ap);
int parse_ptr(specifier opt, char **str, va_list ap);
int parse_float(specifier opt, char **str, va_list ap);

int scan_int(char **str, int width, long long *dest);
int scan_based_uint(char **str, int width, unsigned long long *dest, int base,
                    int neg);
int scan_float(char **str, int width, long double *dest);

long double custom_atof(char **str, int *width);
int nan_inf(char **str, long double *dest);
int scientific(char **str, int *width, long double *res);

#endif