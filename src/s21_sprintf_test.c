#include <check.h>

#include "s21_string.h"

Suite *int_sprintf_test();
Suite *str_sprintf_test();
Suite *char_sprintf_test();
Suite *unsigned_sprintf_test();
Suite *float_sprintf_test();
Suite *percent_sprintf_test();
Suite *combined_sprintf_test();

int main() {
  SRunner *srunner;
  Suite *suites[] = {int_sprintf_test(),     str_sprintf_test(),
                     char_sprintf_test(),    unsigned_sprintf_test(),
                     float_sprintf_test(),   percent_sprintf_test(),
                     combined_sprintf_test()};

  for (int i = 0; i < 7; i++) {
    printf("========================================\n");
    srunner = srunner_create(suites[i]);
    srunner_run_all(srunner, CK_NORMAL);
    srunner_free(srunner);
  }
  return 0;
}

// Тесты для спецификатора %d
START_TEST(int_sprintf_test_1) {
  char str[100];
  char ch = 'a';

  int s21_result = s21_sprintf(str, "char %c", ch);
  int result = sprintf(str, "char %c", ch);

  ck_assert_int_eq(s21_result, result);
}
END_TEST

START_TEST(int_sprintf_test_2) {
  char str[100];
  int num = 10;

  int s21_result = s21_sprintf(str, "int %d", num);
  int result = sprintf(str, "int %d", num);

  ck_assert_int_eq(s21_result, result);
}
END_TEST

START_TEST(int_sprintf_test_3) {
  char str[100];
  int num = -42;

  int s21_result = s21_sprintf(str, "negative: %d", num);
  int result = sprintf(str, "negative: %d", num);

  ck_assert_int_eq(s21_result, result);
}
END_TEST

START_TEST(int_sprintf_test_4) {
  char str[100];
  int num = 123456789;

  int s21_result = s21_sprintf(str, "big number: %d", num);
  int result = sprintf(str, "big number: %d", num);

  ck_assert_int_eq(s21_result, result);
  ck_assert_str_eq(str, "big number: 123456789");
}
END_TEST

Suite *int_sprintf_test() {
  Suite *suite = suite_create("s21_int_sprintf_test");
  TCase *tcase = tcase_create("int_sprintf");

  tcase_add_test(tcase, int_sprintf_test_1);
  tcase_add_test(tcase, int_sprintf_test_2);
  tcase_add_test(tcase, int_sprintf_test_3);
  tcase_add_test(tcase, int_sprintf_test_4);

  suite_add_tcase(suite, tcase);
  return suite;
}

// Тесты для спецификатора %s
START_TEST(str_sprintf_test_1) {
  char str[100];
  char *src = "hello";

  int s21_result = s21_sprintf(str, "string: %s", src);
  int result = sprintf(str, "string: %s", src);

  ck_assert_int_eq(s21_result, result);
  ck_assert_str_eq(str, "string: hello");
}
END_TEST

START_TEST(str_sprintf_test_2) {
  char str[100];
  char *src = "world";

  int s21_result = s21_sprintf(str, "greeting: %s!", src);
  int result = sprintf(str, "greeting: %s!", src);

  ck_assert_int_eq(s21_result, result);
  ck_assert_str_eq(str, "greeting: world!");
}
END_TEST

START_TEST(str_sprintf_test_3) {
  char str[100];

  // Проверка на пустую строку
  char *src = "";

  int s21_result = s21_sprintf(str, "empty string: '%s'", src);
  int result = sprintf(str, "empty string: '%s'", src);

  ck_assert_int_eq(s21_result, result);
  ck_assert_str_eq(str, "empty string: ''");
}
END_TEST

START_TEST(str_sprintf_test_4) {
  char str[100];
  char *src = "Hello, World!";

  int s21_result = s21_sprintf(str, "string with spaces: %s", src);
  int result = sprintf(str, "string with spaces: %s", src);

  ck_assert_int_eq(s21_result, result);
  ck_assert_str_eq(str, "string with spaces: Hello, World!");
}
END_TEST

Suite *str_sprintf_test() {
  Suite *suite = suite_create("s21_str_sprintf_test");
  TCase *tcase = tcase_create("str_sprintf");

  tcase_add_test(tcase, str_sprintf_test_1);
  tcase_add_test(tcase, str_sprintf_test_2);
  tcase_add_test(tcase, str_sprintf_test_3);
  tcase_add_test(tcase, str_sprintf_test_4);

  suite_add_tcase(suite, tcase);
  return suite;
}

