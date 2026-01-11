#include "s21_sprintf.h"

#include <math.h>
#include <stdio.h>

#include "s21_string.h"

/*
str − Это С-строка, которую функция обрабатывает в качестве источника для
извлечения данных; format −  это С-строка, содержащая один или несколько
следующих элементов: пробельный символ, непробельный символ и спецификаторы
формата. Спецификатор формата для печатающих функций следует прототипу:
%[флаги][ширина][.точность][длина]спецификатор. Спецификатор формата для
сканирующих функций следует прототипу: %[*][ширина][длина]спецификатор.
*/

// основная функция
int s21_sprintf(char *str, const char *format, ...) {
  const char specifiers[] = "cdieEfgGosuxXpn%";
  char *src = str;
  va_list args;
  va_start(args, format);
  while (*format) {
    if (*format == '%') {
      format++;
      desc spec = {0};
      spec.number_system = 10;
      format = set_flags(&spec, format, &args);
      while (*format && !s21_strchr(specifiers, *format)) {
        format++;
      }
      if (*format) {
        str = spec_parser(str, src, format, spec, &args);
        format++;
      }
    } else {
      *str = *format;
      str++;
      format++;
    }
  }
  *str = '\0';
  va_end(args);
  return (str - src);
}

// обрабатываем флаги
const char *get_flags(const char *format, desc *spec) {
  while (format) {
    if (*format == '+')
      spec->plus = 1;
    else if (*format == '-')
      spec->minus = 1;
    else if (*format == ' ')
      spec->space = 1;
    else if (*format == '#')
      spec->sharp = 1;
    else if (*format == '0')
      spec->zero = 1;
    else {
      break;
    }
    format++;
  }
  spec->space = (spec->space && !spec->plus);
  return format;
}

// функция установки всех параметров
const char *set_flags(desc *spec, const char *format, va_list *args) {
  format = get_flags(format, spec);
  format = get_width(format, &spec->width, args);
  if (*format == '.') {
    spec->dot = 1;
    format += 1;
    format = get_width(format, &spec->precision, args);
  }
  if (*format == 'l')
    spec->length = 'l';
  else if (*format == 'h')
    spec->length = 'h';
  if (spec->length != 0) format += 1;
  return format;
}

// функция установки ширины
const char *get_width(const char *format, int *width, va_list *args) {
  *width = 0;
  if (*format == '*') {
    *width = va_arg(*args, int);
    format++;
  }
  while (format) {
    if ('0' <= *format && *format <= '9') {
      *width *= 10;
      *width += *format - '0';
    } else {
      break;
    }
    format++;
  }
  return format;
}

// парсер строки
char *spec_parser(char *str, char *src, const char *format, desc spec,
                  va_list *args) {
  if (*format == 'd' || *format == 'i') {
    str = spec_integer(str, spec, args);
  } else if (*format == 'u') {
    str = spec_uinteger(str, spec, *(format - 1), args);
  } else if (*format == 'c') {
    int sym = va_arg(*args, int);
    str = spec_char(str, sym);
  } else if (*format == 's') {
    str = spec_string(str, spec, args);
  } else if (*format == '%') {
    str = spec_char(str, '%');
  } else if (*format == 'f') {
    double value = va_arg(*args, double);
    str = spec_float(str, spec, value);
  } else if (*format == 'x' || *format == 'X') {
    str = spec_hex(str, spec, args, *format);
  } else if (*format == 'o') {
    str = spec_octal(str, spec, args);
  } else if (*format == 'e' || *format == 'E') {
    double value = va_arg(*args, double);
    str = spec_scientific(str, spec, value, *format);
  } else if (*format == 'g' || *format == 'G') {
    double value = va_arg(*args, double);
    str = spec_float_auto(str, spec, value, *format);
  } else if (*format == 'p') {
    void *ptr = va_arg(*args, void *);
    str = spec_pointer(str, spec, ptr);
  } else if (*format == 'n') {
    int *count_ptr = va_arg(*args, int *);
    *count_ptr = (str - src);
  }
  if (!str) *src = '\0';
  return str;
}

