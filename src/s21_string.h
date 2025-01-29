#ifndef S21_STRING_H
#define S21_STRING_H
#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#define s21_size_t unsigned int
#define S21_NULL ((void *)0)
#define CONVERT_TO_AND_SAVE_AS(TO, AS) *va_arg(arg, AS *) = TO

void *s21_memchr(const void *str, int c, s21_size_t n);
int s21_memcmp(const void *str1, const void *str2, s21_size_t n);
void *s21_memcpy(void *dest, const void *src, s21_size_t n);
void *s21_memset(void *str, int c, s21_size_t n);
char *s21_strncat(char *dest, const char *src, s21_size_t n);
char *s21_strchr(const char *str, int c);
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);
char *s21_strncpy(char *dest, const char *src, s21_size_t n);
s21_size_t s21_strcspn(const char *str1, const char *str2);
char *s21_strerror(int errnum);
s21_size_t s21_strlen(const char *str);
char *s21_strpbrk(const char *str1, const char *str2);
char *s21_strrchr(const char *str, int c);
char *s21_strstr(const char *haystack, const char *needle);
char *s21_strtok(char *str, const char *delim);

int s21_sprintf(char *str, const char *format, ...);
int int_counter(int digit);
int short_counter(short digit);
int long_counter(long digit);
void int_to_char(size_t digit, char *array);
size_t long_neg_processing(long number);
size_t short_neg_processing(short number);
size_t int_neg_processing(int number);
void float_to_char(char *array, int array_size, double digit);
void float_to_char_round(char *array, int array_size, double digit, int width);
long s21_pow(int digit, int stepen);
void handle_char(va_list factor, char *str, int *l, int flag_minus, int width);
void handle_int(va_list factor, char *str, int *l, int flag_minus,
                int flag_space, int flag_plus, int short_flag, int long_flag,
                int width);
void handle_string(va_list factor, char *str, int *l, int flag_minus,
                   int width);
void handle_unsigned(va_list factor, char *str, int *l, int flag_minus,
                     int short_flag, int long_flag, int width);
void handle_float(va_list factor, char *str, int *l, int flag_minus,
                  int flag_space, int flag_plus, int point_flag, int width);

typedef struct {
  int width, supress_writing;
  char length, spec;
} format_flags;

int s21_sscanf(const char *str, const char *format, ...);
void read_format(const char *format, format_flags *flags, s21_size_t *pi);
int is_space(const char *str, format_flags flags);
int write_char(va_list arg, const char *str, format_flags flags, int *count);
int write_string(va_list arg, const char *str, format_flags flags, int *count);
int write_signed_int(va_list arg, const char *str, format_flags flags,
                     int *count);
int write_unsigned_int(va_list arg, const char *str, format_flags flags,
                       int *count);
int write_float(va_list arg, const char *str, format_flags flags, int *count);
long int to_integer(char *buffer, int base);
long double to_float(char *buffer);

void *s21_to_upper(const char *str);
void *s21_to_lower(const char *str);
void *s21_insert(const char *src, const char *str, size_t start_index);
void s21_strcpy(char *dest, const char *src);
void *s21_trim(const char *src, const char *trim_chars);

#endif