// Тесты для спецификатора %c
START_TEST(char_sprintf_test_1) {
  char str[100];
  char ch = 'A';

  int s21_result = s21_sprintf(str, "char %c", ch);
  int result = sprintf(str, "char %c", ch);

  ck_assert_int_eq(s21_result, result);
  ck_assert_str_eq(str, "char A");
}
END_TEST

START_TEST(char_sprintf_test_2) {
  char str[100];
  char ch = 'B';

  int s21_result = s21_sprintf(str, "%-5c", ch);
  int result = sprintf(str, "%-5c", ch);

  ck_assert_int_eq(s21_result, result);
  ck_assert_str_eq(str, "B    ");
}
END_TEST

START_TEST(char_sprintf_test_3) {
  char str[100];
  char ch = 'C';

  int s21_result = s21_sprintf(str, "%c!", ch);
  int result = sprintf(str, "%c!", ch);

  ck_assert_int_eq(s21_result, result);
  ck_assert_str_eq(str, "C!");
}
END_TEST

START_TEST(char_sprintf_test_4) {
  char str[100];
  char ch = '\0';

  int s21_result = s21_sprintf(str, "null char: %c", ch);
  int result = sprintf(str, "null char: %c", ch);

  ck_assert_int_eq(s21_result, result);
  ck_assert_str_eq(str, "null char: ");
}
END_TEST

Suite *char_sprintf_test() {
  Suite *suite = suite_create("s21_char_sprintf_test");
  TCase *tcase = tcase_create("char_sprintf");

  tcase_add_test(tcase, char_sprintf_test_1);
  tcase_add_test(tcase, char_sprintf_test_2);
  tcase_add_test(tcase, char_sprintf_test_3);
  tcase_add_test(tcase, char_sprintf_test_4);

  suite_add_tcase(suite, tcase);
  return suite;
}

// Тесты для спецификатора %u
START_TEST(unsigned_sprintf_test_1) {
  char str[100];
  unsigned int num = 123;

  int s21_result = s21_sprintf(str, "unsigned: %u", num);
  int result = sprintf(str, "unsigned: %u", num);

  ck_assert_int_eq(s21_result, result);
  ck_assert_str_eq(str, "unsigned: 123");
}
END_TEST

START_TEST(unsigned_sprintf_test_2) {
  char str[100];
  unsigned int num = 456;

  int s21_result = s21_sprintf(str, "unsigned: %5u", num);
  int result = sprintf(str, "unsigned: %5u", num);

  ck_assert_int_eq(s21_result, result);
  ck_assert_str_eq(str, "unsigned:   456");
}
END_TEST

START_TEST(unsigned_sprintf_test_3) {
  char str[100];
  unsigned int num = 0;

  int s21_result = s21_sprintf(str, "unsigned zero: %u", num);
  int result = sprintf(str, "unsigned zero: %u", num);

  ck_assert_int_eq(s21_result, result);
  ck_assert_str_eq(str, "unsigned zero: 0");
}
END_TEST

START_TEST(unsigned_sprintf_test_4) {
  char str[100];
  unsigned int num = 4294967295;
  int s21_result = s21_sprintf(str, "max unsigned: %u", num);
  int result = sprintf(str, "max unsigned: %u", num);

  ck_assert_int_eq(s21_result, result);
  ck_assert_str_eq(str, "max unsigned: 4294967295");
}
END_TEST

Suite *unsigned_sprintf_test() {
  Suite *suite = suite_create("s21_unsigned_sprintf_test");
  TCase *tcase = tcase_create("unsigned_sprintf");

  tcase_add_test(tcase, unsigned_sprintf_test_1);
  tcase_add_test(tcase, unsigned_sprintf_test_2);
  tcase_add_test(tcase, unsigned_sprintf_test_3);
  tcase_add_test(tcase, unsigned_sprintf_test_4);

  suite_add_tcase(suite, tcase);
  return suite;
}