// обработка спецификатора d и i
char *spec_integer(char *str, desc spec, va_list *args) {
  long int num = 0;
  char num_buffer[100] = {0}, digits[100] = {0};
  int num_index = 0, digit_count = 0, is_negative = 0;
  if (spec.length == 'l')  // Получение аргумента
    num = va_arg(*args, long int);
  else if (spec.length == 'h')
    num = (short)va_arg(*args, int);
  else
    num = va_arg(*args, int);
  if (num < 0) {  // Знак
    is_negative = 1;
    num = -num;
  }
  if (num == 0)  // Цифры
    digits[digit_count++] = '0';
  else {
    long int tmp = num;
    while (tmp > 0) {
      digits[digit_count++] = '0' + (tmp % 10);
      tmp /= 10;
    }
  }
  if (is_negative)  // Префикс знака
    num_buffer[num_index++] = '-';
  else if (spec.plus)
    num_buffer[num_index++] = '+';
  else if (spec.space)
    num_buffer[num_index++] = ' ';
  for (int i = digit_count - 1; i >= 0; i--)  // Обратная запись цифр
    num_buffer[num_index++] = digits[i];
  num_buffer[num_index] = '\0';
  int actual_len = num_index;  // Вычисление ширины
  int pad = spec.width - actual_len;
  if (pad < 0) pad = 0;
  if (spec.minus) {  // Вывод
    for (int i = 0; i < actual_len; i++) *str++ = num_buffer[i];
    for (int i = 0; i < pad; i++) *str++ = ' ';
  } else if (spec.zero && !spec.dot) {
    int prefix_len = (is_negative || spec.plus || spec.space) ? 1 : 0;
    for (int i = 0; i < prefix_len; i++) *str++ = num_buffer[i];
    for (int i = 0; i < pad; i++) *str++ = '0';
    for (int i = prefix_len; i < actual_len; i++) *str++ = num_buffer[i];
  } else {
    for (int i = 0; i < pad; i++) *str++ = ' ';
    for (int i = 0; i < actual_len; i++) *str++ = num_buffer[i];
  }

  return str;
}

char get_num_char(int num) {
  char flag = '0';
  if (num >= 0 && num <= 9) flag = (char)(num + 48);  // 48 == '0'
  return flag;
}

// обработка u
char *spec_uinteger(char *str, desc spec, char format, va_list *args) {
  unsigned long int num = 0;
  if (format == 'l')
    num = (unsigned long int)va_arg(*args, unsigned long int);
  else if (format == 'h')
    num = (unsigned short)va_arg(*args, unsigned int);
  else
    num = (unsigned int)va_arg(*args, unsigned int);

  s21_size_t uinteger_size = get_uint_size(&spec, num);
  char *buf = calloc(uinteger_size + 1, sizeof(char));
  if (buf) {
    int i = uint_to_str(buf, spec, num, uinteger_size);
    for (int j = i - 1; j >= 0; j--) {
      *str = buf[j];
      str++;
    }
  }
  if (buf) free(buf);
  return str;
}

// вычисляю длину unsigned
s21_size_t get_uint_size(desc *spec, unsigned long int num) {
  s21_size_t result = 0;
  unsigned long int num_cpy = num;
  while (num_cpy > 0) {
    num_cpy /= 10;
    result++;
  }
  if (result == 0 && (spec->precision || spec->width || spec->space)) {
    result++;
  }
  if ((s21_size_t)spec->width > result) result = spec->width;
  if ((s21_size_t)spec->precision > result) result = spec->precision;

  if (result == 0 && !spec->precision && !spec->width && !spec->space &&
      !spec->dot) {
    result++;
  }
  return result;
}

int uint_to_str(char *buf, desc spec, unsigned long int num,
                s21_size_t uinteger_size) {
  int i = 0;
  unsigned long int num_cpy = num;
  if ((num_cpy == 0 && (spec.precision || spec.width || spec.space)) ||
      (num_cpy == 0 && !spec.precision && !spec.width && !spec.dot)) {
    char sym = num_cpy % spec.number_system + '0';
    buf[i] = sym;
    i++;
    uinteger_size--;
    num_cpy /= 10;
  }
  while (num_cpy && buf && uinteger_size) {
    char sym = get_num_char(num_cpy % spec.number_system);
    buf[i] = sym;
    i++;
    uinteger_size--;
    num_cpy /= 10;
  }
  if (uinteger_size > 0 && spec.minus == 0) {
    while ((uinteger_size - spec.flag_to_size > 0) && buf) {
      buf[i] = ' ';
      i++;
      uinteger_size--;
    }
  }
  return i;
}

