#include "s21_sscanf.h"

int s21_sscanf(const char *str, const char *fmt, ...) {
  int assigned = 0;

  if (*str == '\0' && *fmt != '\0') assigned = -1;

  SpecBlock spec_block = {0, 0};  // Хранит строку-блок спецификатора
  Config config = {0, 0,  0, 0,
                   0, str};  // Хранит данные спецификатора и служебные данные

  if (validate_params(str, fmt)) {
    s21_size_t fmt_len = s21_strlen(fmt);
    spec_block.preceding_str = (char *)malloc(sizeof(char) * (fmt_len + 1));
    spec_block.specifier = (char *)malloc(sizeof(char) * (fmt_len + 1));
  }

  if (spec_block.preceding_str && spec_block.specifier) {
    char *current_fmt = (char *)fmt;
    char *current_str = (char *)str;
    va_list args;
    va_start(args, fmt);

    while (*current_fmt != '\0' &&
           get_specifier(&current_fmt, &spec_block, &config) == 0) {
      if (match_specifier(&current_str, &args, &spec_block, &config)) {
        assigned++;
      }

      // Обновление конфигурации
      config.suppress_assignment = false;
      config.width = 0;
      config.length1 = 0;
      config.length2 = 0;
      config.specifier = 0;
      // Очищаем буферы
      spec_block.preceding_str[0] = '\0';
      spec_block.specifier[0] = '\0';
    }

    va_end(args);
  }

  if (spec_block.preceding_str) free(spec_block.preceding_str);
  if (spec_block.specifier) free(spec_block.specifier);

  return assigned;
}

// Проверка валидности входных данных на равенство нулю
int validate_params(const char *str, const char *fmt) {
  return (fmt != S21_NULL && *fmt != '\0' && str != S21_NULL && *str != '\0');
}

// Парсит блок спецификатора вида [специальные и неспециальные
// символы]%[*][ширина][длина]спецификатор и заполняет spec_block
int get_specifier(char **cur_fmt_ptr, SpecBlock *spec_block, Config *config) {
  int return_code = 0;
  int found_specifier = 0;

  char *preceding_ptr = spec_block->preceding_str;
  char *specifier_ptr = spec_block->specifier;
  char *temp_fmt = *cur_fmt_ptr;
  char *temp_preceding = preceding_ptr;
  // Идем до первого знака "%"
  while (*temp_fmt != '\0' && !found_specifier) {
    int is_escaped_percent = 0;
    // Проверяем, является ли следующий знак процентом
    if (*temp_fmt == '%') {
      is_escaped_percent = (*(temp_fmt + 1) == '%');
    }
    // Если да, то пропускаем оба "%"
    if (is_escaped_percent) {
      *temp_preceding = '%';
      temp_preceding++;
      temp_fmt += 2;
    } else if (*temp_fmt == '%') {  // Если знак "%" один - это начало
                                    // спецификатора; поднимаем флаг
      temp_fmt++;
      *specifier_ptr = '%';
      specifier_ptr++;
      found_specifier = 1;
    } else {
      *temp_preceding = *temp_fmt;
      temp_preceding++;
      temp_fmt++;
    }
  }
  // Закрытие строки
  *temp_preceding = '\0';
  // Если нашли "%", за которым нет ещё одного "%" - парсим спецификатор
  if (found_specifier) {
    return_code = parse_specifier_components(&temp_fmt, &specifier_ptr, config);
    if (return_code == 0)
      *cur_fmt_ptr = temp_fmt;  // Обновление указателя на строку формата
  } else
    *cur_fmt_ptr = temp_fmt;

  return return_code;
}

// Парсит символы спецификатора после "%", заполняет конфигурацию config
int parse_specifier_components(char **fmt_ptr, char **specifier_ptr,
                               Config *config) {
  int return_code = 0;
  char *fmt = *fmt_ptr;
  char *spec = *specifier_ptr;

  if (*fmt == '*') {  // Подавление присваивания
    *spec = '*';
    spec++;
    fmt++;
    config->suppress_assignment = true;
  }
  if (is_digit(*fmt)) {  // Ширина
    char width_str[16] = {0};
    int i = 0;
    while (is_digit(*fmt) && i < 15) {
      width_str[i++] = *fmt;
      *spec = *fmt;
      spec++;
      fmt++;
    }
    config->width = s21_strtoi(width_str);  // Переводим ширину в число
  }
  // Длина
  if (*fmt == 'h' || *fmt == 'l' || *fmt == 'L') {
    config->length1 = *fmt;
    *spec = *fmt;
    spec++;
    fmt++;
    if ((*(fmt - 1) == 'h' && *fmt == 'h') ||
        (*(fmt - 1) == 'l' && *fmt == 'l')) {
      config->length2 = *fmt;
      *spec = *fmt;
      spec++;
      fmt++;
    }
  }
  // Спецификатор
  if (is_specifier_char(*fmt)) {
    config->specifier = *fmt;
    *spec = *fmt;
    spec++;
    fmt++;
    *spec = '\0';
  } else
    return_code = 1;
  // Обновление указателей на строки
  *fmt_ptr = fmt;
  *specifier_ptr = spec;

  return return_code;
}

