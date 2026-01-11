#include "s21_string.h"

// Вычисляет длину строки str, не включая завершающий нулевой символ.
s21_size_t s21_strlen(const char *str) {
  s21_size_t count = 0;

  while (*str != '\0') {
    str++;
    count++;
  }

  return count;
}
// создаем переменную которая будет отвечать за результат, в цикле перебираем
// входящую строчку пока не достигним конца при этом после каждого символа
// добавляем к длине одну единицу, когда достигним конца возвращаем результат.

// Находит первое вхождение всей строки needle (не включая завершающий нулевой
// символ), которая появляется в строке haystack.
char *s21_strstr(const char *haystack, const char *needle) {
  char *result = S21_NULL;
  int flag_search = 0;

  if (*haystack == '\0' && *needle == '\0') {
    result = (char *)haystack;
  }

  while (*haystack != '\0' && flag_search == 0) {
    const char *temp_haystack = haystack;
    const char *temp_needle = needle;

    while (*temp_needle != '\0' && *temp_haystack == *temp_needle) {
      temp_haystack++;
      temp_needle++;
    }

    if (*temp_needle == '\0') {
      result = (char *)haystack;
      flag_search = 1;
    }

    haystack++;
  }

  return result;
}
// создаем указатель для хранения результата и флаг для выхода из цикла при
// нахождении строки,  проверяем не является искомая строка пустой, если да -
// вызвращаем ссылку на начало строки, если нет - начинаем поиск. запускаем цикл
// поиска до конца оригинальной строки и пока флаг поиска не поменяем значение
// создаем копии строк оригинала и искомой. Запускаем второй цикл поиска пока не
// дойдем до конца копии и пока символы в строках одинаковые, если условия
// совпадают двигаемся по строкам. если дошли до конца искомой строки помещаем в
// результат ссылку на символ где мы находимся и переключаем флаг на значение
// что нашли. Переходим на второй символ если нужно.

//  Копирует до n символов из строки, на которую указывает src, в dest.
char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  char *result = dest;

  while (n > 0 && *src != '\0') {
    *dest = *src;
    n--;
    dest++;
    src++;
  }

  while (n > 0) {
    *dest = '\0';
    dest++;
    n--;
  }

  return result;
}
//  сохраняем ссылку на начало строки, проверяем если ли символы в строке с
//  которой мы будем копировать данные, если нету возвращаем NULL если есть -
//  создаем цикл в котором будем копировать данные пока не дойдем до конца
//  строки или не закончится цыфра количества символов, если строка закончилась
//  быстрее - все остальное пространство заполняем '\0', возвращаем ссылку на
//  начало строки.

//  Находит первый символ в строке str1, который соответствует любому символу,
//  указанному в str2.
char *s21_strpbrk(const char *str1, const char *str2) {
  const char *result = S21_NULL;
  int flag_search = 0;

  while (*str1 != '\0' && flag_search == 0) {
    const char *temp_str2 = str2;

    while (*temp_str2 != '\0' && flag_search == 0) {
      if (*str1 == *temp_str2) {
        result = str1;
        flag_search = 1;
      } else {
        temp_str2++;
      }
    }

    str1++;
  }

  return (char *)result;
}
// создаем контейнер для хранения рузельтата и флаг что символ найден, запускаем
// первый цикл который пойдет по символам первой строки до конца строки или пока
// не будет найдем символ создаем копию второй строки, запускаем второй цикл
// который будет двигатся по копии искомой строки и пока флаг поиска равен 0,
// создаем условия в котором будем сравнивать символ первой строки с поочередне
// сменяющими символами сторой строки, если символ найден - переключаем флаг и
// записываем в результат ссылку на найденный символ в искомой строке если
// символ не найдем двигаемся дальше по строке 2 а потом и по строке 1.

// Выполняет поиск последнего вхождения символа c (беззнаковый тип) в строке, на
// которую указывает аргумент str
char *s21_strrchr(const char *str, int c) {
  const char *result = S21_NULL;

  if (str != S21_NULL) {
    while (*str != '\0') {
      if (*str == c) {
        result = str;
      }
      str++;
    }

    if (*str == c) {
      result = str;
    }
  }

  return (char *)result;
}
// создаем переменную которую будет возвращать функция, проверяем существует ли
// строка в которой будем искать символ, по окончанию поиска в строке проверяем
// является символ поиска концом строки, если да записиваем его как результат,
// возвращяем рузельтат

