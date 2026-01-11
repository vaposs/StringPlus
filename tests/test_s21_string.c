#include <check.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <wchar.h>

#include "../src/s21_sprintf.h"
#include "../src/s21_sscanf.h"
#include "../src/s21_string.h"
#include "../src/s21_strtok.h"

/////////////////////////////
///// s21_strerror TESTS ///
///////////////////////////
START_TEST(errors_usual) {
  char *message_my;
  char *message_orig;
  for (int errnum = 0; errnum < ERRLISTSIZE; ++errnum) {
    message_my = s21_strerror(errnum);
    message_orig = strerror(errnum);
    ck_assert_str_eq(message_my, message_orig);
  }
}
END_TEST

START_TEST(errors_unknown) {
  char *message_my;
  char *message_orig;
  message_my = s21_strerror(1000);
  message_orig = strerror(1000);
  ck_assert_str_eq(message_my, message_orig);
}
END_TEST

/////////////////////////////
///// s21_strpbrk TESTS ////
///////////////////////////
START_TEST(strpbrk_usual) {
  char s1[] = "Some text, containig word hello.";
  char s2[] = "egg";
  ck_assert_str_eq(s21_strpbrk(s1, s2), strpbrk(s1, s2));
}
END_TEST

START_TEST(strpbrk_empty_search) {
  char s1[] = "Some text";
  char s2[] = "";
  ck_assert_ptr_eq(s21_strpbrk(s1, s2), strpbrk(s1, s2));
}
END_TEST

START_TEST(strpbrk_empty_string) {
  char s1[] = "";
  char s2[] = "abc";
  ck_assert_ptr_eq(s21_strpbrk(s1, s2), strpbrk(s1, s2));
}
END_TEST

START_TEST(strpbrk_both_empty) {
  char s1[] = "";
  char s2[] = "";
  ck_assert_ptr_eq(s21_strpbrk(s1, s2), strpbrk(s1, s2));
}
END_TEST

START_TEST(strpbrk_no_match) {
  char s1[] = "Hello world";
  char s2[] = "xyz";
  ck_assert_ptr_eq(s21_strpbrk(s1, s2), strpbrk(s1, s2));
}
END_TEST

START_TEST(strpbrk_first_char_match) {
  char s1[] = "Hello world";
  char s2[] = "H";
  ck_assert_str_eq(s21_strpbrk(s1, s2), strpbrk(s1, s2));
}
END_TEST

START_TEST(strpbrk_middle_match) {
  char s1[] = "Hello world";
  char s2[] = "o";
  ck_assert_str_eq(s21_strpbrk(s1, s2), strpbrk(s1, s2));
}
END_TEST

START_TEST(strpbrk_multiple_chars) {
  char s1[] = "Hello world";
  char s2[] = "dw";
  ck_assert_str_eq(s21_strpbrk(s1, s2), strpbrk(s1, s2));
}
END_TEST

START_TEST(strpbrk_with_spaces) {
  char s1[] = "Hello world";
  char s2[] = " ";
  ck_assert_str_eq(s21_strpbrk(s1, s2), strpbrk(s1, s2));
}
END_TEST

START_TEST(strpbrk_special_chars) {
  char s1[] = "Hello, world!";
  char s2[] = ",!";
  ck_assert_str_eq(s21_strpbrk(s1, s2), strpbrk(s1, s2));
}
END_TEST

START_TEST(strpbrk_numbers) {
  char s1[] = "test123string";
  char s2[] = "321";
  ck_assert_str_eq(s21_strpbrk(s1, s2), strpbrk(s1, s2));
}
END_TEST

START_TEST(strpbrk_null_chars) {
  char s1[] = "Hello\0world";
  char s2[] = "w";
  ck_assert_ptr_eq(s21_strpbrk(s1, s2), strpbrk(s1, s2));
}
END_TEST

START_TEST(strpbrk_duplicate_chars) {
  char s1[] = "Hello world";
  char s2[] = "lll";
  ck_assert_str_eq(s21_strpbrk(s1, s2), strpbrk(s1, s2));
}
END_TEST

/////////////////////////////
///// s21_strrchr TESTS ////
///////////////////////////
START_TEST(strrchr_usual) {
  char str[] = "Text, which contains words such as apple banana arbuz";
  char c = 'b';
  ck_assert_str_eq(s21_strrchr(str, c), strrchr(str, c));
}
END_TEST

START_TEST(strrchr_first_char) {
  char str[] = "Hello world";
  char c = 'H';
  ck_assert_str_eq(s21_strrchr(str, c), strrchr(str, c));
}
END_TEST

START_TEST(strrchr_last_char) {
  char str[] = "Hello world";
  char c = 'd';
  ck_assert_str_eq(s21_strrchr(str, c), strrchr(str, c));
}
END_TEST

START_TEST(strrchr_middle_char) {
  char str[] = "Hello world";
  char c = 'o';
  ck_assert_str_eq(s21_strrchr(str, c), strrchr(str, c));
}
END_TEST

START_TEST(strrchr_multiple_occurrences) {
  char str[] = "Hello world, welcome to programming";
  char c = 'o';
  ck_assert_str_eq(s21_strrchr(str, c), strrchr(str, c));
}
END_TEST

START_TEST(strrchr_not_found) {
  char str[] = "Hello world";
  char c = 'z';
  ck_assert_ptr_eq(s21_strrchr(str, c), strrchr(str, c));
}
END_TEST

START_TEST(strrchr_empty_string) {
  char str[] = "";
  char c = 'a';
  ck_assert_ptr_eq(s21_strrchr(str, c), strrchr(str, c));
}
END_TEST

START_TEST(strrchr_null_byte) {
  char str[] = "Hello world";
  char c = '\0';
  ck_assert_str_eq(s21_strrchr(str, c), strrchr(str, c));
}
END_TEST

START_TEST(strrchr_null_byte_empty) {
  char str[] = "";
  char c = '\0';
  ck_assert_str_eq(s21_strrchr(str, c), strrchr(str, c));
}
END_TEST

START_TEST(strrchr_special_chars) {
  char str[] = "Hello, world!\n\t";
  char c = '\t';
  ck_assert_str_eq(s21_strrchr(str, c), strrchr(str, c));
}
END_TEST

START_TEST(strrchr_numbers) {
  char str[] = "test123456789";
  char c = '5';
  ck_assert_str_eq(s21_strrchr(str, c), strrchr(str, c));
}
END_TEST

START_TEST(strrchr_negative_char) {
  char str[] = "Hello world";
  int c = -1;
  ck_assert_ptr_eq(s21_strrchr(str, c), strrchr(str, c));
}
END_TEST

START_TEST(strrchr_large_char) {
  char str[] = "Hello world";
  int c = 300;
  ck_assert_ptr_eq(s21_strrchr(str, c), strrchr(str, c));
}
END_TEST

START_TEST(strrchr_space) {
  char str[] = "Hello world with spaces";
  char c = ' ';
  ck_assert_str_eq(s21_strrchr(str, c), strrchr(str, c));
}
END_TEST

START_TEST(strrchr_single_char_string) {
  char str[] = "A";
  char c = 'A';
  ck_assert_str_eq(s21_strrchr(str, c), strrchr(str, c));
}
END_TEST

START_TEST(strrchr_single_char_not_found) {
  char str[] = "A";
  char c = 'B';
  ck_assert_ptr_eq(s21_strrchr(str, c), strrchr(str, c));
}
END_TEST

START_TEST(strrchr_duplicate_chars) {
  char str[] = "aaaabbbccccddddd";
  char c = 'b';
  ck_assert_str_eq(s21_strrchr(str, c), strrchr(str, c));
}
END_TEST

START_TEST(strrchr_embedded_null) {
  char str[] = "Hello\0world";
  char c = 'w';
  ck_assert_ptr_eq(s21_strrchr(str, c), strrchr(str, c));
}
END_TEST

/////////////////////////////
///// s21_strstr TESTS ////
///////////////////////////
START_TEST(str_search_usual) {
  char str[] = "Main string containing substring";
  char substr[] = "sub";
  ck_assert_str_eq(s21_strstr(str, substr), strstr(str, substr));
}
END_TEST

START_TEST(str_search_nomatch) {
  char str[] = "Main string not containing substring";
  char substr[] = "qqq";
  ck_assert_ptr_eq(s21_strstr(str, substr), strstr(str, substr));
}
END_TEST

START_TEST(str_search_first) {
  char str[] = "Main string not containing substring";
  char substr[] = "Main";
  ck_assert_str_eq(s21_strstr(str, substr), strstr(str, substr));
}
END_TEST

START_TEST(str_search_last) {
  char str[] = "Main string not containing substring";
  char substr[] = "substring";
  ck_assert_str_eq(s21_strstr(str, substr), strstr(str, substr));
}
END_TEST

START_TEST(str_search_equal_strs) {
  char str[] = "Identical strings";
  char substr[] = "Identical strings";
  ck_assert_str_eq(s21_strstr(str, substr), strstr(str, substr));
}
END_TEST

START_TEST(str_search_zero_1) {
  char str[] = "Some string";
  char substr[] = "";
  ck_assert_str_eq(s21_strstr(str, substr), strstr(str, substr));
}
END_TEST

START_TEST(str_search_zero_2) {
  char str[] = "";
  char substr[] = "Some string";
  ck_assert_ptr_eq(s21_strstr(str, substr), strstr(str, substr));
}
END_TEST

START_TEST(str_search_both_empty) {
  char str[] = "";
  char substr[] = "";
  ck_assert_ptr_eq(s21_strstr(str, substr), strstr(str, substr));
}
END_TEST

/////////////////////////////
///// s21_strncpy TESTS ////
///////////////////////////
START_TEST(copy_usual) {
  char *src = "Some text to copy";
  char dest_my[20] = {'\0'};
  char dest_orig[20] = {'\0'};
  char *result_my = s21_strncpy(dest_my, src, 20);
  char *result_orig = strncpy(dest_orig, src, 20);
  ck_assert_str_eq(result_my, result_orig);
}
END_TEST

START_TEST(copy_not_fit) {
  char *src = "Something to copy";
  char dest_my[5] = {'\0'};
  char dest_orig[5] = {'\0'};
  char *result_my = s21_strncpy(dest_my, src, 4);
  char *result_orig = strncpy(dest_orig, src, 4);
  ck_assert_str_eq(result_my, result_orig);
}
END_TEST

START_TEST(copy_zero_src) {
  char *src = "";
  char dest_my[5] = {'\0'};
  char dest_orig[5] = {'\0'};
  char *result_my = s21_strncpy(dest_my, src, 4);
  char *result_orig = strncpy(dest_orig, src, 4);
  ck_assert_str_eq(result_my, result_orig);
}
END_TEST

/////////////////////////////
///// s21_strlen TESTS /////
///////////////////////////
START_TEST(length_usual) {
  char s[] = "Not empty string";
  ck_assert_uint_eq(s21_strlen(s), strlen(s));
}
END_TEST

START_TEST(length_zero) {
  char s[] = "";
  ck_assert_uint_eq(s21_strlen(s), strlen(s));
}
END_TEST

START_TEST(length_unusual) {
  char s[] = "Symbol '\0' between text";
  ck_assert_uint_eq(s21_strlen(s), strlen(s));
}
END_TEST

/////////////////////////////
///// s21_strtok TESTS /////
///////////////////////////
START_TEST(test_simple_delim) {
  char str1[] = "apple pear plum";
  char str2[] = "apple pear plum";
  char *token_my;
  char *token_orig;

  token_my = s21_strtok(str1, " ");
  token_orig = strtok(str2, " ");
  ck_assert_str_eq(token_my, token_orig);

  token_my = s21_strtok(S21_NULL, " ");
  token_orig = strtok(S21_NULL, " ");
  ck_assert_str_eq(token_my, token_orig);

  token_my = s21_strtok(S21_NULL, " ");
  token_orig = strtok(S21_NULL, " ");
  ck_assert_str_eq(token_my, token_orig);

  token_my = s21_strtok(S21_NULL, " ");
  token_orig = strtok(S21_NULL, " ");
  ck_assert_ptr_eq(token_my, token_orig);
}
END_TEST

START_TEST(test_multiple_delim) {
  char str1[] = ",apple,,pear,,,plum,";
  char str2[] = ",apple,,pear,,,plum,";
  char *token_my;
  char *token_orig;

  token_my = s21_strtok(str1, ",");
  token_orig = strtok(str2, ",");
  ck_assert_str_eq(token_my, token_orig);

  token_my = s21_strtok(S21_NULL, ",");
  token_orig = strtok(S21_NULL, ",");
  ck_assert_str_eq(token_my, token_orig);

  token_my = s21_strtok(S21_NULL, ",");
  token_orig = strtok(S21_NULL, ",");
  ck_assert_str_eq(token_my, token_orig);

  token_my = s21_strtok(S21_NULL, ",");
  token_orig = strtok(S21_NULL, ",");
  ck_assert_ptr_eq(token_my, token_orig);
}
END_TEST

START_TEST(test_different_delim) {
  char str1[] = "apple,pear;plum-+peach";
  char str2[] = "apple,pear;plum-+peach";
  const char delim[] = ",;-+";
  char *token_my;
  char *token_orig;

  token_my = s21_strtok(str1, delim);
  token_orig = strtok(str2, delim);
  ck_assert_str_eq(token_my, token_orig);

  token_my = s21_strtok(S21_NULL, delim);
  token_orig = strtok(S21_NULL, delim);
  ck_assert_str_eq(token_my, token_orig);

  token_my = s21_strtok(S21_NULL, delim);
  token_orig = strtok(S21_NULL, delim);
  ck_assert_str_eq(token_my, token_orig);

  token_my = s21_strtok(S21_NULL, delim);
  token_orig = strtok(S21_NULL, delim);
  ck_assert_str_eq(token_my, token_orig);
}
END_TEST

START_TEST(test_empty_string_delim) {
  char str1[] = "";
  char str2[] = "";
  char *token_my;
  char *token_orig;

  token_my = s21_strtok(str1, " ");
  token_orig = strtok(str2, " ");
  ck_assert_ptr_eq(token_my, token_orig);
}
END_TEST

START_TEST(test_only_delim) {
  char str1[] = ",;-+";
  char str2[] = ",;-+";
  const char delim[] = ",;-+";
  char *token_my;
  char *token_orig;

  token_my = s21_strtok(str1, delim);
  token_orig = s21_strtok(str2, delim);

  ck_assert_ptr_eq(token_my, token_orig);
}
END_TEST

/////////////////////////////
///// s21_strchr TESTS /////
///////////////////////////
START_TEST(test_simple_strchr) {
  char str[] = "apple,pear;plum-+peach";
  char c = 'r';

  char *result_my = s21_strchr(str, c);
  char *result_orig = strchr(str, c);
  ck_assert_str_eq(result_my, result_orig);
}
END_TEST

START_TEST(test_start_strchr) {
  char str[] = "apple,pear;plum-+peach";
  char c = 'a';

  char *result_my = s21_strchr(str, c);
  char *result_orig = strchr(str, c);
  ck_assert_str_eq(result_my, result_orig);
}
END_TEST

START_TEST(test_register_strchr) {
  char str[] = "apple,pear;plum-+peach";
  char c = 'A';

  char *result_my = s21_strchr(str, c);
  char *result_orig = strchr(str, c);
  ck_assert_ptr_eq(result_my, result_orig);
}
END_TEST

START_TEST(test_space_strchr) {
  char str[] = "apple,pe ar;plum-+peach";
  char c = ' ';

  char *result_my = s21_strchr(str, c);
  char *result_orig = strchr(str, c);
  ck_assert_str_eq(result_my, result_orig);
}
END_TEST

START_TEST(test_multiple_strchr) {
  char str[] = "apple,pear;plum-+peach";
  char c = 'e';

  char *result_my = s21_strchr(str, c);
  char *result_orig = strchr(str, c);
  ck_assert_str_eq(result_my, result_orig);
}
END_TEST

START_TEST(test_end_string_strchr) {
  char str[] = "apple,pear;plum-+peach";
  char c = '\0';

  char *result_my = s21_strchr(str, c);
  char *result_orig = strchr(str, c);
  ck_assert_str_eq(result_my, result_orig);
}
END_TEST

START_TEST(test_no_strchr) {
  char str[] = "apple,pear;plum-+peach";
  char c = 'v';

  char *result_my = s21_strchr(str, c);
  char *result_orig = strchr(str, c);
  ck_assert_ptr_eq(result_my, result_orig);
}
END_TEST

START_TEST(test_empty_string_strchr) {
  char str[] = "";
  char c = 'v';

  char *result_my = s21_strchr(str, c);
  char *result_orig = strchr(str, c);
  ck_assert_ptr_eq(result_my, result_orig);
}
END_TEST

/////////////////////////////
///// s21_strcspn TESTS ////
///////////////////////////
START_TEST(empty_str_1) {
  char str1[] = "";
  char str2[] = "";
  ck_assert_uint_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
}
END_TEST

START_TEST(empty_str_2) {
  char str1[] = "";
  char str2[] = "Non-empy string";
  ck_assert_uint_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
}
END_TEST

START_TEST(empty_str_3) {
  char str1[] = "Non-empy string";
  char str2[] = "";
  ck_assert_uint_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
}
END_TEST

START_TEST(match) {
  char str1[] = "Hello world";
  char str2[] = "w";
  ck_assert_uint_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
}
END_TEST

START_TEST(nomatch) {
  char str1[] = "Hello world";
  char str2[] = "*";
  ck_assert_uint_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
}
END_TEST

START_TEST(match_first) {
  char str1[] = "Hello world";
  char str2[] = "H";
  ck_assert_uint_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
}
END_TEST

START_TEST(match_last) {
  char str1[] = "Hello world";
  char str2[] = "d";
  ck_assert_uint_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
}
END_TEST

START_TEST(not_only_one_match) {
  char str1[] = "Hello world";
  char str2[] = "o";
  ck_assert_uint_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
}
END_TEST

/////////////////////////////
///// s21_memchr TESTS /////
///////////////////////////
START_TEST(test_memchr_1) {
  const char *test = "Hello, world";
  const void *result = s21_memchr(test, 'o', 5);
  const void *expected = memchr(test, 'o', 5);

  ck_assert_ptr_eq(result, expected);
}
END_TEST

START_TEST(test_memchr_2) {
  const char *test = "Hello, world";
  const void *result = s21_memchr(test, 'H', 2);
  const void *expected = memchr(test, 'H', 2);

  ck_assert_ptr_eq(result, expected);
}
END_TEST

START_TEST(test_memchr_3) {
  const char *test = "Hello, world";
  const void *result = s21_memchr(test, 'x', 12);
  const void *expected = memchr(test, 'x', 12);

  ck_assert_ptr_eq(result, expected);
}
END_TEST

START_TEST(test_memchr_4) {
  const char *test = "Hello, world";
  const void *result = s21_memchr(test, '\0', 12);
  const void *expected = memchr(test, '\0', 12);

  ck_assert_ptr_eq(result, expected);
}
END_TEST

START_TEST(test_memchr_5) {
  const char *test = "Hello, world";
  const void *result = s21_memchr(test, 'o', 0);
  const void *expected = memchr(test, 'o', 0);

  ck_assert_ptr_eq(result, expected);
}
END_TEST

START_TEST(test_memchr_6) {
  const char *test = "Hello, world";
  const void *result = s21_memchr(test, 'o', 2);
  const void *expected = memchr(test, 'o', 2);

  ck_assert_ptr_eq(result, expected);
}

/////////////////////////////
///// s21_memcmp TESTS /////
///////////////////////////
START_TEST(test_memcmp_1) {
  const char *test = "Hello, world";
  int result = s21_memcmp(test, "Hello", 5);

  ck_assert_int_eq(result, memcmp(test, "Hello", 5));
}
END_TEST

START_TEST(test_memcmp_2) {
  const char *test = "Hello, world";
  int result = s21_memcmp(test, "HelLo", 5);

  ck_assert_int_eq(result, memcmp(test, "HelLo", 5));
}
END_TEST

START_TEST(test_memcmp_3) {
  const char *test = "Hello, world";
  int result = s21_memcmp(test, "world", 5);

  ck_assert_int_eq(result, memcmp(test, "world", 5));
}
END_TEST

START_TEST(test_memcmp_4) {
  const char *test = "Hello, world";
  int result = s21_memcmp(test, "llo", 3);

  ck_assert_int_eq(result, memcmp(test, "llo", 3));
}
END_TEST

START_TEST(test_memcmp_5) {
  const char *test = "Hello, world";
  int result = s21_memcmp(test, "Hello", 5);

  ck_assert_int_eq(result, memcmp(test, "Hello", 5));
}
END_TEST

START_TEST(test_memcmp_6) {
  const char *test = "Hello";
  int result = s21_memcmp(test, "world", 0);

  ck_assert_int_eq(result, memcmp(test, "world", 0));
}
END_TEST

START_TEST(test_memcmp_7) {
  const char *test = NULL;
  int result = s21_memcmp(test, "world", 0);

  ck_assert_int_eq(result, memcmp(test, "world", 0));
}
END_TEST

START_TEST(test_memcmp_8) {
  const char *test = "Hel\0lo";
  int result = s21_memcmp(test, "Hel\0oo", 7);

  ck_assert_int_eq(result, memcmp(test, "Hel\0oo", 7));
}
END_TEST

/////////////////////////////
///// s21_memcpy TESTS /////
///////////////////////////
START_TEST(test_memcpy_1) {
  char src[] = "Hello, world";
  char dest[20] = {0};
  s21_memcpy(dest, src, strlen(src) + 1);
  ck_assert_str_eq(dest, memcpy(dest, src, strlen(src) + 1));
}

START_TEST(test_memcpy_2) {
  char src[] = "Hello, world";
  char dest[20] = {0};
  char dest1[20] = {0};
  s21_memcpy(dest, src, 4);
  ck_assert_str_eq(dest, memcpy(dest1, src, 4));
}
END_TEST

START_TEST(test_memcpy_3) {
  char src[] = "Hello, world";
  char dest[20] = {0};
  char dest1[20] = {0};
  s21_memcpy(dest, src, 0);
  ck_assert_str_eq(dest, memcpy(dest1, src, 0));
}
END_TEST

START_TEST(test_memcpy_4) {
  char src[] = "Hello, world";
  char dest[20] = "abc";
  char dest1[20] = "abc";
  s21_memcpy(dest, src, 3);
  ck_assert_str_eq(dest, memcpy(dest1, src, 3));
}
END_TEST

