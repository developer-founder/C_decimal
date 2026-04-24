#include "s21_tests.h"

START_TEST(test_add_simple) {
  s21_decimal a = {{100, 0, 0, 0}};
  s21_decimal b = {{200, 0, 0, 0}};
  s21_decimal res;

  s21_add(a, b, &res);

  ck_assert_int_eq(res.bits[0], 300);
}
END_TEST

START_TEST(test_add_with_carry) {
  s21_decimal a = {{0xFFFFFFFF, 0, 0, 0}};
  s21_decimal b = {{1, 0, 0, 0}};
  s21_decimal res;

  s21_add(a, b, &res);

  ck_assert_int_eq(res.bits[1], 1);
  ck_assert_int_eq(res.bits[0], 0);
}
END_TEST

START_TEST(test_add_scale) {
  s21_decimal a = {{1234, 0, 0, 0}};
  s21_decimal b = {{123, 0, 0, 0}};

  a.bits[3] = (1 << 16);
  b.bits[3] = (1 << 16);

  s21_decimal res;
  s21_add(a, b, &res);

  ck_assert_int_eq(res.bits[0], 1357);
}
END_TEST

START_TEST(test_add_negative) {
  s21_decimal a = {{100, 0, 0, 0}};
  s21_decimal b = {{50, 0, 0, 0}};

  a.bits[3] |= (1u << 31);
  b.bits[3] |= (1u << 31);

  s21_decimal res;
  s21_add(a, b, &res);

  ck_assert_int_eq(res.bits[0], 150);
  ck_assert_int_eq((res.bits[3] >> 31) & 1, 1);
}
END_TEST

START_TEST(test_add_opposite_sign) {
  s21_decimal a = {{200, 0, 0, 0}};
  s21_decimal b = {{100, 0, 0, 0}};

  b.bits[3] |= (1u << 31);

  s21_decimal res;
  s21_add(a, b, &res);

  ck_assert_int_eq(res.bits[0], 100);
}
END_TEST

#include "s21_tests.h"

START_TEST(test_add_null_result_pointer) {
  s21_decimal a = {{100, 0, 0, 0}};
  s21_decimal b = {{200, 0, 0, 0}};

  int status = s21_add(a, b, NULL);
  ck_assert_int_eq(status, CALCULATION_ERROR);
}
END_TEST

START_TEST(test_add_with_carry_overflow) {
  s21_decimal a = {{0xFFFFFFFF, 0xFFFFFFFF, 0, 0}};
  s21_decimal b = {{1, 0, 0, 0}};
  s21_decimal res;

  int status = s21_add(a, b, &res);

  ck_assert_int_eq(status, SUCCESS);
  ck_assert_int_eq(res.bits[0], 0);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 1);
}
END_TEST

START_TEST(test_add_overflow_detection) {
  s21_decimal a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal b = {{1, 0, 0, 0}};
  s21_decimal res;

  int status = s21_add(a, b, &res);

  ck_assert_int_eq(status, 1);
}
END_TEST

START_TEST(test_add_large_numbers) {
  s21_decimal a = {{123456789, 987654321, 123456789, 0}};
  s21_decimal b = {{987654321, 123456789, 987654321, 0}};
  s21_decimal res;

  int status = s21_add(a, b, &res);

  ck_assert_int_eq(status, SUCCESS);
  ck_assert_int_eq(res.bits[0], 1111111110u);
  ck_assert_int_eq(res.bits[1], 1111111110u);
  ck_assert_int_eq(res.bits[2], 1111111110u);
}
END_TEST

START_TEST(test_add_scale1_less_than_scale2) {
  s21_decimal a = {{123, 0, 0, 0}};
  s21_decimal b = {{456, 0, 0, 0}};
  s21_decimal res;

  a.bits[3] = 1 << 16;
  b.bits[3] = 2 << 16;

  s21_add(a, b, &res);

  ck_assert_int_eq((res.bits[3] >> 16) & 0xFF, 2);
}
END_TEST

START_TEST(test_add_scale2_less_than_scale1) {
  s21_decimal a = {{123, 0, 0, 0}};
  s21_decimal b = {{456, 0, 0, 0}};
  s21_decimal res;

  a.bits[3] = 2 << 16;
  b.bits[3] = 1 << 16;

  s21_add(a, b, &res);

  ck_assert_int_eq((res.bits[3] >> 16) & 0xFF, 2);
}
END_TEST

START_TEST(test_add_opposite_sign_second_larger_abs) {
  s21_decimal a = {{50, 0, 0, 0}};   // +50
  s21_decimal b = {{100, 0, 0, 0}};  // -100

  b.bits[3] |= (1u << 31);

  s21_decimal res;
  s21_add(a, b, &res);

  ck_assert_int_eq(res.bits[0], 50);
  ck_assert_int_eq((res.bits[3] >> 31) & 1, 1);
}
END_TEST

START_TEST(test_add_overflow) {
  s21_decimal a = {{4294967295u, 4294967295u, 4294967295u, 0}};
  s21_decimal b = {{1, 0, 0, 0}};
  s21_decimal res;

  int status = s21_add(a, b, &res);

  ck_assert_int_eq(status, 1);
}
END_TEST

START_TEST(test_add_one_max_value) {
  s21_decimal val = {{4294967295u, 4294967295u, 4294967295u, 0}};

  int ret = s21_add_one(&val);

  ck_assert_int_eq(ret, CALCULATION_ERROR);
}
END_TEST

START_TEST(test_add_one_carry_between_bits) {
  s21_decimal val = {{4294967295u, 0, 0, 0}};

  int ret = s21_add_one(&val);

  ck_assert_int_eq(ret, SUCCESS);
  ck_assert_int_eq(val.bits[0], 0);
  ck_assert_int_eq(val.bits[1], 1);
}
END_TEST

START_TEST(test_add_one_carry_to_bit2) {
  s21_decimal val = {{4294967295u, 4294967295u, 0, 0}};

  int ret = s21_add_one(&val);

  ck_assert_int_eq(ret, SUCCESS);
  ck_assert_int_eq(val.bits[0], 0);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 1);
}
END_TEST

Suite* s21_add_suite(void) {
  Suite* s = suite_create("add");
  TCase* tc = tcase_create("core");

  tcase_add_test(tc, test_add_simple);
  tcase_add_test(tc, test_add_with_carry);
  tcase_add_test(tc, test_add_scale);
  tcase_add_test(tc, test_add_negative);
  tcase_add_test(tc, test_add_opposite_sign);
  tcase_add_test(tc, test_add_null_result_pointer);
  tcase_add_test(tc, test_add_with_carry_overflow);
  tcase_add_test(tc, test_add_overflow_detection);
  tcase_add_test(tc, test_add_large_numbers);
  tcase_add_test(tc, test_add_scale1_less_than_scale2);
  tcase_add_test(tc, test_add_scale2_less_than_scale1);
  tcase_add_test(tc, test_add_opposite_sign_second_larger_abs);
  tcase_add_test(tc, test_add_overflow);
  tcase_add_test(tc, test_add_one_max_value);
  tcase_add_test(tc, test_add_one_carry_between_bits);
  tcase_add_test(tc, test_add_one_carry_to_bit2);

  suite_add_tcase(s, tc);
  return s;
}