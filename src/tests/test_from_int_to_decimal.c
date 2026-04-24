#include "s21_tests.h"

START_TEST(test_from_int_positive) {
  s21_decimal dst;
  int res = s21_from_int_to_decimal(123, &dst);

  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(dst.bits[0], 123);
  ck_assert_int_eq(dst.bits[1], 0);
  ck_assert_int_eq(dst.bits[2], 0);
  ck_assert_int_eq(dst.bits[3], 0);
}
END_TEST

START_TEST(test_from_int_negative) {
  s21_decimal dst;
  int res = s21_from_int_to_decimal(-456, &dst);

  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(dst.bits[0], 456);
  ck_assert_int_eq(dst.bits[1], 0);
  ck_assert_int_eq(dst.bits[2], 0);
  ck_assert_int_eq((dst.bits[3] >> 31) & 1, 1);
}
END_TEST

START_TEST(test_from_int_zero) {
  s21_decimal dst;
  int res = s21_from_int_to_decimal(0, &dst);

  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(dst.bits[0], 0);
  ck_assert_int_eq(dst.bits[1], 0);
  ck_assert_int_eq(dst.bits[2], 0);
  ck_assert_int_eq(dst.bits[3], 0);
}
END_TEST

START_TEST(test_from_int_max) {
  s21_decimal dst;
  int res = s21_from_int_to_decimal(2147483647, &dst);

  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(dst.bits[0], 2147483647);
}
END_TEST

START_TEST(test_from_int_min) {
  s21_decimal dst;
  int res = s21_from_int_to_decimal(-2147483648, &dst);

  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(dst.bits[0], 2147483648u);
  ck_assert_int_eq((dst.bits[3] >> 31) & 1, 1);
}
END_TEST

START_TEST(test_from_int_null_ptr) {
  int res = s21_from_int_to_decimal(123, NULL);
  ck_assert_int_ne(res, 0);
}
END_TEST

Suite* s21_from_int_to_decimal_suite(void) {
  Suite* s = suite_create("s21_from_int_to_decimal");
  TCase* tc = tcase_create("core");

  tcase_add_test(tc, test_from_int_positive);
  tcase_add_test(tc, test_from_int_negative);
  tcase_add_test(tc, test_from_int_zero);
  tcase_add_test(tc, test_from_int_max);
  tcase_add_test(tc, test_from_int_min);
  tcase_add_test(tc, test_from_int_null_ptr);

  suite_add_tcase(s, tc);
  return s;
}