START_TEST(test_memcpy_5) {
  char src[] = "Hello, world";
  char dest[20] = "abcdef";
  char dest1[20] = "abcdef";
  s21_memcpy(dest, src, 3);
  ck_assert_str_eq(dest, memcpy(dest1, src, 3));
}
END_TEST

START_TEST(test_memcpy_6) {
  unsigned char src[] = {1, 2, 3, 4, 5};
  unsigned char dest[4] = {0};
  unsigned char dest1[4] = {0};
  s21_memcpy(dest, src, 4);
  ck_assert_mem_eq(dest, memcpy(dest1, src, 4), 4);
}
END_TEST

/////////////////////////////
///// s21_memset TESTS /////
///////////////////////////
START_TEST(test_memset_1) {
  char str[] = "Hello";
  char str1[] = "Hello";
  s21_memset(str, 'c', 4);
  memset(str1, 'c', 4);
  ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(test_memset_2) {
  char str[] = "Eeee";
  char str1[] = "Eeee";
  s21_memset(str, 'e', 4);
  memset(str1, 'e', 4);
  ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(test_memset_3) {
  char str[6] = "Hello";
  char str1[6] = "Hello";
  s21_memset(str, 0, 6);
  memset(str1, 0, 6);
  ck_assert_int_eq(memcmp(str, str1, 6), 0);
  ck_assert_str_eq(str, "");
}
END_TEST

START_TEST(test_memset_4) {
  unsigned char str[4] = {0};
  unsigned char str1[4] = {0};
  s21_memset(str, 255, 4);
  memset(str1, 255, 4);
  ck_assert_int_eq(memcmp(str, str1, 4), 0);
}
END_TEST

START_TEST(test_memset_5) {
  unsigned char str[3] = {0};
  unsigned char str1[3] = {0};
  s21_memset(str, -1, 3);
  memset(str1, -1, 3);
  ck_assert_int_eq(memcmp(str, str1, 3), 0);
}
END_TEST

START_TEST(test_memset_6) {
  char buf[10] = "initial";
  void *result = s21_memset(buf, 'A', 5);
  ck_assert_ptr_eq(result, buf);
}
END_TEST

/////////////////////////////
///// s21_strncat TESTS ////
///////////////////////////
START_TEST(test_strncat_1) {
  const char *src = "world";
  char dest[20] = "Hello";
  char dest1[20] = "Hello";
  s21_strncat(dest, src, 5);
  strncat(dest1, src, 5);
  ck_assert_str_eq(dest, dest1);
}
END_TEST

START_TEST(test_strncat_2) {
  const char *src = "world";
  char dest[20] = "Hello";
  char dest1[20] = "Hello";
  s21_strncat(dest, src, 0);
  strncat(dest1, src, 0);
  ck_assert_str_eq(dest, dest1);
}
END_TEST

START_TEST(test_strncat_3) {
  const char *src = "world";
  char dest[12] = "Hello";
  char dest1[12] = "Hello";
  s21_strncat(dest, src, 5);
  strncat(dest1, src, 5);
  ck_assert_str_eq(dest, dest1);
}
END_TEST

START_TEST(test_strncat_4) {
  char dest[20] = "";
  char dest1[20] = "";
  const char *src = "Hello";
  s21_strncat(dest, src, 3);
  strncat(dest1, src, 3);
  ck_assert_str_eq(dest, dest1);
}
END_TEST

START_TEST(test_strncat_5) {
  char dest[20] = "Start";
  char dest2[20] = "Start";
  char src[] = {'a', 'b', '\0', 'c', 'd'};
  s21_strncat(dest, src, 5);
  strncat(dest2, src, 5);
  ck_assert_str_eq(dest, dest2);
}
END_TEST

START_TEST(test_strncat_6) {
  char dest[20] = "Hi";
  char dest1[20] = "Hi";
  const char *src = "abc";

  s21_strncat(dest, src, 10);
  strncat(dest1, src, 10);
  ck_assert_str_eq(dest, dest1);
}
END_TEST

START_TEST(test_strncat_7) {
  char dest[20] = "Hello";
  char dest1[20] = "Hello";
  const char *src = "";

  s21_strncat(dest, src, 5);
  strncat(dest1, src, 5);
  ck_assert_str_eq(dest, dest1);
}
END_TEST

START_TEST(test_strncat_8) {
  char dest[20] = "Hello";
  const char *src = " World";
  char *result = s21_strncat(dest, src, 6);
  ck_assert_ptr_eq(result, dest);
}
END_TEST

/////////////////////////////
///// s21_strncmp TESTS ////
///////////////////////////
START_TEST(test_strncmp_1) {
  const char str1[] = "Hello";
  const char str2[] = "Hello";
  ck_assert_int_eq(s21_strncmp(str1, str2, 5), strncmp(str1, str2, 5));
}
END_TEST

START_TEST(test_strncmp_2) {
  const char str1[] = "Hello";
  const char str2[] = "world";
  ck_assert_int_eq(s21_strncmp(str1, str2, 5), strncmp(str1, str2, 5));
}
END_TEST

START_TEST(test_strncmp_3) {
  const char str1[] = "Hello";
  const char str2[] = "hello";
  ck_assert_int_eq(s21_strncmp(str1, str2, 5), strncmp(str1, str2, 5));
}
END_TEST

START_TEST(test_strncmp_4) {
  const char str1[] = "";
  const char str2[] = "";
  ck_assert_int_eq(s21_strncmp(str1, str2, 0), strncmp(str1, str2, 0));
}
END_TEST

START_TEST(test_strncmp_5) {
  const char str1[] = "Hello";
  const char str2[] = "world";
  ck_assert_int_eq(s21_strncmp(str1, str2, 0), strncmp(str1, str2, 0));
}
END_TEST

START_TEST(test_strncmp_6) {
  const char str1[] = "Hello";
  const char str2[] = "world";
  ck_assert_int_eq(s21_strncmp(str1, str2, 10), strncmp(str1, str2, 10));
}
END_TEST

START_TEST(test_strncmp_7) {
  const char str1[] = "Hello";
  const char str2[] = "Hello, world";
  ck_assert_int_eq(s21_strncmp(str1, str2, 6), strncmp(str1, str2, 6));
}
END_TEST

START_TEST(test_strncmp_8) {
  const char str1[] = "Hello";
  const char str2[] = "HellO";
  ck_assert_int_eq(s21_strncmp(str1, str2, 5), strncmp(str1, str2, 5));
}
END_TEST

START_TEST(test_strncmp_9) {
  const char *str1 = "Hello";
  const char *str2 = "Hello";
  ck_assert_int_eq(s21_strncmp(str1, str2, 6), strncmp(str1, str2, 6));
}
END_TEST

/////////////////////////////
///// s21_to_upper TESTS ///
///////////////////////////
START_TEST(test_upper_1) {
  char *result = (char *)s21_to_upper("");
  ck_assert_ptr_nonnull(result);
  ck_assert_str_eq(result, "");
  free(result);
}
END_TEST

START_TEST(test_upper_2) {
  char *result;
  result = (char *)s21_to_upper("hello");
  ck_assert_ptr_nonnull(result);
  ck_assert_str_eq(result, "HELLO");
  free(result);
}
END_TEST

START_TEST(test_upper_3) {
  char *result = (char *)s21_to_upper("HeLlO");
  ck_assert_ptr_nonnull(result);
  ck_assert_str_eq(result, "HELLO");
  free(result);
}
END_TEST

START_TEST(test_upper_4) {
  char *result = (char *)s21_to_upper("HELLO");
  ck_assert_ptr_nonnull(result);
  ck_assert_str_eq(result, "HELLO");
  free(result);
}
END_TEST

START_TEST(test_upper_5) {
  char *result = (char *)s21_to_upper("hel123lo");
  ck_assert_ptr_nonnull(result);
  ck_assert_str_eq(result, "HEL123LO");
  free(result);
}
END_TEST

START_TEST(test_upper_6) {
  char *result = (char *)s21_to_upper("hello world");
  ck_assert_ptr_nonnull(result);
  ck_assert_str_eq(result, "HELLO WORLD");
  free(result);
}
END_TEST

START_TEST(test_upper_7) {
  char *result = (char *)s21_to_upper("hello 123 WORLD");
  ck_assert_ptr_nonnull(result);
  ck_assert_str_eq(result, "HELLO 123 WORLD");
  free(result);
}
END_TEST

START_TEST(test_upper_8) {
  char *result = (char *)s21_to_upper(" hello  world ");
  ck_assert_ptr_nonnull(result);
  ck_assert_str_eq(result, " HELLO  WORLD ");
  free(result);
}
END_TEST

START_TEST(test_upper_9) {
  char *result = (char *)s21_to_upper("123");
  ck_assert_ptr_nonnull(result);
  ck_assert_str_eq(result, "123");
  free(result);
}
END_TEST

START_TEST(test_upper_10) {
  char *result = (char *)s21_to_upper(S21_NULL);
  ck_assert_ptr_null(result);
  free(result);
}
END_TEST

/////////////////////////////
///// s21_to_lower TESTS ///
///////////////////////////
START_TEST(test_lower_1) {
  char *result = (char *)s21_to_lower("");
  ck_assert_ptr_nonnull(result);
  ck_assert_str_eq(result, "");
  free(result);
}
END_TEST

START_TEST(test_lower_2) {
  char *result;
  result = (char *)s21_to_lower("HELLO");
  ck_assert_ptr_nonnull(result);
  ck_assert_str_eq(result, "hello");
  free(result);
}
END_TEST

START_TEST(test_lower_3) {
  char *result = (char *)s21_to_lower("HeLlO");
  ck_assert_ptr_nonnull(result);
  ck_assert_str_eq(result, "hello");
  free(result);
}
END_TEST

START_TEST(test_lower_4) {
  char *result = (char *)s21_to_lower("hello");
  ck_assert_ptr_nonnull(result);
  ck_assert_str_eq(result, "hello");
  free(result);
}
END_TEST

START_TEST(test_lower_5) {
  char *result = (char *)s21_to_lower("HEL123LO");
  ck_assert_ptr_nonnull(result);
  ck_assert_str_eq(result, "hel123lo");
  free(result);
}
END_TEST

START_TEST(test_lower_6) {
  char *result = (char *)s21_to_lower("HELLO WORLD");
  ck_assert_ptr_nonnull(result);
  ck_assert_str_eq(result, "hello world");
  free(result);
}
END_TEST

START_TEST(test_lower_7) {
  char *result = (char *)s21_to_lower("hello 123 WORLD");
  ck_assert_ptr_nonnull(result);
  ck_assert_str_eq(result, "hello 123 world");
  free(result);
}
END_TEST

START_TEST(test_lower_8) {
  char *result = (char *)s21_to_lower(" HELLO  WORLD ");
  ck_assert_ptr_nonnull(result);
  ck_assert_str_eq(result, " hello  world ");
  free(result);
}
END_TEST

START_TEST(test_lower_9) {
  char *result = (char *)s21_to_lower("123");
  ck_assert_ptr_nonnull(result);
  ck_assert_str_eq(result, "123");
  free(result);
}
END_TEST

START_TEST(test_lower_10) {
  char *result = (char *)s21_to_lower(S21_NULL);
  ck_assert_ptr_null(result);
}
END_TEST

/////////////////////////////
///// s21_trim TESTS ///////
///////////////////////////
START_TEST(trim1) {
  char *result = s21_trim("123abc123", "123");
  ck_assert_str_eq(result, "abc");
  free(result);
}
END_TEST

START_TEST(trim2) {
  char *result = s21_trim(S21_NULL, "123");
  ck_assert_ptr_eq(result, S21_NULL);
  free(result);
}
END_TEST

START_TEST(trim3) {
  char *result = s21_trim("123123", "123");
  ck_assert_str_eq(result, "\0");
  free(result);
}
END_TEST

/////////////////////////////
///// s21_insert TESTS /////
///////////////////////////
START_TEST(insert_usual) {
  char src[20] = "Hello  world!";
  char str[5] = "booo";
  char *result = s21_insert(src, str, 6);
  ck_assert_str_eq(result, "Hello booo world!");
  free(result);
}
END_TEST

START_TEST(insert_first) {
  char src[20] = "Hello  world!";
  char str[5] = "booo";
  char *result = s21_insert(src, str, 0);
  ck_assert_str_eq(result, "boooHello  world!");
  free(result);
}
END_TEST

START_TEST(insert_last) {
  char src[20] = "Hello  world!";
  char str[5] = "booo";
  char *result = s21_insert(src, str, 13);
  ck_assert_str_eq(result, "Hello  world!booo");
  free(result);
}
END_TEST

START_TEST(insert_null) {
  char *src = S21_NULL;
  char *str = S21_NULL;
  ck_assert_ptr_null(s21_insert(src, str, 13));
}
END_TEST

Suite *str_proc_func_suite() {
  Suite *s;
  s = suite_create("Text proccessing functions tests");

  TCase *tc_s21_strchr = tcase_create("s21_s21_strchr");
  tcase_add_test(tc_s21_strchr, test_simple_strchr);
  tcase_add_test(tc_s21_strchr, test_start_strchr);
  tcase_add_test(tc_s21_strchr, test_register_strchr);
  tcase_add_test(tc_s21_strchr, test_space_strchr);
  tcase_add_test(tc_s21_strchr, test_multiple_strchr);
  tcase_add_test(tc_s21_strchr, test_end_string_strchr);
  tcase_add_test(tc_s21_strchr, test_no_strchr);
  tcase_add_test(tc_s21_strchr, test_empty_string_strchr);
  suite_add_tcase(s, tc_s21_strchr);

  TCase *tc_s21_strcspn = tcase_create("s21_strcspn");
  tcase_add_test(tc_s21_strcspn, empty_str_1);
  tcase_add_test(tc_s21_strcspn, empty_str_2);
  tcase_add_test(tc_s21_strcspn, empty_str_3);
  tcase_add_test(tc_s21_strcspn, match);
  tcase_add_test(tc_s21_strcspn, nomatch);
  tcase_add_test(tc_s21_strcspn, match_first);
  tcase_add_test(tc_s21_strcspn, match_last);
  tcase_add_test(tc_s21_strcspn, not_only_one_match);
  suite_add_tcase(s, tc_s21_strcspn);

  TCase *tc_s21_to_upper = tcase_create("s21_to_upper");
  tcase_add_test(tc_s21_to_upper, test_upper_1);
  tcase_add_test(tc_s21_to_upper, test_upper_2);
  tcase_add_test(tc_s21_to_upper, test_upper_3);
  tcase_add_test(tc_s21_to_upper, test_upper_4);
  tcase_add_test(tc_s21_to_upper, test_upper_5);
  tcase_add_test(tc_s21_to_upper, test_upper_6);
  tcase_add_test(tc_s21_to_upper, test_upper_7);
  tcase_add_test(tc_s21_to_upper, test_upper_8);
  tcase_add_test(tc_s21_to_upper, test_upper_9);
  tcase_add_test(tc_s21_to_upper, test_upper_10);
  suite_add_tcase(s, tc_s21_to_upper);

  TCase *tc_s21_to_lower = tcase_create("s21_to_lower");
  tcase_add_test(tc_s21_to_lower, test_lower_1);
  tcase_add_test(tc_s21_to_lower, test_lower_2);
  tcase_add_test(tc_s21_to_lower, test_lower_3);
  tcase_add_test(tc_s21_to_lower, test_lower_4);
  tcase_add_test(tc_s21_to_lower, test_lower_5);
  tcase_add_test(tc_s21_to_lower, test_lower_6);
  tcase_add_test(tc_s21_to_lower, test_lower_7);
  tcase_add_test(tc_s21_to_lower, test_lower_8);
  tcase_add_test(tc_s21_to_lower, test_lower_9);
  tcase_add_test(tc_s21_to_lower, test_lower_10);
  suite_add_tcase(s, tc_s21_to_lower);

  TCase *tc_s21_trim = tcase_create("s21_trim");
  tcase_add_test(tc_s21_trim, trim1);
  tcase_add_test(tc_s21_trim, trim2);
  tcase_add_test(tc_s21_trim, trim3);
  suite_add_tcase(s, tc_s21_trim);

  TCase *tc_s21_strtok = tcase_create("s21_strtok");
  tcase_add_test(tc_s21_strtok, test_simple_delim);
  tcase_add_test(tc_s21_strtok, test_multiple_delim);
  tcase_add_test(tc_s21_strtok, test_different_delim);
  tcase_add_test(tc_s21_strtok, test_empty_string_delim);
  tcase_add_test(tc_s21_strtok, test_only_delim);
  suite_add_tcase(s, tc_s21_strtok);

  TCase *tc_s21_strncpy = tcase_create("s21_strncpy");
  tcase_add_test(tc_s21_strncpy, copy_usual);
  tcase_add_test(tc_s21_strncpy, copy_not_fit);
  tcase_add_test(tc_s21_strncpy, copy_zero_src);
  suite_add_tcase(s, tc_s21_strncpy);

  TCase *tc_s21_strlen = tcase_create("s21_strlen");
  tcase_add_test(tc_s21_strlen, length_usual);
  tcase_add_test(tc_s21_strlen, length_zero);
  tcase_add_test(tc_s21_strlen, length_unusual);
  suite_add_tcase(s, tc_s21_strlen);

  TCase *tc_s21_strstr = tcase_create("s21_strstr");
  tcase_add_test(tc_s21_strstr, str_search_usual);
  tcase_add_test(tc_s21_strstr, str_search_nomatch);
  tcase_add_test(tc_s21_strstr, str_search_first);
  tcase_add_test(tc_s21_strstr, str_search_last);
  tcase_add_test(tc_s21_strstr, str_search_equal_strs);
  tcase_add_test(tc_s21_strstr, str_search_zero_1);
  tcase_add_test(tc_s21_strstr, str_search_zero_2);
  tcase_add_test(tc_s21_strstr, str_search_both_empty);
  suite_add_tcase(s, tc_s21_strstr);

  TCase *tc_s21_strcchr = tcase_create("s21_strcchr");
  tcase_add_test(tc_s21_strcchr, strrchr_usual);
  tcase_add_test(tc_s21_strcchr, strrchr_first_char);
  tcase_add_test(tc_s21_strcchr, strrchr_last_char);
  tcase_add_test(tc_s21_strcchr, strrchr_middle_char);
  tcase_add_test(tc_s21_strcchr, strrchr_multiple_occurrences);
  tcase_add_test(tc_s21_strcchr, strrchr_not_found);
  tcase_add_test(tc_s21_strcchr, strrchr_empty_string);
  tcase_add_test(tc_s21_strcchr, strrchr_null_byte);
  tcase_add_test(tc_s21_strcchr, strrchr_null_byte_empty);
  tcase_add_test(tc_s21_strcchr, strrchr_special_chars);
  tcase_add_test(tc_s21_strcchr, strrchr_numbers);
  tcase_add_test(tc_s21_strcchr, strrchr_negative_char);
  tcase_add_test(tc_s21_strcchr, strrchr_large_char);
  tcase_add_test(tc_s21_strcchr, strrchr_space);
  tcase_add_test(tc_s21_strcchr, strrchr_single_char_string);
  tcase_add_test(tc_s21_strcchr, strrchr_single_char_not_found);
  tcase_add_test(tc_s21_strcchr, strrchr_duplicate_chars);
  tcase_add_test(tc_s21_strcchr, strrchr_embedded_null);
  suite_add_tcase(s, tc_s21_strcchr);

  TCase *tc_s21_strpbrk = tcase_create("s21_strpbrk");
  tcase_add_test(tc_s21_strpbrk, strpbrk_usual);
  tcase_add_test(tc_s21_strpbrk, strpbrk_empty_search);
  tcase_add_test(tc_s21_strpbrk, strpbrk_empty_string);
  tcase_add_test(tc_s21_strpbrk, strpbrk_both_empty);
  tcase_add_test(tc_s21_strpbrk, strpbrk_no_match);
  tcase_add_test(tc_s21_strpbrk, strpbrk_first_char_match);
  tcase_add_test(tc_s21_strpbrk, strpbrk_middle_match);
  tcase_add_test(tc_s21_strpbrk, strpbrk_multiple_chars);
  tcase_add_test(tc_s21_strpbrk, strpbrk_with_spaces);
  tcase_add_test(tc_s21_strpbrk, strpbrk_special_chars);
  tcase_add_test(tc_s21_strpbrk, strpbrk_numbers);
  tcase_add_test(tc_s21_strpbrk, strpbrk_null_chars);
  tcase_add_test(tc_s21_strpbrk, strpbrk_duplicate_chars);
  suite_add_tcase(s, tc_s21_strpbrk);

  TCase *tc_s21_strerror = tcase_create("s21_strerror");
  tcase_add_test(tc_s21_strerror, errors_usual);
  tcase_add_test(tc_s21_strerror, errors_unknown);
  suite_add_tcase(s, tc_s21_strerror);

  TCase *tc_s21_memchr = tcase_create("s21_memchr");
  tcase_add_test(tc_s21_memchr, test_memchr_1);
  tcase_add_test(tc_s21_memchr, test_memchr_2);
  tcase_add_test(tc_s21_memchr, test_memchr_3);
  tcase_add_test(tc_s21_memchr, test_memchr_4);
  tcase_add_test(tc_s21_memchr, test_memchr_5);
  tcase_add_test(tc_s21_memchr, test_memchr_6);
  suite_add_tcase(s, tc_s21_memchr);

  TCase *tc_s21_memcmp = tcase_create("s21_memcmp");
  tcase_add_test(tc_s21_memcmp, test_memcmp_1);
  tcase_add_test(tc_s21_memcmp, test_memcmp_2);
  tcase_add_test(tc_s21_memcmp, test_memcmp_3);
  tcase_add_test(tc_s21_memcmp, test_memcmp_4);
  tcase_add_test(tc_s21_memcmp, test_memcmp_5);
  tcase_add_test(tc_s21_memcmp, test_memcmp_6);
  tcase_add_test(tc_s21_memcmp, test_memcmp_7);
  tcase_add_test(tc_s21_memcmp, test_memcmp_8);
  suite_add_tcase(s, tc_s21_memcmp);

  TCase *tc_s21_memcpy = tcase_create("s21_memcpy");
  tcase_add_test(tc_s21_memcpy, test_memcpy_1);
  tcase_add_test(tc_s21_memcpy, test_memcpy_2);
  tcase_add_test(tc_s21_memcpy, test_memcpy_3);
  tcase_add_test(tc_s21_memcpy, test_memcpy_4);
  tcase_add_test(tc_s21_memcpy, test_memcpy_5);
  tcase_add_test(tc_s21_memcpy, test_memcpy_6);
  suite_add_tcase(s, tc_s21_memcpy);

  TCase *tc_s21_memset = tcase_create("s21_memset");
  tcase_add_test(tc_s21_memset, test_memset_1);
  tcase_add_test(tc_s21_memset, test_memset_2);
  tcase_add_test(tc_s21_memset, test_memset_3);
  tcase_add_test(tc_s21_memset, test_memset_4);
  tcase_add_test(tc_s21_memset, test_memset_5);
  tcase_add_test(tc_s21_memset, test_memset_6);
  suite_add_tcase(s, tc_s21_memset);

  TCase *tc_s21_strncat = tcase_create("s21_strncat");
  tcase_add_test(tc_s21_strncat, test_strncat_1);
  tcase_add_test(tc_s21_strncat, test_strncat_2);
  tcase_add_test(tc_s21_strncat, test_strncat_3);
  tcase_add_test(tc_s21_strncat, test_strncat_4);
  tcase_add_test(tc_s21_strncat, test_strncat_5);
  tcase_add_test(tc_s21_strncat, test_strncat_6);
  tcase_add_test(tc_s21_strncat, test_strncat_7);
  tcase_add_test(tc_s21_strncat, test_strncat_8);
  suite_add_tcase(s, tc_s21_strncat);

  TCase *tc_s21_strncmp = tcase_create("s21_strncmp");
  tcase_add_test(tc_s21_strncmp, test_strncmp_1);
  tcase_add_test(tc_s21_strncmp, test_strncmp_2);
  tcase_add_test(tc_s21_strncmp, test_strncmp_3);
  tcase_add_test(tc_s21_strncmp, test_strncmp_4);
  tcase_add_test(tc_s21_strncmp, test_strncmp_5);
  tcase_add_test(tc_s21_strncmp, test_strncmp_6);
  tcase_add_test(tc_s21_strncmp, test_strncmp_7);
  tcase_add_test(tc_s21_strncmp, test_strncmp_8);
  tcase_add_test(tc_s21_strncmp, test_strncmp_9);
  suite_add_tcase(s, tc_s21_strncmp);

  TCase *tc_s21_insert = tcase_create("s21_insert");
  tcase_add_test(tc_s21_insert, insert_usual);
  tcase_add_test(tc_s21_insert, insert_first);
  tcase_add_test(tc_s21_insert, insert_last);
  tcase_add_test(tc_s21_insert, insert_null);
  suite_add_tcase(s, tc_s21_insert);

  return s;
}

/////////////////////////////
///// %u %o %x %X TESTS ////
///////////////////////////
START_TEST(sscanf_o_basic) {
  char str[] = "123 456 777";
  char fmt[] = "%o %o %o";
  unsigned int my1 = 0, my2 = 0, my3 = 0;
  unsigned int orig1 = 0, orig2 = 0, orig3 = 0;

  int result_my = s21_sscanf(str, fmt, &my1, &my2, &my3);
  int result_orig = sscanf(str, fmt, &orig1, &orig2, &orig3);

  ck_assert_uint_eq(my1, orig1);
  ck_assert_uint_eq(my2, orig2);
  ck_assert_uint_eq(my3, orig3);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_o_modifiers) {
  char str[] = "377 177777 37777777777 1777777777777777777777";
  char fmt[] = "%hho %ho %lo %llo";
  unsigned char my1 = 0;
  unsigned short my2 = 0;
  unsigned long my3 = 0;
  unsigned long long my4 = 0;
  unsigned char orig1 = 0;
  unsigned short orig2 = 0;
  unsigned long orig3 = 0;
  unsigned long long orig4 = 0;

  int result_my = s21_sscanf(str, fmt, &my1, &my2, &my3, &my4);
  int result_orig = sscanf(str, fmt, &orig1, &orig2, &orig3, &orig4);

  ck_assert_uint_eq(my1, orig1);
  ck_assert_uint_eq(my2, orig2);
  ck_assert_uint_eq(my3, orig3);
  ck_assert(my4 == orig4);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_o_width_star) {
  char str[] = "123456 777 111";
  char fmt[] = "%3o %*o %2o";
  unsigned int my1 = 0, my2 = 0;
  unsigned int orig1 = 0, orig2 = 0;

  int result_my = s21_sscanf(str, fmt, &my1, &my2);
  int result_orig = sscanf(str, fmt, &orig1, &orig2);

  ck_assert_uint_eq(my1, orig1);
  ck_assert_uint_eq(my2, orig2);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_o_invalid) {
  char str[] = "123 8ab 456";
  char fmt[] = "%o %o %o";
  unsigned int my1 = 0, my2 = 0, my3 = 0;
  unsigned int orig1 = 0, orig2 = 0, orig3 = 0;

  int result_my = s21_sscanf(str, fmt, &my1, &my2, &my3);
  int result_orig = sscanf(str, fmt, &orig1, &orig2, &orig3);

  ck_assert_uint_eq(my1, orig1);
  ck_assert_uint_eq(my2, orig2);
  ck_assert_uint_eq(my3, orig3);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_u_basic) {
  char str[] = "123 456 789 0";
  char fmt[] = "%u %u %u %u";
  unsigned int my1 = 0, my2 = 0, my3 = 0, my4 = 0;
  unsigned int orig1 = 0, orig2 = 0, orig3 = 0, orig4 = 0;

  int result_my = s21_sscanf(str, fmt, &my1, &my2, &my3, &my4);
  int result_orig = sscanf(str, fmt, &orig1, &orig2, &orig3, &orig4);

  ck_assert_uint_eq(my1, orig1);
  ck_assert_uint_eq(my2, orig2);
  ck_assert_uint_eq(my3, orig3);
  ck_assert_uint_eq(my4, orig4);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_u_modifiers) {
  char str[] = "255 65535 4294967295 18446744073709551615";
  char fmt[] = "%hhu %hu %lu %llu";
  unsigned char my1 = 0;
  unsigned short my2 = 0;
  unsigned long my3 = 0;
  unsigned long long my4 = 0;
  unsigned char orig1 = 0;
  unsigned short orig2 = 0;
  unsigned long orig3 = 0;
  unsigned long long orig4 = 0;

  int result_my = s21_sscanf(str, fmt, &my1, &my2, &my3, &my4);
  int result_orig = sscanf(str, fmt, &orig1, &orig2, &orig3, &orig4);

  ck_assert_uint_eq(my1, orig1);
  ck_assert_uint_eq(my2, orig2);
  ck_assert_uint_eq(my3, orig3);
  ck_assert(my4 == orig4);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_u_mixed_width) {
  char str[] = "12345 67890 11111";
  char fmt[] = "%3u %4hu %2lu";
  unsigned int my1 = 0;
  unsigned short my2 = 0;
  unsigned long my3 = 0;
  unsigned int orig1 = 0;
  unsigned short orig2 = 0;
  unsigned long orig3 = 0;

  int result_my = s21_sscanf(str, fmt, &my1, &my2, &my3);
  int result_orig = sscanf(str, fmt, &orig1, &orig2, &orig3);

  ck_assert_uint_eq(my1, orig1);
  ck_assert_uint_eq(my2, orig2);
  ck_assert_uint_eq(my3, orig3);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_x_basic) {
  char str[] = "ff dead beef 123";
  char fmt[] = "%x %x %x %x";
  unsigned int my1 = 0, my2 = 0, my3 = 0, my4 = 0;
  unsigned int orig1 = 0, orig2 = 0, orig3 = 0, orig4 = 0;

  int result_my = s21_sscanf(str, fmt, &my1, &my2, &my3, &my4);
  int result_orig = sscanf(str, fmt, &orig1, &orig2, &orig3, &orig4);

  ck_assert_uint_eq(my1, orig1);
  ck_assert_uint_eq(my2, orig2);
  ck_assert_uint_eq(my3, orig3);
  ck_assert_uint_eq(my4, orig4);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_x_with_prefix) {
  char str[] = "0xff 0xdead 0xBEEF 0x123";
  char fmt[] = "%x %x %x %x";
  unsigned int my1 = 0, my2 = 0, my3 = 0, my4 = 0;
  unsigned int orig1 = 0, orig2 = 0, orig3 = 0, orig4 = 0;

  int result_my = s21_sscanf(str, fmt, &my1, &my2, &my3, &my4);
  int result_orig = sscanf(str, fmt, &orig1, &orig2, &orig3, &orig4);

  ck_assert_uint_eq(my1, orig1);
  ck_assert_uint_eq(my2, orig2);
  ck_assert_uint_eq(my3, orig3);
  ck_assert_uint_eq(my4, orig4);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_x_modifiers) {
  char str[] = "ff ffff ffffffff ffffffffffffffff";
  char fmt[] = "%hhx %hx %lx %llx";
  unsigned char my1 = 0;
  unsigned short my2 = 0;
  unsigned long my3 = 0;
  unsigned long long my4 = 0;
  unsigned char orig1 = 0;
  unsigned short orig2 = 0;
  unsigned long orig3 = 0;
  unsigned long long orig4 = 0;

  int result_my = s21_sscanf(str, fmt, &my1, &my2, &my3, &my4);
  int result_orig = sscanf(str, fmt, &orig1, &orig2, &orig3, &orig4);

  ck_assert_uint_eq(my1, orig1);
  ck_assert_uint_eq(my2, orig2);
  ck_assert_uint_eq(my3, orig3);
  ck_assert(my4 == orig4);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_X_basic) {
  char str[] = "FF DEAD BEEF 123";
  char fmt[] = "%X %X %X %X";
  unsigned int my1 = 0, my2 = 0, my3 = 0, my4 = 0;
  unsigned int orig1 = 0, orig2 = 0, orig3 = 0, orig4 = 0;

  int result_my = s21_sscanf(str, fmt, &my1, &my2, &my3, &my4);
  int result_orig = sscanf(str, fmt, &orig1, &orig2, &orig3, &orig4);

  ck_assert_uint_eq(my1, orig1);
  ck_assert_uint_eq(my2, orig2);
  ck_assert_uint_eq(my3, orig3);
  ck_assert_uint_eq(my4, orig4);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_X_with_prefix) {
  char str[] = "0XFF 0XDEAD 0XBEEF 0X123";
  char fmt[] = "%X %X %X %X";
  unsigned int my1 = 0, my2 = 0, my3 = 0, my4 = 0;
  unsigned int orig1 = 0, orig2 = 0, orig3 = 0, orig4 = 0;

  int result_my = s21_sscanf(str, fmt, &my1, &my2, &my3, &my4);
  int result_orig = sscanf(str, fmt, &orig1, &orig2, &orig3, &orig4);

  ck_assert_uint_eq(my1, orig1);
  ck_assert_uint_eq(my2, orig2);
  ck_assert_uint_eq(my3, orig3);
  ck_assert_uint_eq(my4, orig4);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_x_X_mixed) {
  char str[] = "ff FF dead DEAD";
  char fmt[] = "%x %X %x %X";
  unsigned int my1 = 0, my2 = 0, my3 = 0, my4 = 0;
  unsigned int orig1 = 0, orig2 = 0, orig3 = 0, orig4 = 0;

  int result_my = s21_sscanf(str, fmt, &my1, &my2, &my3, &my4);
  int result_orig = sscanf(str, fmt, &orig1, &orig2, &orig3, &orig4);

  ck_assert_uint_eq(my1, orig1);
  ck_assert_uint_eq(my2, orig2);
  ck_assert_uint_eq(my3, orig3);
  ck_assert_uint_eq(my4, orig4);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_all_specifiers_width_star) {
  char str[] = "123456 37777 deadbeef FEDCBA 999";
  char fmt[] = "%4u %3o %*x %5X %2u";
  unsigned int my1 = 0, my2 = 0, my3 = 0, my4 = 0;
  unsigned int orig1 = 0, orig2 = 0, orig3 = 0, orig4 = 0;

  int result_my = s21_sscanf(str, fmt, &my1, &my2, &my3, &my4);
  int result_orig = sscanf(str, fmt, &orig1, &orig2, &orig3, &orig4);

  ck_assert_uint_eq(my1, orig1);
  ck_assert_uint_eq(my2, orig2);
  ck_assert_uint_eq(my3, orig3);
  ck_assert_uint_eq(my4, orig4);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_all_mixed_modifiers) {
  char str[] = "255 377 ffff FFFF 65535 177777 ffffffff FFFFFFFF";
  char fmt[] = "%hhu %hho %hhx %hhX %hu %ho %hx %hX";
  unsigned char my1 = 0, my2 = 0, my3 = 0, my4 = 0;
  unsigned short my5 = 0, my6 = 0, my7 = 0, my8 = 0;
  unsigned char orig1 = 0, orig2 = 0, orig3 = 0, orig4 = 0;
  unsigned short orig5 = 0, orig6 = 0, orig7 = 0, orig8 = 0;

  int result_my =
      s21_sscanf(str, fmt, &my1, &my2, &my3, &my4, &my5, &my6, &my7, &my8);
  int result_orig = sscanf(str, fmt, &orig1, &orig2, &orig3, &orig4, &orig5,
                           &orig6, &orig7, &orig8);

  ck_assert_uint_eq(my1, orig1);
  ck_assert_uint_eq(my2, orig2);
  ck_assert_uint_eq(my3, orig3);
  ck_assert_uint_eq(my4, orig4);
  ck_assert_uint_eq(my5, orig5);
  ck_assert_uint_eq(my6, orig6);
  ck_assert_uint_eq(my7, orig7);
  ck_assert_uint_eq(my8, orig8);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_all_invalid_data) {
  char str[] = "123 xyz 456 8ab 789 ghi";
  char fmt[] = "%u %u %o %o %x %x";
  unsigned int my1 = 0, my2 = 0, my3 = 0, my4 = 0, my5 = 0, my6 = 0;
  unsigned int orig1 = 0, orig2 = 0, orig3 = 0, orig4 = 0, orig5 = 0, orig6 = 0;

  int result_my = s21_sscanf(str, fmt, &my1, &my2, &my3, &my4, &my5, &my6);
  int result_orig =
      sscanf(str, fmt, &orig1, &orig2, &orig3, &orig4, &orig5, &orig6);

  ck_assert_uint_eq(my1, orig1);
  ck_assert_uint_eq(my2, orig2);
  ck_assert_uint_eq(my3, orig3);
  ck_assert_uint_eq(my4, orig4);
  ck_assert_uint_eq(my5, orig5);
  ck_assert_uint_eq(my6, orig6);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_all_boundary_values) {
  char str[] = "0 0 0 0 4294967295 37777777777 ffffffff FFFFFFFF";
  char fmt[] = "%u %o %x %X %lu %lo %lx %lX";
  unsigned int my1 = 0, my2 = 0, my3 = 0, my4 = 0;
  unsigned long my5 = 0, my6 = 0, my7 = 0, my8 = 0;
  unsigned int orig1 = 0, orig2 = 0, orig3 = 0, orig4 = 0;
  unsigned long orig5 = 0, orig6 = 0, orig7 = 0, orig8 = 0;

  int result_my =
      s21_sscanf(str, fmt, &my1, &my2, &my3, &my4, &my5, &my6, &my7, &my8);
  int result_orig = sscanf(str, fmt, &orig1, &orig2, &orig3, &orig4, &orig5,
                           &orig6, &orig7, &orig8);

  ck_assert_uint_eq(my1, orig1);
  ck_assert_uint_eq(my2, orig2);
  ck_assert_uint_eq(my3, orig3);
  ck_assert_uint_eq(my4, orig4);
  ck_assert_uint_eq(my5, orig5);
  ck_assert_uint_eq(my6, orig6);
  ck_assert_uint_eq(my7, orig7);
  ck_assert_uint_eq(my8, orig8);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_all_with_whitespace_and_text) {
  char str[] = "   Unsigned: 123, Octal: 456, HexLower: dead, HexUpper: beef  ";
  char fmt[] = " Unsigned: %u, Octal: %o, HexLower: %x, HexUpper: %X";
  unsigned int my1 = 0, my2 = 0, my3 = 0, my4 = 0;
  unsigned int orig1 = 0, orig2 = 0, orig3 = 0, orig4 = 0;

  int result_my = s21_sscanf(str, fmt, &my1, &my2, &my3, &my4);
  int result_orig = sscanf(str, fmt, &orig1, &orig2, &orig3, &orig4);

  ck_assert_uint_eq(my1, orig1);
  ck_assert_uint_eq(my2, orig2);
  ck_assert_uint_eq(my3, orig3);
  ck_assert_uint_eq(my4, orig4);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

/////////////////////////////
///////// %i TESTS /////////
///////////////////////////
START_TEST(sscanf_i_basic) {
  char str[] = "123 -456 +789";
  char fmt[] = "%i %i %i";
  int my1 = 0, my2 = 0, my3 = 0;
  int orig1 = 0, orig2 = 0, orig3 = 0;

  int result_my = s21_sscanf(str, fmt, &my1, &my2, &my3);
  int result_orig = sscanf(str, fmt, &orig1, &orig2, &orig3);

  ck_assert_int_eq(my1, orig1);
  ck_assert_int_eq(my2, orig2);
  ck_assert_int_eq(my3, orig3);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_i_hex) {
  char str[] = "0x1A 0XFF -0x2f";
  char fmt[] = "%i %i %i";
  int my1 = 0, my2 = 0, my3 = 0;
  int orig1 = 0, orig2 = 0, orig3 = 0;

  int result_my = s21_sscanf(str, fmt, &my1, &my2, &my3);
  int result_orig = sscanf(str, fmt, &orig1, &orig2, &orig3);

  ck_assert_int_eq(my1, orig1);
  ck_assert_int_eq(my2, orig2);
  ck_assert_int_eq(my3, orig3);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_i_octal) {
  char str[] = "0123 077 -045";
  char fmt[] = "%i %i %i";
  int my1 = 0, my2 = 0, my3 = 0;
  int orig1 = 0, orig2 = 0, orig3 = 0;

  int result_my = s21_sscanf(str, fmt, &my1, &my2, &my3);
  int result_orig = sscanf(str, fmt, &orig1, &orig2, &orig3);

  ck_assert_int_eq(my1, orig1);
  ck_assert_int_eq(my2, orig2);
  ck_assert_int_eq(my3, orig3);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_i_mixed_bases) {
  char str[] = "255 0xFF 0377";
  char fmt[] = "%i %i %i";
  int my1 = 0, my2 = 0, my3 = 0;
  int orig1 = 0, orig2 = 0, orig3 = 0;

  int result_my = s21_sscanf(str, fmt, &my1, &my2, &my3);
  int result_orig = sscanf(str, fmt, &orig1, &orig2, &orig3);

  ck_assert_int_eq(my1, orig1);
  ck_assert_int_eq(my2, orig2);
  ck_assert_int_eq(my3, orig3);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_i_limits) {
  char str[] = "2147483647 -2147483648";
  char fmt[] = "%i %i";
  int my1 = 0, my2 = 0;
  int orig1 = 0, orig2 = 0;

  int result_my = s21_sscanf(str, fmt, &my1, &my2);
  int result_orig = sscanf(str, fmt, &orig1, &orig2);

  ck_assert_int_eq(my1, orig1);
  ck_assert_int_eq(my2, orig2);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_i_invalid) {
  char str[] = "abc 123 xyz";
  char fmt[] = "%i %i %i";
  int my1 = 0, my2 = 0, my3 = 0;
  int orig1 = 0, orig2 = 0, orig3 = 0;

  int result_my = s21_sscanf(str, fmt, &my1, &my2, &my3);
  int result_orig = sscanf(str, fmt, &orig1, &orig2, &orig3);

  ck_assert_int_eq(my1, orig1);
  ck_assert_int_eq(my2, orig2);
  ck_assert_int_eq(my3, orig3);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_i_with_other_specifiers) {
  char str[] = "123 0xFF test 045";
  char fmt[] = "%i %i %s %i";
  int my1 = 0, my2 = 0, my4 = 0;
  int orig1 = 0, orig2 = 0, orig4 = 0;
  char my3[10] = {0}, orig3[10] = {0};

  int result_my = s21_sscanf(str, fmt, &my1, &my2, my3, &my4);
  int result_orig = sscanf(str, fmt, &orig1, &orig2, orig3, &orig4);

  ck_assert_int_eq(my1, orig1);
  ck_assert_int_eq(my2, orig2);
  ck_assert_int_eq(my4, orig4);
  ck_assert_str_eq(my3, orig3);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_i_star) {
  char str[] = "123 0xFF 045";
  char fmt[] = "%i %*i %i";
  int my1 = 0, my2 = 0;
  int orig1 = 0, orig2 = 0;

  int result_my = s21_sscanf(str, fmt, &my1, &my2);
  int result_orig = sscanf(str, fmt, &orig1, &orig2);

  ck_assert_int_eq(my1, orig1);
  ck_assert_int_eq(my2, orig2);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_i_width) {
  char str[] = "123456789";
  char fmt[] = "%3i";
  int my1 = 0;
  int orig1 = 0;

  int result_my = s21_sscanf(str, fmt, &my1);
  int result_orig = sscanf(str, fmt, &orig1);

  ck_assert_int_eq(my1, orig1);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

/////////////////////////////
/////// %eEfgG TESTS ///////
///////////////////////////
START_TEST(sscanf_e_basic) {
  char str[] = "1.5e2 3.14e-2 -2.5e+3";
  char fmt[] = "%e %e %e";
  float my1 = 0, my2 = 0, my3 = 0;
  float orig1 = 0, orig2 = 0, orig3 = 0;

  int result_my = s21_sscanf(str, fmt, &my1, &my2, &my3);
  int result_orig = sscanf(str, fmt, &orig1, &orig2, &orig3);

  ck_assert_float_eq_tol(my1, orig1, 1e-6);
  ck_assert_float_eq_tol(my2, orig2, 1e-6);
  ck_assert_float_eq_tol(my3, orig3, 1e-6);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_E_basic) {
  char str[] = "1.5E2 3.14E-2 -2.5E+3";
  char fmt[] = "%E %E %E";
  float my1 = 0, my2 = 0, my3 = 0;
  float orig1 = 0, orig2 = 0, orig3 = 0;

  int result_my = s21_sscanf(str, fmt, &my1, &my2, &my3);
  int result_orig = sscanf(str, fmt, &orig1, &orig2, &orig3);

  ck_assert_float_eq_tol(my1, orig1, 1e-6);
  ck_assert_float_eq_tol(my2, orig2, 1e-6);
  ck_assert_float_eq_tol(my3, orig3, 1e-6);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_f_basic) {
  char str[] = "3.14159 -2.71828 0.001";
  char fmt[] = "%f %f %f";
  float my1 = 0, my2 = 0, my3 = 0;
  float orig1 = 0, orig2 = 0, orig3 = 0;

  int result_my = s21_sscanf(str, fmt, &my1, &my2, &my3);
  int result_orig = sscanf(str, fmt, &orig1, &orig2, &orig3);

  ck_assert_float_eq_tol(my1, orig1, 1e-6);
  ck_assert_float_eq_tol(my2, orig2, 1e-6);
  ck_assert_float_eq_tol(my3, orig3, 1e-6);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_g_basic) {
  char str[] = "123.456 1.23e-4 1000000";
  char fmt[] = "%g %g %g";
  float my1 = 0, my2 = 0, my3 = 0;
  float orig1 = 0, orig2 = 0, orig3 = 0;

  int result_my = s21_sscanf(str, fmt, &my1, &my2, &my3);
  int result_orig = sscanf(str, fmt, &orig1, &orig2, &orig3);

  ck_assert_float_eq_tol(my1, orig1, 1e-6);
  ck_assert_float_eq_tol(my2, orig2, 1e-6);
  ck_assert_float_eq_tol(my3, orig3, 1e-6);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_G_basic) {
  char str[] = "123.456 1.23E-4 1000000";
  char fmt[] = "%G %G %G";
  float my1 = 0, my2 = 0, my3 = 0;
  float orig1 = 0, orig2 = 0, orig3 = 0;

  int result_my = s21_sscanf(str, fmt, &my1, &my2, &my3);
  int result_orig = sscanf(str, fmt, &orig1, &orig2, &orig3);

  ck_assert_float_eq_tol(my1, orig1, 1e-6);
  ck_assert_float_eq_tol(my2, orig2, 1e-6);
  ck_assert_float_eq_tol(my3, orig3, 1e-6);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_float_scientific_notation) {
  char str[] = "1e10 -2.5E-5 +3.14e+2";
  char fmt[] = "%e %E %g";
  float my1 = 0, my2 = 0, my3 = 0;
  float orig1 = 0, orig2 = 0, orig3 = 0;

  int result_my = s21_sscanf(str, fmt, &my1, &my2, &my3);
  int result_orig = sscanf(str, fmt, &orig1, &orig2, &orig3);

  ck_assert_float_eq_tol(my1, orig1, 1e-6);
  ck_assert_float_eq_tol(my2, orig2, 1e-6);
  ck_assert_float_eq_tol(my3, orig3, 1e-6);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_float_no_fractional) {
  char str[] = "123 .456 789.";
  char fmt[] = "%f %f %f";
  float my1 = 0, my2 = 0, my3 = 0;
  float orig1 = 0, orig2 = 0, orig3 = 0;

  int result_my = s21_sscanf(str, fmt, &my1, &my2, &my3);
  int result_orig = sscanf(str, fmt, &orig1, &orig2, &orig3);

  ck_assert_float_eq_tol(my1, orig1, 1e-6);
  ck_assert_float_eq_tol(my2, orig2, 1e-6);
  ck_assert_float_eq_tol(my3, orig3, 1e-6);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_float_width) {
  char str[] = "12.3456789";
  char fmt[] = "%4f";
  float my1 = 0;
  float orig1 = 0;

  int result_my = s21_sscanf(str, fmt, &my1);
  int result_orig = sscanf(str, fmt, &orig1);

  ck_assert_float_eq_tol(my1, orig1, 1e-6);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_exponential_width) {
  char str[] = "12.345e-005155";
  char fmt[] = "%1f";
  float my1 = 0;
  float orig1 = 0;

  int result_my = s21_sscanf(str, fmt, &my1);
  int result_orig = sscanf(str, fmt, &orig1);

  ck_assert_float_eq_tol(my1, orig1, 1e-6);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_float_star) {
  char str[] = "1.5 2.5 3.5";
  char fmt[] = "%f %*f %f";
  float my1 = 0, my2 = 0;
  float orig1 = 0, orig2 = 0;

  int result_my = s21_sscanf(str, fmt, &my1, &my2);
  int result_orig = sscanf(str, fmt, &orig1, &orig2);

  ck_assert_float_eq_tol(my1, orig1, 1e-6);
  ck_assert_float_eq_tol(my2, orig2, 1e-6);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_float_long) {
  char str[] = "1.23456789012345 -9.87654321098765";
  char fmt[] = "%le %LE";
  double my1 = 0, my2 = 0;
  double orig1 = 0, orig2 = 0;

  int result_my = s21_sscanf(str, fmt, &my1, &my2);
  int result_orig = sscanf(str, fmt, &orig1, &orig2);

  ck_assert_double_eq_tol(my1, orig1, 1e-12);
  ck_assert_double_eq_tol(my2, orig2, 1e-12);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_float_invalid) {
  char str[] = "abc 1.5 def";
  char fmt[] = "%f %f %f";
  float my1 = 0, my2 = 0, my3 = 0;
  float orig1 = 0, orig2 = 0, orig3 = 0;

  int result_my = s21_sscanf(str, fmt, &my1, &my2, &my3);
  int result_orig = sscanf(str, fmt, &orig1, &orig2, &orig3);

  ck_assert_float_eq_tol(my1, orig1, 1e-6);
  ck_assert_float_eq_tol(my2, orig2, 1e-6);
  ck_assert_float_eq_tol(my3, orig3, 1e-6);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_g_auto_notation) {
  char str[] = "1000 0.0001 123.456 1e-10";
  char fmt[] = "%g %g %g %g";
  float my1 = 0, my2 = 0, my3 = 0, my4 = 0;
  float orig1 = 0, orig2 = 0, orig3 = 0, orig4 = 0;

  int result_my = s21_sscanf(str, fmt, &my1, &my2, &my3, &my4);
  int result_orig = sscanf(str, fmt, &orig1, &orig2, &orig3, &orig4);

  ck_assert_float_eq_tol(my1, orig1, 1e-6);
  ck_assert_float_eq_tol(my2, orig2, 1e-6);
  ck_assert_float_eq_tol(my3, orig3, 1e-6);
  ck_assert_float_eq_tol(my4, orig4, 1e-6);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_float_mixed_specifiers) {
  char str[] = "1.5e2 3.14 2.5E-1 1000";
  char fmt[] = "%e %f %G %g";
  float my1 = 0, my2 = 0, my3 = 0, my4 = 0;
  float orig1 = 0, orig2 = 0, orig3 = 0, orig4 = 0;

  int result_my = s21_sscanf(str, fmt, &my1, &my2, &my3, &my4);
  int result_orig = sscanf(str, fmt, &orig1, &orig2, &orig3, &orig4);

  ck_assert_float_eq_tol(my1, orig1, 1e-6);
  ck_assert_float_eq_tol(my2, orig2, 1e-6);
  ck_assert_float_eq_tol(my3, orig3, 1e-6);
  ck_assert_float_eq_tol(my4, orig4, 1e-6);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_float_edge_cases) {
  char str[] = "0.0 -0.0 +0.0";
  char fmt[] = "%e %E %f";
  float my1 = 0, my2 = 0, my3 = 0;
  float orig1 = 0, orig2 = 0, orig3 = 0;

  int result_my = s21_sscanf(str, fmt, &my1, &my2, &my3);
  int result_orig = sscanf(str, fmt, &orig1, &orig2, &orig3);

  ck_assert_float_eq_tol(my1, orig1, 1e-6);
  ck_assert_float_eq_tol(my2, orig2, 1e-6);
  ck_assert_float_eq_tol(my3, orig3, 1e-6);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

/////////////////////////////
///////// %d TESTS /////////
///////////////////////////
START_TEST(sscanf_d_usual) {
  char str[] = " some text and then numbers +2141151 and -3415315  ";
  char fmt[] = " some text and then numbers %d and %d";
  int my1 = 0, my2 = 0;
  int orig1 = 0, orig2 = 0;
  int result_my = s21_sscanf(str, fmt, &my1, &my2);
  int result_orig = sscanf(str, fmt, &orig1, &orig2);
  ck_assert(my1 == orig1);
  ck_assert(my2 == orig2);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_d_usual_signed) {
  char str[] = " +2141151 and -3415315 ";
  char fmt[] = " %4d151 and %7d ";
  int my1 = 0, my2 = 0;
  int orig1 = 0, orig2 = 0;
  int result_my = s21_sscanf(str, fmt, &my1, &my2);
  int result_orig = sscanf(str, fmt, &orig1, &orig2);
  ck_assert(my1 == orig1);
  ck_assert(my2 == orig2);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_d_limits) {
  char str[] = " 	-2147483646 and +2147483647 and 545353434";
  char fmt[] = " %d and %d and %*6d ";
  int my1 = 0, my2 = 0, my3 = 0;
  int orig1 = 0, orig2 = 0, orig3 = 0;
  int result_my = s21_sscanf(str, fmt, &my1, &my2, &my3);
  int result_orig = sscanf(str, fmt, &orig1, &orig2, &orig3);
  ck_assert(my1 == orig1);
  ck_assert(my2 == orig2);
  ck_assert(my3 == orig3);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_d_scam) {
  char str[] = " 	-346 and +436 and    ";
  char fmt[] = " %d and %d and %*6d ";
  int my1 = 0, my2 = 0, my3 = 0;
  int orig1 = 0, orig2 = 0, orig3 = 0;
  int result_my = s21_sscanf(str, fmt, &my1, &my2, &my3);
  int result_orig = sscanf(str, fmt, &orig1, &orig2, &orig3);
  ck_assert(my1 == orig1);
  ck_assert(my2 == orig2);
  ck_assert(my3 == orig3);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_hd_limits) {
  char str[] = " -32768 and +32767 ";
  char fmt[] = " %hd and %hd ";
  short my1 = 0, my2 = 0;
  short orig1 = 0, orig2 = 0;
  int result_my = s21_sscanf(str, fmt, &my1, &my2);
  int result_orig = sscanf(str, fmt, &orig1, &orig2);
  ck_assert(my1 == orig1);
  ck_assert(my2 == orig2);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_hd_over_limits) {
  char str[] = " -40000 and +40000 ";
  char fmt[] = " %hd and %*hd ";
  short my1 = 0, my2 = 0;
  short orig1 = 0, orig2 = 0;
  int result_my = s21_sscanf(str, fmt, &my1, &my2);
  int result_orig = sscanf(str, fmt, &orig1, &orig2);
  ck_assert(my1 == orig1);
  ck_assert(my2 == orig2);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_hhd_overflow) {
  char str[] = " 255 and 300 ";
  char fmt[] = " %hhd and %*hhd ";
  unsigned char my1 = '\0', my2 = '\0';
  unsigned char orig1 = '\0', orig2 = '\0';
  int result_my = s21_sscanf(str, fmt, &my1, &my2);
  int result_orig = sscanf(str, fmt, &orig1, &orig2);
  ck_assert(my1 == orig1);
  ck_assert(my2 == orig2);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_hhd_overflow_star) {
  char str[] = " 255 and 300 ";
  char fmt[] = " %2hhd5 and %*2hhd0 ";
  unsigned char my1 = '\0', my2 = '\0';
  unsigned char orig1 = '\0', orig2 = '\0';
  int result_my = s21_sscanf(str, fmt, &my1, &my2);
  int result_orig = sscanf(str, fmt, &orig1, &orig2);
  ck_assert(my1 == orig1);
  ck_assert(my2 == orig2);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_ld_limits) {
  char str[] = " -2147483646 and 2147483647 ";
  char fmt[] = " %ld and %*ld ";
  long my1 = 0, my2 = 0;
  long orig1 = 0, orig2 = 0;
  int result_my = s21_sscanf(str, fmt, &my1, &my2);
  int result_orig = sscanf(str, fmt, &orig1, &orig2);
  ck_assert(my1 == orig1);
  ck_assert(my2 == orig2);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_ld_width) {
  char str[] = "  -21474836465 and 21474836475  ";
  char fmt[] = " %6ld36465 and %*6ld36475 ";
  long my1 = 0, my2 = 0;
  long orig1 = 0, orig2 = 0;
  int result_my = s21_sscanf(str, fmt, &my1, &my2);
  int result_orig = sscanf(str, fmt, &orig1, &orig2);
  ck_assert(my1 == orig1);
  ck_assert(my2 == orig2);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_lld_limits) {
  char str[] = "-9223372036854775806 and +9223372036854775807 and 555 ";
  char fmt[] = " %lld and % lld and % *lld ";
  long my1 = 0, my2 = 0, my3 = 0;
  long orig1 = 0, orig2 = 0, orig3 = 0;
  int result_my = s21_sscanf(str, fmt, &my1, &my2, &my3);
  int result_orig = sscanf(str, fmt, &orig1, &orig2, &orig3);
  ck_assert(my1 == orig1);
  ck_assert(my2 == orig2);
  ck_assert(my3 == orig3);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_d_hhd) {
  char str[] = "127 -128 0 55";
  char fmt[] = "%hhd %hhd %hhd %hhd";
  signed char my1 = 0, my2 = 0, my3 = 0, my4 = 0;
  signed char orig1 = 0, orig2 = 0, orig3 = 0, orig4 = 0;

  int result_my = s21_sscanf(str, fmt, &my1, &my2, &my3, &my4);
  int result_orig = sscanf(str, fmt, &orig1, &orig2, &orig3, &orig4);

  ck_assert_int_eq(my1, orig1);
  ck_assert_int_eq(my2, orig2);
  ck_assert_int_eq(my3, orig3);
  ck_assert_int_eq(my4, orig4);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_d_hd) {
  char str[] = "32767 -32768 0 12345";
  char fmt[] = "%hd %hd %hd %hd";
  short my1 = 0, my2 = 0, my3 = 0, my4 = 0;
  short orig1 = 0, orig2 = 0, orig3 = 0, orig4 = 0;

  int result_my = s21_sscanf(str, fmt, &my1, &my2, &my3, &my4);
  int result_orig = sscanf(str, fmt, &orig1, &orig2, &orig3, &orig4);

  ck_assert_int_eq(my1, orig1);
  ck_assert_int_eq(my2, orig2);
  ck_assert_int_eq(my3, orig3);
  ck_assert_int_eq(my4, orig4);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_d_ld) {
  char str[] = "2147483647 -2147483648 0 1234567890";
  char fmt[] = "%ld %ld %ld %ld";
  long my1 = 0, my2 = 0, my3 = 0, my4 = 0;
  long orig1 = 0, orig2 = 0, orig3 = 0, orig4 = 0;

  int result_my = s21_sscanf(str, fmt, &my1, &my2, &my3, &my4);
  int result_orig = sscanf(str, fmt, &orig1, &orig2, &orig3, &orig4);

  ck_assert_int_eq(my1, orig1);
  ck_assert_int_eq(my2, orig2);
  ck_assert_int_eq(my3, orig3);
  ck_assert_int_eq(my4, orig4);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_d_lld) {
  char str[] =
      "9223372036854775807 -9223372036854775808 0 123456789012345 224541";
  char fmt[] = "%lld %lld %lld %lld %*lld";
  long long my1 = 0, my2 = 0, my3 = 0, my4 = 0, my5 = 0;
  long long orig1 = 0, orig2 = 0, orig3 = 0, orig4 = 0, orig5 = 0;

  int result_my = s21_sscanf(str, fmt, &my1, &my2, &my3, &my4, &my5);
  int result_orig = sscanf(str, fmt, &orig1, &orig2, &orig3, &orig4, &orig5);

  ck_assert(my1 == orig1);
  ck_assert(my2 == orig2);
  ck_assert(my3 == orig3);
  ck_assert(my4 == orig4);
  ck_assert(my5 == orig5);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_d_mixed_modifiers) {
  char str[] = "127 32767 2147483647 9223372036854775807";
  char fmt[] = "%hhd %hd %ld %lld";
  signed char my1 = 0;
  short my2 = 0;
  long my3 = 0;
  long long my4 = 0;
  signed char orig1 = 0;
  short orig2 = 0;
  long orig3 = 0;
  long long orig4 = 0;

  int result_my = s21_sscanf(str, fmt, &my1, &my2, &my3, &my4);
  int result_orig = sscanf(str, fmt, &orig1, &orig2, &orig3, &orig4);

  ck_assert_int_eq(my1, orig1);
  ck_assert_int_eq(my2, orig2);
  ck_assert_int_eq(my3, orig3);
  ck_assert(my4 == orig4);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_d_modifiers_with_width) {
  char str[] = "12345 67890 11111";
  char fmt[] = "%3hhd %4hd %2ld";
  signed char my1 = 0;
  short my2 = 0;
  long my3 = 0;
  signed char orig1 = 0;
  short orig2 = 0;
  long orig3 = 0;

  int result_my = s21_sscanf(str, fmt, &my1, &my2, &my3);
  int result_orig = sscanf(str, fmt, &orig1, &orig2, &orig3);

  ck_assert_int_eq(my1, orig1);
  ck_assert_int_eq(my2, orig2);
  ck_assert_int_eq(my3, orig3);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_d_modifiers_with_star) {
  char str[] = "127 32767 2147483647";
  char fmt[] = "%hhd %*hd %ld";
  signed char my1 = 0;
  long my2 = 0;
  signed char orig1 = 0;
  long orig2 = 0;

  int result_my = s21_sscanf(str, fmt, &my1, &my2);
  int result_orig = sscanf(str, fmt, &orig1, &orig2);

  ck_assert_int_eq(my1, orig1);
  ck_assert_int_eq(my2, orig2);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_d_modifier_boundaries) {
  char str[] = "-128 127 -32768 32767 -2147483648 2147483647";
  char fmt[] = "%hhd %hhd %hd %hd %ld %ld";
  signed char my1 = 0, my2 = 0;
  short my3 = 0, my4 = 0;
  long my5 = 0, my6 = 0;
  signed char orig1 = 0, orig2 = 0;
  short orig3 = 0, orig4 = 0;
  long orig5 = 0, orig6 = 0;

  int result_my = s21_sscanf(str, fmt, &my1, &my2, &my3, &my4, &my5, &my6);
  int result_orig =
      sscanf(str, fmt, &orig1, &orig2, &orig3, &orig4, &orig5, &orig6);

  ck_assert_int_eq(my1, orig1);
  ck_assert_int_eq(my2, orig2);
  ck_assert_int_eq(my3, orig3);
  ck_assert_int_eq(my4, orig4);
  ck_assert_int_eq(my5, orig5);
  ck_assert_int_eq(my6, orig6);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_d_modifiers_invalid) {
  char str[] = "123 abc 456 def";
  char fmt[] = "%hhd %hd %ld %lld";
  signed char my1 = 0;
  short my2 = 0;
  long my3 = 0;
  long long my4 = 0;
  signed char orig1 = 0;
  short orig2 = 0;
  long orig3 = 0;
  long long orig4 = 0;

  int result_my = s21_sscanf(str, fmt, &my1, &my2, &my3, &my4);
  int result_orig = sscanf(str, fmt, &orig1, &orig2, &orig3, &orig4);

  ck_assert_int_eq(my1, orig1);
  ck_assert_int_eq(my2, orig2);
  ck_assert_int_eq(my3, orig3);
  ck_assert(my4 == orig4);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_d_modifiers_with_text) {
  char str[] = "Value1: 127, Value2: 32767, Value3: 2147483647";
  char fmt[] = "Value1: %hhd, Value2: %hd, Value3: %ld";
  signed char my1 = 0;
  short my2 = 0;
  long my3 = 0;
  signed char orig1 = 0;
  short orig2 = 0;
  long orig3 = 0;

  int result_my = s21_sscanf(str, fmt, &my1, &my2, &my3);
  int result_orig = sscanf(str, fmt, &orig1, &orig2, &orig3);

  ck_assert_int_eq(my1, orig1);
  ck_assert_int_eq(my2, orig2);
  ck_assert_int_eq(my3, orig3);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_d_basic) {
  char str[] = "123 -456 789";
  char fmt[] = "%d %d %d";
  int my1 = 0, my2 = 0, my3 = 0;
  int orig1 = 0, orig2 = 0, orig3 = 0;

  int result_my = s21_sscanf(str, fmt, &my1, &my2, &my3);
  int result_orig = sscanf(str, fmt, &orig1, &orig2, &orig3);

  ck_assert_int_eq(my1, orig1);
  ck_assert_int_eq(my2, orig2);
  ck_assert_int_eq(my3, orig3);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_d_with_text) {
  char str[] = "Numbers: 123 and -456 end";
  char fmt[] = "Numbers: %d and %d end";
  int my1 = 0, my2 = 0;
  int orig1 = 0, orig2 = 0;

  int result_my = s21_sscanf(str, fmt, &my1, &my2);
  int result_orig = sscanf(str, fmt, &orig1, &orig2);

  ck_assert_int_eq(my1, orig1);
  ck_assert_int_eq(my2, orig2);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_d_with_plus_minus) {
  char str[] = "+123 -456 +789 -0";
  char fmt[] = "%d %d %d %d";
  int my1 = 0, my2 = 0, my3 = 0, my4 = 0;
  int orig1 = 0, orig2 = 0, orig3 = 0, orig4 = 0;

  int result_my = s21_sscanf(str, fmt, &my1, &my2, &my3, &my4);
  int result_orig = sscanf(str, fmt, &orig1, &orig2, &orig3, &orig4);

  ck_assert_int_eq(my1, orig1);
  ck_assert_int_eq(my2, orig2);
  ck_assert_int_eq(my3, orig3);
  ck_assert_int_eq(my4, orig4);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_d_int_max_min) {
  char str[100];
  sprintf(str, "%d %d", INT_MAX, INT_MIN);
  char fmt[] = "%d %d";
  int my1 = 0, my2 = 0;
  int orig1 = 0, orig2 = 0;

  int result_my = s21_sscanf(str, fmt, &my1, &my2);
  int result_orig = sscanf(str, fmt, &orig1, &orig2);

  ck_assert_int_eq(my1, orig1);
  ck_assert_int_eq(my2, orig2);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_d_zeros) {
  char str[] = "0 00 000 -0 +0";
  char fmt[] = "%d %d %d %d %d";
  int my1 = 0, my2 = 0, my3 = 0, my4 = 0, my5 = 0;
  int orig1 = 0, orig2 = 0, orig3 = 0, orig4 = 0, orig5 = 0;

  int result_my = s21_sscanf(str, fmt, &my1, &my2, &my3, &my4, &my5);
  int result_orig = sscanf(str, fmt, &orig1, &orig2, &orig3, &orig4, &orig5);

  ck_assert_int_eq(my1, orig1);
  ck_assert_int_eq(my2, orig2);
  ck_assert_int_eq(my3, orig3);
  ck_assert_int_eq(my4, orig4);
  ck_assert_int_eq(my5, orig5);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_d_invalid_data) {
  char str[] = "123 abc -456 def";
  char fmt[] = "%d %d %d %d";
  int my1 = 0, my2 = 0, my3 = 0, my4 = 0;
  int orig1 = 0, orig2 = 0, orig3 = 0, orig4 = 0;

  int result_my = s21_sscanf(str, fmt, &my1, &my2, &my3, &my4);
  int result_orig = sscanf(str, fmt, &orig1, &orig2, &orig3, &orig4);

  ck_assert_int_eq(my1, orig1);
  ck_assert_int_eq(my2, orig2);
  ck_assert_int_eq(my3, orig3);
  ck_assert_int_eq(my4, orig4);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_d_only_invalid) {
  char str[] = "abc def ghi";
  char fmt[] = "%d %d %d";
  int my1 = 0, my2 = 0, my3 = 0;
  int orig1 = 0, orig2 = 0, orig3 = 0;

  int result_my = s21_sscanf(str, fmt, &my1, &my2, &my3);
  int result_orig = sscanf(str, fmt, &orig1, &orig2, &orig3);

  ck_assert_int_eq(my1, orig1);
  ck_assert_int_eq(my2, orig2);
  ck_assert_int_eq(my3, orig3);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_d_with_width) {
  char str[] = "123456789";
  char fmt[] = "%3d %2d %4d";
  int my1 = 0, my2 = 0, my3 = 0;
  int orig1 = 0, orig2 = 0, orig3 = 0;

  int result_my = s21_sscanf(str, fmt, &my1, &my2, &my3);
  int result_orig = sscanf(str, fmt, &orig1, &orig2, &orig3);

  ck_assert_int_eq(my1, orig1);
  ck_assert_int_eq(my2, orig2);
  ck_assert_int_eq(my3, orig3);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_d_with_star) {
  char str[] = "123 456 789";
  char fmt[] = "%d %*d %d";
  int my1 = 0, my2 = 0;
  int orig1 = 0, orig2 = 0;

  int result_my = s21_sscanf(str, fmt, &my1, &my2);
  int result_orig = sscanf(str, fmt, &orig1, &orig2);

  ck_assert_int_eq(my1, orig1);
  ck_assert_int_eq(my2, orig2);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_d_with_whitespace) {
  char str[] = "   123   \t-456   \n789   ";
  char fmt[] = "%d %d %d";
  int my1 = 0, my2 = 0, my3 = 0;
  int orig1 = 0, orig2 = 0, orig3 = 0;

  int result_my = s21_sscanf(str, fmt, &my1, &my2, &my3);
  int result_orig = sscanf(str, fmt, &orig1, &orig2, &orig3);

  ck_assert_int_eq(my1, orig1);
  ck_assert_int_eq(my2, orig2);
  ck_assert_int_eq(my3, orig3);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_d_partial_match) {
  char str[] = "123 and then 456";
  char fmt[] = "%d and then %d";
  int my1 = 0, my2 = 0;
  int orig1 = 0, orig2 = 0;

  int result_my = s21_sscanf(str, fmt, &my1, &my2);
  int result_orig = sscanf(str, fmt, &orig1, &orig2);

  ck_assert_int_eq(my1, orig1);
  ck_assert_int_eq(my2, orig2);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_d_empty_input) {
  char str[] = "";
  char fmt[] = "%d";
  int my1 = 0;
  int orig1 = 0;

  int result_my = s21_sscanf(str, fmt, &my1);
  int result_orig = sscanf(str, fmt, &orig1);

  ck_assert_int_eq(my1, orig1);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

/////////////////////////////
///////// %c TESTS /////////
///////////////////////////
START_TEST(sscanf_c_1) {
  char str[] = "  f  g  ";
  char fmt[] = " %c %*c ";
  char my1 = '\0', my2 = '\0';
  char orig1 = '\0', orig2 = '\0';
  int result_my = s21_sscanf(str, fmt, &my1, &my2);
  int result_orig = sscanf(str, fmt, &orig1, &orig2);
  ck_assert(my1 == orig1);
  ck_assert(my2 == orig2);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_c_2) {
  char str[] = "fg";
  char fmt[] = " %c %*c ";
  char my1 = '\0', my2 = '\0';
  char orig1 = '\0', orig2 = '\0';
  int result_my = s21_sscanf(str, fmt, &my1, &my2);
  int result_orig = sscanf(str, fmt, &orig1, &orig2);
  ck_assert(my1 == orig1);
  ck_assert(my2 == orig2);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_c_3) {
  char str[] = " f g ";
  char fmt[] = " %lc %*lc ";
  wchar_t my1 = '\0', my2 = '\0';
  wchar_t orig1 = '\0', orig2 = '\0';
  int result_my = s21_sscanf(str, fmt, &my1, &my2);
  int result_orig = sscanf(str, fmt, &orig1, &orig2);
  ck_assert(my1 == orig1);
  ck_assert(my2 == orig2);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_c_basic) {
  char str[] = "abc";
  char fmt[] = "%c%c%c";
  char my1 = 0, my2 = 0, my3 = 0;
  char orig1 = 0, orig2 = 0, orig3 = 0;

  int result_my = s21_sscanf(str, fmt, &my1, &my2, &my3);
  int result_orig = sscanf(str, fmt, &orig1, &orig2, &orig3);

  ck_assert_int_eq(my1, orig1);
  ck_assert_int_eq(my2, orig2);
  ck_assert_int_eq(my3, orig3);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_c_whitespace) {
  char str[] = "  a b  c";
  char fmt[] = " %c %c  %c";
  char my1 = 0, my2 = 0, my3 = 0;
  char orig1 = 0, orig2 = 0, orig3 = 0;

  int result_my = s21_sscanf(str, fmt, &my1, &my2, &my3);
  int result_orig = sscanf(str, fmt, &orig1, &orig2, &orig3);

  ck_assert_int_eq(my1, orig1);
  ck_assert_int_eq(my2, orig2);
  ck_assert_int_eq(my3, orig3);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_c_special_chars) {
  char str[] = "\n\t\x01 ";
  char fmt[] = "%c%c%c%c";
  char my1 = 0, my2 = 0, my3 = 0, my4 = 0;
  char orig1 = 0, orig2 = 0, orig3 = 0, orig4 = 0;

  int result_my = s21_sscanf(str, fmt, &my1, &my2, &my3, &my4);
  int result_orig = sscanf(str, fmt, &orig1, &orig2, &orig3, &orig4);

  ck_assert_int_eq(my1, orig1);
  ck_assert_int_eq(my2, orig2);
  ck_assert_int_eq(my3, orig3);
  ck_assert_int_eq(my4, orig4);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_c_width) {
  char str[] = "abcdef";
  char fmt[] = "%2c%3c%1c";
  char my1[3] = {0}, my2[4] = {0}, my3[2] = {0};
  char orig1[3] = {0}, orig2[4] = {0}, orig3[2] = {0};

  int result_my = s21_sscanf(str, fmt, my1, my2, my3);
  int result_orig = sscanf(str, fmt, orig1, orig2, orig3);

  ck_assert_str_eq(my1, orig1);
  ck_assert_str_eq(my2, orig2);
  ck_assert_str_eq(my3, orig3);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_c_width_star) {
  char str[] = "abcd";
  char fmt[] = "%*1c%3c";
  char my1[4] = {0};
  char orig1[4] = {0};

  int result_my = s21_sscanf(str, fmt, my1);
  int result_orig = sscanf(str, fmt, orig1);

  ck_assert_str_eq(my1, orig1);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_c_star) {
  char str[] = "abcde";
  char fmt[] = "%c%*c%c%*c%c";
  char my1 = 0, my2 = 0, my3 = 0;
  char orig1 = 0, orig2 = 0, orig3 = 0;

  int result_my = s21_sscanf(str, fmt, &my1, &my2, &my3);
  int result_orig = sscanf(str, fmt, &orig1, &orig2, &orig3);

  ck_assert_int_eq(my1, orig1);
  ck_assert_int_eq(my2, orig2);
  ck_assert_int_eq(my3, orig3);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_lc_wide_chars) {
  char str[] = "w i d e";
  char fmt[] = "%lc %lc %lc %lc";
  wchar_t my1 = 0, my2 = 0, my3 = 0, my4 = 0;
  wchar_t orig1 = 0, orig2 = 0, orig3 = 0, orig4 = 0;

  int result_my = s21_sscanf(str, fmt, &my1, &my2, &my3, &my4);
  int result_orig = sscanf(str, fmt, &orig1, &orig2, &orig3, &orig4);

  ck_assert_int_eq(my1, orig1);
  ck_assert_int_eq(my2, orig2);
  ck_assert_int_eq(my3, orig3);
  ck_assert_int_eq(my4, orig4);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_lc_width) {
  char str[] = "widechars";
  char fmt[] = "%2lc%3lc%1lc";
  wchar_t my1[3] = {0}, my2[4] = {0}, my3[2] = {0};
  wchar_t orig1[3] = {0}, orig2[4] = {0}, orig3[2] = {0};

  int result_my = s21_sscanf(str, fmt, my1, my2, my3);
  int result_orig = sscanf(str, fmt, orig1, orig2, orig3);

  for (int i = 0; i < 2; i++) {
    ck_assert_int_eq(my1[i], orig1[i]);
  }
  for (int i = 0; i < 3; i++) {
    ck_assert_int_eq(my2[i], orig2[i]);
  }
  for (int i = 0; i < 1; i++) {
    ck_assert_int_eq(my3[i], orig3[i]);
  }
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_lc_star) {
  char str[] = "abcde";
  char fmt[] = "%lc%*lc%lc%*lc%lc";
  wchar_t my1 = 0, my2 = 0, my3 = 0;
  wchar_t orig1 = 0, orig2 = 0, orig3 = 0;

  int result_my = s21_sscanf(str, fmt, &my1, &my2, &my3);
  int result_orig = sscanf(str, fmt, &orig1, &orig2, &orig3);

  ck_assert_int_eq(my1, orig1);
  ck_assert_int_eq(my2, orig2);
  ck_assert_int_eq(my3, orig3);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_c_mixed_types) {
  char str[] = "A 65 test";
  char fmt[] = "%c %d %s";
  char my1 = 0;
  int my2 = 0;
  char my3[10] = {0};
  char orig1 = 0;
  int orig2 = 0;
  char orig3[10] = {0};

  int result_my = s21_sscanf(str, fmt, &my1, &my2, my3);
  int result_orig = sscanf(str, fmt, &orig1, &orig2, orig3);

  ck_assert_int_eq(my1, orig1);
  ck_assert_int_eq(my2, orig2);
  ck_assert_str_eq(my3, orig3);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_c_mixed_lengths) {
  char str[] = "a b c";
  char fmt[] = "%c %lc %c";
  char my1 = 0;
  wchar_t my2 = 0;
  char my3 = 0;
  char orig1 = 0;
  wchar_t orig2 = 0;
  char orig3 = 0;

  int result_my = s21_sscanf(str, fmt, &my1, &my2, &my3);
  int result_orig = sscanf(str, fmt, &orig1, &orig2, &orig3);

  ck_assert_int_eq(my1, orig1);
  ck_assert_int_eq(my2, orig2);
  ck_assert_int_eq(my3, orig3);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_c_empty_input) {
  char str[] = "";
  char fmt[] = "%c";
  char my1 = 0;
  char orig1 = 0;

  int result_my = s21_sscanf(str, fmt, &my1);
  int result_orig = sscanf(str, fmt, &orig1);

  ck_assert_int_eq(my1, orig1);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_c_both_empty) {
  char str[] = "";
  char fmt[] = "";
  char my1 = 0;
  char orig1 = 0;

  int result_my = s21_sscanf(str, fmt, &my1);
  int result_orig = sscanf(str, fmt, &orig1);

  ck_assert_int_eq(my1, orig1);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_c_only_whitespace) {
  char str[] = "   ";
  char fmt[] = "%c %c %c";
  char my1 = 0, my2 = 0, my3 = 0;
  char orig1 = 0, orig2 = 0, orig3 = 0;

  int result_my = s21_sscanf(str, fmt, &my1, &my2, &my3);
  int result_orig = sscanf(str, fmt, &orig1, &orig2, &orig3);

  ck_assert_int_eq(my1, orig1);
  ck_assert_int_eq(my2, orig2);
  ck_assert_int_eq(my3, orig3);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_c_newlines) {
  char str[] = "a\nb\nc";
  char fmt[] = "%c%c%c";
  char my1 = 0, my2 = 0, my3 = 0;
  char orig1 = 0, orig2 = 0, orig3 = 0;

  int result_my = s21_sscanf(str, fmt, &my1, &my2, &my3);
  int result_orig = sscanf(str, fmt, &orig1, &orig2, &orig3);
  ck_assert_int_eq(my1, orig1);
  ck_assert_int_eq(my2, orig2);
  ck_assert_int_eq(my3, orig3);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_c_null_char) {
  char str[] = "a\0b\0c";
  char fmt[] = "%c%c";
  char my1 = 0, my2 = 0;
  char orig1 = 0, orig2 = 0;

  int result_my = s21_sscanf(str, fmt, &my1, &my2);
  int result_orig = sscanf(str, fmt, &orig1, &orig2);

  ck_assert_int_eq(my1, orig1);
  ck_assert_int_eq(my2, orig2);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_c_complex_pattern) {
  char str[] = "X: 65, Y: 66, Z: 67";
  char fmt[] = "%c: %*d, %c: %*d, %c: %*d";
  char my1 = 0, my2 = 0, my3 = 0;
  char orig1 = 0, orig2 = 0, orig3 = 0;

  int result_my = s21_sscanf(str, fmt, &my1, &my2, &my3);
  int result_orig = sscanf(str, fmt, &orig1, &orig2, &orig3);

  ck_assert_int_eq(my1, orig1);
  ck_assert_int_eq(my2, orig2);
  ck_assert_int_eq(my3, orig3);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(invalid_specifier) {
  char str[] = "65 66 67";
  char fmt[] = "%j: %*k, %c";
  char my1 = 0, my2 = 0, my3 = 0;
  char orig1 = 0, orig2 = 0, orig3 = 0;

  int result_my = s21_sscanf(str, fmt, &my1, &my2, &my3);
  int result_orig = sscanf(str, fmt, &orig1, &orig2, &orig3);

  ck_assert_int_eq(my1, orig1);
  ck_assert_int_eq(my2, orig2);
  ck_assert_int_eq(my3, orig3);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

/////////////////////////////
///////// %s TESTS /////////
///////////////////////////
START_TEST(sscanf_s_usual) {
  char str[] = "Hello World Test";
  char fmt[] = "%s %s %s";
  char my1[20] = {0}, my2[20] = {0}, my3[20] = {0};
  char orig1[20] = {0}, orig2[20] = {0}, orig3[20] = {0};

  int result_my = s21_sscanf(str, fmt, my1, my2, my3);
  int result_orig = sscanf(str, fmt, orig1, orig2, orig3);

  ck_assert_str_eq(my1, orig1);
  ck_assert_str_eq(my2, orig2);
  ck_assert_str_eq(my3, orig3);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_s_width) {
  char str[] = "abcdefghijk";
  char fmt[] = "%3s %4s %2s";
  char my1[10] = {0}, my2[10] = {0}, my3[10] = {0};
  char orig1[10] = {0}, orig2[10] = {0}, orig3[10] = {0};

  int result_my = s21_sscanf(str, fmt, my1, my2, my3);
  int result_orig = sscanf(str, fmt, orig1, orig2, orig3);

  ck_assert_str_eq(my1, orig1);
  ck_assert_str_eq(my2, orig2);
  ck_assert_str_eq(my3, orig3);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_s_star) {
  char str[] = "skip this and read this";
  char fmt[] = "%*s %*s %*s %s";
  char my1[20] = {0};
  char orig1[20] = {0};

  int result_my = s21_sscanf(str, fmt, my1);
  int result_orig = sscanf(str, fmt, orig1);

  ck_assert_str_eq(my1, orig1);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_s_width_star) {
  char str[] = "abcdefghijklmnop";
  char fmt[] = "%3s %*4s %2s";
  char my1[10] = {0}, my2[10] = {0};
  char orig1[10] = {0}, orig2[10] = {0};

  int result_my = s21_sscanf(str, fmt, my1, my2);
  int result_orig = sscanf(str, fmt, orig1, orig2);

  ck_assert_str_eq(my1, orig1);
  ck_assert_str_eq(my2, orig2);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_s_whitespace) {
  char str[] = "   Hello   World\tTest\nString";
  char fmt[] = "%s %s %s %s";
  char my1[20] = {0}, my2[20] = {0}, my3[20] = {0}, my4[20] = {0};
  char orig1[20] = {0}, orig2[20] = {0}, orig3[20] = {0}, orig4[20] = {0};

  int result_my = s21_sscanf(str, fmt, my1, my2, my3, my4);
  int result_orig = sscanf(str, fmt, orig1, orig2, orig3, orig4);

  ck_assert_str_eq(my1, orig1);
  ck_assert_str_eq(my2, orig2);
  ck_assert_str_eq(my3, orig3);
  ck_assert_str_eq(my4, orig4);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_s_empty_strings) {
  char str[] = "  first  second  ";
  char fmt[] = "%s %s";
  char my1[20] = {0}, my2[20] = {0};
  char orig1[20] = {0}, orig2[20] = {0};

  int result_my = s21_sscanf(str, fmt, my1, my2);
  int result_orig = sscanf(str, fmt, orig1, orig2);

  ck_assert_str_eq(my1, orig1);
  ck_assert_str_eq(my2, orig2);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_s_special_chars) {
  char str[] = "hello123 test_vsbdfb fhshfd-word";
  char fmt[] = "%s %s %s";
  char my1[30] = {0}, my2[30] = {0}, my3[30] = {0};
  char orig1[30] = {0}, orig2[30] = {0}, orig3[30] = {0};

  int result_my = s21_sscanf(str, fmt, my1, my2, my3);
  int result_orig = sscanf(str, fmt, orig1, orig2, orig3);

  ck_assert_str_eq(my1, orig1);
  ck_assert_str_eq(my2, orig2);
  ck_assert_str_eq(my3, orig3);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_s_buffer_limits) {
  char str[] = "abcdefghijklmnop";
  char fmt[] = "%5s %3s";
  char my1[6] = {0}, my2[4] = {0};
  char orig1[6] = {0}, orig2[4] = {0};

  int result_my = s21_sscanf(str, fmt, my1, my2);
  int result_orig = sscanf(str, fmt, orig1, orig2);

  ck_assert_str_eq(my1, orig1);
  ck_assert_str_eq(my2, orig2);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_s_with_text) {
  char str[] = "Name: John Age: 25 City: London";
  char fmt[] = "Name: %s Age: %s City: %s";
  char my1[20] = {0}, my2[20] = {0}, my3[20] = {0};
  char orig1[20] = {0}, orig2[20] = {0}, orig3[20] = {0};

  int result_my = s21_sscanf(str, fmt, my1, my2, my3);
  int result_orig = sscanf(str, fmt, orig1, orig2, orig3);

  ck_assert_str_eq(my1, orig1);
  ck_assert_str_eq(my2, orig2);
  ck_assert_str_eq(my3, orig3);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_s_partial_match) {
  char str[] = "first second third";
  char fmt[] = "%s %s %s %s";
  char my1[20] = {0}, my2[20] = {0}, my3[20] = {0}, my4[20] = {0};
  char orig1[20] = {0}, orig2[20] = {0}, orig3[20] = {0}, orig4[20] = {0};

  int result_my = s21_sscanf(str, fmt, my1, my2, my3, my4);
  int result_orig = sscanf(str, fmt, orig1, orig2, orig3, orig4);

  ck_assert_str_eq(my1, orig1);
  ck_assert_str_eq(my2, orig2);
  ck_assert_str_eq(my3, orig3);
  ck_assert_str_eq(my4, orig4);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_s_empty_input) {
  char str[] = "";
  char fmt[] = "%s";
  char my1[20] = {0};
  char orig1[20] = {0};

  int result_my = s21_sscanf(str, fmt, my1);
  int result_orig = sscanf(str, fmt, orig1);

  ck_assert_str_eq(my1, orig1);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_s_long_string) {
  char str[] = "jnbjbndbndfbndfobndfonbdfnbdfnbdfnbdfjnb bhdfbuhdfbudfhbudfhb";
  char fmt[] = "%s %s";
  char my1[100] = {0}, my2[100] = {0};
  char orig1[100] = {0}, orig2[100] = {0};

  int result_my = s21_sscanf(str, fmt, my1, my2);
  int result_orig = sscanf(str, fmt, orig1, orig2);

  ck_assert_str_eq(my1, orig1);
  ck_assert_str_eq(my2, orig2);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_s_l_modifier) {
  char str[] = "Hello World";
  char fmt[] = "%ls %ls";
  wchar_t my1[20] = {0}, my2[20] = {0};
  wchar_t orig1[20] = {0}, orig2[20] = {0};

  int result_my = s21_sscanf(str, fmt, my1, my2);
  int result_orig = sscanf(str, fmt, orig1, orig2);

  ck_assert(wcscmp(my1, orig1) == 0);
  ck_assert(wcscmp(my2, orig2) == 0);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_s_l_modifier_width) {
  char str[] = "abcdefghij";
  char fmt[] = "%3ls %2ls";
  wchar_t my1[10] = {0}, my2[10] = {0};
  wchar_t orig1[10] = {0}, orig2[10] = {0};

  int result_my = s21_sscanf(str, fmt, my1, my2);
  int result_orig = sscanf(str, fmt, orig1, orig2);

  ck_assert(wcscmp(my1, orig1) == 0);
  ck_assert(wcscmp(my2, orig2) == 0);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_s_until_newline) {
  char str[] = "first second\nthird fourth";
  char fmt[] = "%s %s";
  char my1[20] = {0}, my2[20] = {0};
  char orig1[20] = {0}, orig2[20] = {0};

  int result_my = s21_sscanf(str, fmt, my1, my2);
  int result_orig = sscanf(str, fmt, orig1, orig2);

  ck_assert_str_eq(my1, orig1);
  ck_assert_str_eq(my2, orig2);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_s_different_delimiters) {
  char str[] = "word1,word2;word3.word4";
  char fmt[] = "%s %s %s %s";
  char my1[20] = {0}, my2[20] = {0}, my3[20] = {0}, my4[20] = {0};
  char orig1[20] = {0}, orig2[20] = {0}, orig3[20] = {0}, orig4[20] = {0};

  int result_my = s21_sscanf(str, fmt, my1, my2, my3, my4);
  int result_orig = sscanf(str, fmt, orig1, orig2, orig3, orig4);

  ck_assert_str_eq(my1, orig1);
  ck_assert_str_eq(my2, orig2);
  ck_assert_str_eq(my3, orig3);
  ck_assert_str_eq(my4, orig4);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

/////////////////////////////
///////// %% TESTS /////////
///////////////////////////

#pragma GCC diagnostic push  // Сохраняем текущие настройки диагностики
#pragma GCC diagnostic ignored \
    "-Wformat-security"  // Временно игнорируем предупреждения о неверном
                         // формате
START_TEST(sscanf_percent_basic) {
  char str[] = "%";
  char fmt[] = "%%";

  int result_my = s21_sscanf(str, fmt);
  int result_orig = sscanf(str, fmt);

  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_percent_multiple) {
  char str[] = "%%%";
  char fmt[] = "%%%%%%";

  int result_my = s21_sscanf(str, fmt);
  int result_orig = sscanf(str, fmt);

  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_percent_with_text) {
  char str[] = "Hello % World";
  char fmt[] = "Hello %% World";

  int result_my = s21_sscanf(str, fmt);
  int result_orig = sscanf(str, fmt);

  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_percent_mixed_specifiers) {
  char str[] = "25% discount 50%";
  char fmt[] = "%d%% discount %d%%";
  int my1 = 0, my2 = 0;
  int orig1 = 0, orig2 = 0;

  int result_my = s21_sscanf(str, fmt, &my1, &my2);
  int result_orig = sscanf(str, fmt, &orig1, &orig2);

  ck_assert_int_eq(my1, orig1);
  ck_assert_int_eq(my2, orig2);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_percent_complex) {
  char str[] = "Price: $100 (15% tax) Total: $115";
  char fmt[] = "Price: $%d (%d%% tax) Total: $%d";
  int my1 = 0, my2 = 0, my3 = 0;
  int orig1 = 0, orig2 = 0, orig3 = 0;

  int result_my = s21_sscanf(str, fmt, &my1, &my2, &my3);
  int result_orig = sscanf(str, fmt, &orig1, &orig2, &orig3);

  ck_assert_int_eq(my1, orig1);
  ck_assert_int_eq(my2, orig2);
  ck_assert_int_eq(my3, orig3);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_percent_whitespace) {
  char str[] = "   %   %   %   ";
  char fmt[] = "%% %% %%";

  int result_my = s21_sscanf(str, fmt);
  int result_orig = sscanf(str, fmt);

  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_percent_start) {
  char str[] = "% Hello";
  char fmt[] = "%% Hello";

  int result_my = s21_sscanf(str, fmt);
  int result_orig = sscanf(str, fmt);

  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_percent_end) {
  char str[] = "Hello %";
  char fmt[] = "Hello %%";

  int result_my = s21_sscanf(str, fmt);
  int result_orig = sscanf(str, fmt);

  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_percent_mismatch) {
  char str[] = "Hello World";
  char fmt[] = "Hello %% World";

  int result_my = s21_sscanf(str, fmt);
  int result_orig = sscanf(str, fmt);

  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_percent_partial_match) {
  char str[] = "50%";
  char fmt[] = "%d%% complete";
  int my1 = 0;
  int orig1 = 0;

  int result_my = s21_sscanf(str, fmt, &my1);
  int result_orig = sscanf(str, fmt, &orig1);

  ck_assert_int_eq(my1, orig1);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_percent_with_hex) {
  char str[] = "Memory: 0xFF% used";
  char fmt[] = "Memory: %X%% used";
  unsigned int my1 = 0;
  unsigned int orig1 = 0;

  int result_my = s21_sscanf(str, fmt, &my1);
  int result_orig = sscanf(str, fmt, &orig1);

  ck_assert_uint_eq(my1, orig1);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_percent_with_octal) {
  char str[] = "Permission: 755% secure";
  char fmt[] = "Permission: %o%% secure";
  unsigned int my1 = 0;
  unsigned int orig1 = 0;

  int result_my = s21_sscanf(str, fmt, &my1);
  int result_orig = sscanf(str, fmt, &orig1);

  ck_assert_uint_eq(my1, orig1);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_percent_with_unsigned) {
  char str[] = "Battery: 85% charged";
  char fmt[] = "Battery: %u%% charged";
  unsigned int my1 = 0;
  unsigned int orig1 = 0;

  int result_my = s21_sscanf(str, fmt, &my1);
  int result_orig = sscanf(str, fmt, &orig1);

  ck_assert_uint_eq(my1, orig1);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_percent_with_size_modifiers) {
  char str[] = "Values: 100% 200% 300%";
  char fmt[] = "Values: %hd%% %ld%% %lld%%";
  short my1 = 0;
  long my2 = 0;
  long long my3 = 0;
  short orig1 = 0;
  long orig2 = 0;
  long long orig3 = 0;

  int result_my = s21_sscanf(str, fmt, &my1, &my2, &my3);
  int result_orig = sscanf(str, fmt, &orig1, &orig2, &orig3);

  ck_assert_int_eq(my1, orig1);
  ck_assert_int_eq(my2, orig2);
  ck_assert_int_eq(my3, orig3);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_percent_with_string_width) {
  char str[] = "File: test.txt 75% processed";
  char fmt[] = "File: %5s %d%% processed";
  char my1[10] = {0};
  int my2 = 0;
  char orig1[10] = {0};
  int orig2 = 0;

  int result_my = s21_sscanf(str, fmt, my1, &my2);
  int result_orig = sscanf(str, fmt, orig1, &orig2);

  ck_assert_str_eq(my1, orig1);
  ck_assert_int_eq(my2, orig2);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_percent_with_star) {
  char str[] = "Data: 50% 75% 100%";
  char fmt[] = "Data: %*d%% %d%% %*d%%";
  int my1 = 0;
  int orig1 = 0;

  int result_my = s21_sscanf(str, fmt, &my1);
  int result_orig = sscanf(str, fmt, &orig1);

  ck_assert_int_eq(my1, orig1);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_percent_literal) {
  char str[] = "100%% completion rate";
  char fmt[] = "%d%% completion rate";
  int my1 = 0;
  int orig1 = 0;

  int result_my = s21_sscanf(str, fmt, &my1);
  int result_orig = sscanf(str, fmt, &orig1);

  ck_assert_int_eq(my1, orig1);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_percent_empty) {
  char str[] = "";
  char fmt[] = "%%";

  int result_my = s21_sscanf(str, fmt);
  int result_orig = sscanf(str, fmt);

  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_percent_complex_mix) {
  char str[] = "Start %% Middle 42%% End%%";
  char fmt[] = "Start %% Middle %d%% End%%";
  int my1 = 0;
  int orig1 = 0;

  int result_my = s21_sscanf(str, fmt, &my1);
  int result_orig = sscanf(str, fmt, &orig1);

  ck_assert_int_eq(my1, orig1);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

#pragma GCC diagnostic pop  // Восстанавливаем сохраненные настройки

/////////////////////////////
///////// %n TESTS /////////
///////////////////////////
START_TEST(sscanf_n_basic) {
  char str[] = "Hello World";
  char fmt[] = "Hello World%n";
  int my_count = 0;
  int orig_count = 0;

  int result_my = s21_sscanf(str, fmt, &my_count);
  int result_orig = sscanf(str, fmt, &orig_count);

  ck_assert_int_eq(my_count, orig_count);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_n_middle) {
  char str[] = "123 abc 456";
  char fmt[] = "%d %n %s";
  int my1 = 0, my_count = 0;
  char my2[10] = {0};
  int orig1 = 0, orig_count = 0;
  char orig2[10] = {0};

  int result_my = s21_sscanf(str, fmt, &my1, &my_count, my2);
  int result_orig = sscanf(str, fmt, &orig1, &orig_count, orig2);

  ck_assert_int_eq(my1, orig1);
  ck_assert_int_eq(my_count, orig_count);
  ck_assert_str_eq(my2, orig2);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_n_beginning) {
  char str[] = "Test string";
  char fmt[] = "%nTest string";
  int my_count = 0;
  int orig_count = 0;

  int result_my = s21_sscanf(str, fmt, &my_count);
  int result_orig = sscanf(str, fmt, &orig_count);

  ck_assert_int_eq(my_count, orig_count);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_n_end) {
  char str[] = "Hello World";
  char fmt[] = "Hello World%n";
  int my_count = 0;
  int orig_count = 0;

  int result_my = s21_sscanf(str, fmt, &my_count);
  int result_orig = sscanf(str, fmt, &orig_count);

  ck_assert_int_eq(my_count, orig_count);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_n_multiple) {
  char str[] = "123 abc 456 def";
  char fmt[] = "%d %n %s %n %d %n %s";
  int my1 = 0, my_count1 = 0, my_count2 = 0, my_count3 = 0;
  char my2[10] = {0};
  int my3 = 0;
  char my4[10] = {0};
  int orig1 = 0, orig_count1 = 0, orig_count2 = 0, orig_count3 = 0;
  char orig2[10] = {0};
  int orig3 = 0;
  char orig4[10] = {0};

  int result_my = s21_sscanf(str, fmt, &my1, &my_count1, my2, &my_count2, &my3,
                             &my_count3, my4);
  int result_orig = sscanf(str, fmt, &orig1, &orig_count1, orig2, &orig_count2,
                           &orig3, &orig_count3, orig4);

  ck_assert_int_eq(my1, orig1);
  ck_assert_int_eq(my_count1, orig_count1);
  ck_assert_str_eq(my2, orig2);
  ck_assert_int_eq(my_count2, orig_count2);
  ck_assert_int_eq(my3, orig3);
  ck_assert_int_eq(my_count3, orig_count3);
  ck_assert_str_eq(my4, orig4);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_n_with_hex) {
  char str[] = "0xABC 0xDEF";
  char fmt[] = "%x %n %x";
  unsigned int my1 = 0, my_count = 0, my2 = 0;
  unsigned int orig1 = 0, orig_count = 0, orig2 = 0;

  int result_my = s21_sscanf(str, fmt, &my1, &my_count, &my2);
  int result_orig = sscanf(str, fmt, &orig1, &orig_count, &orig2);

  ck_assert_uint_eq(my1, orig1);
  ck_assert_int_eq(my_count, orig_count);
  ck_assert_uint_eq(my2, orig2);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_n_with_octal) {
  char str[] = "777 123 456";
  char fmt[] = "%o %n %o %n %o";
  unsigned int my1 = 0, my_count1 = 0, my2 = 0, my_count2 = 0, my3 = 0;
  unsigned int orig1 = 0, orig_count1 = 0, orig2 = 0, orig_count2 = 0,
               orig3 = 0;

  int result_my =
      s21_sscanf(str, fmt, &my1, &my_count1, &my2, &my_count2, &my3);
  int result_orig =
      sscanf(str, fmt, &orig1, &orig_count1, &orig2, &orig_count2, &orig3);

  ck_assert_uint_eq(my1, orig1);
  ck_assert_int_eq(my_count1, orig_count1);
  ck_assert_uint_eq(my2, orig2);
  ck_assert_int_eq(my_count2, orig_count2);
  ck_assert_uint_eq(my3, orig3);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_n_with_unsigned) {
  char str[] = "100 200 300";
  char fmt[] = "%u %n %u %n %u";
  unsigned int my1 = 0, my_count1 = 0, my2 = 0, my_count2 = 0, my3 = 0;
  unsigned int orig1 = 0, orig_count1 = 0, orig2 = 0, orig_count2 = 0,
               orig3 = 0;

  int result_my =
      s21_sscanf(str, fmt, &my1, &my_count1, &my2, &my_count2, &my3);
  int result_orig =
      sscanf(str, fmt, &orig1, &orig_count1, &orig2, &orig_count2, &orig3);

  ck_assert_uint_eq(my1, orig1);
  ck_assert_int_eq(my_count1, orig_count1);
  ck_assert_uint_eq(my2, orig2);
  ck_assert_int_eq(my_count2, orig_count2);
  ck_assert_uint_eq(my3, orig3);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_n_with_string_width) {
  char str[] = "abcdefghijk";
  char fmt[] = "%5s %n %3s";
  char my1[10] = {0};
  int my_count = 0;
  char my2[10] = {0};
  char orig1[10] = {0};
  int orig_count = 0;
  char orig2[10] = {0};

  int result_my = s21_sscanf(str, fmt, my1, &my_count, my2);
  int result_orig = sscanf(str, fmt, orig1, &orig_count, orig2);

  ck_assert_str_eq(my1, orig1);
  ck_assert_int_eq(my_count, orig_count);
  ck_assert_str_eq(my2, orig2);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_n_with_chars) {
  char str[] = "A B C D";
  char fmt[] = "%c %n %c %n %c %n %c";
  char my1 = 0, my2 = 0, my3 = 0, my4 = 0;
  int my_count1 = 0, my_count2 = 0, my_count3 = 0;
  char orig1 = 0, orig2 = 0, orig3 = 0, orig4 = 0;
  int orig_count1 = 0, orig_count2 = 0, orig_count3 = 0;

  int result_my = s21_sscanf(str, fmt, &my1, &my_count1, &my2, &my_count2, &my3,
                             &my_count3, &my4);
  int result_orig = sscanf(str, fmt, &orig1, &orig_count1, &orig2, &orig_count2,
                           &orig3, &orig_count3, &orig4);

  ck_assert_int_eq(my1, orig1);
  ck_assert_int_eq(my_count1, orig_count1);
  ck_assert_int_eq(my2, orig2);
  ck_assert_int_eq(my_count2, orig_count2);
  ck_assert_int_eq(my3, orig3);
  ck_assert_int_eq(my_count3, orig_count3);
  ck_assert_int_eq(my4, orig4);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_n_no_star_suppression) {
  char str[] = "123 abc";
  char fmt[] = "%d %*s %n";
  int my1 = 0, my_count = 0;
  int orig1 = 0, orig_count = 0;

  int result_my = s21_sscanf(str, fmt, &my1, &my_count);
  int result_orig = sscanf(str, fmt, &orig1, &orig_count);

  ck_assert_int_eq(my1, orig1);
  ck_assert_int_eq(my_count, orig_count);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_n_whitespace) {
  char str[] = "   Hello   World  ";
  char fmt[] = "%s %n %s %n";
  char my1[10] = {0}, my2[10] = {0};
  int my_count1 = 0, my_count2 = 0;
  char orig1[10] = {0}, orig2[10] = {0};
  int orig_count1 = 0, orig_count2 = 0;

  int result_my = s21_sscanf(str, fmt, my1, &my_count1, my2, &my_count2);
  int result_orig = sscanf(str, fmt, orig1, &orig_count1, orig2, &orig_count2);

  ck_assert_str_eq(my1, orig1);
  ck_assert_int_eq(my_count1, orig_count1);
  ck_assert_str_eq(my2, orig2);
  ck_assert_int_eq(my_count2, orig_count2);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_n_with_wide_chars) {
  char str[] = "Hello World";
  char fmt[] = "Hello %ls %n";
  wchar_t my1[20] = {0};
  int my_count = 0;
  wchar_t orig1[20] = {0};
  int orig_count = 0;

  int result_my = s21_sscanf(str, fmt, my1, &my_count);
  int result_orig = sscanf(str, fmt, orig1, &orig_count);

  ck_assert(wcscmp(my1, orig1) == 0);
  ck_assert_int_eq(my_count, orig_count);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_n_all_modifiers) {
  char str[] = "123 456 789 1000";
  char fmt[] = "%hhd %hn %hd %hn %ld %hn %lld %hn";
  signed char my1 = 0;
  short my_count1 = 0;
  short my2 = 0;
  long my_count2 = 0;
  long my3 = 0;
  long long my_count3 = 0;
  long long my4 = 0;
  int my_count4 = 0;

  signed char orig1 = 0;
  short orig_count1 = 0;
  short orig2 = 0;
  long orig_count2 = 0;
  long orig3 = 0;
  long long orig_count3 = 0;
  long long orig4 = 0;
  int orig_count4 = 0;

  int result_my = s21_sscanf(str, fmt, &my1, &my_count1, &my2, &my_count2, &my3,
                             &my_count3, &my4, &my_count4);
  int result_orig = sscanf(str, fmt, &orig1, &orig_count1, &orig2, &orig_count2,
                           &orig3, &orig_count3, &orig4, &orig_count4);

  ck_assert_int_eq(my1, orig1);
  ck_assert_int_eq(my_count1, orig_count1);
  ck_assert_int_eq(my2, orig2);
  ck_assert_int_eq(my_count2, orig_count2);
  ck_assert_int_eq(my3, orig3);
  ck_assert(my_count3 == orig_count3);
  ck_assert(my4 == orig4);
  ck_assert_int_eq(my_count4, orig_count4);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

/////////////////////////////
///////// %p TESTS /////////
///////////////////////////
START_TEST(sscanf_p_basic) {
  char str[] = "0x12345678";
  char fmt[] = "%p";
  void *my_ptr = NULL;
  void *orig_ptr = NULL;

  int result_my = s21_sscanf(str, fmt, &my_ptr);
  int result_orig = sscanf(str, fmt, &orig_ptr);

  ck_assert_ptr_eq(my_ptr, orig_ptr);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_p_multiple) {
  char str[] = "0x12345678 0xABCDEF00 0x7FFE1234";
  char fmt[] = "%p %p %p";
  void *my1 = NULL, *my2 = NULL, *my3 = NULL;
  void *orig1 = NULL, *orig2 = NULL, *orig3 = NULL;

  int result_my = s21_sscanf(str, fmt, &my1, &my2, &my3);
  int result_orig = sscanf(str, fmt, &orig1, &orig2, &orig3);

  ck_assert_ptr_eq(my1, orig1);
  ck_assert_ptr_eq(my2, orig2);
  ck_assert_ptr_eq(my3, orig3);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_p_lowercase_hex) {
  char str[] = "0x123abc 0x456def";
  char fmt[] = "%p %p";
  void *my1 = NULL, *my2 = NULL;
  void *orig1 = NULL, *orig2 = NULL;

  int result_my = s21_sscanf(str, fmt, &my1, &my2);
  int result_orig = sscanf(str, fmt, &orig1, &orig2);

  ck_assert_ptr_eq(my1, orig1);
  ck_assert_ptr_eq(my2, orig2);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_p_uppercase_hex) {
  char str[] = "0X123ABC 0X456DEF";
  char fmt[] = "%p %p";
  void *my1 = NULL, *my2 = NULL;
  void *orig1 = NULL, *orig2 = NULL;

  int result_my = s21_sscanf(str, fmt, &my1, &my2);
  int result_orig = sscanf(str, fmt, &orig1, &orig2);

  ck_assert_ptr_eq(my1, orig1);
  ck_assert_ptr_eq(my2, orig2);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_p_no_prefix) {
  char str[] = "12345678 ABCDEF00";
  char fmt[] = "%p %p";
  void *my1 = NULL, *my2 = NULL;
  void *orig1 = NULL, *orig2 = NULL;

  int result_my = s21_sscanf(str, fmt, &my1, &my2);
  int result_orig = sscanf(str, fmt, &orig1, &orig2);

  ck_assert_ptr_eq(my1, orig1);
  ck_assert_ptr_eq(my2, orig2);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_p_zero_pointer) {
  char str[] = "0 0x0 00000000";
  char fmt[] = "%p %p %p";
  void *my1 = NULL, *my2 = NULL, *my3 = NULL;
  void *orig1 = NULL, *orig2 = NULL, *orig3 = NULL;

  int result_my = s21_sscanf(str, fmt, &my1, &my2, &my3);
  int result_orig = sscanf(str, fmt, &orig1, &orig2, &orig3);

  ck_assert_ptr_eq(my1, orig1);
  ck_assert_ptr_eq(my2, orig2);
  ck_assert_ptr_eq(my3, orig3);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_p_max_pointer) {
  char str[] = "0xFFFFFFFF 0xFFFFFFFFFF 0x7FFFFFFFFFFFFFFF";
  char fmt[] = "%p %p %p";
  void *my1 = NULL, *my2 = NULL, *my3 = NULL;
  void *orig1 = NULL, *orig2 = NULL, *orig3 = NULL;

  int result_my = s21_sscanf(str, fmt, &my1, &my2, &my3);
  int result_orig = sscanf(str, fmt, &orig1, &orig2, &orig3);

  ck_assert_ptr_eq(my1, orig1);
  ck_assert_ptr_eq(my2, orig2);
  ck_assert_ptr_eq(my3, orig3);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_p_with_text) {
  char str[] = "Pointer: 0x12345678 Address: 0xABCDEF00";
  char fmt[] = "Pointer: %p Address: %p";
  void *my1 = NULL, *my2 = NULL;
  void *orig1 = NULL, *orig2 = NULL;

  int result_my = s21_sscanf(str, fmt, &my1, &my2);
  int result_orig = sscanf(str, fmt, &orig1, &orig2);

  ck_assert_ptr_eq(my1, orig1);
  ck_assert_ptr_eq(my2, orig2);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_p_whitespace) {
  char str[] = "   0x12345678   \t  0xABCDEF00   \n  0x123ABC   ";
  char fmt[] = "%p %p %p";
  void *my1 = NULL, *my2 = NULL, *my3 = NULL;
  void *orig1 = NULL, *orig2 = NULL, *orig3 = NULL;

  int result_my = s21_sscanf(str, fmt, &my1, &my2, &my3);
  int result_orig = sscanf(str, fmt, &orig1, &orig2, &orig3);

  ck_assert_ptr_eq(my1, orig1);
  ck_assert_ptr_eq(my2, orig2);
  ck_assert_ptr_eq(my3, orig3);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_p_mixed_specifiers) {
  char str[] = "Value: 123 Pointer: 0x12345678 String: Hello";
  char fmt[] = "Value: %d Pointer: %p String: %s";
  int my1 = 0;
  void *my2 = NULL;
  char my3[20] = {0};
  int orig1 = 0;
  void *orig2 = NULL;
  char orig3[20] = {0};

  int result_my = s21_sscanf(str, fmt, &my1, &my2, my3);
  int result_orig = sscanf(str, fmt, &orig1, &orig2, orig3);

  ck_assert_int_eq(my1, orig1);
  ck_assert_ptr_eq(my2, orig2);
  ck_assert_str_eq(my3, orig3);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_p_with_width) {
  char str[] = "0x123456789ABCDEF0";
  char fmt[] = "%8p %16p";
  void *my1 = NULL, *my2 = NULL;
  void *orig1 = NULL, *orig2 = NULL;

  int result_my = s21_sscanf(str, fmt, &my1, &my2);
  int result_orig = sscanf(str, fmt, &orig1, &orig2);

  ck_assert_ptr_eq(my1, orig1);
  ck_assert_ptr_eq(my2, orig2);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_p_star) {
  char str[] = "0x12345678 0xABCDEF00 0x123ABC";
  char fmt[] = "%*p %p %*p";
  void *my1 = NULL;
  void *orig1 = NULL;

  int result_my = s21_sscanf(str, fmt, &my1);
  int result_orig = sscanf(str, fmt, &orig1);

  ck_assert_ptr_eq(my1, orig1);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_p_invalid_data) {
  char str[] = "0xGHIJKLM 0x12345678 invalid";
  char fmt[] = "%p %p %p";
  void *my1 = NULL, *my2 = NULL, *my3 = NULL;
  void *orig1 = NULL, *orig2 = NULL, *orig3 = NULL;

  int result_my = s21_sscanf(str, fmt, &my1, &my2, &my3);
  int result_orig = sscanf(str, fmt, &orig1, &orig2, &orig3);

  ck_assert_ptr_eq(my1, orig1);
  ck_assert_ptr_eq(my2, orig2);
  ck_assert_ptr_eq(my3, orig3);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_p_partial_match) {
  char str[] = "0x12345678";
  char fmt[] = "%p %p %p";
  void *my1 = NULL, *my2 = NULL, *my3 = NULL;
  void *orig1 = NULL, *orig2 = NULL, *orig3 = NULL;

  int result_my = s21_sscanf(str, fmt, &my1, &my2, &my3);
  int result_orig = sscanf(str, fmt, &orig1, &orig2, &orig3);

  ck_assert_ptr_eq(my1, orig1);
  ck_assert_ptr_eq(my2, orig2);
  ck_assert_ptr_eq(my3, orig3);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_p_different_bases) {
  char str[] = "01234567 0x12345678 123456789";
  char fmt[] = "%p %p %p";
  void *my1 = NULL, *my2 = NULL, *my3 = NULL;
  void *orig1 = NULL, *orig2 = NULL, *orig3 = NULL;

  int result_my = s21_sscanf(str, fmt, &my1, &my2, &my3);
  int result_orig = sscanf(str, fmt, &orig1, &orig2, &orig3);

  ck_assert_ptr_eq(my1, orig1);
  ck_assert_ptr_eq(my2, orig2);
  ck_assert_ptr_eq(my3, orig3);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_p_variable_digits) {
  char str[] = "0x1 0x12 0x123 0x1234 0x12345";
  char fmt[] = "%p %p %p %p %p";
  void *my1 = NULL, *my2 = NULL, *my3 = NULL, *my4 = NULL, *my5 = NULL;
  void *orig1 = NULL, *orig2 = NULL, *orig3 = NULL, *orig4 = NULL,
       *orig5 = NULL;

  int result_my = s21_sscanf(str, fmt, &my1, &my2, &my3, &my4, &my5);
  int result_orig = sscanf(str, fmt, &orig1, &orig2, &orig3, &orig4, &orig5);

  ck_assert_ptr_eq(my1, orig1);
  ck_assert_ptr_eq(my2, orig2);
  ck_assert_ptr_eq(my3, orig3);
  ck_assert_ptr_eq(my4, orig4);
  ck_assert_ptr_eq(my5, orig5);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_p_case_insensitive) {
  char str[] = "0xabcdef 0xABCDEF 0xAbCdEf";
  char fmt[] = "%p %p %p";
  void *my1 = NULL, *my2 = NULL, *my3 = NULL;
  void *orig1 = NULL, *orig2 = NULL, *orig3 = NULL;

  int result_my = s21_sscanf(str, fmt, &my1, &my2, &my3);
  int result_orig = sscanf(str, fmt, &orig1, &orig2, &orig3);

  ck_assert_ptr_eq(my1, orig1);
  ck_assert_ptr_eq(my2, orig2);
  ck_assert_ptr_eq(my3, orig3);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_p_empty_string) {
  char str[] = "";
  char fmt[] = "%p";
  void *my_ptr = NULL;
  void *orig_ptr = NULL;

  int result_my = s21_sscanf(str, fmt, &my_ptr);
  int result_orig = sscanf(str, fmt, &orig_ptr);

  ck_assert_ptr_eq(my_ptr, orig_ptr);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

START_TEST(sscanf_p_real_pointers) {
  int x = 42;
  char y = 'A';
  double z = 3.14;

  char str[256];
  sprintf(str, "%p %p %p", (void *)&x, (void *)&y, (void *)&z);

  char fmt[] = "%p %p %p";
  void *my1 = NULL, *my2 = NULL, *my3 = NULL;
  void *orig1 = NULL, *orig2 = NULL, *orig3 = NULL;

  int result_my = s21_sscanf(str, fmt, &my1, &my2, &my3);
  int result_orig = sscanf(str, fmt, &orig1, &orig2, &orig3);

  ck_assert_ptr_eq(my1, orig1);
  ck_assert_ptr_eq(my2, orig2);
  ck_assert_ptr_eq(my3, orig3);
  ck_assert_int_eq(result_my, result_orig);

  if (my1 != NULL) ck_assert_ptr_eq(my1, &x);
  if (my2 != NULL) ck_assert_ptr_eq(my2, &y);
  if (my3 != NULL) ck_assert_ptr_eq(my3, &z);
}
END_TEST

START_TEST(sscanf_p_ignore_modifiers) {
  char str[] = "0x12345678 0xABCDEF00";
  char fmt[] = "%hp %lp %llp";
  void *my1 = NULL, *my2 = NULL, *my3 = NULL;
  void *orig1 = NULL, *orig2 = NULL, *orig3 = NULL;

  int result_my = s21_sscanf(str, fmt, &my1, &my2, &my3);
  int result_orig = sscanf(str, fmt, &orig1, &orig2, &orig3);

  ck_assert_ptr_eq(my1, orig1);
  ck_assert_ptr_eq(my2, orig2);
  ck_assert_ptr_eq(my3, orig3);
  ck_assert_int_eq(result_my, result_orig);
}
END_TEST

/////////////////////////////
///// s21_sprintf TESTS ////
///////////////////////////
#pragma GCC diagnostic push  // Сохраняем текущие настройки диагностики
#pragma GCC diagnostic ignored "-Wformat-zero-length"
#pragma GCC diagnostic ignored "-Wformat"
#pragma GCC diagnostic ignored "-Wformat-overflow="
// Временно игнорируем предупреждения о неверном формате

START_TEST(test_sprintf_1) {
  char buf[10], buf1[10];
  int value = 42;
  int res = s21_sprintf(buf, "%d", value);
  int res1 = sprintf(buf1, "%d", value);
  ck_assert_str_eq(buf, buf1);
  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(test_sprintf_2) {
  char buf[12], buf1[12];
  int value = 42, value1 = 8;
  int res = s21_sprintf(buf, "%d + %d = %d", value, value1, value + value1);
  int res1 = sprintf(buf1, "%d + %d = %d", value, value1, value + value1);
  ck_assert_str_eq(buf, buf1);
  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(test_sprintf_3) {
  char buf[20], buf1[20];
  const char *str = "Hello, world";
  int res = s21_sprintf(buf, "%s", str);
  int res1 = sprintf(buf1, "%s", str);
  ck_assert_str_eq(buf, buf1);
  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(test_sprintf_4) {
  char buf[50], buf1[50];
  const char *str = "Hello, world";
  int value = 50;
  int res = s21_sprintf(buf, "Word: %s; value: %d", str, value);
  int res1 = sprintf(buf1, "Word: %s; value: %d", str, value);
  ck_assert_str_eq(buf, buf1);
  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(test_sprintf_5) {
  char buf[10], buf1[10];
  int value = -42;
  int res = s21_sprintf(buf, "%d", value);
  int res1 = sprintf(buf1, "%d", value);
  ck_assert_str_eq(buf, buf1);
  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(test_sprintf_6) {
  char buf[50], buf1[50];
  int res = s21_sprintf(buf, "%+d", 42);
  int res1 = sprintf(buf1, "%+d", 42);
  ck_assert_str_eq(buf, buf1);
  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(test_sprintf_7) {
  char c = 'A';
  char buf[10], buf1[10];
  int res = s21_sprintf(buf, "%c", c);
  int res1 = sprintf(buf1, "%c", c);
  ck_assert_str_eq(buf, buf1);
  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(test_sprintf_8) {
  char buf[50], buf1[50];
  int res = s21_sprintf(buf, "%-10d", 42);
  int res1 = sprintf(buf1, "%-10d", 42);
  ck_assert_str_eq(buf, buf1);
  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(test_sprintf_9) {
  char buf[50], buf1[50];
  int res = s21_sprintf(buf, "% d", 42);
  int res1 = sprintf(buf1, "% d", 42);
  ck_assert_str_eq(buf, buf1);
  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(test_sprintf_10) {
  char buf[50], buf1[50];
  unsigned int val = 4294967295U;
  int res = s21_sprintf(buf, "%u", val);
  int res1 = sprintf(buf1, "%u", val);
  ck_assert_str_eq(buf, buf1);
  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(test_sprintf_11) {
  char buf[50], buf1[50];
  unsigned long val = 18446744073709551615UL;
  int res = s21_sprintf(buf, "%lu", val);
  int res1 = sprintf(buf1, "%lu", val);
  ck_assert_str_eq(buf, buf1);
  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(test_sprintf_12) {
  char buf[50], buf1[50];
  unsigned short val = 65535U;
  int res = s21_sprintf(buf, "%hu", val);
  int res1 = sprintf(buf1, "%hu", val);
  ck_assert_str_eq(buf, buf1);
  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(test_sprintf_13) {
  char buf[50], buf1[50];
  unsigned int val = 0;
  int res = s21_sprintf(buf, "%u", val);
  int res1 = sprintf(buf1, "%u", val);
  ck_assert_str_eq(buf, buf1);
  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(test_sprintf_14) {
  char buf[50], buf1[50];
  unsigned int val = 123;
  int res = s21_sprintf(buf, "%u", val);
  int res1 = sprintf(buf1, "%u", val);
  ck_assert_str_eq(buf, buf1);
  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(test_sprintf_16) {
  char buf[50] = {0}, buf1[50] = {0};
  const char *s = "hi";
  int res = s21_sprintf(buf, "%10s", s);
  int res1 = sprintf(buf1, "%10s", s);
  ck_assert_str_eq(buf, buf1);
  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(test_sprintf_17) {
  char buf[50] = {0}, buf1[50] = {0};
  const char *s = "hi";
  int res = s21_sprintf(buf, "%-10s", s);
  int res1 = sprintf(buf1, "%-10s", s);
  ck_assert_str_eq(buf, buf1);
  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(test_sprintf_18) {
  char buf[50] = {0}, buf1[50] = {0};
  const char *s = "hello";
  int res = s21_sprintf(buf, "%.3s", s);
  int res1 = sprintf(buf1, "%.3s", s);
  ck_assert_str_eq(buf, buf1);
  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(test_sprintf_19) {
  char buf[50] = {0}, buf1[50] = {0};
  const char *s = "world";
  int res = s21_sprintf(buf, "%-8.3s", s);
  int res1 = sprintf(buf1, "%-8.3s", s);
  ck_assert_str_eq(buf, buf1);
  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(test_sprintf_20) {
  char buf[50], buf1[50];
  double val = 0.123;
  int res = s21_sprintf(buf, "%f", val);
  int res1 = sprintf(buf1, "%f", val);
  ck_assert_str_eq(buf, buf1);
  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(test_sprintf_21) {
  char buf[50], buf1[50];
  double val = 123.456;
  int res = s21_sprintf(buf, "%f", val);
  int res1 = sprintf(buf1, "%f", val);
  ck_assert_str_eq(buf, buf1);
  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(test_sprintf_22) {
  char buf[50], buf1[50];
  double val = 3.14;
  int res = s21_sprintf(buf, "%f", val);
  int res1 = sprintf(buf1, "%f", val);
  ck_assert_str_eq(buf, buf1);
  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(test_sprintf_23) {
  char buf[50], buf1[50];
  double val = 2.71828;
  int res = s21_sprintf(buf, "%.2f", val);
  int res1 = sprintf(buf1, "%.2f", val);
  ck_assert_str_eq(buf, buf1);
  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(test_sprintf_percent) {
  char buf[100], buf1[100];
  int res = s21_sprintf(buf, "%%");
  int res1 = sprintf(buf1, "%%");
  ck_assert_str_eq(buf, buf1);
  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(test_sprintf_char) {
  char buf[100], buf1[100];
  char ch = 'A';
  int res = s21_sprintf(buf, "%c", ch);
  int res1 = sprintf(buf1, "%c", ch);
  ck_assert_str_eq(buf, buf1);
  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(test_sprintf_string) {
  char buf[100], buf1[100];
  char *str = "Hello, World!";
  int res = s21_sprintf(buf, "%s", str);
  int res1 = sprintf(buf1, "%s", str);
  ck_assert_str_eq(buf, buf1);
  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(test_sprintf_string_null) {
  char buf[100], buf1[100];
  int res = s21_sprintf(buf, "%s", NULL);
  int res1 = sprintf(buf1, "%s", NULL);
  ck_assert_str_eq(buf, buf1);
  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(test_sprintf_int) {
  char buf[100], buf1[100];
  int value = 42;
  int res = s21_sprintf(buf, "%d", value);
  int res1 = sprintf(buf1, "%d", value);
  ck_assert_str_eq(buf, buf1);
  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(test_sprintf_int_negative) {
  char buf[100], buf1[100];
  int value = -42;
  int res = s21_sprintf(buf, "%d", value);
  int res1 = sprintf(buf1, "%d", value);
  ck_assert_str_eq(buf, buf1);
  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(test_sprintf_int_zero) {
  char buf[100], buf1[100];
  int value = 0;
  int res = s21_sprintf(buf, "%d", value);
  int res1 = sprintf(buf1, "%d", value);
  ck_assert_str_eq(buf, buf1);
  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(test_sprintf_int_max) {
  char buf[100], buf1[100];
  int value = INT_MAX;
  int res = s21_sprintf(buf, "%d", value);
  int res1 = sprintf(buf1, "%d", value);
  ck_assert_str_eq(buf, buf1);
  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(test_sprintf_int_min) {
  char buf[100], buf1[100];
  int value = INT_MIN;
  int res = s21_sprintf(buf, "%d", value);
  int res1 = sprintf(buf1, "%d", value);
  ck_assert_str_eq(buf, buf1);
  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(test_sprintf_unsigned) {
  char buf[100], buf1[100];
  unsigned int value = 123456;
  int res = s21_sprintf(buf, "%u", value);
  int res1 = sprintf(buf1, "%u", value);
  ck_assert_str_eq(buf, buf1);
  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(test_sprintf_unsigned_max) {
  char buf[100], buf1[100];
  unsigned int value = UINT_MAX;
  int res = s21_sprintf(buf, "%u", value);
  int res1 = sprintf(buf1, "%u", value);
  ck_assert_str_eq(buf, buf1);
  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(test_sprintf_float) {
  char buf[100], buf1[100];
  double value = 3.14159;
  int res = s21_sprintf(buf, "%f", value);
  int res1 = sprintf(buf1, "%f", value);
  ck_assert_str_eq(buf, buf1);
  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(test_sprintf_float_negative) {
  char buf[100], buf1[100];
  double value = -3.14159;
  int res = s21_sprintf(buf, "%f", value);
  int res1 = sprintf(buf1, "%f", value);
  ck_assert_str_eq(buf, buf1);
  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(test_sprintf_float_zero) {
  char buf[100], buf1[100];
  double value = 0.0;
  int res = s21_sprintf(buf, "%f", value);
  int res1 = sprintf(buf1, "%f", value);
  ck_assert_str_eq(buf, buf1);
  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(test_sprintf_float_large) {
  char buf[100], buf1[100];
  double value = 1234567.890123;
  int res = s21_sprintf(buf, "%f", value);
  int res1 = sprintf(buf1, "%f", value);
  ck_assert_str_eq(buf, buf1);
  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(test_sprintf_g_lower) {
  char buf[100], buf1[100];
  double value = 123423.456;
  int res = s21_sprintf(buf, "%g", value);
  int res1 = sprintf(buf1, "%g", value);
  ck_assert_str_eq(buf, buf1);
  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(test_sprintf_g_upper) {
  char buf[100], buf1[100];
  double value = 123.456;
  int res = s21_sprintf(buf, "%G", value);
  int res1 = sprintf(buf1, "%G", value);
  ck_assert_str_eq(buf, buf1);
  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(test_sprintf_width) {
  char buf[100], buf1[100];
  int value = 42;
  int res = s21_sprintf(buf, "%10d", value);
  int res1 = sprintf(buf1, "%10d", value);
  ck_assert_str_eq(buf, buf1);
  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(test_sprintf_precision) {
  char buf[100], buf1[100];
  double value = 3.14159;
  int res = s21_sprintf(buf, "%.2f", value);
  int res1 = sprintf(buf1, "%.2f", value);
  ck_assert_str_eq(buf, buf1);
  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(test_sprintf_width_precision) {
  char buf[100], buf1[100];
  double value = 3.14159;
  int res = s21_sprintf(buf, "%10.3f", value);
  int res1 = sprintf(buf1, "%10.3f", value);
  ck_assert_str_eq(buf, buf1);
  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(test_sprintf_left_align) {
  char buf[100], buf1[100];
  int value = 42;
  int res = s21_sprintf(buf, "%-10d", value);
  int res1 = sprintf(buf1, "%-10d", value);
  ck_assert_str_eq(buf, buf1);
  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(test_sprintf_plus_flag) {
  char buf[100], buf1[100];
  int value = 42;
  int res = s21_sprintf(buf, "%+d", value);
  int res1 = sprintf(buf1, "%+d", value);
  ck_assert_str_eq(buf, buf1);
  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(test_sprintf_space_flag) {
  char buf[100], buf1[100];
  int value = 42;
  int res = s21_sprintf(buf, "% d", value);
  int res1 = sprintf(buf1, "% d", value);
  ck_assert_str_eq(buf, buf1);
  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(test_sprintf_zero_padding) {
  char buf[100], buf1[100];
  int value = 42;
  int res = s21_sprintf(buf, "%05d", value);
  int res1 = sprintf(buf1, "%05d", value);
  ck_assert_str_eq(buf, buf1);
  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(test_sprintf_hash_flag_hex) {
  char buf[100], buf1[100];
  unsigned int value = 255;
  int res = s21_sprintf(buf, "%#x", value);
  int res1 = sprintf(buf1, "%#x", value);
  ck_assert_str_eq(buf, buf1);
  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(test_sprintf_hash_flag_octal) {
  char buf[100], buf1[100];
  unsigned int value = 63;
  int res = s21_sprintf(buf, "%#o", value);
  int res1 = sprintf(buf1, "%#o", value);
  ck_assert_str_eq(buf, buf1);
  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(test_sprintf_mixed_format) {
  char buf[100], buf1[100];
  int i = 42;
  double f = 3.14;
  char *s = "test";
  int res = s21_sprintf(buf, "Integer: %d, Float: %.2f, String: %s", i, f, s);
  int res1 = sprintf(buf1, "Integer: %d, Float: %.2f, String: %s", i, f, s);
  ck_assert_str_eq(buf, buf1);
  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(test_sprintf_complex_format) {
  char buf[100], buf1[100];
  int i = -123;
  unsigned u = 456;
  double f = -7.89;
  int res = s21_sprintf(buf, "%+08d | %#10x | %-10.3f", i, u, f);
  int res1 = sprintf(buf1, "%+08d | %#10x | %-10.3f", i, u, f);
  ck_assert_str_eq(buf, buf1);
  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(test_sprintf_empty_string) {
  char buf[100], buf1[100];
  int res = s21_sprintf(buf, "");
  int res1 = sprintf(buf1, "");
  ck_assert_str_eq(buf, buf1);
  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(test_sprintf_no_format) {
  char buf[100], buf1[100];
  int res = s21_sprintf(buf, "Hello World");
  int res1 = sprintf(buf1, "Hello World");
  ck_assert_str_eq(buf, buf1);
  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(test_sprintf_int_basic) {
  char buf[50], buf1[50];
  int val = 42;
  int res = s21_sprintf(buf, "%d", val);
  int res1 = sprintf(buf1, "%d", val);
  ck_assert_str_eq(buf, buf1);
  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(test_sprintf_int_long) {
  char buf[50], buf1[50];
  int val = 42;
  int res = s21_sprintf(buf, "%ld", val);
  int res1 = sprintf(buf1, "%ld", val);
  ck_assert_str_eq(buf, buf1);
  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(test_sprintf_int_short) {
  char buf[50], buf1[50];
  int val = 42;
  int res = s21_sprintf(buf, "%hd", val);
  int res1 = sprintf(buf1, "%hd", val);
  ck_assert_str_eq(buf, buf1);
  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(test_sprintf_int_flags) {
  char buf[50], buf1[50];
  int val = -42;
  int res = s21_sprintf(buf, "%+6d", val);
  int res1 = sprintf(buf1, "%+6d", val);
  ck_assert_str_eq(buf, buf1);
  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(test_sprintf_int_zero_pad) {
  char buf[50], buf1[50];
  int val = 7;
  int res = s21_sprintf(buf, "%05d", val);
  int res1 = sprintf(buf1, "%05d", val);
  ck_assert_str_eq(buf, buf1);
  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(test_sprintf_uint) {
  char buf[50], buf1[50];
  unsigned int val = 300;
  int res = s21_sprintf(buf, "%u", val);
  int res1 = sprintf(buf1, "%u", val);
  ck_assert_str_eq(buf, buf1);
  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(test_sprintf_hex_lower) {
  char buf[50], buf1[50];
  unsigned int val = 255;
  int res = s21_sprintf(buf, "%x", val);
  int res1 = sprintf(buf1, "%x", val);
  ck_assert_str_eq(buf, buf1);
  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(test_sprintf_hex_upper) {
  char buf[50], buf1[50];
  unsigned int val = 255;
  int res = s21_sprintf(buf, "%X", val);
  int res1 = sprintf(buf1, "%X", val);
  ck_assert_str_eq(buf, buf1);
  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(test_sprintf_hex_sharp) {
  char buf[50], buf1[50];
  unsigned int val = 255;
  int res = s21_sprintf(buf, "%#x", val);
  int res1 = sprintf(buf1, "%#x", val);
  ck_assert_str_eq(buf, buf1);
  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(test_sprintf_hex_long) {
  char buf[50], buf1[50];
  unsigned int val = 255;
  int res = s21_sprintf(buf, "%lx", val);
  int res1 = sprintf(buf1, "%lx", val);
  ck_assert_str_eq(buf, buf1);
  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(test_sprintf_hex_short) {
  char buf[50], buf1[50];
  unsigned int val = 255;
  int res = s21_sprintf(buf, "%hx", val);
  int res1 = sprintf(buf1, "%hx", val);
  ck_assert_str_eq(buf, buf1);
  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(test_sprintf_octal) {
  char buf[50], buf1[50];
  unsigned int val = 64;
  int res = s21_sprintf(buf, "%o", val);
  int res1 = sprintf(buf1, "%o", val);
  ck_assert_str_eq(buf, buf1);
  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(test_sprintf_octal_sharp) {
  char buf[50], buf1[50];
  unsigned int val = 64;
  int res = s21_sprintf(buf, "%#o", val);
  int res1 = sprintf(buf1, "%#o", val);
  ck_assert_str_eq(buf, buf1);
  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(test_sprintf_pointer_null) {
  char buf[50], buf1[50];
  void *ptr = NULL;
  int res = s21_sprintf(buf, "%p", ptr);
  int res1 = sprintf(buf1, "%p", ptr);
  ck_assert_str_eq(buf, buf1);
  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(test_sprintf_pointer) {
  char buf[50], buf1[50];
  int x = 42;
  void *ptr = &x;
  int res = s21_sprintf(buf, "%p", ptr);
  int res1 = sprintf(buf1, "%p", ptr);
  ck_assert_str_eq(buf, buf1);
  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(test_sprintf_float_basic) {
  char buf[50], buf1[50];
  double val = 3.14159;
  int res = s21_sprintf(buf, "%f", val);
  int res1 = sprintf(buf1, "%f", val);
  ck_assert_str_eq(buf, buf1);
  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(test_sprintf_float_precision) {
  char buf[50], buf1[50];
  double val = 3.14159;
  int res = s21_sprintf(buf, "%.2f", val);
  int res1 = sprintf(buf1, "%.2f", val);
  ck_assert_str_eq(buf, buf1);
  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(test_sprintf_float_plus_space) {
  char buf[50], buf1[50];
  double val = -1.23;
  int res = s21_sprintf(buf, "%+ f", val);
  int res1 = sprintf(buf1, "%+ f", val);
  ck_assert_str_eq(buf, buf1);
  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(test_sprintf_scientific_lower) {
  char buf[50], buf1[50];
  double val = 12345.6789;
  int res = s21_sprintf(buf, "%e", val);
  int res1 = sprintf(buf1, "%e", val);
  ck_assert_str_eq(buf, buf1);
  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(test_sprintf_scientific_upper) {
  char buf[50], buf1[50];
  double val = 12345.6789;
  int res = s21_sprintf(buf, "%E", val);
  int res1 = sprintf(buf1, "%E", val);
  ck_assert_str_eq(buf, buf1);
  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(test_sprintf_n) {
  char buf[50], buf1[50];
  int val1 = 0, val2 = 0;
  int res = s21_sprintf(buf, "Hello world%n", &val1);
  int res1 = sprintf(buf1, "Hello world%n", &val2);
  ck_assert_str_eq(buf, buf1);
  ck_assert_int_eq(res, res1);
}
END_TEST

#pragma GCC diagnostic pop  // Восстанавливаем сохраненные настройки

Suite *io_suite() {
  Suite *s;
  s = suite_create("Input/output functions tests");

  // s21_sscanf tests
  TCase *tc_c = tcase_create("%c specifier");
  tcase_add_test(tc_c, sscanf_c_1);
  tcase_add_test(tc_c, sscanf_c_2);
  tcase_add_test(tc_c, sscanf_c_3);
  tcase_add_test(tc_c, sscanf_c_basic);
  tcase_add_test(tc_c, sscanf_c_whitespace);
  tcase_add_test(tc_c, sscanf_c_special_chars);
  tcase_add_test(tc_c, sscanf_c_width);
  tcase_add_test(tc_c, sscanf_c_width_star);
  tcase_add_test(tc_c, sscanf_c_star);
  tcase_add_test(tc_c, sscanf_lc_wide_chars);
  tcase_add_test(tc_c, sscanf_lc_width);
  tcase_add_test(tc_c, sscanf_lc_star);
  tcase_add_test(tc_c, sscanf_c_mixed_types);
  tcase_add_test(tc_c, sscanf_c_mixed_lengths);
  tcase_add_test(tc_c, sscanf_c_empty_input);
  tcase_add_test(tc_c, sscanf_c_both_empty);
  tcase_add_test(tc_c, sscanf_c_only_whitespace);
  tcase_add_test(tc_c, sscanf_c_newlines);
  tcase_add_test(tc_c, sscanf_c_null_char);
  tcase_add_test(tc_c, sscanf_c_complex_pattern);
  suite_add_tcase(s, tc_c);

  TCase *tc_d = tcase_create("%d specifier");
  tcase_add_test(tc_d, sscanf_d_basic);
  tcase_add_test(tc_d, sscanf_d_with_text);
  tcase_add_test(tc_d, sscanf_d_with_plus_minus);
  tcase_add_test(tc_d, sscanf_d_int_max_min);
  tcase_add_test(tc_d, sscanf_d_zeros);
  tcase_add_test(tc_d, sscanf_d_invalid_data);
  tcase_add_test(tc_d, sscanf_d_only_invalid);
  tcase_add_test(tc_d, sscanf_d_with_width);
  tcase_add_test(tc_d, sscanf_d_with_star);
  tcase_add_test(tc_d, sscanf_d_with_whitespace);
  tcase_add_test(tc_d, sscanf_d_partial_match);
  tcase_add_test(tc_d, sscanf_d_empty_input);
  tcase_add_test(tc_d, sscanf_d_usual);
  tcase_add_test(tc_d, sscanf_d_usual_signed);
  tcase_add_test(tc_d, sscanf_d_limits);
  tcase_add_test(tc_d, sscanf_d_scam);
  tcase_add_test(tc_d, sscanf_hd_limits);
  tcase_add_test(tc_d, sscanf_hd_over_limits);
  tcase_add_test(tc_d, sscanf_hhd_overflow);
  tcase_add_test(tc_d, sscanf_hhd_overflow_star);
  tcase_add_test(tc_d, sscanf_ld_limits);
  tcase_add_test(tc_d, sscanf_ld_width);
  tcase_add_test(tc_d, sscanf_lld_limits);
  tcase_add_test(tc_d, sscanf_d_hhd);
  tcase_add_test(tc_d, sscanf_d_hd);
  tcase_add_test(tc_d, sscanf_d_ld);
  tcase_add_test(tc_d, sscanf_d_lld);
  tcase_add_test(tc_d, sscanf_d_mixed_modifiers);
  tcase_add_test(tc_d, sscanf_d_modifiers_with_width);
  tcase_add_test(tc_d, sscanf_d_modifiers_with_star);
  tcase_add_test(tc_d, sscanf_d_modifier_boundaries);
  tcase_add_test(tc_d, sscanf_d_modifiers_invalid);
  tcase_add_test(tc_d, sscanf_d_modifiers_with_text);
  suite_add_tcase(s, tc_d);

  TCase *tc_ouxX = tcase_create("%o %u %x %X specifiers");
  tcase_add_test(tc_ouxX, sscanf_o_basic);
  tcase_add_test(tc_ouxX, sscanf_o_modifiers);
  tcase_add_test(tc_ouxX, sscanf_o_width_star);
  tcase_add_test(tc_ouxX, sscanf_o_invalid);
  tcase_add_test(tc_ouxX, sscanf_u_basic);
  tcase_add_test(tc_ouxX, sscanf_u_modifiers);
  tcase_add_test(tc_ouxX, sscanf_u_mixed_width);
  tcase_add_test(tc_ouxX, sscanf_x_basic);
  tcase_add_test(tc_ouxX, sscanf_x_with_prefix);
  tcase_add_test(tc_ouxX, sscanf_x_modifiers);
  tcase_add_test(tc_ouxX, sscanf_X_basic);
  tcase_add_test(tc_ouxX, sscanf_X_with_prefix);
  tcase_add_test(tc_ouxX, sscanf_x_X_mixed);
  tcase_add_test(tc_ouxX, sscanf_all_specifiers_width_star);
  tcase_add_test(tc_ouxX, sscanf_all_mixed_modifiers);
  tcase_add_test(tc_ouxX, sscanf_all_invalid_data);
  tcase_add_test(tc_ouxX, sscanf_all_boundary_values);
  tcase_add_test(tc_ouxX, sscanf_all_with_whitespace_and_text);
  suite_add_tcase(s, tc_ouxX);

  TCase *tc_s = tcase_create("%s specifier");
  tcase_add_test(tc_s, sscanf_s_usual);
  tcase_add_test(tc_s, sscanf_s_width);
  tcase_add_test(tc_s, sscanf_s_star);
  tcase_add_test(tc_s, sscanf_s_width_star);
  tcase_add_test(tc_s, sscanf_s_whitespace);
  tcase_add_test(tc_s, sscanf_s_empty_strings);
  tcase_add_test(tc_s, sscanf_s_with_text);
  tcase_add_test(tc_s, sscanf_s_partial_match);
  tcase_add_test(tc_s, sscanf_s_empty_input);
  tcase_add_test(tc_s, sscanf_s_long_string);
  tcase_add_test(tc_s, sscanf_s_buffer_limits);
  tcase_add_test(tc_s, sscanf_s_special_chars);
  tcase_add_test(tc_s, sscanf_s_until_newline);
  tcase_add_test(tc_s, sscanf_s_different_delimiters);
  tcase_add_test(tc_s, sscanf_s_l_modifier);
  tcase_add_test(tc_s, sscanf_s_l_modifier_width);
  suite_add_tcase(s, tc_s);

  TCase *tc_other = tcase_create("Other tests");
  tcase_add_test(tc_other, invalid_specifier);
  suite_add_tcase(s, tc_other);

  TCase *tc_pcnt = tcase_create("%% specifier");
  tcase_add_test(tc_pcnt, sscanf_percent_basic);
  tcase_add_test(tc_pcnt, sscanf_percent_multiple);
  tcase_add_test(tc_pcnt, sscanf_percent_with_text);
  tcase_add_test(tc_pcnt, sscanf_percent_start);
  tcase_add_test(tc_pcnt, sscanf_percent_end);
  tcase_add_test(tc_pcnt, sscanf_percent_whitespace);
  tcase_add_test(tc_pcnt, sscanf_percent_mismatch);
  tcase_add_test(tc_pcnt, sscanf_percent_partial_match);
  tcase_add_test(tc_pcnt, sscanf_percent_empty);
  tcase_add_test(tc_pcnt, sscanf_percent_mixed_specifiers);
  tcase_add_test(tc_pcnt, sscanf_percent_complex);
  tcase_add_test(tc_pcnt, sscanf_percent_complex_mix);
  tcase_add_test(tc_pcnt, sscanf_percent_with_hex);
  tcase_add_test(tc_pcnt, sscanf_percent_with_octal);
  tcase_add_test(tc_pcnt, sscanf_percent_with_unsigned);
  tcase_add_test(tc_pcnt, sscanf_percent_with_size_modifiers);
  tcase_add_test(tc_pcnt, sscanf_percent_with_string_width);
  tcase_add_test(tc_pcnt, sscanf_percent_with_star);
  tcase_add_test(tc_pcnt, sscanf_percent_literal);
  suite_add_tcase(s, tc_pcnt);

  TCase *tc_n = tcase_create("%n specifier");
  tcase_add_test(tc_n, sscanf_n_basic);
  tcase_add_test(tc_n, sscanf_n_middle);
  tcase_add_test(tc_n, sscanf_n_beginning);
  tcase_add_test(tc_n, sscanf_n_end);
  tcase_add_test(tc_n, sscanf_n_multiple);
  tcase_add_test(tc_n, sscanf_n_with_hex);
  tcase_add_test(tc_n, sscanf_n_with_octal);
  tcase_add_test(tc_n, sscanf_n_with_unsigned);
  tcase_add_test(tc_n, sscanf_n_with_string_width);
  tcase_add_test(tc_n, sscanf_n_with_chars);
  tcase_add_test(tc_n, sscanf_n_with_wide_chars);
  tcase_add_test(tc_n, sscanf_n_no_star_suppression);
  tcase_add_test(tc_n, sscanf_n_whitespace);
  tcase_add_test(tc_n, sscanf_n_all_modifiers);
  suite_add_tcase(s, tc_n);

  TCase *tc_i = tcase_create("%i specifier");
  tcase_add_test(tc_i, sscanf_i_basic);
  tcase_add_test(tc_i, sscanf_i_hex);
  tcase_add_test(tc_i, sscanf_i_octal);
  tcase_add_test(tc_i, sscanf_i_mixed_bases);
  tcase_add_test(tc_i, sscanf_i_limits);
  tcase_add_test(tc_i, sscanf_i_invalid);
  tcase_add_test(tc_i, sscanf_i_with_other_specifiers);
  tcase_add_test(tc_i, sscanf_i_star);
  tcase_add_test(tc_i, sscanf_i_width);
  suite_add_tcase(s, tc_i);

  TCase *tc_eEfgG = tcase_create("%eEdgG specifiers");
  tcase_add_test(tc_eEfgG, sscanf_e_basic);
  tcase_add_test(tc_eEfgG, sscanf_E_basic);
  tcase_add_test(tc_eEfgG, sscanf_f_basic);
  tcase_add_test(tc_eEfgG, sscanf_g_basic);
  tcase_add_test(tc_eEfgG, sscanf_G_basic);
  tcase_add_test(tc_eEfgG, sscanf_float_scientific_notation);
  tcase_add_test(tc_eEfgG, sscanf_float_no_fractional);
  tcase_add_test(tc_eEfgG, sscanf_float_width);
  tcase_add_test(tc_eEfgG, sscanf_exponential_width);
  tcase_add_test(tc_eEfgG, sscanf_float_star);
  tcase_add_test(tc_eEfgG, sscanf_float_long);
  tcase_add_test(tc_eEfgG, sscanf_float_invalid);
  tcase_add_test(tc_eEfgG, sscanf_g_auto_notation);
  tcase_add_test(tc_eEfgG, sscanf_float_mixed_specifiers);
  tcase_add_test(tc_eEfgG, sscanf_float_edge_cases);
  suite_add_tcase(s, tc_eEfgG);

  TCase *tc_p = tcase_create("%p specifier");
  tcase_add_test(tc_p, sscanf_p_basic);
  tcase_add_test(tc_p, sscanf_p_multiple);
  tcase_add_test(tc_p, sscanf_p_lowercase_hex);
  tcase_add_test(tc_p, sscanf_p_uppercase_hex);
  tcase_add_test(tc_p, sscanf_p_no_prefix);
  tcase_add_test(tc_p, sscanf_p_case_insensitive);
  tcase_add_test(tc_p, sscanf_p_zero_pointer);
  tcase_add_test(tc_p, sscanf_p_max_pointer);
  tcase_add_test(tc_p, sscanf_p_with_text);
  tcase_add_test(tc_p, sscanf_p_whitespace);
  tcase_add_test(tc_p, sscanf_p_mixed_specifiers);
  tcase_add_test(tc_p, sscanf_p_with_width);
  tcase_add_test(tc_p, sscanf_p_star);
  tcase_add_test(tc_p, sscanf_p_ignore_modifiers);
  tcase_add_test(tc_p, sscanf_p_invalid_data);
  tcase_add_test(tc_p, sscanf_p_partial_match);
  tcase_add_test(tc_p, sscanf_p_different_bases);
  tcase_add_test(tc_p, sscanf_p_variable_digits);
  tcase_add_test(tc_p, sscanf_p_empty_string);
  tcase_add_test(tc_p, sscanf_p_real_pointers);
  suite_add_tcase(s, tc_p);

  // s21_sprintf tests
  TCase *tc_sprintf = tcase_create("sprintf");
  tcase_add_test(tc_sprintf, test_sprintf_1);
  tcase_add_test(tc_sprintf, test_sprintf_2);
  tcase_add_test(tc_sprintf, test_sprintf_3);
  tcase_add_test(tc_sprintf, test_sprintf_4);
  tcase_add_test(tc_sprintf, test_sprintf_5);
  tcase_add_test(tc_sprintf, test_sprintf_6);
  tcase_add_test(tc_sprintf, test_sprintf_7);
  tcase_add_test(tc_sprintf, test_sprintf_8);
  tcase_add_test(tc_sprintf, test_sprintf_9);
  tcase_add_test(tc_sprintf, test_sprintf_10);
  tcase_add_test(tc_sprintf, test_sprintf_11);
  tcase_add_test(tc_sprintf, test_sprintf_12);
  tcase_add_test(tc_sprintf, test_sprintf_13);
  tcase_add_test(tc_sprintf, test_sprintf_14);
  tcase_add_test(tc_sprintf, test_sprintf_16);
  tcase_add_test(tc_sprintf, test_sprintf_17);
  tcase_add_test(tc_sprintf, test_sprintf_18);
  tcase_add_test(tc_sprintf, test_sprintf_19);
  tcase_add_test(tc_sprintf, test_sprintf_19);
  tcase_add_test(tc_sprintf, test_sprintf_20);
  tcase_add_test(tc_sprintf, test_sprintf_21);
  tcase_add_test(tc_sprintf, test_sprintf_22);
  tcase_add_test(tc_sprintf, test_sprintf_23);
  tcase_add_test(tc_sprintf, test_sprintf_percent);
  tcase_add_test(tc_sprintf, test_sprintf_char);
  tcase_add_test(tc_sprintf, test_sprintf_string);
  tcase_add_test(tc_sprintf, test_sprintf_string_null);
  tcase_add_test(tc_sprintf, test_sprintf_int);
  tcase_add_test(tc_sprintf, test_sprintf_int_negative);
  tcase_add_test(tc_sprintf, test_sprintf_int_zero);
  tcase_add_test(tc_sprintf, test_sprintf_int_max);
  tcase_add_test(tc_sprintf, test_sprintf_int_min);
  tcase_add_test(tc_sprintf, test_sprintf_unsigned);
  tcase_add_test(tc_sprintf, test_sprintf_unsigned_max);
  tcase_add_test(tc_sprintf, test_sprintf_float);
  tcase_add_test(tc_sprintf, test_sprintf_float_negative);
  tcase_add_test(tc_sprintf, test_sprintf_float_zero);
  tcase_add_test(tc_sprintf, test_sprintf_float_large);
  tcase_add_test(tc_sprintf, test_sprintf_g_lower);
  tcase_add_test(tc_sprintf, test_sprintf_g_upper);
  tcase_add_test(tc_sprintf, test_sprintf_width);
  tcase_add_test(tc_sprintf, test_sprintf_precision);
  tcase_add_test(tc_sprintf, test_sprintf_width_precision);
  tcase_add_test(tc_sprintf, test_sprintf_left_align);
  tcase_add_test(tc_sprintf, test_sprintf_plus_flag);
  tcase_add_test(tc_sprintf, test_sprintf_space_flag);
  tcase_add_test(tc_sprintf, test_sprintf_zero_padding);
  tcase_add_test(tc_sprintf, test_sprintf_hash_flag_hex);
  tcase_add_test(tc_sprintf, test_sprintf_hash_flag_octal);
  tcase_add_test(tc_sprintf, test_sprintf_mixed_format);
  tcase_add_test(tc_sprintf, test_sprintf_complex_format);
  tcase_add_test(tc_sprintf, test_sprintf_empty_string);
  tcase_add_test(tc_sprintf, test_sprintf_no_format);
  tcase_add_test(tc_sprintf, test_sprintf_int_basic);
  tcase_add_test(tc_sprintf, test_sprintf_int_long);
  tcase_add_test(tc_sprintf, test_sprintf_int_short);
  tcase_add_test(tc_sprintf, test_sprintf_int_flags);
  tcase_add_test(tc_sprintf, test_sprintf_int_zero_pad);
  tcase_add_test(tc_sprintf, test_sprintf_uint);
  tcase_add_test(tc_sprintf, test_sprintf_hex_lower);
  tcase_add_test(tc_sprintf, test_sprintf_hex_upper);
  tcase_add_test(tc_sprintf, test_sprintf_hex_sharp);
  tcase_add_test(tc_sprintf, test_sprintf_hex_long);
  tcase_add_test(tc_sprintf, test_sprintf_hex_short);
  tcase_add_test(tc_sprintf, test_sprintf_octal);
  tcase_add_test(tc_sprintf, test_sprintf_octal_sharp);
  tcase_add_test(tc_sprintf, test_sprintf_pointer_null);
  tcase_add_test(tc_sprintf, test_sprintf_pointer);
  tcase_add_test(tc_sprintf, test_sprintf_float_basic);
  tcase_add_test(tc_sprintf, test_sprintf_float_precision);
  tcase_add_test(tc_sprintf, test_sprintf_float_plus_space);
  tcase_add_test(tc_sprintf, test_sprintf_scientific_lower);
  tcase_add_test(tc_sprintf, test_sprintf_scientific_upper);
  tcase_add_test(tc_sprintf, test_sprintf_n);
  suite_add_tcase(s, tc_sprintf);

  return s;
}

int main(void) {
  int number_failed;
  SRunner *sr;

  sr = srunner_create(str_proc_func_suite());
  srunner_add_suite(sr, io_suite());
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  printf("=== TEST STRING PROCESSING FUNCTIONS SUMMARY ===\n");
  printf("Failed tests: %d\n\n", number_failed);

  return (number_failed == 0) ? 0 : 1;
}