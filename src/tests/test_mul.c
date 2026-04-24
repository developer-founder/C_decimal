#include "s21_tests.h"

START_TEST(test_mul_simple) {
  s21_decimal a = {{10, 0, 0, 0}};
  s21_decimal b = {{20, 0, 0, 0}};
  s21_decimal res;

  s21_mul(a, b, &res);

  ck_assert_int_eq(res.bits[0], 200);
}
END_TEST

START_TEST(test_mul_zero) {
  s21_decimal a = {{0, 0, 0, 0}};
  s21_decimal b = {{12345, 0, 0, 0}};
  s21_decimal res;

  s21_mul(a, b, &res);

  ck_assert_int_eq(res.bits[0], 0);
}
END_TEST

START_TEST(test_mul_negative) {
  s21_decimal a = {{10, 0, 0, 0}};
  s21_decimal b = {{20, 0, 0, 0}};

  a.bits[3] |= (1u << 31);

  s21_decimal res;
  s21_mul(a, b, &res);

  ck_assert_int_eq(res.bits[0], 200);
  ck_assert_int_eq((res.bits[3] >> 31) & 1, 1);
}
END_TEST

START_TEST(test_mul_both_negative) {
  s21_decimal a = {{10, 0, 0, 0}};
  s21_decimal b = {{20, 0, 0, 0}};

  a.bits[3] |= (1u << 31);
  b.bits[3] |= (1u << 31);

  s21_decimal res;
  s21_mul(a, b, &res);

  ck_assert_int_eq(res.bits[0], 200);
  ck_assert_int_eq((res.bits[3] >> 31) & 1, 0);
}
END_TEST

START_TEST(test_mul_10_null_pointer) {
  int ret = s21_mul_10(NULL);
  ck_assert_int_eq(ret, 1);
}
END_TEST

START_TEST(test_mul_10_overflow) {
  s21_decimal val = {{4294967295u, 4294967295u, 4294967295u, 0}};

  int ret = s21_mul_10(&val);

  ck_assert_int_eq(ret, 1);
}
END_TEST

Suite* s21_mul_suite(void) {
  Suite* s = suite_create("mul");
  TCase* tc = tcase_create("core");

  tcase_add_test(tc, test_mul_simple);
  tcase_add_test(tc, test_mul_zero);
  tcase_add_test(tc, test_mul_negative);
  tcase_add_test(tc, test_mul_both_negative);
  tcase_add_test(tc, test_mul_10_null_pointer);
  tcase_add_test(tc, test_mul_10_overflow);

  suite_add_tcase(s, tc);
  return s;
}