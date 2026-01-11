#include "s21_strtok.h"

// функция поиска разделителя в строке
static int delim_search(char** last_ptr, const char* delim, int is_start) {
  int flag = 0;
  int end_cycle = 1;  // Флаг для завершения цикла while
  while (**last_ptr != '\0' && end_cycle) {
    int is_delim = 0;  // флаг, есть ли разделитель в строке
    // идем по массиву разделителей пока не будет совпадения
    for (const char* d = delim; *d != '\0' && !is_delim; d++) {
      // если есть совпадение, меняем флаг на 1
      if (**last_ptr == *d) {
        is_delim = 1;
      }
    }
    if ((is_start) ? (!is_delim) : (is_delim)) {
      end_cycle = 0;
    } else {
      (*last_ptr)++;
    }
    // если это начало строки, то если нет совпадения - выходим из цикла; если
    // это продолжение строки, то если есть совпадение - выходим из цикла. а
    // иначе двигаемся дальше по строке
  }
  flag = (**last_ptr == '\0') ? 1 : 0;
  return flag;
}

char* s21_strtok(char* str, const char* delim) {
  char* start_ptr = S21_NULL;
  static char* last_ptr = S21_NULL;
  // static - Сохраняет свое значение между вызовами функции,
  // Не видна outside функции,
  // Инициализируется только один раз при первом вызове
  if (str != S21_NULL) {  // если передаем новую строку
    last_ptr = str;
  }
  if (last_ptr == S21_NULL ||
      *last_ptr == '\0') {  // если нет указателя или строка закончилась
    start_ptr = S21_NULL;
  } else {
    int is_start = 1;  // флаг начала строки
    int flag = 0;
    flag = delim_search(&last_ptr, delim, is_start);
    // проверяем начало строки, чтобы пропустить
    // разделители в начале

    start_ptr = (flag == 0) ? last_ptr : S21_NULL;
    // проверям, если вся строка - это разделители,
    // то возвращаем S21_NULL, иначе начинаем поиск с
    // того места, где остановились

    is_start = 0;
    delim_search(&last_ptr, delim, is_start);
    if (*last_ptr != '\0') {
      *last_ptr = '\0';  // присваивам конец строки токену
      last_ptr++;  // сдвигаемся на следующий символ
    } else {
      last_ptr = S21_NULL;  // если закончилась строка
    }
  }

  return start_ptr;
}
