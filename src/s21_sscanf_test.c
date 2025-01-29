#include <check.h>

#include "s21_string.h"

Suite *int_sscanf_test();

int main() {
  SRunner *srunner;
  Suite *suites[] = {int_sscanf_test()};

  for (int i = 0; i < 1; i++) {
    printf("========================================\n");
    srunner = srunner_create(suites[i]);
    srunner_run_all(srunner, CK_NORMAL);
    srunner_free(srunner);
  }
  return 0;
}

//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
START_TEST(int_sscanf_test_1) {
  int num;

  int s21_result = s21_sscanf("10", "%d", &num);
  int result = sscanf("10", "%d", &num);

  ck_assert_int_eq(s21_result, result);
}
END_TEST

START_TEST(int_sscanf_test_2) {
  int num;

  int s21_result = s21_sscanf("-10", "%d", &num);
  int result = sscanf("-10", "%d", &num);

  ck_assert_int_eq(s21_result, result);
}
END_TEST

START_TEST(int_sscanf_test_3) {
  unsigned int num;

  int s21_result = s21_sscanf("-10", "%u", &num);
  int result = sscanf("-10", "%u", &num);

  ck_assert_int_eq(s21_result, result);
}
END_TEST

START_TEST(int_sscanf_test_4) {
  char ch;

  int s21_result = s21_sscanf("A", "%c", &ch);
  int result = sscanf("A", "%c", &ch);

  ck_assert_int_eq(s21_result, result);
}
END_TEST

START_TEST(int_sscanf_test_5) {
  char chs[6];

  int s21_result = s21_sscanf("hello", "%s", chs);
  int result = sscanf("hello", "%s", chs);

  ck_assert_int_eq(s21_result, result);
}
END_TEST

START_TEST(int_sscanf_test_6) {
  float num;

  int s21_result = s21_sscanf("12.34", "%f", &num);
  int result = sscanf("12.34", "%f", &num);

  ck_assert_int_eq(s21_result, result);
}
END_TEST

START_TEST(int_sscanf_test_7) {
  // Удалён неверный формат "%.2f", так как sscanf не поддерживает precision.
  float num;

  int s21_result = s21_sscanf("12.345", "%f", &num);
  int result = sscanf("12.345", "%f", &num);

  ck_assert_int_eq(s21_result, result);
}
END_TEST

START_TEST(int_sscanf_test_8) {
  int num;

  int s21_result = s21_sscanf(" 12", "%d", &num);
  int result = sscanf(" 12", "%d", &num);

  ck_assert_int_eq(s21_result, result);
}
END_TEST

START_TEST(int_sscanf_test_9) {
  float num;

  int s21_result = s21_sscanf("12.34", "%f", &num);
  int result = sscanf("12.34", "%f", &num);

  ck_assert_int_eq(s21_result, result);
}
END_TEST

START_TEST(int_sscanf_test_10) {
  int num;
  char ch;

  int s21_result = s21_sscanf("12 hello", "%d %c", &num, &ch);
  int result = sscanf("12 hello", "%d %c", &num, &ch);

  ck_assert_int_eq(s21_result, result);
}
END_TEST

START_TEST(int_sscanf_test_11) {
  int num;

  int s21_result = s21_sscanf("2A", "%x", &num);
  int result = sscanf("2A", "%x", &num);

  ck_assert_int_eq(s21_result, result);
}
END_TEST

START_TEST(int_sscanf_test_12) {
  float num;

  int s21_result = s21_sscanf(" 12.345 ", "%f", &num);
  int result = sscanf(" 12.345 ", "%f", &num);

  ck_assert_int_eq(s21_result, result);
}
END_TEST

START_TEST(int_sscanf_test_13) {
  float num;

  int s21_result = s21_sscanf("0.1", "%f", &num);
  int result = sscanf("0.1", "%f", &num);

  ck_assert_int_eq(s21_result, result);
}
END_TEST

START_TEST(int_sscanf_test_14) {
  char chs[6];
  char ch;

  int s21_result = s21_sscanf("67", "%c %s", &ch, chs);
  int result = sscanf("67", "%c %s", &ch, chs);

  ck_assert_int_eq(s21_result, result);
}
END_TEST

START_TEST(int_sscanf_test_15) {
  int num;

  int s21_result = s21_sscanf("67", "%o", &num);
  int result = sscanf("67", "%o", &num);

  ck_assert_int_eq(s21_result, result);
}
END_TEST

START_TEST(int_sscanf_test_16) {
  int num;
  char ch;

  int s21_result = s21_sscanf("12 A", "%d %c", &num, &ch);
  int result = sscanf("12 A", "%d %c", &num, &ch);

  ck_assert_int_eq(s21_result, result);
}
END_TEST

START_TEST(int_sscanf_test_17) {
  float num;

  int s21_result = s21_sscanf("-2.5e2", "%e", &num);
  int result = sscanf("-2.5e2", "%e", &num);

  ck_assert_int_eq(s21_result, result);
}
END_TEST

START_TEST(int_sscanf_test_18) {
  int num1;
  int num2;

  int s21_result = s21_sscanf("01 02", "%02d %02d", &num1, &num2);
  int result = sscanf("01 02", "%02d %02d", &num1, &num2);

  ck_assert_int_eq(s21_result, result);
}
END_TEST

START_TEST(int_sscanf_test_19) {
  int num1;
  float num2;
  char ch;
  char chs[6];

  int s21_result =
      s21_sscanf("1 1.1 a aa", "%d %f %c %s", &num1, &num2, &ch, chs);
  int result = sscanf("1 1.1 a aa", "%d %f %c %s", &num1, &num2, &ch, chs);

  ck_assert_int_eq(s21_result, result);
}
END_TEST

START_TEST(int_sscanf_test_20) {
  int num1;
  int num2;

  int s21_result = s21_sscanf("01 02", "%02d %02d", &num1, &num2);
  int result = sscanf("01 02", "%02d %02d", &num1, &num2);

  ck_assert_int_eq(s21_result, result);
}
END_TEST

Suite *int_sscanf_test() {
  Suite *suite = suite_create("s21_int_sscanf_test");
  TCase *tcase = tcase_create("int_sscanf");

  tcase_add_test(tcase, int_sscanf_test_1);
  tcase_add_test(tcase, int_sscanf_test_2);
  tcase_add_test(tcase, int_sscanf_test_3);
  tcase_add_test(tcase, int_sscanf_test_4);
  tcase_add_test(tcase, int_sscanf_test_5);
  tcase_add_test(tcase, int_sscanf_test_6);
  tcase_add_test(tcase, int_sscanf_test_7);
  tcase_add_test(tcase, int_sscanf_test_8);
  tcase_add_test(tcase, int_sscanf_test_9);
  tcase_add_test(tcase, int_sscanf_test_10);
  tcase_add_test(tcase, int_sscanf_test_11);
  tcase_add_test(tcase, int_sscanf_test_12);
  tcase_add_test(tcase, int_sscanf_test_13);
  tcase_add_test(tcase, int_sscanf_test_14);
  tcase_add_test(tcase, int_sscanf_test_15);
  tcase_add_test(tcase, int_sscanf_test_16);
  tcase_add_test(tcase, int_sscanf_test_17);
  tcase_add_test(tcase, int_sscanf_test_18);
  tcase_add_test(tcase, int_sscanf_test_19);
  tcase_add_test(tcase, int_sscanf_test_20);

  suite_add_tcase(suite, tcase);
  return suite;
}