// Тесты для спецификатора %f
START_TEST(float_sprintf_test_1) {
  char str[100];
  double num = 3.14159;

  int s21_result = s21_sprintf(str, "float: %f", num);
  int result = sprintf(str, "float: %f", num);

  ck_assert_int_eq(s21_result, result);
  ck_assert_str_eq(str, "float: 3.141590");
}
END_TEST

START_TEST(float_sprintf_test_2) {
  char str[100];
  double num = 3.14159;

  int s21_result = s21_sprintf(str, "float: %.2f", num);
  int result = sprintf(str, "float: %.2f", num);

  ck_assert_int_eq(s21_result, result);
  ck_assert_str_eq(str, "float: 3.14");
}
END_TEST

START_TEST(float_sprintf_test_3) {
  char str[100];
  double num = -123.456;

  int s21_result = s21_sprintf(str, "negative float: %f", num);
  int result = sprintf(str, "negative float: %f", num);

  ck_assert_int_eq(s21_result, result);
  ck_assert_str_eq(str, "negative float: -123.456000");
}
END_TEST

Suite *float_sprintf_test() {
  Suite *suite = suite_create("s21_float_sprintf_test");
  TCase *tcase = tcase_create("float_sprintf");

  tcase_add_test(tcase, float_sprintf_test_1);
  tcase_add_test(tcase, float_sprintf_test_2);
  tcase_add_test(tcase, float_sprintf_test_3);

  suite_add_tcase(suite, tcase);
  return suite;
}

// Тесты для спецификатора %%
START_TEST(percent_sprintf_test_1) {
  char str[100];

  int s21_result = s21_sprintf(str, "100%%");
  int result = sprintf(str, "100%%");

  ck_assert_int_eq(s21_result, result);
  ck_assert_str_eq(str, "100%");
}
END_TEST

START_TEST(percent_sprintf_test_2) {
  char str[100];

  int s21_result = s21_sprintf(str, "50%% discount on %d items", 10);
  int result = sprintf(str, "50%% discount on %d items", 10);

  ck_assert_int_eq(s21_result, result);
  ck_assert_str_eq(str, "50% discount on 10 items");
}
END_TEST

Suite *percent_sprintf_test() {
  Suite *suite = suite_create("s21_percent_sprintf_test");
  TCase *tcase = tcase_create("percent_sprintf");

  tcase_add_test(tcase, percent_sprintf_test_1);
  tcase_add_test(tcase, percent_sprintf_test_2);

  suite_add_tcase(suite, tcase);
  return suite;
}

// Комбинированные тесты
START_TEST(combined_sprintf_test_1) {
  char str[100];
  int num = 42;
  char ch = 'A';
  char *src = "Test";

  int s21_result = s21_sprintf(str, "Combined: %d %c %s", num, ch, src);
  int result = sprintf(str, "Combined: %d %c %s", num, ch, src);

  ck_assert_int_eq(s21_result, result);
  ck_assert_str_eq(str, "Combined: 42 A Test");
}
END_TEST

START_TEST(combined_sprintf_test_2) {
  char str[100];
  int num = -10;
  char ch = 'Z';
  char *src = "Combined Test";

  int s21_result = s21_sprintf(str, "Combined: %d %c %s %%", num, ch, src);
  int result = sprintf(str, "Combined: %d %c %s %%", num, ch, src);

  ck_assert_int_eq(s21_result, result);
  ck_assert_str_eq(str, "Combined: -10 Z Combined Test %");
}
END_TEST

START_TEST(combined_sprintf_test_3) {
  char str[100];
  int num = 42;
  char ch = 'A';
  char *src = "Test";
  double fnum = 3.14;

  int s21_result =
      s21_sprintf(str, "Combined: %d %c %s %.2f %%", num, ch, src, fnum);
  int result = sprintf(str, "Combined: %d %c %s %.2f %%", num, ch, src, fnum);

  ck_assert_int_eq(s21_result, result);
  ck_assert_str_eq(str, "Combined: 42 A Test 3.14 %");
}
END_TEST

Suite *combined_sprintf_test() {
  Suite *suite = suite_create("s21_combined_sprintf_test");
  TCase *tcase = tcase_create("combined_sprintf");

  tcase_add_test(tcase, combined_sprintf_test_1);
  tcase_add_test(tcase, combined_sprintf_test_2);
  tcase_add_test(tcase, combined_sprintf_test_3);
  suite_add_tcase(suite, tcase);
  return suite;
}