// Сопоставляет обычный текст перед спецификатором и вызывает обработку
// спецификатора
int match_specifier(char **current_str, va_list *args, SpecBlock *spec_block,
                    Config *config) {
  int assigned = 0;
  char *current_pos = *current_str;
  bool over = false;

  // Обработка preceding_str
  const char *preceding = spec_block->preceding_str;
  while (!over && *preceding != '\0') {
    if (is_special_char(*preceding)) {
      while (is_special_char(*current_pos)) {
        current_pos++;
      }
    } else {
      if (*current_pos != *preceding) {
        over = true;
      }
      current_pos++;
    }
    preceding++;
  }

  // Обработка спецификатора (если все символы до спецификатора совпали)
  if (!over && config->specifier != 0) {
    const char *new_pos = current_pos;
    assigned = process_specifier(current_pos, args, config, &new_pos);
    *current_str = (char *)new_pos;  // Обновление внешнего указателя
  } else {
    *current_str = current_pos;
  }

  return assigned;
}

// Диспетчер спецификаторов - вызывает нужный исходя из конфигурации
bool process_specifier(const char *str, va_list *args, Config *config,
                       const char **new_pos) {
  bool assigned = false;
  const char *current = str;
  // Пропускаем ведущие пробелы для большинства спецификаторов
  if (config->specifier != 'c' && config->specifier != 'n') {
    while (is_special_char(*current)) {
      current++;
    }
  }

  if (*current != '\0' || config->specifier == 'n') {
    switch (config->specifier) {
      case 'd':
        assigned = parse_decimal(current, args, config, new_pos);
        break;
      case 'i':
        assigned = parse_integer(current, args, config, new_pos);
        break;
      case 'u':
      case 'o':
      case 'x':
      case 'X':
        assigned = parse_unsigned(current, args, config, new_pos, 1);
        break;
      case 'c':
        assigned = parse_char(current, args, config, new_pos);
        break;
      case 's':
        assigned = parse_string(current, args, config, new_pos);
        break;
      case 'f':
      case 'e':
      case 'E':
      case 'g':
      case 'G':
        assigned = parse_float(current, args, config, new_pos);
        break;
      case 'p':
        assigned = parse_pointer(current, args, config, new_pos);
        break;
      case 'n':
        assigned = parse_chars_count(str, args, config, new_pos);
        break;
    }
  }

  return assigned;
}

// Парсинг целых чисел
bool parse_decimal(const char *str, va_list *args, Config *config,
                   const char **new_pos) {
  const char *current = str;
  long long value = 0;
  int sign = 1;
  int digits = 0;
  int result = true;

  // Знак
  if (*current == '-') {
    sign = -1;
    current++;
    digits++;
  } else if (*current == '+') {
    current++;
    digits++;
  }
  // Парсинг числа
  while (is_digit(*current) && (config->width == 0 || digits < config->width)) {
    value = value * 10 + (*current - '0');
    current++;
    digits++;
  }
  // Присваивание результата по адресу из va_list
  if (digits > 0) {
    value *= sign;
    if (config->suppress_assignment == 0) {
      if (config->length1 == 'h' && config->length2 == 'h') {
        signed char *ptr = va_arg(*args, signed char *);
        *ptr = (signed char)value;
      } else if (config->length1 == 'h') {
        short *ptr = va_arg(*args, short *);
        *ptr = (short)value;
      } else if (config->length1 == 'l' && config->length2 == 'l') {
        long long *ptr = va_arg(*args, long long *);
        *ptr = value;
      } else if (config->length1 == 'l') {
        long *ptr = va_arg(*args, long *);
        *ptr = (long)value;
      } else {
        int *ptr = va_arg(*args, int *);
        *ptr = (int)value;
      }
    } else
      result = false;
  } else
    result = false;
  *new_pos = current;

  return result;
}

