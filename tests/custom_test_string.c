#include <check.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "../include/custom_string.h"

#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_RESET "\x1b[0m"
#define NAME_TEST(X)                                                         \
  printf("%sTesting func: %s%s%s\n", ANSI_COLOR_YELLOW, ANSI_COLOR_GREEN, X, \
         ANSI_COLOR_RESET);

START_TEST(test_strlen) {
  char expected[7][62] = {
      "",
      "\n",
      "Aboba",
      "School21",
      "string+.h"
      "      C      H  U R KKKK IIII",
      "DudleyparkourKillerDarkBravoStarsAssassinStalkerSniper1998rus"};
  for (int i = 0; i < 5; i++) {
    ck_assert_uint_eq(custom_strlen(expected[i]), strlen(expected[i]));
  }
}
END_TEST

START_TEST(test_strncmp) {
  char expected[7][62] = {
      "",
      "\n",
      "Aboba",
      "School21",
      "string+.h"
      "      C      H  U R KKKK IIII",
      "DudleyparkourKillerDarkBravoStarsAssassinStalkerSniper1998rus"};
  for (int i = 0; i < 7; i++) {
    for (int j = 0; j < 7; j++) {
      ck_assert_int_eq(
          custom_strncmp(expected[i], expected[j], custom_strlen(expected[j])),
          strncmp(expected[i], expected[j], strlen(expected[j])));
    }
  }
}
END_TEST

START_TEST(test_strchr) {
  char expected[5][62] = {
      "", "\n", "Aboba", "Shleba",
      "DudleyparkourKillerDarkBravoStarsAssassinStalkerSniper1998rus"};
  char sym_array[5] = {' ', 'a', 'b', 'l', 'e'};
  char sym = 0;
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      sym = sym_array[j];
      ck_assert_ptr_eq(custom_strchr(expected[i], sym),
                       strchr(expected[i], sym));
    }
  }
}
END_TEST

START_TEST(test_strstr) {
  char expected[5][62] = {
      "", "\n", "Aboba", "Shleba",
      "DudleyparkourKillerDarkBravoStarsAssassinStalkerSniper1998rus"};
  char *patterns[] = {"Abo", "ba", "ley", "Killer"};
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 4; j++) {
      ck_assert_ptr_eq(custom_strstr(expected[i], patterns[j]),
                       strstr(expected[i], patterns[j]));
    }
  }
}
END_TEST

START_TEST(test_strrchr) {
  char expected[5][62] = {
      "", "\n", "Aboba", "Shleba",
      "DudleyparkourKillerDarkBravoStarsAssassinStalkerSniper1998rus"};
  char sym_array[5] = {' ', 'a', 'b', 'l', 'e'};
  char sym = 0;
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      sym = sym_array[j];
      ck_assert_ptr_eq(custom_strchr(expected[i], sym),
                       strchr(expected[i], sym));
    }
  }
}
END_TEST

START_TEST(test_strtok) {
  char test_string[10][100] = {
      "This,is,a,test,string",      "Another:example:with:different:delimiters",
      "One more,test,string",       "No,delimiters,here",
      "Delimiters at the end,",     ",Delimiters at the start",
      "Delimiters,,in,,middle",     "NoDelimitersAtAll",
      "Multiple delimiters, ,here", "Last,test,case"};

  const char *delims[10] = {",", ":", ",", ",", ",", ",", ",", ",", ", ", ","};

  char *custom_token = NULL_VALUE, *token = NULL;
  for (int i = 0; i < 10; i++) {
    custom_token = custom_strtok(test_string[i], delims[i]);
    token = strtok(test_string[i], delims[i]);
    int j = 0;
    while (token != NULL || custom_token != NULL_VALUE) {
      ck_assert_ptr_eq(custom_strtok(test_string[i], delims[i]),
                       strtok(test_string[i], delims[i]));
      custom_token = custom_strtok(NULL_VALUE, delims[i]);
      token = strtok(NULL, delims[i]);
      j++;
    }
  }
}
END_TEST

START_TEST(test_strncat) {
  char str1[50] = "Hello";
  char str2[] = " World!";
  ck_assert_str_eq(custom_strncat(str1, str2, 7), "Hello World!");

  char str3[50] = "123";
  char str4[] = "456789";
  ck_assert_str_eq(custom_strncat(str3, str4, 3), "123456");

  char str5[50] = "";
  char str6[] = "test";
  ck_assert_str_eq(custom_strncat(str5, str6, 4), "test");

  char str7[50] = "abc";
  char str8[] = "";
  ck_assert_str_eq(custom_strncat(str7, str8, 5), "abc");

  char str9[50] = "abc";
  char str10[] = "def";
  ck_assert_str_eq(custom_strncat(str9, str10, 0), "abc");

  char str11[50] = "overflow";
  char str12[] = "test";
  ck_assert_str_eq(
      custom_strncat(str11, str12, 50),
      "overflowtest");  // Проверка на возможный переполнение буфера
}
END_TEST

START_TEST(test_strncpy) {
  char str1[50];
  char str2[] = "Hello, world!";
  char str3[] = "Short";
  char str4[50] = "Initial content";
  char *result;

  result = custom_strncpy(str1, str2, 5);
  ck_assert_ptr_eq(result, str1);

  result = custom_strncpy(str1, str3, 10);
  ck_assert_ptr_eq(result, str1);

  result = custom_strncpy(str4, str3, 10);
  ck_assert_ptr_eq(result, str4);

  result = custom_strncpy(str1, str2, 0);
  ck_assert_ptr_eq(result, str1);

  result = custom_strncpy(str1, "", 5);
  ck_assert_ptr_eq(result, str1);

  // Тестирование передачи NULL в качестве аргументов
  result = custom_strncpy(NULL, str2, 5);
  ck_assert_ptr_eq(result, NULL);

  result = custom_strncpy(str1, NULL, 5);
  ck_assert_ptr_eq(result, NULL);

  result = custom_strncpy(NULL, NULL, 5);
  ck_assert_ptr_eq(result, NULL);
}
END_TEST

START_TEST(test_strerror) {
  ck_assert_str_eq(custom_strerror(1), strerror(1));
  ck_assert_str_eq(custom_strerror(2), strerror(2));
  ck_assert_str_eq(custom_strerror(-5), strerror(-5));
  ck_assert_str_eq(custom_strerror(9999), strerror(9999));
}
END_TEST

START_TEST(test_strpbrk) {
  char str1[] = "Hello, world!";
  char str2[] = "world";
  char str3[] = "";
  char str4[] = "world";
  char str5[] = "Hello, world!";
  char str6[] = "";
  ck_assert_ptr_eq(custom_strpbrk(str1, str2), strpbrk(str1, str2));
  ck_assert_ptr_eq(custom_strpbrk(str3, str4), strpbrk(str3, str4));
  ck_assert_ptr_eq(custom_strpbrk(str5, str6), strpbrk(str5, str6));
  ck_assert_ptr_eq(custom_strpbrk(str3, str5), strpbrk(str3, str5));
}

START_TEST(test_strcspn) {
  char str1[] = "Hello, world!";
  char str2[] = "world";
  char str3[] = "xyz";
  char str5[] = "Hello, world!";
  char str6[] = "";
  ck_assert_uint_eq(custom_strcspn(str1, str2), strcspn(str1, str2));
  ck_assert_uint_eq(custom_strcspn(str1, str3), strcspn(str1, str3));
  ck_assert_uint_eq(custom_strcspn(str6, str5), strcspn(str6, str5));
  ck_assert_uint_eq(custom_strcspn(str1, str6), strcspn(str1, str6));
}

START_TEST(test_memcpy) {
  char str1[50];
  char str2[] = "Hello, world!";
  char str3[] = "Short";
  char str4[50] = "Initial content";
  char *result;

  result = custom_memcpy(str1, str2, 5);
  ck_assert_ptr_eq(result, str1);

  result = custom_memcpy(str1, str3, 10);
  ck_assert_ptr_eq(result, str1);

  result = custom_memcpy(str4, str3, 10);
  ck_assert_ptr_eq(result, str4);

  result = custom_memcpy(str1, str2, 0);
  ck_assert_ptr_eq(result, str1);

  result = custom_memcpy(str1, "", 5);
  ck_assert_ptr_eq(result, str1);

  // Тестирование передачи NULL в качестве аргументов
  result = custom_memcpy(NULL, str2, 5);
  ck_assert_ptr_eq(result, NULL);

  result = custom_memcpy(str1, NULL, 5);
  ck_assert_ptr_eq(result, NULL);

  result = custom_memcpy(NULL, NULL, 5);
  ck_assert_ptr_eq(result, NULL);
}
END_TEST

START_TEST(test_memcmp) {
  char str1[] = "Hello";
  char str2[] = "Hello";
  ck_assert_int_eq(custom_memcmp(str1, str2, 5), memcmp(str1, str2, 5));

  char str3[] = "Hello";
  char str4[] = "World";
  ck_assert_int_eq(custom_memcmp(str3, str4, 5), memcmp(str3, str4, 5));

  char str5[] = "HelloWorld";
  char str6[] = "HelloUniverse";
  ck_assert_int_eq(custom_memcmp(str5, str6, 5), memcmp(str5, str6, 5));
}
END_TEST

START_TEST(test_memset) {
  char str1[10];
  custom_memset(str1, 'a', 9);
  str1[9] = '\0';
  ck_assert_str_eq(str1, "aaaaaaaaa");

  char str2[10] = "abcdefghi";
  custom_memset(str2, 'x', 0);
  ck_assert_str_eq(str2, "abcdefghi");

  char str3[10] = "abcdefghi";
  custom_memset(str3, 'x', 5);
  ck_assert_str_eq(str3, "xxxxxfghi");

  // Test case 4: Using non-printable character
  char str4[5];
  custom_memset(str4, '\0', 5);
  ck_assert_mem_eq(str4, "\0\0\0\0\0", 5);
}
END_TEST

START_TEST(test_memchr) {
  char str1[] = "Hello World";
  ck_assert_ptr_eq(custom_memchr(str1, 'W', 11), &str1[6]);

  ck_assert_ptr_eq(custom_memchr(str1, 'x', 11), NULL);

  ck_assert_ptr_eq(custom_memchr(str1, 'o', 5), &str1[4]);

  ck_assert_ptr_eq(custom_memchr(str1, 'o', 3), NULL);

  char str2[] = "Hello\0World";
  ck_assert_ptr_eq(custom_memchr(str2, '\0', 11), &str2[5]);
}
END_TEST

