#include "s21_string.h"

#include <check.h>
#include <string.h>

Suite *memchr_test();
Suite *memcmp_test();
Suite *memcpy_test();
Suite *memset_test();
Suite *strncat_test();
Suite *strchr_test();
Suite *strncmp_test();
Suite *strncpy_test();
Suite *strcspn_test();
Suite *strerror_test();
Suite *strlen_test();
Suite *strpbrk_test();
Suite *strrchr_test();
Suite *strstr_test();
Suite *strtok_test();

int main() {
  SRunner *srunner;
  Suite *suites[] = {
      memchr_test(),  memcmp_test(),   memcpy_test(),  memset_test(),
      strncat_test(), strchr_test(),   strncmp_test(), strncpy_test(),
      strcspn_test(), strerror_test(), strlen_test(),  strpbrk_test(),
      strrchr_test(), strstr_test(),   strtok_test(),
  };

  for (int i = 0; i < 15; i++) {
    printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@Í\n");
    srunner = srunner_create(suites[i]);
    srunner_run_all(srunner, CK_NORMAL);
    srunner_free(srunner);
  }
  return 0;
}

START_TEST(memchr_test_1) {
  char str[] = "Hello, niggas";
  int c = 'o';
  size_t n = strlen(str);

  void *s21_result = s21_memchr(str, c, n);
  void *result = memchr(str, c, n);

  ck_assert_ptr_eq(s21_result, result);
}
END_TEST

START_TEST(memchr_test_2) {
  char str[] = "\t\n";
  int c = '0';
  size_t n = strlen(str);

  void *s21_result = s21_memchr(str, c, n);
  void *result = memchr(str, c, n);

  ck_assert_ptr_eq(s21_result, result);
}
END_TEST

START_TEST(memchr_test_3) {
  char str[] = "";
  int c = ' ';
  size_t n = strlen(str);

  void *s21_result = s21_memchr(str, c, n);
  void *result = memchr(str, c, n);

  ck_assert_ptr_eq(s21_result, result);
}
END_TEST

START_TEST(memchr_test_4) {
  char str[] = "hello\0hello";
  int c = 'o';
  size_t n = strlen(str);

  void *s21_result = s21_memchr(str, c, n);
  void *result = memchr(str, c, n);

  ck_assert_ptr_eq(s21_result, result);
}
END_TEST

START_TEST(memchr_test_5) {
  char str[] = "";
  int c = '\0';
  size_t n = strlen(str);

  void *s21_result = s21_memchr(str, c, n);
  void *result = memchr(str, c, n);

  ck_assert_ptr_eq(s21_result, result);
}
END_TEST

START_TEST(memchr_test_6) {
  char str[] = "Hello, niggas";
  int c = 'o';
  size_t n = 0;

  void *s21_result = s21_memchr(str, c, n);
  void *result = memchr(str, c, n);

  ck_assert_ptr_eq(s21_result, result);
}
END_TEST

START_TEST(memchr_test_7) {
  char str[] = "Hello, niggas";
  int c = 'o';
  size_t n = strlen(str) + 1;

  void *s21_result = s21_memchr(str, c, n);
  void *result = memchr(str, c, n);

  ck_assert_ptr_eq(s21_result, result);
}
END_TEST

START_TEST(memchr_test_8) {
  char str[] = "Hello\1World";
  int c = 1;
  size_t n = strlen(str);

  void *s21_result = s21_memchr(str, c, n);
  void *result = memchr(str, c, n);

  ck_assert_ptr_eq(s21_result, result);
}
END_TEST

START_TEST(memchr_test_9) {
  char str[] = "0x1";
  int c = 0x1;
  size_t n = strlen(str);

  void *s21_result = s21_memchr(str, c, n);
  void *result = memchr(str, c, n);

  ck_assert_ptr_eq(s21_result, result);
}
END_TEST

START_TEST(memchr_test_10) {
  char str[] = {1, 2, 3, 4};
  int c = 1;
  size_t n = sizeof(str);

  void *s21_result = s21_memchr(str, c, n);
  void *result = memchr(str, c, n);

  ck_assert_ptr_eq(s21_result, result);
}
END_TEST

Suite *memchr_test() {
  Suite *suite = suite_create("s21_memchr_test");
  TCase *tcase = tcase_create("memchr");

  tcase_add_test(tcase, memchr_test_1);
  tcase_add_test(tcase, memchr_test_2);
  tcase_add_test(tcase, memchr_test_3);
  tcase_add_test(tcase, memchr_test_4);
  tcase_add_test(tcase, memchr_test_5);
  tcase_add_test(tcase, memchr_test_6);
  tcase_add_test(tcase, memchr_test_7);
  tcase_add_test(tcase, memchr_test_8);
  tcase_add_test(tcase, memchr_test_9);
  tcase_add_test(tcase, memchr_test_10);

  suite_add_tcase(suite, tcase);
  return suite;
}

START_TEST(memcmp_test_1) {
  char str1[] = "Hello, niggas";
  char str2[] = "Hello, niggas";
  size_t n = strlen(str1);

  int s21_result = s21_memcmp(str1, str2, n);
  int result = memcmp(str1, str2, n);

  ck_assert_int_eq(s21_result, result);
}
END_TEST

START_TEST(memcmp_test_2) {
  char str1[] = "Hello, niggas";
  char str2[] = "";
  size_t n = strlen(str1);

  int s21_result = s21_memcmp(str1, str2, n);
  int result = memcmp(str1, str2, n);

  ck_assert_int_eq(s21_result, result);
}
END_TEST

START_TEST(memcmp_test_3) {
  char str1[] = "";
  char str2[] = "";
  size_t n = strlen(str1);

  int s21_result = s21_memcmp(str1, str2, n);
  int result = memcmp(str1, str2, n);

  ck_assert_int_eq(s21_result, result);
}
END_TEST

START_TEST(memcmp_test_4) {
  char str1[] = "\n\t\0";
  char str2[] = "\0\n\n";
  size_t n = strlen(str1);

  int s21_result = s21_memcmp(str1, str2, n);
  int result = memcmp(str1, str2, n);

  ck_assert_int_eq(s21_result, result);
}
END_TEST

START_TEST(memcmp_test_5) {
  char str1[] = "\n\t\0";
  char str2[] = "\0\n\n";
  size_t n = 0;

  int s21_result = s21_memcmp(str1, str2, n);
  int result = memcmp(str1, str2, n);

  ck_assert_int_eq(s21_result, result);
}
END_TEST