// обработка char
char *spec_char(char *str, int sym) {
  *str++ = (char)sym;
  return str;
}

// обработка строк
char *spec_string(char *str, desc spec, va_list *args) {
  char *string = va_arg(*args, char *);
  // char *start = str;

  if (!string) {
    string = "(null)";
  }

  int str_len = s21_strlen(string);
  int output_len = str_len;

  if (spec.dot && spec.precision < output_len) {
    output_len = spec.precision;
  }

  int padding = spec.width - output_len;
  if (padding < 0) padding = 0;

  if (!spec.minus) {
    for (int i = 0; i < padding; i++) {
      *str++ = ' ';
    }
  }

  for (int i = 0; i < output_len; i++) {
    *str++ = string[i];
  }

  if (spec.minus) {
    for (int i = 0; i < padding; i++) {
      *str++ = ' ';
    }
  }

  return str;
}

// для обработки шестнадцатеричных чисел (%x, %X)
static int write_hex(unsigned long int num, char *buf, char format) {
  const char *digits =
      (format == 'X') ? "0123456789ABCDEF" : "0123456789abcdef";
  int count = 0;
  if (num == 0) {
    buf[count++] = '0';
  } else {
    char temp[100];
    int i = 0;
    while (num) {
      temp[i++] = digits[num % 16];
      num /= 16;
    }
    while (i--) buf[count++] = temp[i];
  }
  return count;
}

// Обработка спецификатора %x / %X
char *spec_hex(char *str, desc spec, va_list *args, char format) {
  unsigned long int num = 0;
  char num_buffer[100] = {0};
  int num_index = 0;

  // Получение аргумента
  if (spec.length == 'l')
    num = va_arg(*args, unsigned long int);
  else if (spec.length == 'h')
    num = (unsigned short)va_arg(*args, unsigned int);
  else
    num = va_arg(*args, unsigned int);

  // Префикс 0x/0X (только если число не равно 0)
  if (spec.sharp && num != 0) {
    num_buffer[num_index++] = '0';
    num_buffer[num_index++] = (format == 'X') ? 'X' : 'x';
  }

  // Запись шестнадцатеричных цифр
  num_index += write_hex(num, num_buffer + num_index, format);
  num_buffer[num_index] = '\0';

  // Вычисление ширины
  int actual_len = num_index;
  int pad = spec.width - actual_len;
  if (pad < 0) pad = 0;

  // Вывод
  if (spec.minus) {
    for (int i = 0; i < actual_len; i++) *str++ = num_buffer[i];
    for (int i = 0; i < pad; i++) *str++ = ' ';
  } else if (spec.zero && !spec.dot) {
    for (int i = 0; i < pad; i++) *str++ = '0';
    for (int i = 0; i < actual_len; i++) *str++ = num_buffer[i];
  } else {
    for (int i = 0; i < pad; i++) *str++ = ' ';
    for (int i = 0; i < actual_len; i++) *str++ = num_buffer[i];
  }

  return str;
}

// для вычисления размера шестнадцатеричного числа
s21_size_t get_hex_size(desc *spec, unsigned long int num) {
  s21_size_t result = 0;
  unsigned long int num_cpy = num;

  if (num_cpy == 0) {
    result = 1;
  } else {
    while (num_cpy > 0) {
      num_cpy /= spec->number_system;
      result++;
    }
  }

  if (spec->sharp && num != 0) {
    result += 2;
  }

  if ((s21_size_t)spec->precision > result) {
    result = spec->precision;
  }

  if ((s21_size_t)spec->width > result) {
    result = spec->width;
  }

  return result;
}

// для преобразования hex в строку
int hex_to_str(char *buf, desc spec, unsigned long int num, char format) {
  int i = 0;
  const char *digits =
      (format == 'X') ? "0123456789ABCDEF" : "0123456789abcdef";

  if (num == 0) {
    buf[i++] = '0';
  } else {
    unsigned long int num_cpy = num;
    while (num_cpy > 0) {
      buf[i++] = digits[num_cpy % spec.number_system];
      num_cpy /= spec.number_system;
    }
  }

  while (i < spec.precision) {
    buf[i++] = '0';
  }

  if (spec.sharp && num != 0) {
    buf[i++] = (format == 'X') ? 'X' : 'x';
    buf[i++] = '0';
  }

  return i;
}