char *s21_strchr(const char *str, int c) {
  int is_match = 0;
  const char *ptr = str;
  if (str != S21_NULL) {
    while (*ptr != '\0' && *ptr != c) {
      ptr++;
    }
    if (*ptr == c || c == '\0') {
      is_match = 1;
    }
  }

  return (is_match) ? (char *)ptr : S21_NULL;
}

s21_size_t s21_strcspn(const char *string1, const char *string2) {
  int found = 0;
  s21_size_t str1_len = s21_strlen(string1);
  s21_size_t str2_len = s21_strlen(string2);
  s21_size_t position = 0;

  while (!found && position < str1_len) {
    s21_size_t j = 0;
    while (!found && j < str2_len) {
      if (string1[position] == string2[j]) {
        found = 1;
      } else {
        j++;
      }
    }

    if (!found) {
      position++;
    }
  }

  return position;
}

void *s21_memchr(const void *str, int c, s21_size_t n) {
  const unsigned char *line = (const unsigned char *)str;
  unsigned char search_symbol = (unsigned char)c;
  void *result = S21_NULL;

  if (str != S21_NULL) {
    int flag = 0;
    for (s21_size_t i = 0; i < n && !flag; i++) {
      if (line[i] == search_symbol && result == S21_NULL) {
        result = (void *)(line + i);
        flag = 1;
      }
    }
  }
  return result;
}

int s21_memcmp(const void *s1, const void *s2, s21_size_t n) {
  const unsigned char *p1 = (const unsigned char *)s1;
  const unsigned char *p2 = (const unsigned char *)s2;
  int result = 0;
  int flag = 0;

  for (s21_size_t i = 0; i < n && !flag; i++) {
    if (p1[i] != p2[i]) {
      result = (int)(p1[i] - p2[i]);
      flag = 1;
    }
  }

  return result;
}
//  0 если равны
//  -1 если s1 < s2
//  1 если s1 > s2
//  сравниваем результат посимвольно, если битовое число 1 меньше битового числа
//  2 возвращаем (-1), если больше - (1), если они равны оставляем результат 0,
//  если в какой то момент информация разнится перестаем сравнвать и заканчиваем
//  цикл,
// результат возващаем в зависимости от ситуации, если дошли до n-символа и они
// равни возвращаем флаг 0

//  Копирует n символов из src в dest.
void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  unsigned char *line_copy = dest;
  const unsigned char *line_orig = src;

  for (s21_size_t i = 0; i < n; i++) {
    line_copy[i] = line_orig[i];
  }

  return dest;
}
//   unsigned char *lineOrig = src, unsigned char *lineCopy = dest - привели к
//   формату char для побайтового копирования в цикле копируем байти информации
//   из оригинальной строки в нужную возвращаем нужную строку

// Копирует символ c (беззнаковый тип) в первые n символов строки, на которую
// указывает  аргумент str.
void *s21_memset(void *str, int c, s21_size_t n) {
  unsigned char *line = str;
  unsigned char copy_symbol = (unsigned char)c;

  for (s21_size_t i = 0; i < n; i++) {
    line[i] = copy_symbol;
  }

  return str;
}

//  Добавляет строку, на которую указывает src, в конец строки, на которую
//  указывает dest, длиной до n символов.
char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  char *result = dest;

  while (*dest != '\0') {
    dest++;
  }

  while (n > 0 && *src != '\0') {
    *dest = *src;
    dest++;
    src++;
    n--;
  }

  *dest = '\0';

  return result;
}

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  int result = 0;
  int flag = 0;

  while (!flag && n > 0 && result == 0) {
    unsigned char c1 = (unsigned char)*str1;
    unsigned char c2 = (unsigned char)*str2;

    if (c1 != c2) {
      result = (int)(c1 - c2);
    } else if (c1 == '\0') {
      flag = 1;  // Строки совпали до конца — результат остаётся 0
    }

    str1++;
    str2++;
    n--;
  }

  return result;
}