// Парсинг символов
bool parse_char(const char *str, va_list *args, Config *config,
                const char **new_pos) {
  bool result = true;

  if (!config->suppress_assignment) {
    if (config->length1 == 'l') {
      wchar_t *ptr = va_arg(*args, wchar_t *);
      if (config->width > 0) {
        for (int i = 0; i < config->width && *str != '\0'; ++i)
          *ptr++ = (wchar_t)(unsigned char)*str++;
      } else {
        *ptr = (wchar_t)(unsigned char)*str++;
      }

    } else {
      char *ptr = va_arg(*args, char *);
      if (config->width > 0) {
        for (int i = 0; i < config->width && *str != '\0'; ++i)
          *(ptr++) = *(str++);
      } else {
        *ptr = *(str++);
      }
    }
  } else {
    result = false;
    if (config->width > 0) {
      for (int i = 0; i < config->width && *str != '\0'; ++i) str++;
    } else
      str++;
  }

  *new_pos = str;

  return result;
}

// Парсинг строк
bool parse_string(const char *str, va_list *args, Config *config,
                  const char **new_pos) {
  const char *current = str;
  int chars_copied = 0;
  bool result = false;

  union {
    char *char_ptr;
    wchar_t *wchar_ptr;
  } write_ptr = {S21_NULL};

  if (config->suppress_assignment == 0) {
    if (config->length1 == 'l') {
      write_ptr.wchar_ptr = va_arg(*args, wchar_t *);
    } else {
      write_ptr.char_ptr = va_arg(*args, char *);
    }
  }

  while (*current != '\0' && is_special_char(*current) == 0 &&
         (config->width == 0 || chars_copied < config->width)) {
    if (config->suppress_assignment == 0) {
      if (config->length1 == 'l') {
        *write_ptr.wchar_ptr++ = (wchar_t)(unsigned char)*current;
      } else {
        *write_ptr.char_ptr++ = *current;
      }
      chars_copied++;
      result = true;
    } else {
      chars_copied++;
    }
    current++;
  }

  if (config->suppress_assignment == 0) {
    if (config->length1 == 'l') {
      *write_ptr.wchar_ptr = L'\0';
    } else {
      *write_ptr.char_ptr = '\0';
    }
  }

  *new_pos = current;
  return result;
}

// Парсинг беззнаковых чисел
bool parse_unsigned(const char *str, va_list *args, Config *config,
                    const char **new_pos, int sign) {
  const char *current = str;
  unsigned long long value = 0;
  int digits = 0, base = 10;
  bool result = true;

  if (config->specifier == 'o') {  // Определяем систему счисления
    base = 8;
  } else if (config->specifier == 'x' || config->specifier == 'X') {
    // Пропускаем "0x" или "0X" если есть
    if (current[0] == '0' && (current[1] == 'x' || current[1] == 'X')) {
      current += 2;
    }
    base = 16;
  }
  // Чтение цифр
  while (is_valid_digit(*current, base) &&
         (config->width == 0 || digits < config->width)) {
    value = value * base + get_digit_value(*current);
    current++;
    digits++;
  }
  // Присваивание результата по адресу из va_list
  if (digits > 0) {
    value *= sign;
    if (config->suppress_assignment == 0) {
      if (config->length1 == 'h' && config->length2 == 'h') {
        unsigned char *ptr = va_arg(*args, unsigned char *);
        *ptr = (unsigned char)value;
      } else if (config->length1 == 'h') {
        unsigned short *ptr = va_arg(*args, unsigned short *);
        *ptr = (unsigned short)value;
      } else if (config->length1 == 'l' && config->length2 == 'l') {
        unsigned long long *ptr = va_arg(*args, unsigned long long *);
        *ptr = value;
      } else if (config->length1 == 'l') {
        unsigned long *ptr = va_arg(*args, unsigned long *);
        *ptr = (unsigned long)value;
      } else {
        unsigned int *ptr = va_arg(*args, unsigned int *);
        *ptr = (unsigned int)value;
      }
    } else
      result = false;
  } else
    result = false;
  *new_pos = current;

  return result;
}