START_TEST(memcmp_test_6) {
  char str1[] = "Hello";
  char str2[] = "World";
  size_t n = strlen(str1) * 2;

  int s21_result = s21_memcmp(str1, str2, n);
  int result = memcmp(str1, str2, n);

  ck_assert_int_eq(s21_result, result);
}
END_TEST

START_TEST(memcmp_test_7) {
  char str1[] = "Hello, niggas";
  char str2[] = "";
  size_t n = 0;

  int s21_result = s21_memcmp(str1, str2, n);
  int result = memcmp(str1, str2, n);

  ck_assert_int_eq(s21_result, result);
}
END_TEST

START_TEST(memcmp_test_8) {
  char str1[] = {1, 2, 3, 4};
  char str2[] = {'a', 'b', 'c', 'd', 'e'};
  size_t n = sizeof(str1);

  int s21_result = s21_memcmp(str1, str2, n);
  int result = memcmp(str1, str2, n);

  ck_assert_int_eq(s21_result, result);
}
END_TEST

START_TEST(memcmp_test_9) {
  char str1[] = {'a', 'b', 'c', 'd', 'e'};
  char str2[] = "black cats";
  size_t n = sizeof(str1);

  int s21_result = s21_memcmp(str1, str2, n);
  int result = memcmp(str1, str2, n);

  ck_assert_int_eq(s21_result, result);
}
END_TEST

START_TEST(memcmp_test_10) {
  char str1[] = {0x1, 0x2, 0x3, 0x4};
  char str2[] = "meowmeow";
  size_t n = sizeof(str1);

  int s21_result = s21_memcmp(str1, str2, n);
  int result = memcmp(str1, str2, n);

  ck_assert_int_eq(s21_result, result);
}
END_TEST

Suite *memcmp_test() {
  Suite *suite = suite_create("s21_memcmp_test");
  TCase *tcase = tcase_create("memcmp");

  tcase_add_test(tcase, memcmp_test_1);
  tcase_add_test(tcase, memcmp_test_2);
  tcase_add_test(tcase, memcmp_test_3);
  tcase_add_test(tcase, memcmp_test_4);
  tcase_add_test(tcase, memcmp_test_5);
  tcase_add_test(tcase, memcmp_test_6);
  tcase_add_test(tcase, memcmp_test_7);
  tcase_add_test(tcase, memcmp_test_9);

  suite_add_tcase(suite, tcase);
  return suite;
}

START_TEST(memcpy_test_1) {
  char dest[] = "Hello, niggas";
  char src[] = "Hello, niggas";
  size_t n = strlen(src);

  void *s21_result = s21_memcpy(dest, src, n);
  void *result = memcpy(dest, src, n);

  ck_assert_ptr_eq(s21_result, result);
}
END_TEST

START_TEST(memcpy_test_2) {
  char dest[] = "";
  char src[] = "Hello, niggas";
  size_t n = strlen(src);

  void *s21_result = s21_memcpy(dest, src, n);
  void *result = memcpy(dest, src, n);

  ck_assert_ptr_eq(s21_result, result);
}
END_TEST

START_TEST(memcpy_test_3) {
  char dest[] = "Hello, niggas";
  char src[] = "";
  size_t n = strlen(src);

  void *s21_result = s21_memcpy(dest, src, n);
  void *result = memcpy(dest, src, n);

  ck_assert_ptr_eq(s21_result, result);
}
END_TEST

START_TEST(memcpy_test_4) {
  char dest[] = "";
  char src[] = "";
  size_t n = strlen(src);

  void *s21_result = s21_memcpy(dest, src, n);
  void *result = memcpy(dest, src, n);

  ck_assert_ptr_eq(s21_result, result);
}
END_TEST

START_TEST(memcpy_test_5) {
  char dest[] = "\0";
  char src[] = "black cats";
  size_t n = strlen(src) * 2;

  void *s21_result = s21_memcpy(dest, src, n);
  void *result = memcpy(dest, src, n);

  ck_assert_ptr_eq(s21_result, result);
}
END_TEST

START_TEST(memcpy_test_6) {
  char dest[] = "\0";
  char src[] = "\0";
  size_t n = strlen(src);

  void *s21_result = s21_memcpy(dest, src, n);
  void *result = memcpy(dest, src, n);

  ck_assert_ptr_eq(s21_result, result);
}
END_TEST

START_TEST(memcpy_test_7) {
  char dest[] = "\1\2\3\4";
  char src[] = "\0";
  size_t n = strlen(src);

  void *s21_result = s21_memcpy(dest, src, n);
  void *result = memcpy(dest, src, n);

  ck_assert_ptr_eq(s21_result, result);
}
END_TEST

START_TEST(memcpy_test_9) {
  char dest[] = {0x1, 0x2, 0x3, 0x4};
  char src[] = {1, 2, 3, 4};
  size_t n = sizeof(src);

  void *s21_result = s21_memcpy(dest, src, n);
  void *result = memcpy(dest, src, n);

  ck_assert_ptr_eq(s21_result, result);
}
END_TEST

Suite *memcpy_test() {
  Suite *suite = suite_create("s21_memcpy_test");
  TCase *tcase = tcase_create("memcpy");

  tcase_add_test(tcase, memcpy_test_1);
  tcase_add_test(tcase, memcpy_test_2);
  tcase_add_test(tcase, memcpy_test_3);
  tcase_add_test(tcase, memcpy_test_4);
  tcase_add_test(tcase, memcpy_test_6);
  tcase_add_test(tcase, memcpy_test_7);
  tcase_add_test(tcase, memcpy_test_9);

  suite_add_tcase(suite, tcase);
  return suite;
}

START_TEST(memset_test_1) {
  char str[] = "Hello, niggas";
  char c = ' ';
  size_t n = strlen(str);

  void *s21_result = s21_memset(str, c, n);
  void *result = memset(str, c, n);

  ck_assert_ptr_eq(s21_result, result);
}
END_TEST

START_TEST(memset_test_2) {
  char str[] = "";
  char c = ' ';
  size_t n = strlen(str);

  void *s21_result = s21_memset(str, c, n);
  void *result = memset(str, c, n);

  ck_assert_ptr_eq(s21_result, result);
}
END_TEST

START_TEST(memset_test_3) {
  char str[] = "Hello, niggas";
  char c = ' ';
  size_t n = strlen(str);

  void *s21_result = s21_memset(str, c, n);
  void *result = memset(str, c, n);

  ck_assert_ptr_eq(s21_result, result);
}
END_TEST

START_TEST(memset_test_4) {
  char str[] = "";
  char c = ' ';
  size_t n = strlen(str);

  void *s21_result = s21_memset(str, c, n);
  void *result = memset(str, c, n);

  ck_assert_ptr_eq(s21_result, result);
}
END_TEST

