#include "s21_tests.h"

START_TEST(test_int_to_decimal_positive) {
  s21_decimal res;
  int ret = s21_from_int_to_decimal(123, &res);

  ck_assert_int_eq(ret, 0);
  ck_assert_int_eq(res.bits[0], 123);
  ck_assert_int_eq((res.bits[3] >> 31) & 1, 0);
}
END_TEST

START_TEST(test_int_to_decimal_negative) {
  s21_decimal res;
  int ret = s21_from_int_to_decimal(-123, &res);

  ck_assert_int_eq(ret, 0);
  ck_assert_int_eq(res.bits[0], 123);
  ck_assert_int_eq((res.bits[3] >> 31) & 1, 1);
}
END_TEST

START_TEST(test_int_to_decimal_zero) {
  s21_decimal res;
  s21_from_int_to_decimal(0, &res);

  ck_assert_int_eq(res.bits[0], 0);
}
END_TEST

START_TEST(test_int_max) {
  s21_decimal res;
  int ret = s21_from_int_to_decimal(2147483647, &res);

  ck_assert_int_eq(ret, 0);
  ck_assert_int_eq(res.bits[0], 2147483647);
}
END_TEST

START_TEST(test_decimal_to_int_basic) {
  s21_decimal src = {{123, 0, 0, 0}};
  int dst = 0;

  s21_from_decimal_to_int(src, &dst);

  ck_assert_int_eq(dst, 123);
}
END_TEST

START_TEST(test_decimal_to_int_with_scale) {
  s21_decimal src = {{1234, 0, 0, 0}};
  src.bits[3] = (1 << 16);

  int dst = 0;
  s21_from_decimal_to_int(src, &dst);

  ck_assert_int_eq(dst, 123);
}
END_TEST

START_TEST(test_decimal_to_int_negative) {
  s21_decimal src = {{123, 0, 0, 0}};
  src.bits[3] |= (1u << 31);

  int dst = 0;
  s21_from_decimal_to_int(src, &dst);

  ck_assert_int_eq(dst, -123);
}
END_TEST

START_TEST(test_decimal_to_int_overflow) {
  s21_decimal src = {{4000000000u, 0, 0, 0}};
  int dst = 0;

  int ret = s21_from_decimal_to_int(src, &dst);

  ck_assert_int_eq(ret, 1);
}
END_TEST

START_TEST(test_from_float_to_decimal_positive) {
  float src = 123.45f;
  s21_decimal dst;
  float result = 0.0f;

  int status = s21_from_float_to_decimal(src, &dst);

  ck_assert_int_eq(status, SUCCESS);

  s21_from_decimal_to_float(dst, &result);
  ck_assert_float_eq_tol(result, src, 1e-6);
}
END_TEST

START_TEST(test_from_float_to_decimal_negative) {
  float src = -123.45f;
  s21_decimal dst;
  float result = 0.0f;

  int status = s21_from_float_to_decimal(src, &dst);

  ck_assert_int_eq(status, SUCCESS);

  s21_from_decimal_to_float(dst, &result);
  ck_assert_float_eq_tol(result, src, 1e-6);
}
END_TEST

START_TEST(test_from_float_to_decimal_zero) {
  float src = 0.0f;
  s21_decimal dst;

  int status = s21_from_float_to_decimal(src, &dst);

  ck_assert_int_eq(status, SUCCESS);
  ck_assert_int_eq(dst.bits[0], 0);
  ck_assert_int_eq(dst.bits[1], 0);
  ck_assert_int_eq(dst.bits[2], 0);
}
END_TEST

START_TEST(test_from_float_to_decimal_null_pointer) {
  float src = 123.45f;

  int status = s21_from_float_to_decimal(src, NULL);

  ck_assert_int_eq(status, CALCULATION_ERROR);
}
END_TEST

START_TEST(test_from_float_to_decimal_nan) {
  float src = NAN;
  s21_decimal dst;

  int status = s21_from_float_to_decimal(src, &dst);

  ck_assert_int_eq(status, CALCULATION_ERROR);
}
END_TEST

START_TEST(test_from_float_to_decimal_inf) {
  float src = INFINITY;
  s21_decimal dst;

  int status = s21_from_float_to_decimal(src, &dst);

  ck_assert_int_eq(status, CALCULATION_ERROR);
}
END_TEST

START_TEST(test_from_float_to_decimal_integer) {
  float src = 123.0f;
  s21_decimal dst;

  int status = s21_from_float_to_decimal(src, &dst);

  ck_assert_int_eq(status, SUCCESS);
  ck_assert_int_eq(dst.bits[0], 123);
  ck_assert_int_eq((dst.bits[3] >> 16) & 0xFF, 0);  // scale = 0
}
END_TEST

Suite* s21_conversion_suite(void) {
  Suite* s = suite_create("conversion");
  TCase* tc = tcase_create("core");

  tcase_add_test(tc, test_int_to_decimal_positive);
  tcase_add_test(tc, test_int_to_decimal_negative);
  tcase_add_test(tc, test_int_to_decimal_zero);
  tcase_add_test(tc, test_int_max);

  tcase_add_test(tc, test_decimal_to_int_basic);
  tcase_add_test(tc, test_decimal_to_int_with_scale);
  tcase_add_test(tc, test_decimal_to_int_negative);
  tcase_add_test(tc, test_decimal_to_int_overflow);

  tcase_add_test(tc, test_from_float_to_decimal_positive);
  tcase_add_test(tc, test_from_float_to_decimal_negative);
  tcase_add_test(tc, test_from_float_to_decimal_zero);
  tcase_add_test(tc, test_from_float_to_decimal_null_pointer);
  tcase_add_test(tc, test_from_float_to_decimal_nan);
  tcase_add_test(tc, test_from_float_to_decimal_inf);
  tcase_add_test(tc, test_from_float_to_decimal_integer);

  suite_add_tcase(s, tc);
  return s;
}