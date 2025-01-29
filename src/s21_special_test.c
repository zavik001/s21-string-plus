#include <check.h>
#include <string.h>

#include "s21_string.h"

Suite *to_upper_suite();
Suite *to_lower_suite();
Suite *insert_suite();
Suite *trim_suite();

int main() {
  SRunner *test_runner;
  Suite *test_suites[] = {to_upper_suite(), to_lower_suite(), insert_suite(),
                          trim_suite()};

  for (int i = 0; i < 4; i++) {
    printf("========================================\n");
    test_runner = srunner_create(test_suites[i]);
    srunner_run_all(test_runner, CK_NORMAL);
    srunner_free(test_runner);
  }
  return 0;
}

// Тесты для функции s21_to_upper
START_TEST(to_upper_test_1) {
  void *result = s21_to_upper("abc");
  char *expected = "ABC";

  ck_assert_pstr_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(to_upper_test_2) {
  void *result = s21_to_upper("r");
  char *expected = "R";

  ck_assert_pstr_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(to_upper_test_3) {
  void *result = s21_to_upper("7");
  char *expected = "7";

  ck_assert_pstr_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(to_upper_test_4) {
  void *result = s21_to_upper("abc 123");
  char *expected = "ABC 123";

  ck_assert_pstr_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(to_upper_test_5) {
  void *result = s21_to_upper("\t \t \t \n");
  char *expected = "\t \t \t \n";

  ck_assert_pstr_eq(result, expected);
  free(result);
}
END_TEST

Suite *to_upper_suite() {
  Suite *suite = suite_create("s21_to_upper_test");
  TCase *test_case = tcase_create("to_upper");

  tcase_add_test(test_case, to_upper_test_1);
  tcase_add_test(test_case, to_upper_test_2);
  tcase_add_test(test_case, to_upper_test_3);
  tcase_add_test(test_case, to_upper_test_4);
  tcase_add_test(test_case, to_upper_test_5);

  suite_add_tcase(suite, test_case);
  return suite;
}

// Тесты для функции s21_to_lower
START_TEST(to_lower_test_1) {
  void *result = s21_to_lower("ABC");
  char *expected = "abc";

  ck_assert_pstr_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(to_lower_test_2) {
  void *result = s21_to_lower("G");
  char *expected = "g";

  ck_assert_pstr_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(to_lower_test_3) {
  void *result = s21_to_lower("9");
  char *expected = "9";

  ck_assert_pstr_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(to_lower_test_4) {
  void *result = s21_to_lower("ABC 123");
  char *expected = "abc 123";

  ck_assert_pstr_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(to_lower_test_5) {
  void *result = s21_to_lower("\t \t \t \n");
  char *expected = "\t \t \t \n";

  ck_assert_pstr_eq(result, expected);
  free(result);
}
END_TEST

Suite *to_lower_suite() {
  Suite *suite = suite_create("s21_to_lower_test");
  TCase *test_case = tcase_create("to_lower");

  tcase_add_test(test_case, to_lower_test_1);
  tcase_add_test(test_case, to_lower_test_2);
  tcase_add_test(test_case, to_lower_test_3);
  tcase_add_test(test_case, to_lower_test_4);
  tcase_add_test(test_case, to_lower_test_5);

  suite_add_tcase(suite, test_case);
  return suite;
}

// Тесты для функции s21_insert
START_TEST(insert_test_1) {
  char source[] = "YZ";
  char insert_str[] = "X";
  size_t index = 0;

  void *result = s21_insert(source, insert_str, index);
  char expected[] = "XYZ";

  ck_assert_pstr_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(insert_test_2) {
  char source[] = "abc";
  char insert_str[] = "abc";
  size_t index = 0;

  void *result = s21_insert(source, insert_str, index);
  char expected[] = "abcabc";

  ck_assert_pstr_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(insert_test_3) {
  char source[] = "f";
  char insert_str[] = "f";
  size_t index = 1;

  void *result = s21_insert(source, insert_str, index);
  char *expected = NULL;

  ck_assert_pstr_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(insert_test_4) {
  char source[] = "123";
  char insert_str[] = "123";
  size_t index = 1;

  void *result = s21_insert(source, insert_str, index);
  char expected[] = "112323";

  ck_assert_pstr_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(insert_test_5) {
  char source[] = "";
  char insert_str[] = "abc";
  size_t index = 1;

  void *result = s21_insert(source, insert_str, index);
  char *expected = NULL;

  ck_assert_pstr_eq(result, expected);
  free(result);
}
END_TEST

Suite *insert_suite() {
  Suite *suite = suite_create("s21_insert_test");
  TCase *test_case = tcase_create("insert");

  tcase_add_test(test_case, insert_test_1);
  tcase_add_test(test_case, insert_test_2);
  tcase_add_test(test_case, insert_test_3);
  tcase_add_test(test_case, insert_test_4);
  tcase_add_test(test_case, insert_test_5);

  suite_add_tcase(suite, test_case);
  return suite;
}

// Тесты для функции s21_trim
START_TEST(trim_test_1) {
  char source[] = "ABA";
  char trim_chars[] = "A";

  void *result = s21_trim(source, trim_chars);
  char expected[] = "B";

  ck_assert_pstr_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(trim_test_2) {
  char source[] = "25abc25xyz25";
  char trim_chars[] = "25";

  void *result = s21_trim(source, trim_chars);
  char expected[] = "abc25xyz";

  ck_assert_pstr_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(trim_test_3) {
  char source[] = "abc25xyz25";
  char trim_chars[] = "25";

  void *result = s21_trim(source, trim_chars);
  char expected[] = "abc25xyz";

  ck_assert_pstr_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(trim_test_4) {
  char source[] = "52abc52xyz";
  char trim_chars[] = "52";

  void *result = s21_trim(source, trim_chars);
  char expected[] = "abc52xyz";

  ck_assert_pstr_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(trim_test_5) {
  char source[] = "AVBCVA";
  char trim_chars[] = "V";

  void *result = s21_trim(source, trim_chars);
  char expected[] = "AVBCVA";

  ck_assert_pstr_eq(result, expected);
  free(result);
}
END_TEST

Suite *trim_suite() {
  Suite *suite = suite_create("s21_trim_test");
  TCase *test_case = tcase_create("trim");

  tcase_add_test(test_case, trim_test_1);
  tcase_add_test(test_case, trim_test_2);
  tcase_add_test(test_case, trim_test_3);
  tcase_add_test(test_case, trim_test_4);
  tcase_add_test(test_case, trim_test_5);

  suite_add_tcase(suite, test_case);
  return suite;
}