START_TEST(memset_test_6) {
  char str[] = "\0";
  char c = ' ';
  size_t n = strlen(str);

  void *s21_result = s21_memset(str, c, n);
  void *result = memset(str, c, n);

  ck_assert_ptr_eq(s21_result, result);
}
END_TEST

START_TEST(memset_test_7) {
  char str[] = "\1\2\3\4";
  char c = ' ';
  size_t n = strlen(str);

  void *s21_result = s21_memset(str, c, n);
  void *result = memset(str, c, n);

  ck_assert_ptr_eq(s21_result, result);
}
END_TEST

START_TEST(memset_test_8) {
  char str[] = {'a', 'b', 'c', 'd', 'e'};
  char c = ' ';
  size_t n = sizeof(str);

  void *s21_result = s21_memset(str, c, n);
  void *result = memset(str, c, n);

  ck_assert_ptr_eq(s21_result, result);
}
END_TEST

START_TEST(memset_test_9) {
  char str[] = {0x1, 0x2, 0x3, 0x4};
  char c = ' ';
  size_t n = sizeof(str);

  void *s21_result = s21_memset(str, c, n);
  void *result = memset(str, c, n);

  ck_assert_ptr_eq(s21_result, result);
}
END_TEST

START_TEST(memset_test_10) {
  char str[] = "black cats";
  char c = ' ';
  size_t n = 0;

  void *s21_result = s21_memset(str, c, n);
  void *result = memset(str, c, n);

  ck_assert_ptr_eq(s21_result, result);
}
END_TEST

Suite *memset_test() {
  Suite *suite = suite_create("s21_memset_test");
  TCase *tcase = tcase_create("memset");

  tcase_add_test(tcase, memset_test_1);
  tcase_add_test(tcase, memset_test_2);
  tcase_add_test(tcase, memset_test_3);
  tcase_add_test(tcase, memset_test_4);
  tcase_add_test(tcase, memset_test_6);
  tcase_add_test(tcase, memset_test_7);
  tcase_add_test(tcase, memset_test_8);
  tcase_add_test(tcase, memset_test_9);
  tcase_add_test(tcase, memset_test_10);

  suite_add_tcase(suite, tcase);
  return suite;
}

START_TEST(strncat_test_1) {
  char dest[] = "Hello, niggas";
  char src[] = "Hello, world!";
  size_t n = strlen(dest);

  char *s21_result = s21_strncat(dest, src, n);
  char *result = strncat(dest, src, n);

  ck_assert_str_eq(s21_result, result);
}
END_TEST

START_TEST(strncat_test_2) {
  char dest[] = "Hello, niggas";
  char src[] = "Hello, world!";
  size_t n = 0;

  char *s21_result = s21_strncat(dest, src, n);
  char *result = strncat(dest, src, n);

  ck_assert_str_eq(s21_result, result);
}
END_TEST

START_TEST(strncat_test_3) {
  char dest[] = "Hello, niggas";
  char src[] = "Hello";
  size_t n = strlen(dest) * 2;

  char *s21_result = s21_strncat(dest, src, n);
  char *result = strncat(dest, src, n);

  ck_assert_str_eq(s21_result, result);
}
END_TEST

START_TEST(strncat_test_4) {
  char dest[] = "";
  char src[] = "";
  size_t n = strlen(dest);

  char *s21_result = s21_strncat(dest, src, n);
  char *result = strncat(dest, src, n);

  ck_assert_str_eq(s21_result, result);
}
END_TEST

START_TEST(strncat_test_5) {
  char dest[] = "black cats";
  char src[] = "black cats";
  size_t n = sizeof(dest);

  char *s21_result = s21_strncat(dest, src, n);
  char *result = strncat(dest, src, n);

  ck_assert_str_eq(s21_result, result);
}
END_TEST

START_TEST(strncat_test_6) {
  char dest[] = "\0";
  char src[] = "\0";
  size_t n = strlen(dest);

  char *s21_result = s21_strncat(dest, src, n);
  char *result = strncat(dest, src, n);

  ck_assert_str_eq(s21_result, result);
}
END_TEST

START_TEST(strncat_test_7) {
  char dest[] = "\1\2\3\4";
  char src[] = "\0\t\n";
  size_t n = strlen(dest);

  char *s21_result = s21_strncat(dest, src, n);
  char *result = strncat(dest, src, n);

  ck_assert_str_eq(s21_result, result);
}
END_TEST

START_TEST(strncat_test_8) {
  char dest[] = "123";
  char src[] = "1";
  size_t n = strlen(dest);

  char *s21_result = s21_strncat(dest, src, n);
  char *result = strncat(dest, src, n);

  ck_assert_str_eq(s21_result, result);
}
END_TEST

START_TEST(strncat_test_9) {
  char dest[] = "black cats";
  char src[] = "";
  size_t n = strlen(dest);

  char *s21_result = s21_strncat(dest, src, n);
  char *result = strncat(dest, src, n);

  ck_assert_str_eq(s21_result, result);
}
END_TEST

START_TEST(strncat_test_10) {
  char dest[] = "";
  char src[] = "black cats";
  size_t n = strlen(dest);

  char *s21_result = s21_strncat(dest, src, n);
  char *result = strncat(dest, src, n);

  ck_assert_str_eq(s21_result, result);
}
END_TEST

Suite *strncat_test() {
  Suite *suite = suite_create("s21_strncat_test");
  TCase *tcase = tcase_create("strncat");

  tcase_add_test(tcase, strncat_test_2);
  tcase_add_test(tcase, strncat_test_4);
  tcase_add_test(tcase, strncat_test_6);
  tcase_add_test(tcase, strncat_test_7);
  tcase_add_test(tcase, strncat_test_9);
  tcase_add_test(tcase, strncat_test_10);

  suite_add_tcase(suite, tcase);
  return suite;
}

START_TEST(strchr_test_2) {
  char str[] = "";
  char c = ' ';

  void *s21_result = s21_strchr(str, c);
  void *result = strchr(str, c);

  ck_assert_ptr_eq(s21_result, result);
}
END_TEST

START_TEST(strchr_test_4) {
  char str[] = "";
  char c = ' ';

  void *s21_result = s21_strchr(str, c);
  void *result = strchr(str, c);

  ck_assert_ptr_eq(s21_result, result);
}
END_TEST

START_TEST(strchr_test_6) {
  char str[] = "\0";
  char c = ' ';

  void *s21_result = s21_strchr(str, c);
  void *result = strchr(str, c);

  ck_assert_ptr_eq(s21_result, result);
}
END_TEST