// Парсинг целых чисел
bool parse_integer(const char *str, va_list *args, Config *config,
                   const char **new_pos) {
  bool result = false;
  const char *current = str;
  int sign = 1;

  // Знак
  if (*current == '-') {
    sign = -1;
    current++;
  } else if (*current == '+') {
    current++;
  }
  // Определение системы счисления
  if (*current == '0') {
    current++;
    if (*current == 'x' || *current == 'X') {
      // Шестнадцатеричное
      current++;
      config->specifier = 'x';
    } else {
      // Восьмеричное
      config->specifier = 'o';
    }
  } else {
    // Десятичное
    config->specifier = 'd';
  }

  if (config->specifier) {
    result = parse_unsigned(current, args, config, new_pos, sign);
  }

  return result;
}
// Парсинг чисел с плавающей запятой
bool parse_float(const char *str, va_list *args, Config *config,
                 const char **new_pos) {
  bool result = false;
  long double value = 0, p = 10.0L;
  ;
  double sign = 1.0;
  int digits = 0;
  sign = parse_sign(&str);
  while (*str != '\0' && is_digit(*str) &&
         (config->width == 0 || digits < config->width)) {  // Целая часть
    value = value * 10.0L + (*str++ - '0');
    digits++;
  }
  if (*str == '.') {  // Точка
    str++;
    digits++;
  }
  while (*str != '\0' && is_digit(*str) &&
         (config->width == 0 || digits < config->width)) {  // Дробная часть
    value += (*str++ - '0') / p;
    p *= 10.0L;
    digits++;
  }
  if (*str == 'E' || *str == 'e') {  // E e
    int exponent = 0;
    int exp_sign = 1.0;
    str++;
    exp_sign = parse_sign(&str);
    while (*str != '\0' && is_digit(*str) &&
           (config->width == 0 || digits < config->width)) {  // Научная нотация
      exponent = exponent * 10 + (*str++ - '0');
      digits++;
    }
    value *= powl(10.0L, exp_sign * exponent);
  }
  value *= sign;
  if (config->suppress_assignment == 0 && digits > 0) {
    if (config->length1 == 'L') {
      long double *ptr = va_arg(*args, long double *);
      *ptr = value;
    } else if (config->length1 == 'l') {
      double *ptr = va_arg(*args, double *);
      *ptr = (double)value;
    } else {
      float *ptr = va_arg(*args, float *);
      *ptr = (float)value;
    }
    result = true;
  }
  *new_pos = str;
  return result;
}

double parse_sign(const char **str_ptr) {
  double sign = 1.0;
  if (**str_ptr == '-') {
    sign = -1.0;
    (*str_ptr)++;
  } else if (**str_ptr == '+') {
    (*str_ptr)++;
  }
  return sign;
}

// Парсинг адреса
bool parse_pointer(const char *str, va_list *args, Config *config,
                   const char **new_pos) {
  const char *current = str;
  uintptr_t value = 0;
  int digits = 0;
  bool result = false;

  // Пропускаем "0x" если есть
  if (current[0] == '0' && (current[1] == 'x' || current[1] == 'X')) {
    current += 2;
    digits += 2;
  }

  // Чтение шестнадцатеричного числа
  while (is_hex_digit(*current) &&
         (config->width == 0 || digits < config->width)) {
    value = value * 16 + get_digit_value(*current);
    current++;
    digits++;
  }

  if (digits > 0) {
    if (!config->suppress_assignment) {
      void **ptr = va_arg(*args, void **);
      *ptr = (void *)value;
      result = true;
    }
    *new_pos = current;
  }

  return result;
}

// Подсчет символов, предшествующих "%n"
bool parse_chars_count(const char *str, va_list *args, Config *config,
                       const char **new_pos) {
  if (!config->suppress_assignment) {
    int *count_ptr = va_arg(*args, int *);
    *count_ptr =
        str - config->begin_of_str_ptr;  // Количество обработанных символов
  }
  *new_pos =
      str;  // Не продвигаем указатель, потому что %n не потребляет символы
  return false;
}

// Проверка на число
bool is_digit(char c) { return (c >= '0' && c <= '9'); }

// Проверка на символ спецификатора
bool is_specifier_char(char c) {
  bool result = false;
  static char *specifiers = "cdieEfgGosuxXpn";
  int i = 0;

  while (specifiers[i] != '\0' && result == false) {
    if (c == specifiers[i]) {
      result = true;
    }
    i++;
  }

  return result;
}

// Проверка на специальные символы
// (пробел, таб, перевод строки, вовзрат каретки, вертикальный таб, перевод на
// новую строку)
bool is_special_char(char c) {
  return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v' ||
          c == '\f');
}

s21_size_t s21_strtoi(const char *str) {
  s21_size_t result = 0;

  while (is_digit(*str)) {
    result = result * 10 + (*str - '0');
    str++;
  }

  return result;
}

// Проверка валидности цифры для данной системы счисления
bool is_valid_digit(char c, int base) {
  bool result = false;

  if (base == 10) result = is_digit(c);
  if (base == 8) result = (c >= '0' && c <= '7');
  if (base == 16) result = is_hex_digit(c);

  return result;
}

// Проверка шестнадцатеричной цифры
bool is_hex_digit(char c) {
  return is_digit(c) || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F');
}

// Получение значения цифры
int get_digit_value(char c) {
  int result = 0;

  if (c >= '0' && c <= '9') result = c - '0';
  if (c >= 'a' && c <= 'f') result = c - 'a' + 10;
  if (c >= 'A' && c <= 'F') result = c - 'A' + 10;

  return result;
}