// для обработки восьмеричных чисел (%o)
static int write_octal(unsigned long int num, char *buf) {
  int count = 0;
  if (num == 0) {
    buf[count++] = '0';
  } else {
    char temp[100];
    int i = 0;
    while (num) {
      temp[i++] = (char)('0' + (num % 8));
      num /= 8;
    }
    while (i--) buf[count++] = temp[i];
  }
  return count;
}

// Обработка спецификатора %o
char *spec_octal(char *str, desc spec, va_list *args) {
  unsigned long int num = 0;
  char num_buffer[100] = {0};
  int num_index = 0;

  // Получение аргумент
  if (spec.length == 'l')
    num = va_arg(*args, unsigned long int);
  else if (spec.length == 'h')
    num = (unsigned short)va_arg(*args, unsigned int);
  else
    num = va_arg(*args, unsigned int);

  // Флаг # (ведущий 0, если требуется)
  if (spec.sharp && (num != 0 || spec.dot)) num_buffer[num_index++] = '0';

  // Запись цифр
  num_index += write_octal(num, num_buffer + num_index);
  num_buffer[num_index] = '\0';

  // Ширина и выравнивание
  int actual_len = num_index;
  int pad = spec.width - actual_len;
  if (pad < 0) pad = 0;

  if (spec.minus) {
    for (int i = 0; i < actual_len; i++) *str++ = num_buffer[i];
    for (int i = 0; i < pad; i++) *str++ = ' ';
  } else if (spec.zero && !spec.dot) {
    for (int i = 0; i < pad; i++) *str++ = '0';
    for (int i = 0; i < actual_len; i++) *str++ = num_buffer[i];
  } else {
    for (int i = 0; i < pad; i++) *str++ = ' ';
    for (int i = 0; i < actual_len; i++) *str++ = num_buffer[i];
  }

  return str;
}

// для нотации (%e, %E)
char *spec_scientific(char *str, desc spec, double value, char format) {
  int exponent = 0;

  if (value != 0.0) {
    while (value >= 10.0) {
      value /= 10.0;
      exponent++;
    }
    while (value < 1.0 && value > 0.0) {
      value *= 10.0;
      exponent--;
    }
  }

  str = spec_float(str, spec, value);

  *str++ = (format == 'E') ? 'E' : 'e';
  *str++ = (exponent >= 0) ? '+' : '-';

  int exp_abs = (exponent < 0) ? -exponent : exponent;
  if (exp_abs < 10) {
    *str++ = '0';
    *str++ = '0' + exp_abs;
  } else {
    *str++ = '0' + (exp_abs / 10);
    *str++ = '0' + (exp_abs % 10);
  }

  return str;
}

// Вспомогательная функция: запись целой части числа
static int write_integer(long long num, char *buf) {
  int count = 0;
  if (num == 0) {
    buf[count++] = '0';
  } else {
    char temp[100];
    int i = 0;
    while (num) {
      temp[i++] = '0' + (num % 10);
      num /= 10;
    }
    while (i--) buf[count++] = temp[i];
  }
  return count;
}

// Вспомогательная функция: запись дробной части числа
static int write_fraction(long long frac, int precision, char *buf) {
  int count = 0;
  char temp[100];

  if (frac == 0) {
    // Добавляем нужное количество нулей
    for (int j = 0; j < precision; j++) buf[count++] = '0';
  } else {
    int i = 0;
    while (frac) {
      temp[i++] = '0' + (frac % 10);
      frac /= 10;
    }
    // Добавляем ведущие нули
    for (int j = i; j < precision; j++) buf[count++] = '0';
    while (i--) buf[count++] = temp[i];
  }

  return count;
}