START_TEST(test_to_lower) {
  char str1[] = "Hello World!";
  char *str_lower = (char *)custom_to_lower(str1);
  ck_assert_str_eq(str_lower, "hello world!");
  free(str_lower);

  char str2[] = "123 ABC xyz!";
  str_lower = (char *)custom_to_lower(str2);
  ck_assert_str_eq(str_lower, "123 abc xyz!");
  free(str_lower);

  char str3[] = "";
  str_lower = (char *)custom_to_lower(str3);
  ck_assert_str_eq(str_lower, "");
  free(str_lower);
}
END_TEST

START_TEST(test_to_upper) {
  char str1[] = "Hello World!";
  char *str_upper = (char *)custom_to_upper(str1);
  ck_assert_str_eq(str_upper, "HELLO WORLD!");
  free(str_upper);

  char str2[] = "123 ABC xyz!";
  str_upper = (char *)custom_to_upper(str2);
  ck_assert_str_eq(str_upper, "123 ABC XYZ!");
  free(str_upper);

  char str3[] = "";
  str_upper = (char *)custom_to_upper(str3);
  ck_assert_str_eq(str_upper, "");
  free(str_upper);
}
END_TEST

START_TEST(test_trim) {
  char src1[] = "  hello  ";
  char trim_chars1[] = " ";
  char *result1 = custom_trim(src1, trim_chars1);
  ck_assert_str_eq(result1, "hello");
  free(result1);

  char src2[] = "!!!hello!!!";
  char trim_chars2[] = "!";
  char *result2 = custom_trim(src2, trim_chars2);
  ck_assert_str_eq(result2, "hello");
  free(result2);

  char src3[] = "hello";
  char trim_chars3[] = "xyz";
  char *result3 = custom_trim(src3, trim_chars3);
  ck_assert_str_eq(result3, "hello");
  free(result3);
}
END_TEST

START_TEST(test_insert) {
  char src1[] = "hello";
  char str1[] = "world";
  size_t index1 = 3;
  char *result1 = custom_insert(src1, str1, index1);
  ck_assert_str_eq(result1, "helworldlo");
  free(result1);

  char src2[] = "hello";
  char str2[] = "world";
  size_t index2 = 0;
  char *result2 = custom_insert(src2, str2, index2);
  ck_assert_str_eq(result2, "worldhello");
  free(result2);

  char src3[] = "hello";
  char str3[] = "world";
  size_t index3 = 5;
  char *result3 = custom_insert(src3, str3, index3);
  ck_assert_str_eq(result3, "helloworld");
  free(result3);

  char src4[] = "hello";
  char str4[] = "world";
  size_t index4 = 10;
  char *result4 = custom_insert(src4, str4, index4);
  ck_assert_ptr_eq(result4, NULL);
}
END_TEST

START_TEST(custom_sprintf_c_test) {
  char result[20];
  char assert[20];
  custom_sprintf(result, "Count: %c", 'a');
  sprintf(assert, "Count: %c", 'a');
  ck_assert_str_eq(result, assert);

  custom_memset(result, '\0', 20);
  custom_memset(assert, '\0', 20);
  char c = 'b';
  custom_sprintf(result, "Count: %c", c);
  sprintf(assert, "Count: %c", c);
  ck_assert_str_eq(result, assert);

  custom_memset(result, '\0', 20);
  custom_memset(assert, '\0', 20);
  c = 'b';
  int a = custom_sprintf(result, "Count: %5c", c);
  int b = sprintf(assert, "Count: %5c", c);
  ck_assert_str_eq(result, assert);
  ck_assert_int_eq(a, b);

  custom_memset(result, '\0', 20);
  custom_memset(assert, '\0', 20);
  c = 'b';
  a = custom_sprintf(result, "Count: %-5c", c);
  b = sprintf(assert, "Count: %-5c", c);
  ck_assert_str_eq(result, assert);
  ck_assert_int_eq(a, b);

  custom_memset(result, '\0', 20);
  custom_memset(assert, '\0', 20);
  c = 'z';
  custom_sprintf(result, "Count: %lc", c);
  sprintf(assert, "Count: %lc", c);
  ck_assert_str_eq(result, assert);
}

START_TEST(custom_sprintf_test) {
  char str[80];
  char str_origin[80];
  const char *format_str1 = "Hello";
  char c = 'X';
  char d = 'Y';
  int result1 = custom_sprintf(str, format_str1, c);
  int result_origin1 = sprintf(str_origin, format_str1, c);
  ck_assert_int_eq(result1, result_origin1);
  ck_assert_str_eq(str, str_origin);

  const char *format_str2 = "Hello, %c %c";
  int result2 = custom_sprintf(str, format_str2, c, d);
  int result_origin2 = sprintf(str_origin, format_str2, c, d);
  ck_assert_int_eq(result2, result_origin2);
  ck_assert_str_eq(str, str_origin);

  char *s1 = "world!";
  char *s2 = "Hello world!";
  const char *format_str3 = "Hello, %10s %10.15s";
  int result3 = custom_sprintf(str, format_str3, s1, s2);
  int result_origin3 = sprintf(str_origin, format_str3, s1, s2);
  ck_assert_int_eq(result3, result_origin3);
  ck_assert_str_eq(str, str_origin);
}
END_TEST

START_TEST(custom_sprintf_f_test) {
  char str[80];
  char str_orig[80];

  double b = 1;  // Yes
  int res_1 = custom_sprintf(str, "%.f", b);
  int res_1_orig = sprintf(str_orig, "%.f", b);

  ck_assert_int_eq(res_1, res_1_orig);
  ck_assert_str_eq(str, str_orig);

  double b_2 = 0.00000002345;  // Yes
  int res_2 = custom_sprintf(str, "%+-10.3f", b_2);
  int res_2_orig = sprintf(str_orig, "%+-10.3f", b_2);

  ck_assert_int_eq(res_2, res_2_orig);
  ck_assert_str_eq(str, str_orig);

  long double b_3 = -23.087654;  // Yes
  int res_3 = custom_sprintf(str, "%20.10Lf", b_3);
  int res_3_orig = sprintf(str_orig, "%20.10Lf", b_3);

  ck_assert_int_eq(res_3, res_3_orig);
  ck_assert_str_eq(str, str_orig);

  double b_4 = 0;  // Yes
  int res_4 = custom_sprintf(str, "%0+.15F", b_4);
  int res_4_orig = sprintf(str_orig, "%0+.15F", b_4);

  ck_assert_int_eq(res_4, res_4_orig);
  ck_assert_str_eq(str, str_orig);

  long double b_5 = 0;  // Yes
  int res_5 = custom_sprintf(str, "%#.0Lf", b_5);
  int res_5_orig = sprintf(str_orig, "%#.0Lf", b_5);

  ck_assert_int_eq(res_5, res_5_orig);
  ck_assert_str_eq(str, str_orig);

  double b_6 = 1.0 / 0.0;  // Yes
  int res_6 = custom_sprintf(str, "%#10.0f", b_6);
  int res_6_orig = sprintf(str_orig, "%#10.0f", b_6);

  ck_assert_int_eq(res_6, res_6_orig);
  ck_assert_str_eq(str, str_orig);

  double b_7 = 1234523459.123456789;  // Yes
  int res_7 = custom_sprintf(str, "%.5f", b_7);
  int res_7_orig = sprintf(str_orig, "%.5f", b_7);

  ck_assert_int_eq(res_7, res_7_orig);
  ck_assert_str_eq(str, str_orig);

  double b_8 = 1;  // Yes
  int res_8 = custom_sprintf(str, "%f", b_8);
  int res_8_orig = sprintf(str_orig, "%f", b_8);

  ck_assert_int_eq(res_8, res_8_orig);
  ck_assert_str_eq(str, str_orig);

  double b_9 = 0.00345;  // Yes
  int res_9 = custom_sprintf(str, "%f", b_9);
  int res_9_orig = sprintf(str_orig, "%f", b_9);

  ck_assert_int_eq(res_9, res_9_orig);
  ck_assert_str_eq(str, str_orig);

  double b_10 = 0.00345;  // Yes
  int res_10 = custom_sprintf(str, "%f", b_10);
  int res_10_orig = sprintf(str_orig, "%f", b_10);

  ck_assert_int_eq(res_10, res_10_orig);
  ck_assert_str_eq(str, str_orig);

  double b_11 = 1234567.003459876;  // Yes
  int res_11 = custom_sprintf(str, "%.7F", b_11);
  int res_11_orig = sprintf(str_orig, "%.7F", b_11);

  ck_assert_int_eq(res_11, res_11_orig);
  ck_assert_str_eq(str, str_orig);
}
END_TEST

START_TEST(custom_sprintf_prc_test) {
  char str[80];
  char str_orig[80];

  int res_1 = custom_sprintf(str, "%%");
  int res_1_orig = sprintf(str_orig, "%%");
  ck_assert_int_eq(res_1, res_1_orig);
  ck_assert_str_eq(str, str_orig);

  int res_2 = custom_sprintf(str, "%10%");

  ck_assert_int_eq(res_2, 10);
  ck_assert_str_eq(str, "         %");

  int a_prc = 14;
  int res_3 = custom_sprintf(str, "hhhh%0*%", a_prc);

  ck_assert_int_eq(res_3, 18);
  ck_assert_str_eq(str, "hhhh0000000000000%");

  int width_prc = 30;
  int res_4 = custom_sprintf(str, "%-*%12345", width_prc);

  ck_assert_int_eq(res_4, 35);
  ck_assert_str_eq(str, "%                             12345");

  int res_5 = custom_sprintf(str, "abc%%defg");
  int res_5_orig = sprintf(str_orig, "abc%%defg");

  ck_assert_int_eq(res_5, res_5_orig);
  ck_assert_str_eq(str, str_orig);

  double b_5 = -0.000000654;
  double b_6 = 320.0;
  int res_6 = custom_sprintf(str, "%+-25g%g", b_5, b_6);
  ck_assert_int_eq(res_6, res_6);
  ck_assert_str_eq(str, str);

  double b_7 = -120.0001;
  int res_7 = custom_sprintf(str, "aaa%# 20.3G bbb %+.5f ccc", b_7, b_7);
  ck_assert_int_eq(res_7, res_7);
  ck_assert_str_eq(str, str);

  double b_10 = 5.0, b_8 = 0.0000000012345, b_9 = 1.0;
  int res_8 = custom_sprintf(str, "%-20G %010.5g %+Fhello", b_8, b_9, b_10);
  ck_assert_int_eq(res_8, res_8);
  ck_assert_str_eq(str, str);

  double b_11 = 0.001;
  int res_11 = custom_sprintf(str, "%0.g", b_11);
  ck_assert_int_eq(res_11, res_11);
  ck_assert_str_eq(str, str);

  double b_12 = 0.00000000001;
  int res_12 = custom_sprintf(str, "%.10g", b_12);
  ck_assert_int_eq(res_12, res_12);
  ck_assert_str_eq(str, str);
}
END_TEST