// Выполняет поиск во внутреннем массиве номера ошибки errnum и возвращает
// указатель на строку с сообщением об ошибке.
char *s21_strerror(int errnum) {
  char *result = S21_NULL;
  static char unknown[25];

  if ((errnum != 41) && (errnum != 58) &&
      (errnum >= 0 && errnum < ERRLISTSIZE)) {
    const char *error_array[] = ERROR_MESSAGES;
    // * по индексам 41 и 58 в массиве ошибок отстуствуют какие-либо ошибки
    result = (char *)error_array[errnum];
  } else {
    s21_sprintf(unknown, "Unknown error %d", errnum);
    result = unknown;
  }

  return result;
}
//  создали файл для хранения массива всех возможный ошибок, в зависимости от
//  платформы с названием - strerrorLib.h, создали переменную для хранения
//  результата, инициализировали массив ошибок, определили, известна нам ошибка
//  или нет, если известна - возвращаем строку ошибки, ели нет - возвращаем
//  фразу что ошибка с таким номером нам неизвестна.

void *s21_to_upper(const char *str) {
  char *result = S21_NULL;

  if (str != S21_NULL) {
    size_t len = s21_strlen(str);
    result = malloc(len + 1);

    if (result != S21_NULL) {
      char *p = result;
      for (size_t i = 0; i < len; i++) {
        if (str[i] >= 'a' && str[i] <= 'z')
          *p = str[i] - 32;
        else
          *p = str[i];
        p++;
      }
      *p = '\0';
    }
  }

  return result;
}

void *s21_to_lower(const char *str) {
  char *result = S21_NULL;

  if (str != S21_NULL) {
    size_t len = s21_strlen(str);
    result = malloc(len + 1);

    if (result != S21_NULL) {
      char *p = result;
      for (size_t i = 0; i < len; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z')
          *p = str[i] + 32;
        else
          *p = str[i];
        p++;
      }
      *p = '\0';
    }
  }

  return result;
}

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  if (src == S21_NULL || str == S21_NULL) {
    return S21_NULL;
  }

  char *result = S21_NULL;
  s21_size_t src_len = s21_strlen(src);
  s21_size_t str_len = s21_strlen(str);

  if (start_index <= src_len) {
    s21_size_t size_result = src_len + str_len + 1;
    result = (char *)calloc(size_result, sizeof(char));

    if (result != S21_NULL) {
      char *src_tmp = (char *)src;
      char *str_tmp = (char *)str;

      char *result_ptr = result;

      s21_size_t i = 0;
      while (*src_tmp != '\0' && i < start_index) {
        *result_ptr = *src_tmp;
        result_ptr++;
        src_tmp++;
        i++;
      }
      for (i = 0; i < str_len; i++) {
        *result_ptr = *str_tmp;
        result_ptr++;
        str_tmp++;
      }
      while (*src_tmp != '\0') {
        *result_ptr = *src_tmp;
        result_ptr++;
        src_tmp++;
      }

      *result_ptr = '\0';
    }
  }

  return (void *)result;
}
// вставляем строку str в строку  src под индексом start_index
// создаем переменную результат которую инициализируем MY_NULL, проверяем не
// пустие ли входящии строки, узнаем длину сходящих строк, проверяем не выходит
// ли индекс вставки за пределы размера строки в которую будем вставлять, узнаем
// длину строки результата, выделяем память под новую строчку, проверяем
// выделилась ли память, вставляем в рузельтат количество символов до места
// вставки из первичной строки, обьеденяем строку результата в вставкий,
// обьеденяем строку резульата с остатком первичной строки.

void *s21_trim(const char *src, const char *trim_chars) {
  if (src == S21_NULL) {
    return S21_NULL;
  }

  const char *start_index = src;
  const char *end_index = src + s21_strlen(src) - 1;
  int error = 0;
  while (*start_index && trim_chars != S21_NULL &&
         s21_strchr(trim_chars, *start_index) != S21_NULL) {
    start_index += 1;
  }

  while (end_index > start_index && trim_chars != S21_NULL &&
         s21_strchr(trim_chars, *end_index) != S21_NULL) {
    end_index -= 1;
  }

  s21_size_t result_len =
      (end_index >= start_index) ? (end_index - start_index + 1) : 0;
  char *result = (char *)malloc(result_len + 1);
  if (result == S21_NULL) error = 1;

  if (!error) {
    if (result_len > 0) {
      s21_strncpy(result, start_index, result_len);
    }
    result[result_len] = '\0';
  }

  return (char *)result;
}