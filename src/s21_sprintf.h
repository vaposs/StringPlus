#ifndef S21_SPRINTF
#define S21_SPRINTF

#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200809L
#endif

#include <math.h>
#include <stdarg.h>

#include "s21_string.h"

#define S21_NULL ((void *)0)

typedef unsigned long int s21_size_t;

typedef struct descriptions {
  int minus;          // к левому краю
  int plus;           // пишем знак
  int space;          // знак или пробел
  int width;          // ширина
  int precision;      // точность
  char length;        // тип переменной (l, h)
  int number_system;  // система исчисления (8, 10, 16)
  int flag_to_size;  // если число отрицательное или есть + или space
  int dot;  // наличие точки в числе
  int g;    // наличие спецификатора g
  int e;    // запись числа в научной нотации
  int sharp;  // флаг '#' для альтернативной формы (0x, 0)
  int zero;        // флаг '0' для дополнения нулями
  int upper_case;  // верхний регистр для X, E, G
} desc;

int s21_sprintf(char *str, const char *format, ...);
const char *get_flags(const char *format, desc *spec);
const char *set_flags(desc *spec, const char *format, va_list *args);
const char *get_width(const char *format, int *width, va_list *args);
char *spec_parser(char *str, char *src, const char *format, desc spec,
                  va_list *args);
char *spec_integer(char *str, desc spec, va_list *arguments);
char get_num_char(int num);
char *spec_uinteger(char *str, desc spec, char format, va_list *args);
s21_size_t get_uint_size(desc *spec, unsigned long int num);
int uint_to_str(char *buf, desc spec, unsigned long int num,
                s21_size_t uinteger_size);
char *spec_char(char *str, int sym);
char *spec_string(char *str, desc spec, va_list *args);
char *spec_float(char *str, desc spec, double value);
char *spec_hex(char *str, desc spec, va_list *args, char format);
s21_size_t get_hex_size(desc *spec, unsigned long int num);
int hex_to_str(char *buf, desc spec, unsigned long int num, char format);
char *spec_octal(char *str, desc spec, va_list *args);
char *spec_scientific(char *str, desc spec, double value, char format);
char *spec_float_auto(char *str, desc spec, double value, char format);
char *spec_pointer(char *str, desc spec, void *ptr);

#endif  // S21_SPRINTF