START_TEST(custom_sprintf_s_test) {
  char str[80];
  char str1[80];
  char *x = "blablabla";
  int res = custom_sprintf(str, "%-11.10s", x);
  int res1 = sprintf(str1, "%-11.10s", x);
  ck_assert_uint_eq((unsigned long)*str, (unsigned long)*str1);
  ck_assert_int_eq(res, res1);

  res = custom_sprintf(str, "%11.8s", x);
  res1 = sprintf(str1, "%11.8s", x);
  ck_assert_uint_eq((unsigned long)*str, (unsigned long)*str1);
  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(custom_sprintf_n_test) {
  char str[80];
  char str_orig[80];

  int c_1, c_1_orig;
  int res_1 = custom_sprintf(str, "%n", &c_1);
  int res_1_orig = sprintf(str_orig, "%n", &c_1_orig);

  ck_assert_int_eq(res_1, res_1_orig);
  ck_assert_int_eq(c_1, c_1_orig);
  ck_assert_str_eq(str, str_orig);

  int c_2, c_2_orig;
  int res_2 = custom_sprintf(str, "12345%n678910", &c_2);
  int res_2_orig = sprintf(str_orig, "12345%n678910", &c_2_orig);

  ck_assert_int_eq(res_2, res_2_orig);
  ck_assert_int_eq(c_2, c_2_orig);
  ck_assert_str_eq(str, str_orig);

  int c_3, c_3_orig;
  int res_3 = custom_sprintf(str, "%nqwerty", &c_3);
  int res_3_orig = sprintf(str_orig, "%nqwerty", &c_3_orig);

  ck_assert_int_eq(res_3, res_3_orig);
  ck_assert_int_eq(c_3, c_3_orig);
  ck_assert_str_eq(str, str_orig);

  int c_4, c_4_orig;
  int res_4 = custom_sprintf(str, "hhhhh%n%%", &c_4);
  int res_4_orig = sprintf(str_orig, "hhhhh%n%%", &c_4_orig);

  ck_assert_int_eq(res_4, res_4_orig);
  ck_assert_int_eq(c_4, c_4_orig);
  ck_assert_str_eq(str, str_orig);
}
END_TEST

START_TEST(custom_sprintf_p_test) {
  char str[80];
  char str_origin[80];
  int a = 10;
  char *format_str1 = "This is the pointer: %p\n";
  int result1 = custom_sprintf(str, format_str1, &a);
  int result_origin1 = sprintf(str_origin, format_str1, &a);

  ck_assert_int_eq(result1, result_origin1);
  ck_assert_str_eq(str, str_origin);

  char *pointer = "Test";
  double double_pointer = 84759375969;

  char *format_str2 = "To the left: %-20p!\nTo the right %20p!";

  int result2 = custom_sprintf(str, format_str2, pointer, &double_pointer);
  int result_origin2 =
      sprintf(str_origin, format_str2, pointer, &double_pointer);
  ck_assert_int_eq(result2, result_origin2);
  ck_assert_str_eq(str, str_origin);
}
END_TEST

START_TEST(custom_sprintf_d_test_1) {
  char str[80];
  char str_orig[80];
  int a = 0;

  int res_1 = custom_sprintf(str, "%+10.5d", a);
  int res_1_orig = sprintf(str_orig, "%+10.5d", a);

  ck_assert_int_eq(res_1, res_1_orig);
  ck_assert_str_eq(str, str_orig);

  int res_3 = custom_sprintf(str, "%+3.5d", a);
  int res_3_orig = sprintf(str_orig, "%+3.5d", a);

  ck_assert_int_eq(res_3, res_3_orig);
  ck_assert_str_eq(str, str_orig);

  int res_4 = custom_sprintf(str, "%+d", a);
  int res_4_orig = sprintf(str_orig, "%+d", a);

  ck_assert_int_eq(res_4, res_4_orig);
  ck_assert_str_eq(str, str_orig);

  int res_5 = custom_sprintf(str, "%05d", a);
  int res_5_orig = sprintf(str_orig, "%05d", a);

  ck_assert_int_eq(res_5, res_5_orig);
  ck_assert_str_eq(str, str_orig);

  int res_7 = custom_sprintf(str, "%+d", a);
  int res_7_orig = sprintf(str_orig, "%+d", a);

  ck_assert_int_eq(res_7, res_7_orig);
  ck_assert_str_eq(str, str_orig);

  int res_9 = custom_sprintf(str, "%+5d", a);
  int res_9_orig = sprintf(str_orig, "%+5d", a);

  ck_assert_int_eq(res_9, res_9_orig);
  ck_assert_str_eq(str, str_orig);

  int res_12 = custom_sprintf(str, "%+5d", a);
  int res_12_orig = sprintf(str_orig, "%+5d", a);

  ck_assert_int_eq(res_12, res_12_orig);
  ck_assert_str_eq(str, str_orig);

  int res_14 = custom_sprintf(str, "%+.5d", a);
  int res_14_orig = sprintf(str_orig, "%+.5d", a);

  ck_assert_int_eq(res_14, res_14_orig);
  ck_assert_str_eq(str, str_orig);

  int res_15 = custom_sprintf(str, "%+.5d", a);
  int res_15_orig = sprintf(str_orig, "%+.5d", a);

  ck_assert_int_eq(res_15, res_15_orig);
  ck_assert_str_eq(str, str_orig);

  int res_20 = custom_sprintf(str, "%+10.5d", a);
  int res_20_orig = sprintf(str_orig, "%+10.5d", a);

  ck_assert_int_eq(res_20, res_20_orig);
  ck_assert_str_eq(str, str_orig);

  int res_22 = custom_sprintf(str, "%+3.5d", a);
  int res_22_orig = sprintf(str_orig, "%+3.5d", a);

  ck_assert_int_eq(res_22, res_22_orig);
  ck_assert_str_eq(str, str_orig);

  int res_26 = custom_sprintf(str, "%+05d", a);
  int res_26_orig = sprintf(str_orig, "%+05d", a);

  ck_assert_int_eq(res_26, res_26_orig);
  ck_assert_str_eq(str, str_orig);
}
END_TEST

START_TEST(custom_sprintf_d_test_2) {
  char str[80];
  char str_orig[80];
  int a = -23454546;

  int res_1 = custom_sprintf(str, "%10.*d", 5, a);
  int res_1_orig = sprintf(str_orig, "%10.*d", 5, a);

  ck_assert_int_eq(res_1, res_1_orig);
  ck_assert_str_eq(str, str_orig);

  int res_2 = custom_sprintf(str, "% 10.5d", a);
  int res_2_orig = sprintf(str_orig, "% 10.5d", a);

  ck_assert_int_eq(res_2, res_2_orig);
  ck_assert_str_eq(str, str_orig);

  int res_3 = custom_sprintf(str, "%3.5d", a);
  int res_3_orig = sprintf(str_orig, "%3.5d", a);

  ck_assert_int_eq(res_3, res_3_orig);
  ck_assert_str_eq(str, str_orig);

  int res_4 = custom_sprintf(str, "%d", a);
  int res_4_orig = sprintf(str_orig, "%d", a);

  ck_assert_int_eq(res_4, res_4_orig);
  ck_assert_str_eq(str, str_orig);

  int res_5 = custom_sprintf(str, "%0d", a);
  int res_5_orig = sprintf(str_orig, "%0d", a);

  ck_assert_int_eq(res_5, res_5_orig);
  ck_assert_str_eq(str, str_orig);

  int res_6 = custom_sprintf(str, "%-d", a);
  int res_6_orig = sprintf(str_orig, "%-d", a);

  ck_assert_int_eq(res_6, res_6_orig);
  ck_assert_str_eq(str, str_orig);

  int res_7 = custom_sprintf(str, "%+d", a);
  int res_7_orig = sprintf(str_orig, "%+d", a);

  ck_assert_int_eq(res_7, res_7_orig);
  ck_assert_str_eq(str, str_orig);

  int res_8 = custom_sprintf(str, "% d", a);
  int res_8_orig = sprintf(str_orig, "% d", a);

  ck_assert_int_eq(res_8, res_8_orig);
  ck_assert_str_eq(str, str_orig);

  int res_9 = custom_sprintf(str, "%5d", a);
  int res_9_orig = sprintf(str_orig, "%5d", a);

  ck_assert_int_eq(res_9, res_9_orig);
  ck_assert_str_eq(str, str_orig);

  int res_10 = custom_sprintf(str, "%0*d", 5, a);
  int res_10_orig = sprintf(str_orig, "%0*d", 5, a);

  ck_assert_int_eq(res_10, res_10_orig);
  ck_assert_str_eq(str, str_orig);

  int res_11 = custom_sprintf(str, "%-5d", a);
  int res_11_orig = sprintf(str_orig, "%-5d", a);

  ck_assert_int_eq(res_11, res_11_orig);
  ck_assert_str_eq(str, str_orig);

  int res_12 = custom_sprintf(str, "%+5d", a);
  int res_12_orig = sprintf(str_orig, "%+5d", a);

  ck_assert_int_eq(res_12, res_12_orig);
  ck_assert_str_eq(str, str_orig);

  int res_13 = custom_sprintf(str, "% 5d", a);
  int res_13_orig = sprintf(str_orig, "% 5d", a);

  ck_assert_int_eq(res_13, res_13_orig);
  ck_assert_str_eq(str, str_orig);

  int res_14 = custom_sprintf(str, "%.5d", a);
  int res_14_orig = sprintf(str_orig, "%.5d", a);

  ck_assert_int_eq(res_14, res_14_orig);
  ck_assert_str_eq(str, str_orig);

  int res_15 = custom_sprintf(str, "%.5d", a);
  int res_15_orig = sprintf(str_orig, "%.5d", a);

  ck_assert_int_eq(res_15, res_15_orig);
  ck_assert_str_eq(str, str_orig);

  int res_16 = custom_sprintf(str, "% .5d", a);
  int res_16_orig = sprintf(str_orig, "% .5d", a);

  ck_assert_int_eq(res_16, res_16_orig);
  ck_assert_str_eq(str, str_orig);

  int res_17 = custom_sprintf(str, "%+.5d", a);
  int res_17_orig = sprintf(str_orig, "%+.5d", a);

  ck_assert_int_eq(res_17, res_17_orig);
  ck_assert_str_eq(str, str_orig);

  int res_18 = custom_sprintf(str, "%-.5d", a);
  int res_18_orig = sprintf(str_orig, "%-.5d", a);

  ck_assert_int_eq(res_18, res_18_orig);
  ck_assert_str_eq(str, str_orig);

  int res_19 = custom_sprintf(str, "%10.5d", a);
  int res_19_orig = sprintf(str_orig, "%10.5d", a);

  ck_assert_int_eq(res_19, res_19_orig);
  ck_assert_str_eq(str, str_orig);

  int res_20 = custom_sprintf(str, "%+10.5d", a);
  int res_20_orig = sprintf(str_orig, "%+10.5d", a);

  ck_assert_int_eq(res_20, res_20_orig);
  ck_assert_str_eq(str, str_orig);

  int res_21 = custom_sprintf(str, "%-10.5d", a);
  int res_21_orig = sprintf(str_orig, "%-10.5d", a);

  ck_assert_int_eq(res_21, res_21_orig);
  ck_assert_str_eq(str, str_orig);

  int res_22 = custom_sprintf(str, "%3.5d", a);
  int res_22_orig = sprintf(str_orig, "%3.5d", a);

  ck_assert_int_eq(res_22, res_22_orig);
  ck_assert_str_eq(str, str_orig);

  int res_23 = custom_sprintf(str, "% 3.5d", a);
  int res_23_orig = sprintf(str_orig, "% 3.5d", a);

  ck_assert_int_eq(res_23, res_23_orig);
  ck_assert_str_eq(str, str_orig);

  int res_24 = custom_sprintf(str, "%+3.5d", a);
  int res_24_orig = sprintf(str_orig, "%+3.5d", a);

  ck_assert_int_eq(res_24, res_24_orig);
  ck_assert_str_eq(str, str_orig);

  int res_25 = custom_sprintf(str, "%-3.5d", a);
  int res_25_orig = sprintf(str_orig, "%-3.5d", a);

  ck_assert_int_eq(res_25, res_25_orig);
  ck_assert_str_eq(str, str_orig);
}
END_TEST

START_TEST(custom_sprintf_d_test_3) {
  char str[80];
  char str_orig[80];
  int a = 234;

  int res_1 = custom_sprintf(str, "%10.5d", a);
  int res_1_orig = sprintf(str_orig, "%10.5d", a);

  ck_assert_int_eq(res_1, res_1_orig);
  ck_assert_str_eq(str, str_orig);

  int res_2 = custom_sprintf(str, "% 10.5d", a);
  int res_2_orig = sprintf(str_orig, "% 10.5d", a);

  ck_assert_int_eq(res_2, res_2_orig);
  ck_assert_str_eq(str, str_orig);

  int res_3 = custom_sprintf(str, "%3.5d", a);
  int res_3_orig = sprintf(str_orig, "%3.5d", a);

  ck_assert_int_eq(res_3, res_3_orig);
  ck_assert_str_eq(str, str_orig);

  int res_4 = custom_sprintf(str, "%d", a);
  int res_4_orig = sprintf(str_orig, "%d", a);

  ck_assert_int_eq(res_4, res_4_orig);
  ck_assert_str_eq(str, str_orig);

  int res_5 = custom_sprintf(str, "%0d", a);
  int res_5_orig = sprintf(str_orig, "%0d", a);

  ck_assert_int_eq(res_5, res_5_orig);
  ck_assert_str_eq(str, str_orig);

  int res_6 = custom_sprintf(str, "%-d", a);
  int res_6_orig = sprintf(str_orig, "%-d", a);

  ck_assert_int_eq(res_6, res_6_orig);
  ck_assert_str_eq(str, str_orig);

  int res_7 = custom_sprintf(str, "%+d", a);
  int res_7_orig = sprintf(str_orig, "%+d", a);

  ck_assert_int_eq(res_7, res_7_orig);
  ck_assert_str_eq(str, str_orig);

  int res_8 = custom_sprintf(str, "% d", a);
  int res_8_orig = sprintf(str_orig, "% d", a);

  ck_assert_int_eq(res_8, res_8_orig);
  ck_assert_str_eq(str, str_orig);

  int res_9 = custom_sprintf(str, "%5d", a);
  int res_9_orig = sprintf(str_orig, "%5d", a);

  ck_assert_int_eq(res_9, res_9_orig);
  ck_assert_str_eq(str, str_orig);

  int res_10 = custom_sprintf(str, "%05d", a);
  int res_10_orig = sprintf(str_orig, "%05d", a);

  ck_assert_int_eq(res_10, res_10_orig);
  ck_assert_str_eq(str, str_orig);

  int res_11 = custom_sprintf(str, "%-5d", a);
  int res_11_orig = sprintf(str_orig, "%-5d", a);

  ck_assert_int_eq(res_11, res_11_orig);
  ck_assert_str_eq(str, str_orig);

  int res_12 = custom_sprintf(str, "%+5d", a);
  int res_12_orig = sprintf(str_orig, "%+5d", a);

  ck_assert_int_eq(res_12, res_12_orig);
  ck_assert_str_eq(str, str_orig);

  int res_13 = custom_sprintf(str, "% 5d", a);
  int res_13_orig = sprintf(str_orig, "% 5d", a);

  ck_assert_int_eq(res_13, res_13_orig);
  ck_assert_str_eq(str, str_orig);

  int res_14 = custom_sprintf(str, "%.5d", a);
  int res_14_orig = sprintf(str_orig, "%.5d", a);

  ck_assert_int_eq(res_14, res_14_orig);
  ck_assert_str_eq(str, str_orig);

  int res_15 = custom_sprintf(str, "%.5d", a);
  int res_15_orig = sprintf(str_orig, "%.5d", a);

  ck_assert_int_eq(res_15, res_15_orig);
  ck_assert_str_eq(str, str_orig);

  int res_16 = custom_sprintf(str, "% .5d", a);
  int res_16_orig = sprintf(str_orig, "% .5d", a);

  ck_assert_int_eq(res_16, res_16_orig);
  ck_assert_str_eq(str, str_orig);

  int res_17 = custom_sprintf(str, "%+.5d", a);
  int res_17_orig = sprintf(str_orig, "%+.5d", a);

  ck_assert_int_eq(res_17, res_17_orig);
  ck_assert_str_eq(str, str_orig);

  int res_18 = custom_sprintf(str, "%-.5d", a);
  int res_18_orig = sprintf(str_orig, "%-.5d", a);

  ck_assert_int_eq(res_18, res_18_orig);
  ck_assert_str_eq(str, str_orig);

  int res_19 = custom_sprintf(str, "%10.5d", a);
  int res_19_orig = sprintf(str_orig, "%10.5d", a);

  ck_assert_int_eq(res_19, res_19_orig);
  ck_assert_str_eq(str, str_orig);

  int res_20 = custom_sprintf(str, "%+10.5d", a);
  int res_20_orig = sprintf(str_orig, "%+10.5d", a);

  ck_assert_int_eq(res_20, res_20_orig);
  ck_assert_str_eq(str, str_orig);

  int res_21 = custom_sprintf(str, "%-10.5d", a);
  int res_21_orig = sprintf(str_orig, "%-10.5d", a);

  ck_assert_int_eq(res_21, res_21_orig);
  ck_assert_str_eq(str, str_orig);

  int res_22 = custom_sprintf(str, "%3.5d", a);
  int res_22_orig = sprintf(str_orig, "%3.5d", a);

  ck_assert_int_eq(res_22, res_22_orig);
  ck_assert_str_eq(str, str_orig);

  int res_23 = custom_sprintf(str, "% 3.5d", a);
  int res_23_orig = sprintf(str_orig, "% 3.5d", a);

  ck_assert_int_eq(res_23, res_23_orig);
  ck_assert_str_eq(str, str_orig);

  int res_24 = custom_sprintf(str, "%+3.5d", a);
  int res_24_orig = sprintf(str_orig, "%+3.5d", a);

  ck_assert_int_eq(res_24, res_24_orig);
  ck_assert_str_eq(str, str_orig);

  int res_25 = custom_sprintf(str, "%-3.5d", a);
  int res_25_orig = sprintf(str_orig, "%-3.5d", a);

  ck_assert_int_eq(res_25, res_25_orig);
  ck_assert_str_eq(str, str_orig);

  int res_26 = custom_sprintf(str, "%+6.2d", a);
  int res_26_orig = sprintf(str_orig, "%+6.2d", a);

  ck_assert_int_eq(res_26, res_26_orig);
  ck_assert_str_eq(str, str_orig);

  int res_27 = custom_sprintf(str, "%+6.3d", a);
  int res_27_orig = sprintf(str_orig, "%+6.3d", a);

  ck_assert_int_eq(res_27, res_27_orig);
  ck_assert_str_eq(str, str_orig);

  int res_28 = custom_sprintf(str, "%+6.4d", a);
  int res_28_orig = sprintf(str_orig, "%+6.4d", a);

  ck_assert_int_eq(res_28, res_28_orig);
  ck_assert_str_eq(str, str_orig);

  int res_29 = custom_sprintf(str, "%-6.2d", -a);
  int res_29_orig = sprintf(str_orig, "%-6.2d", -a);

  ck_assert_int_eq(res_29, res_29_orig);
  ck_assert_str_eq(str, str_orig);

  int res_30 = custom_sprintf(str, "%+05d", a);
  int res_30_orig = sprintf(str_orig, "%+05d", a);

  ck_assert_int_eq(res_30, res_30_orig);
  ck_assert_str_eq(str, str_orig);
}
END_TEST

START_TEST(custom_sprintf_d_test_4) {
  char str[80];
  char str_orig[80];
  int a = -23;

  int res_1 = custom_sprintf(str, "%10.5d", a);
  int res_1_orig = sprintf(str_orig, "%10.5d", a);

  ck_assert_int_eq(res_1, res_1_orig);
  ck_assert_str_eq(str, str_orig);

  int res_2 = custom_sprintf(str, "% 10.5d", a);
  int res_2_orig = sprintf(str_orig, "% 10.5d", a);

  ck_assert_int_eq(res_2, res_2_orig);
  ck_assert_str_eq(str, str_orig);

  int res_3 = custom_sprintf(str, "%3.5d", a);
  int res_3_orig = sprintf(str_orig, "%3.5d", a);

  ck_assert_int_eq(res_3, res_3_orig);
  ck_assert_str_eq(str, str_orig);

  int res_4 = custom_sprintf(str, "%d", a);
  int res_4_orig = sprintf(str_orig, "%d", a);

  ck_assert_int_eq(res_4, res_4_orig);
  ck_assert_str_eq(str, str_orig);

  int res_5 = custom_sprintf(str, "%0d", a);
  int res_5_orig = sprintf(str_orig, "%0d", a);

  ck_assert_int_eq(res_5, res_5_orig);
  ck_assert_str_eq(str, str_orig);

  int res_6 = custom_sprintf(str, "%-d", a);
  int res_6_orig = sprintf(str_orig, "%-d", a);

  ck_assert_int_eq(res_6, res_6_orig);
  ck_assert_str_eq(str, str_orig);

  int res_7 = custom_sprintf(str, "%+d", a);
  int res_7_orig = sprintf(str_orig, "%+d", a);

  ck_assert_int_eq(res_7, res_7_orig);
  ck_assert_str_eq(str, str_orig);

  int res_8 = custom_sprintf(str, "% d", a);
  int res_8_orig = sprintf(str_orig, "% d", a);

  ck_assert_int_eq(res_8, res_8_orig);
  ck_assert_str_eq(str, str_orig);

  int res_9 = custom_sprintf(str, "%5d", a);
  int res_9_orig = sprintf(str_orig, "%5d", a);

  ck_assert_int_eq(res_9, res_9_orig);
  ck_assert_str_eq(str, str_orig);

  int res_10 = custom_sprintf(str, "%05d", a);
  int res_10_orig = sprintf(str_orig, "%05d", a);

  ck_assert_int_eq(res_10, res_10_orig);
  ck_assert_str_eq(str, str_orig);

  int res_11 = custom_sprintf(str, "%-5d", a);
  int res_11_orig = sprintf(str_orig, "%-5d", a);

  ck_assert_int_eq(res_11, res_11_orig);
  ck_assert_str_eq(str, str_orig);

  int res_12 = custom_sprintf(str, "%+5d", a);
  int res_12_orig = sprintf(str_orig, "%+5d", a);

  ck_assert_int_eq(res_12, res_12_orig);
  ck_assert_str_eq(str, str_orig);

  int res_13 = custom_sprintf(str, "% 5d", a);
  int res_13_orig = sprintf(str_orig, "% 5d", a);

  ck_assert_int_eq(res_13, res_13_orig);
  ck_assert_str_eq(str, str_orig);

  int res_14 = custom_sprintf(str, "%.5d", a);
  int res_14_orig = sprintf(str_orig, "%.5d", a);

  ck_assert_int_eq(res_14, res_14_orig);
  ck_assert_str_eq(str, str_orig);

  int res_15 = custom_sprintf(str, "%.5d", a);
  int res_15_orig = sprintf(str_orig, "%.5d", a);

  ck_assert_int_eq(res_15, res_15_orig);
  ck_assert_str_eq(str, str_orig);

  int res_16 = custom_sprintf(str, "% .5d", a);
  int res_16_orig = sprintf(str_orig, "% .5d", a);

  ck_assert_int_eq(res_16, res_16_orig);
  ck_assert_str_eq(str, str_orig);

  int res_17 = custom_sprintf(str, "%+.5d", a);
  int res_17_orig = sprintf(str_orig, "%+.5d", a);

  ck_assert_int_eq(res_17, res_17_orig);
  ck_assert_str_eq(str, str_orig);

  int res_18 = custom_sprintf(str, "%-.5d", a);
  int res_18_orig = sprintf(str_orig, "%-.5d", a);

  ck_assert_int_eq(res_18, res_18_orig);
  ck_assert_str_eq(str, str_orig);

  int res_19 = custom_sprintf(str, "%10.5d", a);
  int res_19_orig = sprintf(str_orig, "%10.5d", a);

  ck_assert_int_eq(res_19, res_19_orig);
  ck_assert_str_eq(str, str_orig);

  int res_20 = custom_sprintf(str, "%+10.5d", a);
  int res_20_orig = sprintf(str_orig, "%+10.5d", a);

  ck_assert_int_eq(res_20, res_20_orig);
  ck_assert_str_eq(str, str_orig);

  int res_21 = custom_sprintf(str, "%-10.5d", a);
  int res_21_orig = sprintf(str_orig, "%-10.5d", a);

  ck_assert_int_eq(res_21, res_21_orig);
  ck_assert_str_eq(str, str_orig);

  int res_22 = custom_sprintf(str, "%3.5d", a);
  int res_22_orig = sprintf(str_orig, "%3.5d", a);

  ck_assert_int_eq(res_22, res_22_orig);
  ck_assert_str_eq(str, str_orig);

  int res_23 = custom_sprintf(str, "% 3.5d", a);
  int res_23_orig = sprintf(str_orig, "% 3.5d", a);

  ck_assert_int_eq(res_23, res_23_orig);
  ck_assert_str_eq(str, str_orig);

  int res_24 = custom_sprintf(str, "%+3.5d", a);
  int res_24_orig = sprintf(str_orig, "%+3.5d", a);

  ck_assert_int_eq(res_24, res_24_orig);
  ck_assert_str_eq(str, str_orig);

  int res_25 = custom_sprintf(str, "%-3.5d", a);
  int res_25_orig = sprintf(str_orig, "%-3.5d", a);

  ck_assert_int_eq(res_25, res_25_orig);
  ck_assert_str_eq(str, str_orig);

  int res_26 = custom_sprintf(str, "%+05d", a);
  int res_26_orig = sprintf(str_orig, "%+05d", a);

  ck_assert_int_eq(res_26, res_26_orig);
  ck_assert_str_eq(str, str_orig);
}
END_TEST

START_TEST(custom_sprintf_d_test_5) {
  char str[80];
  char str_orig[80];
  int a = -2344;

  int res_2 = custom_sprintf(str, "% 10.5d", a);
  int res_2_orig = sprintf(str_orig, "% 10.5d", a);

  ck_assert_int_eq(res_2, res_2_orig);
  ck_assert_str_eq(str, str_orig);

  int res_3 = custom_sprintf(str, "%3.5d", a);
  int res_3_orig = sprintf(str_orig, "%3.5d", a);

  ck_assert_int_eq(res_3, res_3_orig);
  ck_assert_str_eq(str, str_orig);

  int res_4 = custom_sprintf(str, "%d", a);
  int res_4_orig = sprintf(str_orig, "%d", a);

  ck_assert_int_eq(res_4, res_4_orig);
  ck_assert_str_eq(str, str_orig);

  int res_5 = custom_sprintf(str, "%0d", a);
  int res_5_orig = sprintf(str_orig, "%0d", a);

  ck_assert_int_eq(res_5, res_5_orig);
  ck_assert_str_eq(str, str_orig);

  int res_6 = custom_sprintf(str, "%-d", a);
  int res_6_orig = sprintf(str_orig, "%-d", a);

  ck_assert_int_eq(res_6, res_6_orig);
  ck_assert_str_eq(str, str_orig);

  int res_7 = custom_sprintf(str, "%+d", a);
  int res_7_orig = sprintf(str_orig, "%+d", a);

  ck_assert_int_eq(res_7, res_7_orig);
  ck_assert_str_eq(str, str_orig);

  int res_8 = custom_sprintf(str, "% d", a);
  int res_8_orig = sprintf(str_orig, "% d", a);

  ck_assert_int_eq(res_8, res_8_orig);
  ck_assert_str_eq(str, str_orig);

  int res_9 = custom_sprintf(str, "%5d", a);
  int res_9_orig = sprintf(str_orig, "%5d", a);

  ck_assert_int_eq(res_9, res_9_orig);
  ck_assert_str_eq(str, str_orig);

  int res_10 = custom_sprintf(str, "%05d", a);
  int res_10_orig = sprintf(str_orig, "%05d", a);

  ck_assert_int_eq(res_10, res_10_orig);
  ck_assert_str_eq(str, str_orig);

  int res_11 = custom_sprintf(str, "%-5d", a);
  int res_11_orig = sprintf(str_orig, "%-5d", a);

  ck_assert_int_eq(res_11, res_11_orig);
  ck_assert_str_eq(str, str_orig);

  int res_12 = custom_sprintf(str, "%+5d", a);
  int res_12_orig = sprintf(str_orig, "%+5d", a);

  ck_assert_int_eq(res_12, res_12_orig);
  ck_assert_str_eq(str, str_orig);

  int res_13 = custom_sprintf(str, "% 5d", a);
  int res_13_orig = sprintf(str_orig, "% 5d", a);

  ck_assert_int_eq(res_13, res_13_orig);
  ck_assert_str_eq(str, str_orig);

  int res_14 = custom_sprintf(str, "%.5d", a);
  int res_14_orig = sprintf(str_orig, "%.5d", a);

  ck_assert_int_eq(res_14, res_14_orig);
  ck_assert_str_eq(str, str_orig);

  int res_15 = custom_sprintf(str, "%.5d", a);
  int res_15_orig = sprintf(str_orig, "%.5d", a);

  ck_assert_int_eq(res_15, res_15_orig);
  ck_assert_str_eq(str, str_orig);

  int res_16 = custom_sprintf(str, "% .5d", a);
  int res_16_orig = sprintf(str_orig, "% .5d", a);

  ck_assert_int_eq(res_16, res_16_orig);
  ck_assert_str_eq(str, str_orig);

  int res_17 = custom_sprintf(str, "%+.5d", a);
  int res_17_orig = sprintf(str_orig, "%+.5d", a);

  ck_assert_int_eq(res_17, res_17_orig);
  ck_assert_str_eq(str, str_orig);

  int res_18 = custom_sprintf(str, "%-.5d", a);
  int res_18_orig = sprintf(str_orig, "%-.5d", a);

  ck_assert_int_eq(res_18, res_18_orig);
  ck_assert_str_eq(str, str_orig);

  int res_19 = custom_sprintf(str, "%10.5d", a);
  int res_19_orig = sprintf(str_orig, "%10.5d", a);

  ck_assert_int_eq(res_19, res_19_orig);
  ck_assert_str_eq(str, str_orig);

  int res_20 = custom_sprintf(str, "%+10.5d", a);
  int res_20_orig = sprintf(str_orig, "%+10.5d", a);

  ck_assert_int_eq(res_20, res_20_orig);
  ck_assert_str_eq(str, str_orig);

  int res_21 = custom_sprintf(str, "%-10.5d", a);
  int res_21_orig = sprintf(str_orig, "%-10.5d", a);

  ck_assert_int_eq(res_21, res_21_orig);
  ck_assert_str_eq(str, str_orig);

  int res_22 = custom_sprintf(str, "%3.5d", a);
  int res_22_orig = sprintf(str_orig, "%3.5d", a);

  ck_assert_int_eq(res_22, res_22_orig);
  ck_assert_str_eq(str, str_orig);

  int res_23 = custom_sprintf(str, "% 3.5d", a);
  int res_23_orig = sprintf(str_orig, "% 3.5d", a);

  ck_assert_int_eq(res_23, res_23_orig);
  ck_assert_str_eq(str, str_orig);

  int res_24 = custom_sprintf(str, "%+3.5d", a);
  int res_24_orig = sprintf(str_orig, "%+3.5d", a);

  ck_assert_int_eq(res_24, res_24_orig);
  ck_assert_str_eq(str, str_orig);

  int res_25 = custom_sprintf(str, "%-3.5d", a);
  int res_25_orig = sprintf(str_orig, "%-3.5d", a);

  ck_assert_int_eq(res_25, res_25_orig);
  ck_assert_str_eq(str, str_orig);

  int res_26 = custom_sprintf(str, "%+05d", a);
  int res_26_orig = sprintf(str_orig, "%+05d", a);

  ck_assert_int_eq(res_26, res_26_orig);
  ck_assert_str_eq(str, str_orig);
}
END_TEST

START_TEST(custom_sprintf_d_test_6) {
  char str[80];
  char str_orig[80];
  int a = 23;

  int res_1 = custom_sprintf(str, "%+10.5d", a);
  int res_1_orig = sprintf(str_orig, "%+10.5d", a);

  ck_assert_int_eq(res_1, res_1_orig);
  ck_assert_str_eq(str, str_orig);

  int res_3 = custom_sprintf(str, "%+3.5d", a);
  int res_3_orig = sprintf(str_orig, "%+3.5d", a);

  ck_assert_int_eq(res_3, res_3_orig);
  ck_assert_str_eq(str, str_orig);

  int res_4 = custom_sprintf(str, "%+d", a);
  int res_4_orig = sprintf(str_orig, "%+d", a);

  ck_assert_int_eq(res_4, res_4_orig);
  ck_assert_str_eq(str, str_orig);

  int res_5 = custom_sprintf(str, "%+0d", a);
  int res_5_orig = sprintf(str_orig, "%+0d", a);

  ck_assert_int_eq(res_5, res_5_orig);
  ck_assert_str_eq(str, str_orig);

  int res_6 = custom_sprintf(str, "%-+d", a);
  int res_6_orig = sprintf(str_orig, "%-+d", a);

  ck_assert_int_eq(res_6, res_6_orig);
  ck_assert_str_eq(str, str_orig);

  int res_7 = custom_sprintf(str, "%+d", a);
  int res_7_orig = sprintf(str_orig, "%+d", a);

  ck_assert_int_eq(res_7, res_7_orig);
  ck_assert_str_eq(str, str_orig);

  int res_9 = custom_sprintf(str, "%+5d", a);
  int res_9_orig = sprintf(str_orig, "%+5d", a);

  ck_assert_int_eq(res_9, res_9_orig);
  ck_assert_str_eq(str, str_orig);

  int res_11 = custom_sprintf(str, "%-+5d", a);
  int res_11_orig = sprintf(str_orig, "%-+5d", a);

  ck_assert_int_eq(res_11, res_11_orig);
  ck_assert_str_eq(str, str_orig);

  int res_12 = custom_sprintf(str, "%+5d", a);
  int res_12_orig = sprintf(str_orig, "%+5d", a);

  ck_assert_int_eq(res_12, res_12_orig);
  ck_assert_str_eq(str, str_orig);

  int res_14 = custom_sprintf(str, "%+.5d", a);
  int res_14_orig = sprintf(str_orig, "%+.5d", a);

  ck_assert_int_eq(res_14, res_14_orig);
  ck_assert_str_eq(str, str_orig);

  int res_15 = custom_sprintf(str, "%+.5d", a);
  int res_15_orig = sprintf(str_orig, "%+.5d", a);

  ck_assert_int_eq(res_15, res_15_orig);
  ck_assert_str_eq(str, str_orig);

  int res_16 = custom_sprintf(str, "% .5d", a);
  int res_16_orig = sprintf(str_orig, "% .5d", a);

  ck_assert_int_eq(res_16, res_16_orig);
  ck_assert_str_eq(str, str_orig);

  int res_18 = custom_sprintf(str, "%-+.5d", a);
  int res_18_orig = sprintf(str_orig, "%-+.5d", a);

  ck_assert_int_eq(res_18, res_18_orig);
  ck_assert_str_eq(str, str_orig);

  int res_20 = custom_sprintf(str, "%+10.5d", a);
  int res_20_orig = sprintf(str_orig, "%+10.5d", a);

  ck_assert_int_eq(res_20, res_20_orig);
  ck_assert_str_eq(str, str_orig);

  int res_21 = custom_sprintf(str, "%-+10.5d", a);
  int res_21_orig = sprintf(str_orig, "%-+10.5d", a);

  ck_assert_int_eq(res_21, res_21_orig);
  ck_assert_str_eq(str, str_orig);

  int res_22 = custom_sprintf(str, "%+3.5d", a);
  int res_22_orig = sprintf(str_orig, "%+3.5d", a);

  ck_assert_int_eq(res_22, res_22_orig);
  ck_assert_str_eq(str, str_orig);

  int res_23 = custom_sprintf(str, "% 3.5d", a);
  int res_23_orig = sprintf(str_orig, "% 3.5d", a);

  ck_assert_int_eq(res_23, res_23_orig);
  ck_assert_str_eq(str, str_orig);

  int res_25 = custom_sprintf(str, "%-+3.5d", a);
  int res_25_orig = sprintf(str_orig, "%-+3.5d", a);

  ck_assert_int_eq(res_25, res_25_orig);
  ck_assert_str_eq(str, str_orig);

  int res_26 = custom_sprintf(str, "%+05d", a);
  int res_26_orig = sprintf(str_orig, "%+05d", a);

  ck_assert_int_eq(res_26, res_26_orig);
  ck_assert_str_eq(str, str_orig);
}
END_TEST

START_TEST(custom_sprintf_d_test_7) {
  char str[80];
  char str_orig[80];
  int a = 0;

  int res_1 = custom_sprintf(str, "%+10.5d", a);
  int res_1_orig = sprintf(str_orig, "%+10.5d", a);

  ck_assert_int_eq(res_1, res_1_orig);
  ck_assert_str_eq(str, str_orig);

  int res_3 = custom_sprintf(str, "%+3.5d", a);
  int res_3_orig = sprintf(str_orig, "%+3.5d", a);

  ck_assert_int_eq(res_3, res_3_orig);
  ck_assert_str_eq(str, str_orig);

  int res_4 = custom_sprintf(str, "%+d", a);
  int res_4_orig = sprintf(str_orig, "%+d", a);

  ck_assert_int_eq(res_4, res_4_orig);
  ck_assert_str_eq(str, str_orig);

  int res_5 = custom_sprintf(str, "%05d", a);
  int res_5_orig = sprintf(str_orig, "%05d", a);

  ck_assert_int_eq(res_5, res_5_orig);
  ck_assert_str_eq(str, str_orig);

  int res_7 = custom_sprintf(str, "%+d", a);
  int res_7_orig = sprintf(str_orig, "%+d", a);

  ck_assert_int_eq(res_7, res_7_orig);
  ck_assert_str_eq(str, str_orig);

  int res_9 = custom_sprintf(str, "%+5d", a);
  int res_9_orig = sprintf(str_orig, "%+5d", a);

  ck_assert_int_eq(res_9, res_9_orig);
  ck_assert_str_eq(str, str_orig);

  int res_12 = custom_sprintf(str, "%+5d", a);
  int res_12_orig = sprintf(str_orig, "%+5d", a);

  ck_assert_int_eq(res_12, res_12_orig);
  ck_assert_str_eq(str, str_orig);

  int res_14 = custom_sprintf(str, "%+.5d", a);
  int res_14_orig = sprintf(str_orig, "%+.5d", a);

  ck_assert_int_eq(res_14, res_14_orig);
  ck_assert_str_eq(str, str_orig);

  int res_15 = custom_sprintf(str, "%+.5d", a);
  int res_15_orig = sprintf(str_orig, "%+.5d", a);

  ck_assert_int_eq(res_15, res_15_orig);
  ck_assert_str_eq(str, str_orig);

  int res_20 = custom_sprintf(str, "%+10.5d", a);
  int res_20_orig = sprintf(str_orig, "%+10.5d", a);

  ck_assert_int_eq(res_20, res_20_orig);
  ck_assert_str_eq(str, str_orig);

  int res_22 = custom_sprintf(str, "%+3.5d", a);
  int res_22_orig = sprintf(str_orig, "%+3.5d", a);

  ck_assert_int_eq(res_22, res_22_orig);
  ck_assert_str_eq(str, str_orig);

  int res_26 = custom_sprintf(str, "%+05d", a);
  int res_26_orig = sprintf(str_orig, "%+05d", a);

  ck_assert_int_eq(res_26, res_26_orig);
  ck_assert_str_eq(str, str_orig);
}
END_TEST

START_TEST(custom_sprintf_u_test) {
  char str[80];
  char str_orig[80];
  unsigned int a = 2345;

  int res_1 = custom_sprintf(str, "%10.5u", a);
  int res_1_orig = sprintf(str_orig, "%10.5u", a);

  ck_assert_int_eq(res_1, res_1_orig);
  ck_assert_str_eq(str, str_orig);

  int res_2 = custom_sprintf(str, "%10.5u", a);
  int res_2_orig = sprintf(str_orig, "%10.5u", a);

  ck_assert_int_eq(res_2, res_2_orig);
  ck_assert_str_eq(str, str_orig);

  int res_3 = custom_sprintf(str, "%3.5u", a);
  int res_3_orig = sprintf(str_orig, "%3.5u", a);

  ck_assert_int_eq(res_3, res_3_orig);
  ck_assert_str_eq(str, str_orig);

  int res_4 = custom_sprintf(str, "%0u", a);
  int res_4_orig = sprintf(str_orig, "%0u", a);

  ck_assert_int_eq(res_4, res_4_orig);
  ck_assert_str_eq(str, str_orig);

  int res_5 = custom_sprintf(str, "%-u", a);
  int res_5_orig = sprintf(str_orig, "%-u", a);

  ck_assert_int_eq(res_5, res_5_orig);
  ck_assert_str_eq(str, str_orig);

  int res_6 = custom_sprintf(str, "%u", a);
  int res_6_orig = sprintf(str_orig, "%u", a);

  ck_assert_int_eq(res_6, res_6_orig);
  ck_assert_str_eq(str, str_orig);

  int res_7 = custom_sprintf(str, "%5u", a);
  int res_7_orig = sprintf(str_orig, "%5u", a);

  ck_assert_int_eq(res_7, res_7_orig);
  ck_assert_str_eq(str, str_orig);

  int res_8 = custom_sprintf(str, "%05u", a);
  int res_8_orig = sprintf(str_orig, "%05u", a);

  ck_assert_int_eq(res_8, res_8_orig);
  ck_assert_str_eq(str, str_orig);

  int res_9 = custom_sprintf(str, "%-5u", a);
  int res_9_orig = sprintf(str_orig, "%-5u", a);

  ck_assert_int_eq(res_9, res_9_orig);
  ck_assert_str_eq(str, str_orig);

  int res_10 = custom_sprintf(str, "%.5u", a);
  int res_10_orig = sprintf(str_orig, "%.5u", a);

  ck_assert_int_eq(res_10, res_10_orig);
  ck_assert_str_eq(str, str_orig);

  int res_11 = custom_sprintf(str, "%.5u", a);
  int res_11_orig = sprintf(str_orig, "%.5u", a);

  ck_assert_int_eq(res_11, res_11_orig);
  ck_assert_str_eq(str, str_orig);

  int res_12 = custom_sprintf(str, "%-.5u", a);
  int res_12_orig = sprintf(str_orig, "%-.5u", a);

  ck_assert_int_eq(res_12, res_12_orig);
  ck_assert_str_eq(str, str_orig);

  int res_13 = custom_sprintf(str, "%-10.5u", a);
  int res_13_orig = sprintf(str_orig, "%-10.5u", a);

  ck_assert_int_eq(res_13, res_13_orig);
  ck_assert_str_eq(str, str_orig);

  int res_14 = custom_sprintf(str, "%3.5u", a);
  int res_14_orig = sprintf(str_orig, "%3.5u", a);

  ck_assert_int_eq(res_14, res_14_orig);
  ck_assert_str_eq(str, str_orig);

  int res_15 = custom_sprintf(str, "%-3.5u", a);
  int res_15_orig = sprintf(str_orig, "%-3.5u", a);

  ck_assert_int_eq(res_15, res_15_orig);
  ck_assert_str_eq(str, str_orig);

  int res_16 = custom_sprintf(str, "%6.2u", a);
  int res_16_orig = sprintf(str_orig, "%6.2u", a);

  ck_assert_int_eq(res_16, res_16_orig);
  ck_assert_str_eq(str, str_orig);

  int res_17 = custom_sprintf(str, "%3.2u", a);
  int res_17_orig = sprintf(str_orig, "%3.2u", a);

  ck_assert_int_eq(res_17, res_17_orig);
  ck_assert_str_eq(str, str_orig);

  int res_18 = custom_sprintf(str, "%01u", a);
  int res_18_orig = sprintf(str_orig, "%01u", a);

  ck_assert_int_eq(res_18, res_18_orig);
  ck_assert_str_eq(str, str_orig);

  int res_19 = custom_sprintf(str, "%hu", (unsigned short)a);
  int res_19_orig = sprintf(str_orig, "%hu", (unsigned short)a);

  ck_assert_int_eq(res_19, res_19_orig);
  ck_assert_str_eq(str, str_orig);

  int res_20 = custom_sprintf(str, "%lu", (unsigned long)a);
  int res_20_orig = sprintf(str_orig, "%lu", (unsigned long)a);

  ck_assert_int_eq(res_20, res_20_orig);
  ck_assert_str_eq(str, str_orig);
}
END_TEST

START_TEST(custom_sprintf_o_test) {
  int arr1[] = {0, -1, 1, 123, 1234, -1383, 9387};
  char str[80];
  char str1[80];
  int res = custom_sprintf(str, "%o", arr1[0]);
  int res1 = sprintf(str1, "%o", arr1[0]);
  ck_assert_uint_eq((unsigned long)*str, (unsigned long)*str1);
  ck_assert_int_eq(res, res1);

  res = custom_sprintf(str, "%-12.3lo", (unsigned long)arr1[4]);
  res1 = sprintf(str1, "%-12.3lo", (unsigned long)arr1[4]);
  ck_assert_uint_eq((unsigned long)*str, (unsigned long)*str1);
  ck_assert_int_eq(res, res1);

  res = custom_sprintf(str, "%010.5o", arr1[5]);
  ck_assert_str_eq(str, "37777775231");
  ck_assert_int_eq(res, 11);

  res = custom_sprintf(str, "%0#3.7o gterth", arr1[6]);
  ck_assert_str_eq(str, "0022253 gterth");
  ck_assert_int_eq(res, 14);

  res = custom_sprintf(str, "%-.4o gterth", arr1[6]);
  res1 = sprintf(str1, "%-.4o gterth", arr1[6]);
  ck_assert_uint_eq((unsigned long)*str, (unsigned long)*str1);
  ck_assert_int_eq(res, res1);

  res = custom_sprintf(str, "%-#.9o gterth", arr1[6]);
  res1 = sprintf(str1, "%-#.9o gterth", arr1[6]);
  ck_assert_uint_eq((unsigned long)*str, (unsigned long)*str1);
  ck_assert_int_eq(res, res1);

  res = custom_sprintf(str, "hello %0.o gterth", arr1[6]);
  ck_assert_str_eq(str, "hello 22253 gterth");
  ck_assert_int_eq(res, 18);

  res = custom_sprintf(str, "hello %#o gterth", arr1[6]);
  res1 = sprintf(str1, "hello %#o gterth", arr1[6]);
  ck_assert_uint_eq((unsigned long)*str, (unsigned long)*str1);
  ck_assert_int_eq(res, res1);

  res = custom_sprintf(str, "hello %*.o gterth", 5, arr1[6]);
  res1 = sprintf(str1, "hello %*.o gterth", 5, arr1[6]);
  ck_assert_uint_eq((unsigned long)*str, (unsigned long)*str1);
  ck_assert_int_eq(res, res1);

  res = custom_sprintf(str, "hello %010.7o gterth", arr1[6]);
  ck_assert_str_eq(str, "hello    0022253 gterth");
  ck_assert_int_eq(res, 23);

  res = custom_sprintf(str, "%010.7ho", (unsigned short)arr1[6]);
  ck_assert_str_eq(str, "   0022253");
  ck_assert_int_eq(res, 10);
}
END_TEST

START_TEST(custom_sprintf_x_X_test) {
  int arr1[] = {0, -1, 1, 123, 1234, -1383, 9387};
  char str[80];
  char str1[80];
  int res = custom_sprintf(str, "%x", arr1[0]);
  int res1 = sprintf(str1, "%x", arr1[0]);
  ck_assert_uint_eq((unsigned long)*str, (unsigned long)*str1);
  ck_assert_int_eq(res, res1);

  res = custom_sprintf(str, "%#10.7hx", (unsigned short)arr1[3]);
  res1 = sprintf(str1, "%#10.7hx", (unsigned short)arr1[3]);
  ck_assert_uint_eq((unsigned long)*str, (unsigned long)*str1);
  ck_assert_int_eq(res, res1);

  res = custom_sprintf(str, "%-#10.3lx", (unsigned long)arr1[3]);
  res1 = sprintf(str1, "%-#10.3lx", (unsigned long)arr1[3]);
  ck_assert_uint_eq((unsigned long)*str, (unsigned long)*str1);
  ck_assert_int_eq(res, res1);

  res = custom_sprintf(str, "%X", arr1[0]);
  res1 = sprintf(str1, "%X", arr1[0]);
  ck_assert_uint_eq((unsigned long)*str, (unsigned long)*str1);
  ck_assert_int_eq(res, res1);

  res = custom_sprintf(str, "%#10.7lX", (unsigned long)arr1[3]);
  res1 = sprintf(str1, "%#10.7lX", (unsigned long)arr1[3]);
  ck_assert_uint_eq((unsigned long)*str, (unsigned long)*str1);
  ck_assert_int_eq(res, res1);

  res = custom_sprintf(str, "%-#10.3hX", (unsigned short)arr1[3]);
  res1 = sprintf(str1, "%-#10.3hX", (unsigned short)arr1[3]);
  ck_assert_uint_eq((unsigned long)*str, (unsigned long)*str1);
  ck_assert_int_eq(res, res1);

  res = custom_sprintf(str, "%-#*.3hX", 10, (unsigned short)arr1[3]);
  res1 = sprintf(str1, "%-#*.3hX", 10, (unsigned short)arr1[3]);
  ck_assert_uint_eq((unsigned long)*str, (unsigned long)*str1);
  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(custom_sprintf_e_test) {
  char str[80];
  char str_origin[80];
  const char *format_str1 = "% 10.15LE yo";
  long double mantissa1 = 0.0000003044058697058435;
  int result1 = custom_sprintf(str, format_str1, mantissa1);
  int result_origin1 = sprintf(str_origin, format_str1, mantissa1);

  ck_assert_int_eq(result1, result_origin1);
  ck_assert_str_eq(str, str_origin);

  const char *format_str2 = "%-20.7e yo";
  double mantissa2 = -4044050;
  int result2 = custom_sprintf(str, format_str2, mantissa2);
  int result_origin2 = sprintf(str_origin, format_str2, mantissa2);
  ck_assert_int_eq(result2, result_origin2);
  ck_assert_str_eq(str, str_origin);

  const char *format_str3 = "%-.5E yo";
  double mantissa3 = -0.00;
  int result3 = custom_sprintf(str, format_str3, mantissa3);
  int result_origin3 = sprintf(str_origin, format_str3, mantissa3);
  ck_assert_int_eq(result3, result_origin3);
  ck_assert_str_eq(str, str_origin);

  const char *format_str6 = "% -10.15E yo";
  double mantissa6 = 0.00003044058697058435;
  int result6 = custom_sprintf(str, format_str6, mantissa6);
  int result_origin6 = sprintf(str_origin, format_str6, mantissa6);
  ck_assert_int_eq(result6, result_origin6);
  ck_assert_str_eq(str, str_origin);
}
END_TEST

Suite *string_suite(void) {
  Suite *s;
  TCase *tc_strlen = NULL, *tc_strncmp = NULL, *tc_strchr = NULL,
        *tc_strstr = NULL, *tc_strrchr = NULL, *tc_strtok = NULL,
        *tc_strncat = NULL, *tc_strncpy = NULL, *tc_strerror = NULL,
        *tc_strcspn = NULL, *tc_memcpy = NULL, *tc_memcmp = NULL,
        *tc_memset = NULL, *tc_memchr = NULL, *tc_to_lower = NULL,
        *tc_to_upper = NULL, *tc_insert = NULL, *tc_trim = NULL,
        *tc_sprintf_f = NULL, *tc_sprintf_c = NULL, *tc_sprintf_test = NULL,
        *tc_sprintf_p = NULL, *tc_sprintf_d_1 = NULL, *tc_sprintf_d_2 = NULL,
        *tc_sprintf_d_3 = NULL, *tc_sprintf_d_4 = NULL, *tc_sprintf_d_5 = NULL,
        *tc_sprintf_d_6 = NULL, *tc_sprintf_d_7 = NULL, *tc_sprintf_prc = NULL,
        *tc_sprintf_n = NULL, *tc_sprintf_s = NULL, *tc_sprintf_u = NULL,
        *tc_sprintf_o = NULL, *tc_sprintf_x_X = NULL, *tc_sprintf_e = NULL,
        *tc_strpbrk = NULL;
  s = suite_create("custom_string+");
  NAME_TEST("strlen");
  tc_strlen = tcase_create("strlen");
  tcase_add_test(tc_strlen, test_strlen);
  suite_add_tcase(s, tc_strlen);

  NAME_TEST("strncmp");
  tc_strncmp = tcase_create("strncmp");
  tcase_add_test(tc_strncmp, test_strncmp);
  suite_add_tcase(s, tc_strncmp);

  NAME_TEST("strpbrk");
  tc_strpbrk = tcase_create("strpbrk");
  tcase_add_test(tc_strpbrk, test_strpbrk);
  suite_add_tcase(s, tc_strpbrk);

  NAME_TEST("strchr");
  tc_strchr = tcase_create("strchr");
  tcase_add_test(tc_strchr, test_strchr);
  suite_add_tcase(s, tc_strchr);

  NAME_TEST("strstr");
  tc_strstr = tcase_create("strstr");
  tcase_add_test(tc_strstr, test_strstr);
  suite_add_tcase(s, tc_strstr);

  NAME_TEST("strrchr");
  tc_strrchr = tcase_create("strrchr");
  tcase_add_test(tc_strrchr, test_strrchr);
  suite_add_tcase(s, tc_strrchr);

  NAME_TEST("strtok");
  tc_strtok = tcase_create("strtok");
  tcase_add_test(tc_strtok, test_strtok);
  suite_add_tcase(s, tc_strtok);

  NAME_TEST("strncat");
  tc_strncat = tcase_create("strncat");
  tcase_add_test(tc_strncat, test_strncat);
  suite_add_tcase(s, tc_strncat);

  NAME_TEST("strncpy");
  tc_strncpy = tcase_create("strncpy");
  tcase_add_test(tc_strncpy, test_strncpy);
  suite_add_tcase(s, tc_strncpy);

  NAME_TEST("strerror");
  tc_strerror = tcase_create("strerror");
  tcase_add_test(tc_strerror, test_strerror);
  suite_add_tcase(s, tc_strerror);

  NAME_TEST("strcspn");
  tc_strcspn = tcase_create("strcspn");
  tcase_add_test(tc_strcspn, test_strcspn);
  suite_add_tcase(s, tc_strcspn);

  NAME_TEST("memcpy");
  tc_memcpy = tcase_create("memcpy");
  tcase_add_test(tc_memcpy, test_memcpy);
  suite_add_tcase(s, tc_memcpy);

  NAME_TEST("memcmp");
  tc_memcmp = tcase_create("memcmp");
  tcase_add_test(tc_memcmp, test_memcmp);
  suite_add_tcase(s, tc_memcmp);

  NAME_TEST("memset");
  tc_memset = tcase_create("memset");
  tcase_add_test(tc_memset, test_memset);
  suite_add_tcase(s, tc_memset);

  NAME_TEST("memchr");
  tc_memchr = tcase_create("memchr");
  tcase_add_test(tc_memchr, test_memchr);
  suite_add_tcase(s, tc_memchr);

  NAME_TEST("to_lower");
  tc_to_lower = tcase_create("to_lower");
  tcase_add_test(tc_to_lower, test_to_lower);
  suite_add_tcase(s, tc_to_lower);

  NAME_TEST("to_upper");
  tc_to_upper = tcase_create("to_upper");
  tcase_add_test(tc_to_upper, test_to_upper);
  suite_add_tcase(s, tc_to_upper);

  NAME_TEST("insert");
  tc_insert = tcase_create("insert");
  tcase_add_test(tc_insert, test_insert);
  suite_add_tcase(s, tc_insert);

  NAME_TEST("trim");
  tc_trim = tcase_create("trim");
  tcase_add_test(tc_trim, test_trim);
  suite_add_tcase(s, tc_trim);

  NAME_TEST("sprintf f");
  tc_sprintf_f = tcase_create("sprintf f");
  tcase_add_test(tc_sprintf_f, custom_sprintf_f_test);
  suite_add_tcase(s, tc_sprintf_f);

  NAME_TEST("sprintf c");
  tc_sprintf_c = tcase_create("sprintf c");
  tcase_add_test(tc_sprintf_c, custom_sprintf_c_test);
  suite_add_tcase(s, tc_sprintf_c);

  NAME_TEST("sprintf (parser like str)");
  tc_sprintf_test = tcase_create("sprintf (parser like str)");
  tcase_add_test(tc_sprintf_test, custom_sprintf_test);
  suite_add_tcase(s, tc_sprintf_test);

  NAME_TEST("sprintf p");
  tc_sprintf_p = tcase_create("sprintf p");
  tcase_add_test(tc_sprintf_p, custom_sprintf_p_test);
  suite_add_tcase(s, tc_sprintf_p);

  NAME_TEST("sprintf d 1");
  tc_sprintf_d_1 = tcase_create("sprintf d 1");
  tcase_add_test(tc_sprintf_d_1, custom_sprintf_d_test_1);
  suite_add_tcase(s, tc_sprintf_d_1);

  NAME_TEST("sprintf d 2");
  tc_sprintf_d_2 = tcase_create("sprintf d 2");
  tcase_add_test(tc_sprintf_d_2, custom_sprintf_d_test_2);
  suite_add_tcase(s, tc_sprintf_d_2);

  NAME_TEST("sprintf d 3");
  tc_sprintf_d_3 = tcase_create("sprintf d 3");
  tcase_add_test(tc_sprintf_d_3, custom_sprintf_d_test_3);
  suite_add_tcase(s, tc_sprintf_d_3);

  NAME_TEST("sprintf d 4");
  tc_sprintf_d_4 = tcase_create("sprintf d 4");
  tcase_add_test(tc_sprintf_d_4, custom_sprintf_d_test_4);
  suite_add_tcase(s, tc_sprintf_d_4);

  NAME_TEST("sprintf d 5");
  tc_sprintf_d_5 = tcase_create("sprintf d 5");
  tcase_add_test(tc_sprintf_d_5, custom_sprintf_d_test_5);
  suite_add_tcase(s, tc_sprintf_d_5);

  NAME_TEST("sprintf d 6");
  tc_sprintf_d_6 = tcase_create("sprintf d 6");
  tcase_add_test(tc_sprintf_d_6, custom_sprintf_d_test_6);
  suite_add_tcase(s, tc_sprintf_d_6);

  NAME_TEST("sprintf d 7");
  tc_sprintf_d_7 = tcase_create("sprintf d 7");
  tcase_add_test(tc_sprintf_d_7, custom_sprintf_d_test_7);
  suite_add_tcase(s, tc_sprintf_d_7);

  NAME_TEST("sprintf prc");
  tc_sprintf_prc = tcase_create("sprintf prc");
  tcase_add_test(tc_sprintf_prc, custom_sprintf_prc_test);
  suite_add_tcase(s, tc_sprintf_prc);

  NAME_TEST("sprintf n");
  tc_sprintf_n = tcase_create("sprintf n");
  tcase_add_test(tc_sprintf_n, custom_sprintf_n_test);
  suite_add_tcase(s, tc_sprintf_n);

  NAME_TEST("sprintf s");
  tc_sprintf_s = tcase_create("sprintf s");
  tcase_add_test(tc_sprintf_s, custom_sprintf_s_test);
  suite_add_tcase(s, tc_sprintf_s);

  NAME_TEST("sprintf u");
  tc_sprintf_u = tcase_create("sprintf u");
  tcase_add_test(tc_sprintf_u, custom_sprintf_u_test);
  suite_add_tcase(s, tc_sprintf_u);

  NAME_TEST("sprintf o");
  tc_sprintf_o = tcase_create("sprintf o");
  tcase_add_test(tc_sprintf_o, custom_sprintf_o_test);
  suite_add_tcase(s, tc_sprintf_o);

  NAME_TEST("sprintf x|X");
  tc_sprintf_x_X = tcase_create("sprintf x|X");
  tcase_add_test(tc_sprintf_x_X, custom_sprintf_x_X_test);
  suite_add_tcase(s, tc_sprintf_x_X);

  NAME_TEST("sprintf e|E");
  tc_sprintf_e = tcase_create("sprintf e|E");
  tcase_add_test(tc_sprintf_e, custom_sprintf_e_test);
  suite_add_tcase(s, tc_sprintf_e);

  return s;
}

int main(void) {
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = string_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}