START_TEST(strchr_test_7) {
  char str[] = "\1\2\3\4";
  char c = '\1';

  void *s21_result = s21_strchr(str, c);
  void *result = strchr(str, c);

  ck_assert_ptr_eq(s21_result, result);
}
END_TEST

START_TEST(strchr_test_9) {
  char str[] = {0x1, 0x2, 0x3, 0x4};
  char c = 0x1;

  void *s21_result = s21_strchr(str, c);
  void *result = strchr(str, c);

  ck_assert_ptr_eq(s21_result, result);
}
END_TEST

START_TEST(strchr_test_10) {
  char str[] = "black cats";
  char c = 'q';

  void *s21_result = s21_strchr(str, c);
  void *result = strchr(str, c);

  ck_assert_ptr_eq(s21_result, result);
}
END_TEST

Suite *strchr_test() {
  Suite *suite = suite_create("s21_strchr_test");
  TCase *tcase = tcase_create("strchr");

  tcase_add_test(tcase, strchr_test_2);
  tcase_add_test(tcase, strchr_test_4);
  tcase_add_test(tcase, strchr_test_6);
  tcase_add_test(tcase, strchr_test_7);
  tcase_add_test(tcase, strchr_test_9);
  tcase_add_test(tcase, strchr_test_10);

  suite_add_tcase(suite, tcase);
  return suite;
}

START_TEST(strncmp_test_1) {
  char str1[] = "Hello, niggas";
  char str2[] = "Hello, niggas";
  size_t n = strlen(str1);

  int s21_result = s21_strncmp(str1, str2, n);
  int result = strncmp(str1, str2, n);

  ck_assert_int_eq(s21_result, result);
}
END_TEST

START_TEST(strncmp_test_2) {
  char str1[] = "Hello, niggas";
  char str2[] = "";
  size_t n = strlen(str1);

  int s21_result = s21_strncmp(str1, str2, n);
  int result = strncmp(str1, str2, n);

  ck_assert_int_eq(s21_result, result);
}
END_TEST

START_TEST(strncmp_test_3) {
  char str1[] = "";
  char str2[] = "";
  size_t n = strlen(str1);

  int s21_result = s21_strncmp(str1, str2, n);
  int result = strncmp(str1, str2, n);

  ck_assert_int_eq(s21_result, result);
}
END_TEST

START_TEST(strncmp_test_4) {
  char str1[] = "\n\t\0";
  char str2[] = "\0\n\n";
  size_t n = strlen(str1);

  int s21_result = s21_strncmp(str1, str2, n);
  int result = strncmp(str1, str2, n);

  ck_assert_int_eq(s21_result, result);
}
END_TEST

START_TEST(strncmp_test_5) {
  char str1[] = "\n\t\0";
  char str2[] = "\0\n\n";
  size_t n = 0;

  int s21_result = s21_strncmp(str1, str2, n);
  int result = strncmp(str1, str2, n);

  ck_assert_int_eq(s21_result, result);
}
END_TEST

START_TEST(strncmp_test_6) {
  char str1[] = "Hello";
  char str2[] = "World";
  size_t n = strlen(str1) * 2;

  int s21_result = s21_strncmp(str1, str2, n);
  int result = strncmp(str1, str2, n);

  ck_assert_int_eq(s21_result, result);
}
END_TEST

START_TEST(strncmp_test_7) {
  char str1[] = "Hello, niggas";
  char str2[] = "";
  size_t n = 0;

  int s21_result = s21_strncmp(str1, str2, n);
  int result = strncmp(str1, str2, n);

  ck_assert_int_eq(s21_result, result);
}
END_TEST

START_TEST(strncmp_test_8) {
  char str1[] = "black cats";
  char str2[] = " ";
  size_t n = strlen(str1);

  int s21_result = s21_strncmp(str1, str2, n);
  int result = strncmp(str1, str2, n);

  ck_assert_int_eq(s21_result, result);
}
END_TEST

START_TEST(strncmp_test_9) {
  char str1[] = "black cats";
  char str2[] = " ";
  size_t n = strlen(str1);

  int s21_result = s21_strncmp(str1, str2, n);
  int result = strncmp(str1, str2, n);

  ck_assert_int_eq(s21_result, result);
}
END_TEST

START_TEST(strncmp_test_10) {
  char str1[] = "black cats";
  char str2[] = " ";
  size_t n = strlen(str1);

  int s21_result = s21_strncmp(str1, str2, n);
  int result = strncmp(str1, str2, n);

  ck_assert_int_eq(s21_result, result);
}
END_TEST

Suite *strncmp_test() {
  Suite *suite = suite_create("s21_strncmp_test");
  TCase *tcase = tcase_create("strncmp");

  tcase_add_test(tcase, strncmp_test_1);
  tcase_add_test(tcase, strncmp_test_2);
  tcase_add_test(tcase, strncmp_test_3);
  tcase_add_test(tcase, strncmp_test_4);
  tcase_add_test(tcase, strncmp_test_5);
  tcase_add_test(tcase, strncmp_test_6);
  tcase_add_test(tcase, strncmp_test_7);
  tcase_add_test(tcase, strncmp_test_8);
  tcase_add_test(tcase, strncmp_test_9);
  tcase_add_test(tcase, strncmp_test_10);

  suite_add_tcase(suite, tcase);
  return suite;
}

START_TEST(strncpy_test_1) {
  char dest[20] = "Hello, niggas";
  char src[] = "Hello, world!";
  size_t n = strlen(src);

  char *s21_result = s21_strncpy(dest, src, n);
  char *result = strncpy(dest, src, n);

  ck_assert_mem_eq(s21_result, result, n);
}
END_TEST

START_TEST(strncpy_test_2) {
  char dest[] = "Hello, niggas";
  char src[] = "Hello, world!";
  size_t n = 0;

  char *s21_result = s21_strncpy(dest, src, n);
  char *result = strncpy(dest, src, n);

  ck_assert_str_eq(s21_result, result);
}
END_TEST

START_TEST(strncpy_test_3) {
  char dest[20] = "Hello, niggas";
  char src[] = "Hello";
  size_t n = 10;

  char *s21_result = s21_strncpy(dest, src, n);
  char *result = strncpy(dest, src, n);

  ck_assert_mem_eq(s21_result, result, n);
}
END_TEST

START_TEST(strncpy_test_4) {
  char dest[] = "";
  char src[] = "";
  size_t n = strlen(dest);

  char *s21_result = s21_strncpy(dest, src, n);
  char *result = strncpy(dest, src, n);

  ck_assert_str_eq(s21_result, result);
}
END_TEST

