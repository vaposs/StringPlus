#ifndef S21_SSCANF
#define S21_SSCANF

#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200809L
#endif

#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "s21_string.h"

typedef struct {
  bool suppress_assignment;  // Считывает данные указанного типа, но подавляет
                             // их присваивание
  int width;  // Максимальное число символов, которые будут считываться для
              // этого поля
  char length1;  // Первый символ модификатора длины
  char length2;  // Второй символ модификатора длины
  char specifier;                      // Спецификатор
  const char *const begin_of_str_ptr;  // Указатель на начало str
} Config;

typedef struct {
  char *preceding_str;  // Строка специальных и неспециальных символов
  char *specifier;      // Строка спецификатора
} SpecBlock;

int s21_sscanf(const char *str, const char *fmt, ...);
int validate_params(const char *str, const char *fmt);
int get_specifier(char **cur_fmt_ptr, SpecBlock *spec_block, Config *config);
int parse_specifier_components(char **fmt_ptr, char **specifier_ptr,
                               Config *config);
int match_specifier(char **current_str, va_list *args, SpecBlock *spec_block,
                    Config *config);
bool process_specifier(const char *str, va_list *args, Config *config,
                       const char **new_pos);
bool parse_decimal(const char *str, va_list *args, Config *config,
                   const char **new_pos);
bool parse_char(const char *str, va_list *args, Config *config,
                const char **new_pos);
bool parse_string(const char *str, va_list *args, Config *config,
                  const char **new_pos);
bool parse_unsigned(const char *str, va_list *args, Config *config,
                    const char **new_pos, int sign);
bool parse_integer(const char *str, va_list *args, Config *config,
                   const char **new_pos);
bool parse_float(const char *str, va_list *args, Config *config,
                 const char **new_pos);
double parse_sign(const char **str_ptr);
bool parse_pointer(const char *str, va_list *args, Config *config,
                   const char **new_pos);
bool parse_chars_count(const char *str, va_list *args, Config *config,
                       const char **new_pos);
bool is_digit(char c);
bool is_specifier_char(char c);
bool is_special_char(char c);
s21_size_t s21_strtoi(const char *str);
bool is_valid_digit(char c, int base);
bool is_hex_digit(char c);
int get_digit_value(char c);

#endif  // S21_SSCANF