// Основной обработчик float
char *spec_float(char *str, desc spec, double value) {
  int precision = spec.dot ? spec.precision : 6;
  if (precision < 0) precision = 0;

  int is_negative = 0;
  if (value < 0) {
    is_negative = 1;
    value = -value;
  }

  double multiplier = 1.0;
  for (int i = 0; i < precision; i++) multiplier *= 10.0;
  long long total = (long long)(value * multiplier + 0.5);

  long long int_part = total / (long long)multiplier;
  long long frac_part = total % (long long)multiplier;

  char buf[400];
  int idx = 0;

  if (is_negative)
    buf[idx++] = '-';
  else if (spec.plus)
    buf[idx++] = '+';
  else if (spec.space)
    buf[idx++] = ' ';

  idx += write_integer(int_part, buf + idx);

  if (precision > 0 || spec.sharp) {
    buf[idx++] = '.';
    idx += write_fraction(frac_part, precision, buf + idx);
  }

  buf[idx] = '\0';
  int actual_len = idx;
  int pad = spec.width - actual_len;
  if (pad < 0) pad = 0;

  if (spec.minus) {
    for (int i = 0; i < actual_len; i++) *str++ = buf[i];
    for (int i = 0; i < pad; i++) *str++ = ' ';
  } else {
    for (int i = 0; i < pad; i++) *str++ = ' ';
    for (int i = 0; i < actual_len; i++) *str++ = buf[i];
  }

  return str;
}

// автоматического выбора формата (%g, %G)
// Вспомогательная функция: выбор научной или обычной нотации
static void prepare_float_auto(double value, int *use_sci, double *out_value) {
  *use_sci = (value >= 1e6 || (value > 0 && value < 1e-4)) ? 1 : 0;
  *out_value = value;
}

// Вспомогательная функция: обрезка незначащих нулей после точки
static char *trim_trailing_zeros(char *buffer, char *result) {
  char *p = buffer;
  while (*p && *p != '.') *result++ = *p++;
  if (*p == '.') {
    char *dot_pos = p++;
    char *last_sig = dot_pos;
    char *current = p;
    while (*current) {
      if (*current != '0') last_sig = current;
      current++;
    }
    if (last_sig > dot_pos) {
      *result++ = '.';
      char *digit = p;
      while (digit <= last_sig) *result++ = *digit++;
    }
  }
  return result;
}

// Основной обработчик float auto (%g/%G)
char *spec_float_auto(char *str, desc spec, double value, char format) {
  int precision = spec.dot ? spec.precision : 6;
  if (precision == 0) precision = 1;

  double abs_value = value < 0 ? -value : value;
  int use_sci = 0;
  double prepared_value = value;

  prepare_float_auto(abs_value, &use_sci, &prepared_value);

  char buffer[400] = {0};

  if (use_sci) {
    spec.precision = precision - 1;
    spec_scientific(buffer, spec, value, (format == 'G') ? 'E' : 'e');
  } else {
    if (abs_value > 0) {
      int exponent = 0;
      double temp = abs_value;
      while (temp >= 1.0) {
        temp /= 10.0;
        exponent++;
      }
      while (temp < 0.1 && temp > 0) {
        temp *= 10.0;
        exponent--;
      }

      double round_power = 1.0;
      for (int i = 0; i < precision; i++) round_power *= 10.0;
      temp = round(temp * round_power) / round_power;

      while (exponent > 0) {
        temp *= 10.0;
        exponent--;
      }
      while (exponent < 0) {
        temp /= 10.0;
        exponent++;
      }

      prepared_value = (value < 0) ? -temp : temp;
    }

    desc temp_spec = spec;
    temp_spec.precision = precision + 6;
    spec_float(buffer, temp_spec, prepared_value);
  }

  return trim_trailing_zeros(buffer, str);
}

// для указателей (%p)
char *spec_pointer(char *str, desc spec, void *ptr) {
  // NULL указатель
  const char *null_str = "(nil)";
#ifdef __APPLE__
  null_str = "0x0";
#endif
  if (ptr == NULL) {
    int len = 0;
    while (null_str[len]) len++;
    int padding = spec.width - len;
    if (padding < 0) padding = 0;

    if (!spec.minus)
      for (int i = 0; i < padding; i++) *str++ = ' ';

    for (int i = 0; i < len; i++) *str++ = null_str[i];

    if (spec.minus)
      for (int i = 0; i < padding; i++) *str++ = ' ';

  } else {
    // Указатель не NULL
    unsigned long int address = (unsigned long int)ptr;
    spec.number_system = 16;
    spec.sharp = 1;

    s21_size_t ptr_size = get_hex_size(&spec, address);
    char *buf = calloc(ptr_size + 1, sizeof(char));
    if (buf) {
      int i = hex_to_str(buf, spec, address, 'x');
      for (int j = i - 1; j >= 0; j--) *str++ = buf[j];
      free(buf);
    }
  }

  return str;
}