START_TEST(strncpy_test_5) {
  char dest[] = {1, 'a', 2, 'b'};
  char src[] = {1, 'a', 2, 'b'};
  size_t n = sizeof(dest);

  char *s21_result = s21_strncpy(dest, src, n);
  char *result = strncpy(dest, src, n);

  ck_assert_str_eq(s21_result, result);
}
END_TEST

START_TEST(strncpy_test_6) {
  char dest[] = "\0";
  char src[] = "\0";
  size_t n = strlen(dest);

  char *s21_result = s21_strncpy(dest, src, n);
  char *result = strncpy(dest, src, n);

  ck_assert_str_eq(s21_result, result);
}
END_TEST

START_TEST(strncpy_test_7) {
  char dest[] = "\1\2\3\4";
  char src[] = "\0\t\n";
  size_t n = strlen(dest);

  char *s21_result = s21_strncpy(dest, src, n);
  char *result = strncpy(dest, src, n);

  ck_assert_str_eq(s21_result, result);
}
END_TEST

START_TEST(strncpy_test_8) {
  char dest[] = "black cats";
  char src[] = "\t";
  size_t n = strlen(dest);

  char *s21_result = s21_strncpy(dest, src, n);
  char *result = strncpy(dest, src, n);

  ck_assert_str_eq(s21_result, result);
}
END_TEST

START_TEST(strncpy_test_9) {
  char dest[] = "black cats";
  char src[] = "";
  size_t n = strlen(dest);

  char *s21_result = s21_strncpy(dest, src, n);
  char *result = strncpy(dest, src, n);

  ck_assert_str_eq(s21_result, result);
}
END_TEST

START_TEST(strncpy_test_10) {
  char dest[] = "";
  char src[] = "black cats";
  size_t n = strlen(dest);

  char *s21_result = s21_strncpy(dest, src, n);
  char *result = strncpy(dest, src, n);

  ck_assert_str_eq(s21_result, result);
}
END_TEST

Suite *strncpy_test() {
  Suite *suite = suite_create("s21_strncpy_test");
  TCase *tcase = tcase_create("strncpy");

  tcase_add_test(tcase, strncpy_test_1);
  tcase_add_test(tcase, strncpy_test_2);
  tcase_add_test(tcase, strncpy_test_3);
  tcase_add_test(tcase, strncpy_test_4);
  tcase_add_test(tcase, strncpy_test_5);
  tcase_add_test(tcase, strncpy_test_6);
  tcase_add_test(tcase, strncpy_test_7);
  tcase_add_test(tcase, strncpy_test_8);
  tcase_add_test(tcase, strncpy_test_9);
  tcase_add_test(tcase, strncpy_test_10);

  suite_add_tcase(suite, tcase);
  return suite;
}

START_TEST(strcspn_test_1) {
  char str1[] = "Hello, niggas";
  char str2[] = "xyz";

  size_t s21_result = s21_strcspn(str1, str2);
  size_t result = strcspn(str1, str2);

  ck_assert_int_eq(s21_result, result);
}
END_TEST

START_TEST(strcspn_test_2) {
  char str1[] = "Hello, niggas";
  char str2[] = "eo";

  size_t s21_result = s21_strcspn(str1, str2);
  size_t result = strcspn(str1, str2);

  ck_assert_int_eq(s21_result, result);
}
END_TEST

START_TEST(strcspn_test_3) {
  char str1[] = "";
  char str2[] = "abc";

  size_t s21_result = s21_strcspn(str1, str2);
  size_t result = strcspn(str1, str2);

  ck_assert_int_eq(s21_result, result);
}
END_TEST

START_TEST(strcspn_test_4) {
  char str1[] = "Hello, niggas";
  char str2[] = "";

  size_t s21_result = s21_strcspn(str1, str2);
  size_t result = strcspn(str1, str2);

  ck_assert_int_eq(s21_result, result);
}
END_TEST

START_TEST(strcspn_test_5) {
  char str1[] = "black cats";
  char str2[] = "blck cts";

  size_t s21_result = s21_strcspn(str1, str2);
  size_t result = strcspn(str1, str2);

  ck_assert_int_eq(s21_result, result);
}
END_TEST

START_TEST(strcspn_test_6) {
  char str1[] = "\0";
  char str2[] = "abc";

  size_t s21_result = s21_strcspn(str1, str2);
  size_t result = strcspn(str1, str2);

  ck_assert_int_eq(s21_result, result);
}
END_TEST

START_TEST(strcspn_test_7) {
  char str1[] = "\1\2\3\4";
  char str2[] = "\0\t\n";

  size_t s21_result = s21_strcspn(str1, str2);
  size_t result = strcspn(str1, str2);

  ck_assert_int_eq(s21_result, result);
}
END_TEST

START_TEST(strcspn_test_8) {
  char str1[] = "\t\f";
  char str2[] = "\t";

  size_t s21_result = s21_strcspn(str1, str2);
  size_t result = strcspn(str1, str2);

  ck_assert_int_eq(s21_result, result);
}
END_TEST

START_TEST(strcspn_test_9) {
  char str1[] = "black cats";
  char str2[] = "";

  size_t s21_result = s21_strcspn(str1, str2);
  size_t result = strcspn(str1, str2);

  ck_assert_int_eq(s21_result, result);
}
END_TEST

START_TEST(strcspn_test_10) {
  char str1[] = "";
  char str2[] = "black cats";

  size_t s21_result = s21_strcspn(str1, str2);
  size_t result = strcspn(str1, str2);

  ck_assert_int_eq(s21_result, result);
}
END_TEST

Suite *strcspn_test() {
  Suite *suite = suite_create("s21_strcspn_test");
  TCase *tcase = tcase_create("strcspn");

  tcase_add_test(tcase, strcspn_test_1);
  tcase_add_test(tcase, strcspn_test_2);
  tcase_add_test(tcase, strcspn_test_3);
  tcase_add_test(tcase, strcspn_test_4);
  tcase_add_test(tcase, strcspn_test_5);
  tcase_add_test(tcase, strcspn_test_6);
  tcase_add_test(tcase, strcspn_test_7);
  tcase_add_test(tcase, strcspn_test_8);
  tcase_add_test(tcase, strcspn_test_9);
  tcase_add_test(tcase, strcspn_test_10);

  suite_add_tcase(suite, tcase);
  return suite;
}

START_TEST(strerror_test_1) {
  int errnum = 0;

  char *s21_result = s21_strerror(errnum);
  char *result = strerror(errnum);

  ck_assert_str_eq(s21_result, result);
}
END_TEST

