#ifndef S21_STRTOK
#define S21_STRTOK

#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200809L
#endif

#define S21_NULL ((void *)0)

char *s21_strtok(char *str, const char *delim);

#endif  // S21_STRTOK