START_TEST(strerror_test_2) {
  int errnum = 1;

  char *s21_result = s21_strerror(errnum);
  char *result = strerror(errnum);

  ck_assert_str_eq(s21_result, result);
}
END_TEST

START_TEST(strerror_test_3) {
  int errnum = 2;

  char *s21_result = s21_strerror(errnum);
  char *result = strerror(errnum);

  ck_assert_str_eq(s21_result, result);
}
END_TEST

START_TEST(strerror_test_4) {
  int errnum = 3;
  char *s21_result = s21_strerror(errnum);
  char *result = strerror(errnum);

  ck_assert_str_eq(s21_result, result);
}
END_TEST

START_TEST(strerror_test_5) {
  int errnum = 4;

  char *s21_result = s21_strerror(errnum);
  char *result = strerror(errnum);

  ck_assert_str_eq(s21_result, result);
}
END_TEST

START_TEST(strerror_test_6) {
  int errnum = 5;

  char *s21_result = s21_strerror(errnum);
  char *result = strerror(errnum);

  ck_assert_str_eq(s21_result, result);
}
END_TEST

START_TEST(strerror_test_7) {
  int errnum = 6;

  char *s21_result = s21_strerror(errnum);
  char *result = strerror(errnum);

  ck_assert_str_eq(s21_result, result);
}
END_TEST

START_TEST(strerror_test_8) {
  int errnum = 7;

  char *s21_result = s21_strerror(errnum);
  char *result = strerror(errnum);

  ck_assert_str_eq(s21_result, result);
}
END_TEST

START_TEST(strerror_test_9) {
  int errnum = 8;

  char *s21_result = s21_strerror(errnum);
  char *result = strerror(errnum);

  ck_assert_str_eq(s21_result, result);
}
END_TEST

START_TEST(strerror_test_10) {
  int errnum = 9;

  char *s21_result = s21_strerror(errnum);
  char *result = strerror(errnum);

  ck_assert_str_eq(s21_result, result);
}
END_TEST

Suite *strerror_test() {
  Suite *suite = suite_create("s21_strerror_test");
  TCase *tcase = tcase_create("strerror");

  tcase_add_test(tcase, strerror_test_1);
  tcase_add_test(tcase, strerror_test_2);
  tcase_add_test(tcase, strerror_test_3);
  tcase_add_test(tcase, strerror_test_4);
  tcase_add_test(tcase, strerror_test_5);
  tcase_add_test(tcase, strerror_test_6);
  tcase_add_test(tcase, strerror_test_7);
  tcase_add_test(tcase, strerror_test_8);
  tcase_add_test(tcase, strerror_test_9);
  tcase_add_test(tcase, strerror_test_10);

  suite_add_tcase(suite, tcase);
  return suite;
}

START_TEST(strlen_test_1) {
  char str[] = "Hello, niggas";

  size_t s21_result = s21_strlen(str);
  size_t result = strlen(str);

  ck_assert_int_eq(s21_result, result);
}
END_TEST

START_TEST(strlen_test_2) {
  char str[] = "Hello \n\t niggas";

  size_t s21_result = s21_strlen(str);
  size_t result = strlen(str);

  ck_assert_int_eq(s21_result, result);
}
END_TEST

START_TEST(strlen_test_3) {
  char str[] = "\0black cats";

  size_t s21_result = s21_strlen(str);
  size_t result = strlen(str);

  ck_assert_int_eq(s21_result, result);
}
END_TEST

START_TEST(strlen_test_4) {
  char str[] = "";

  size_t s21_result = s21_strlen(str);
  size_t result = strlen(str);

  ck_assert_int_eq(s21_result, result);
}
END_TEST

START_TEST(strlen_test_5) {
  char str[] = "\0sadasd";

  size_t s21_result = s21_strlen(str);
  size_t result = strlen(str);

  ck_assert_int_eq(s21_result, result);
}
END_TEST

START_TEST(strlen_test_6) {
  char str[] = "\0";

  size_t s21_result = s21_strlen(str);
  size_t result = strlen(str);

  ck_assert_int_eq(s21_result, result);
}
END_TEST

START_TEST(strlen_test_7) {
  char str[] = "\1\2\3\4";

  size_t s21_result = s21_strlen(str);
  size_t result = strlen(str);

  ck_assert_int_eq(s21_result, result);
}
END_TEST

START_TEST(strlen_test_8) {
  char str[] = "";

  size_t s21_result = s21_strlen(str);
  size_t result = strlen(str);

  ck_assert_int_eq(s21_result, result);
}
END_TEST

START_TEST(strlen_test_9) {
  char str[] = "black cats";

  size_t s21_result = s21_strlen(str);
  size_t result = strlen(str);

  ck_assert_int_eq(s21_result, result);
}
END_TEST

START_TEST(strlen_test_10) {
  char str[] = "\0";

  size_t s21_result = s21_strlen(str);
  size_t result = strlen(str);

  ck_assert_int_eq(s21_result, result);
}
END_TEST

Suite *strlen_test() {
  Suite *suite = suite_create("s21_strlen_test");
  TCase *tcase = tcase_create("strlen_");

  tcase_add_test(tcase, strlen_test_1);
  tcase_add_test(tcase, strlen_test_2);
  tcase_add_test(tcase, strlen_test_3);
  tcase_add_test(tcase, strlen_test_4);
  tcase_add_test(tcase, strlen_test_5);
  tcase_add_test(tcase, strlen_test_6);
  tcase_add_test(tcase, strlen_test_7);
  tcase_add_test(tcase, strlen_test_8);
  tcase_add_test(tcase, strlen_test_9);
  tcase_add_test(tcase, strlen_test_10);

  suite_add_tcase(suite, tcase);
  return suite;
}

START_TEST(strpbrk_test_1) {
  char str1[] = "Hello, niggas";
  char str2[] = "lo";

  char *s21_result = s21_strpbrk(str1, str2);
  char *result = strpbrk(str1, str2);

  ck_assert_pstr_eq(s21_result, result);
}
END_TEST

START_TEST(strpbrk_test_2) {
  char str1[] = "Hello, niggas";
  char str2[] = "xyz";

  char *s21_result = s21_strpbrk(str1, str2);
  char *result = strpbrk(str1, str2);

  ck_assert_pstr_eq(s21_result, result);
}
END_TEST

START_TEST(strpbrk_test_3) {
  char str1[] = "Hello, niggas";
  char str2[] = "";

  char *s21_result = s21_strpbrk(str1, str2);
  char *result = strpbrk(str1, str2);

  ck_assert_pstr_eq(s21_result, result);
}
END_TEST

START_TEST(strpbrk_test_4) {
  char str1[] = "";
  char str2[] = "";

  char *s21_result = s21_strpbrk(str1, str2);
  char *result = strpbrk(str1, str2);

  ck_assert_pstr_eq(s21_result, result);
}
END_TEST

START_TEST(strpbrk_test_5) {
  char str1[] = "black cats";
  char str2[] = "blck cts";

  char *s21_result = s21_strpbrk(str1, str2);
  char *result = strpbrk(str1, str2);

  ck_assert_pstr_eq(s21_result, result);
}
END_TEST

START_TEST(strpbrk_test_6) {
  char str1[] = "\0";
  char str2[] = "\0";

  char *s21_result = s21_strpbrk(str1, str2);
  char *result = strpbrk(str1, str2);

  ck_assert_pstr_eq(s21_result, result);
}
END_TEST

START_TEST(strpbrk_test_7) {
  char str1[] = "\1\2\3\4";
  char str2[] = "\0\t\n";

  char *s21_result = s21_strpbrk(str1, str2);
  char *result = strpbrk(str1, str2);

  ck_assert_pstr_eq(s21_result, result);
}
END_TEST

START_TEST(strpbrk_test_8) {
  char str1[] = "black cats";
  char str2[] = "\t";

  char *s21_result = s21_strpbrk(str1, str2);
  char *result = strpbrk(str1, str2);

  ck_assert_pstr_eq(s21_result, result);
}
END_TEST

START_TEST(strpbrk_test_9) {
  char str1[] = "black cats";
  char str2[] = "";

  char *s21_result = s21_strpbrk(str1, str2);
  char *result = strpbrk(str1, str2);

  ck_assert_pstr_eq(s21_result, result);
}
END_TEST

START_TEST(strpbrk_test_10) {
  char str1[] = "";
  char str2[] = "black cats";

  char *s21_result = s21_strpbrk(str1, str2);
  char *result = strpbrk(str1, str2);

  ck_assert_pstr_eq(s21_result, result);
}
END_TEST

Suite *strpbrk_test() {
  Suite *suite = suite_create("s21_strpbrk_test");
  TCase *tcase = tcase_create("strpbrk");

  tcase_add_test(tcase, strpbrk_test_1);
  tcase_add_test(tcase, strpbrk_test_2);
  tcase_add_test(tcase, strpbrk_test_3);
  tcase_add_test(tcase, strpbrk_test_4);
  tcase_add_test(tcase, strpbrk_test_5);
  tcase_add_test(tcase, strpbrk_test_6);
  tcase_add_test(tcase, strpbrk_test_7);
  tcase_add_test(tcase, strpbrk_test_8);
  tcase_add_test(tcase, strpbrk_test_9);
  tcase_add_test(tcase, strpbrk_test_10);

  suite_add_tcase(suite, tcase);
  return suite;
}

START_TEST(strrchr_test_1) {
  char str[] = "Hello, niggas";
  int c = '0';

  char *s21_result = s21_strrchr(str, c);
  char *result = strrchr(str, c);

  ck_assert_pstr_eq(s21_result, result);
}
END_TEST

START_TEST(strrchr_test_2) {
  char str[] = "Hello, niggas";
  int c = 0x1;

  char *s21_result = s21_strrchr(str, c);
  char *result = strrchr(str, c);

  ck_assert_pstr_eq(s21_result, result);
}
END_TEST

START_TEST(strrchr_test_3) {
  char str[] = "Hello, niggas";
  int c = 332;

  char *s21_result = s21_strrchr(str, c);
  char *result = strrchr(str, c);

  ck_assert_pstr_eq(s21_result, result);
}
END_TEST

START_TEST(strrchr_test_4) {
  char str[] = "";
  int c = 12;

  char *s21_result = s21_strrchr(str, c);
  char *result = strrchr(str, c);

  ck_assert_pstr_eq(s21_result, result);
}
END_TEST

START_TEST(strrchr_test_5) {
  char str[] = "black cats";
  int c = 9;

  char *s21_result = s21_strrchr(str, c);
  char *result = strrchr(str, c);

  ck_assert_pstr_eq(s21_result, result);
}
END_TEST

START_TEST(strrchr_test_6) {
  char str[] = "\0";
  int c = 0;

  char *s21_result = s21_strrchr(str, c);
  char *result = strrchr(str, c);

  ck_assert_pstr_eq(s21_result, result);
}
END_TEST

START_TEST(strrchr_test_7) {
  char str[] = "\1\2\3\4";
  int c = 0x21;

  char *s21_result = s21_strrchr(str, c);
  char *result = strrchr(str, c);

  ck_assert_pstr_eq(s21_result, result);
}
END_TEST

START_TEST(strrchr_test_8) {
  char str[] = "123456";
  int c = 2;

  char *s21_result = s21_strrchr(str, c);
  char *result = strrchr(str, c);

  ck_assert_pstr_eq(s21_result, result);
}
END_TEST

START_TEST(strrchr_test_9) {
  char str[] = "black cats";
  int c = 6;

  char *s21_result = s21_strrchr(str, c);
  char *result = strrchr(str, c);

  ck_assert_pstr_eq(s21_result, result);
}
END_TEST

START_TEST(strrchr_test_10) {
  char str[] = "";
  int c = 0;

  char *s21_result = s21_strrchr(str, c);
  char *result = strrchr(str, c);

  ck_assert_pstr_eq(s21_result, result);
}
END_TEST

Suite *strrchr_test() {
  Suite *suite = suite_create("s21_strrchr_test");
  TCase *tcase = tcase_create("strrchr");

  tcase_add_test(tcase, strrchr_test_1);
  tcase_add_test(tcase, strrchr_test_2);
  tcase_add_test(tcase, strrchr_test_3);
  tcase_add_test(tcase, strrchr_test_4);
  tcase_add_test(tcase, strrchr_test_5);
  tcase_add_test(tcase, strrchr_test_6);
  tcase_add_test(tcase, strrchr_test_7);
  tcase_add_test(tcase, strrchr_test_8);
  tcase_add_test(tcase, strrchr_test_9);
  tcase_add_test(tcase, strrchr_test_10);

  suite_add_tcase(suite, tcase);
  return suite;
}

START_TEST(strstr_test_1) {
  char haystack[] = "Hello, niggas";
  char needle[] = "Hello";

  char *s21_result = s21_strstr(haystack, needle);
  char *result = strstr(haystack, needle);

  ck_assert_pstr_eq(s21_result, result);
}
END_TEST

START_TEST(strstr_test_2) {
  char haystack[] = "Hello, niggas";
  char needle[] = "niggas";

  char *s21_result = s21_strstr(haystack, needle);
  char *result = strstr(haystack, needle);

  ck_assert_pstr_eq(s21_result, result);
}
END_TEST

START_TEST(strstr_test_3) {
  char haystack[] = "Hello, niggas";
  char needle[] = "world";

  char *s21_result = s21_strstr(haystack, needle);
  char *result = strstr(haystack, needle);

  ck_assert_pstr_eq(s21_result, result);
}
END_TEST

START_TEST(strstr_test_4) {
  char haystack[] = "";
  char needle[] = "";

  char *s21_result = s21_strstr(haystack, needle);
  char *result = strstr(haystack, needle);

  ck_assert_pstr_eq(s21_result, result);
}
END_TEST

START_TEST(strstr_test_5) {
  char haystack[] = "\t\n\f\0";
  char needle[] = "\t\n\f\0";

  char *s21_result = s21_strstr(haystack, needle);
  char *result = strstr(haystack, needle);

  ck_assert_pstr_eq(s21_result, result);
}
END_TEST

START_TEST(strstr_test_6) {
  char haystack[] = "\0";
  char needle[] = "\0";

  char *s21_result = s21_strstr(haystack, needle);
  char *result = strstr(haystack, needle);

  ck_assert_pstr_eq(s21_result, result);
}
END_TEST

START_TEST(strstr_test_7) {
  char haystack[] = "\1\2\3\4";
  char needle[] = "\0\t\n";

  char *s21_result = s21_strstr(haystack, needle);
  char *result = strstr(haystack, needle);

  ck_assert_pstr_eq(s21_result, result);
}
END_TEST

START_TEST(strstr_test_8) {
  char haystack[] = "\t\n\f\0";
  char needle[] = "\t";

  char *s21_result = s21_strstr(haystack, needle);
  char *result = strstr(haystack, needle);

  ck_assert_pstr_eq(s21_result, result);
}
END_TEST

START_TEST(strstr_test_9) {
  char haystack[] = "black cats";
  char needle[] = "";

  char *s21_result = s21_strstr(haystack, needle);
  char *result = strstr(haystack, needle);

  ck_assert_pstr_eq(s21_result, result);
}
END_TEST

START_TEST(strstr_test_10) {
  char haystack[] = "";
  char needle[] = "black cats";

  char *s21_result = s21_strstr(haystack, needle);
  char *result = strstr(haystack, needle);

  ck_assert_pstr_eq(s21_result, result);
}
END_TEST

Suite *strstr_test() {
  Suite *suite = suite_create("s21_strstr_test");
  TCase *tcase = tcase_create("strstr");

  tcase_add_test(tcase, strstr_test_1);
  tcase_add_test(tcase, strstr_test_2);
  tcase_add_test(tcase, strstr_test_3);
  tcase_add_test(tcase, strstr_test_4);
  tcase_add_test(tcase, strstr_test_5);
  tcase_add_test(tcase, strstr_test_6);
  tcase_add_test(tcase, strstr_test_7);
  tcase_add_test(tcase, strstr_test_8);
  tcase_add_test(tcase, strstr_test_9);
  tcase_add_test(tcase, strstr_test_10);

  suite_add_tcase(suite, tcase);
  return suite;
}

START_TEST(strtok_test_1) {
  char str[] = "Hello, niggas";
  char delim[] = "Hello, niggas";

  char *s21_result = s21_strtok(str, delim);
  char *result = strtok(str, delim);

  ck_assert_pstr_eq(s21_result, result);
}
END_TEST

START_TEST(strtok_test_2) {
  char str[] = "Hello, niggas! This is a test.";
  char delim[] = ",!";

  char *s21_result = s21_strtok(str, delim);
  char *result = strtok(str, delim);

  ck_assert_pstr_eq(s21_result, result);
}
END_TEST

START_TEST(strtok_test_3) {
  char str[] = ",,,Hello, niggas,,,";
  char delim[] = ",";

  char *s21_result = s21_strtok(str, delim);
  char *result = strtok(str, delim);

  ck_assert_pstr_eq(s21_result, result);
}
END_TEST

START_TEST(strtok_test_4) {
  char str[] = "";
  char delim[] = "";

  char *s21_result = s21_strtok(str, delim);
  char *result = strtok(str, delim);

  ck_assert_pstr_eq(s21_result, result);
}
END_TEST

START_TEST(strtok_test_5) {
  char str[] = "\t\n\f\0";
  char delim[] = "\t\n\f\0";

  char *s21_result = s21_strtok(str, delim);
  char *result = strtok(str, delim);

  ck_assert_pstr_eq(s21_result, result);
}
END_TEST

START_TEST(strtok_test_6) {
  char str[] = "\0";
  char delim[] = "\0";

  char *s21_result = s21_strtok(str, delim);
  char *result = strtok(str, delim);

  ck_assert_pstr_eq(s21_result, result);
}
END_TEST

START_TEST(strtok_test_7) {
  char str[] = "\1\2\3\4";
  char delim[] = "\0\t\n";

  char *s21_result = s21_strtok(str, delim);
  char *result = strtok(str, delim);

  ck_assert_pstr_eq(s21_result, result);
}
END_TEST

START_TEST(strtok_test_8) {
  char str[] = "\t\n\f\0";
  char delim[] = "\t";

  char *s21_result = s21_strtok(str, delim);
  char *result = strtok(str, delim);

  ck_assert_pstr_eq(s21_result, result);
}
END_TEST

START_TEST(strtok_test_9) {
  char str[] = "black cats";
  char delim[] = "";

  char *s21_result = s21_strtok(str, delim);
  char *result = strtok(str, delim);

  ck_assert_pstr_eq(s21_result, result);
}
END_TEST

START_TEST(strtok_test_10) {
  char str[] = "";
  char delim[] = "black cats";

  char *s21_result = s21_strtok(str, delim);
  char *result = strtok(str, delim);

  ck_assert_pstr_eq(s21_result, result);
}
END_TEST

Suite *strtok_test() {
  Suite *suite = suite_create("s21_strtok_test");
  TCase *tcase = tcase_create("strtok");

  tcase_add_test(tcase, strtok_test_1);
  tcase_add_test(tcase, strtok_test_2);
  tcase_add_test(tcase, strtok_test_3);
  tcase_add_test(tcase, strtok_test_4);
  tcase_add_test(tcase, strtok_test_5);
  tcase_add_test(tcase, strtok_test_6);
  tcase_add_test(tcase, strtok_test_7);
  tcase_add_test(tcase, strtok_test_8);
  tcase_add_test(tcase, strtok_test_9);
  tcase_add_test(tcase, strtok_test_10);

  suite_add_tcase(suite, tcase);
  return suite;
}
