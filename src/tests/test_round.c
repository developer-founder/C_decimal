#include "s21_tests.h"

START_TEST(test_round_positive_no_fraction) {
  s21_decimal val = {{123, 0, 0, 0}};
  s21_decimal res;

  int ret = s21_round(val, &res);

  ck_assert_int_eq(ret, 0);
  ck_assert_int_eq(res.bits[0], 123);
  ck_assert_int_eq((res.bits[3] >> 31) & 1, 0);
}
END_TEST

START_TEST(test_round_positive_less_5) {
  s21_decimal val = {{1234, 0, 0, 0}};
  val.bits[3] |= (1 << 16);

  s21_decimal res;
  s21_round(val, &res);

  ck_assert_int_eq(res.bits[0], 123);
  ck_assert_int_eq((res.bits[3] >> 31) & 1, 0);
}
END_TEST

START_TEST(test_round_positive_greater_5) {
  s21_decimal val = {{1236, 0, 0, 0}};
  val.bits[3] |= (1 << 16);

  s21_decimal res;
  s21_round(val, &res);

  ck_assert_int_eq(res.bits[0], 124);
  ck_assert_int_eq((res.bits[3] >> 31) & 1, 0);
}
END_TEST

START_TEST(test_round_positive_equal_5) {
  s21_decimal val = {{1235, 0, 0, 0}};
  val.bits[3] |= (1 << 16);

  s21_decimal res;
  s21_round(val, &res);

  ck_assert_int_eq(res.bits[0], 124);
  ck_assert_int_eq((res.bits[3] >> 31) & 1, 0);
}
END_TEST

START_TEST(test_round_positive_equal_5_large) {
  s21_decimal val = {{1245, 0, 0, 0}};
  val.bits[3] |= (1 << 16);

  s21_decimal res;
  s21_round(val, &res);

  ck_assert_int_eq(res.bits[0], 125);
  ck_assert_int_eq((res.bits[3] >> 31) & 1, 0);
}
END_TEST

START_TEST(test_round_negative_less_5) {
  s21_decimal val = {{1234, 0, 0, 0}};
  val.bits[3] |= (1 << 16);
  val.bits[3] |= (1u << 31);

  s21_decimal res;
  s21_round(val, &res);

  ck_assert_int_eq(res.bits[0], 123);
  ck_assert_int_eq((res.bits[3] >> 31) & 1, 1);
}
END_TEST

START_TEST(test_round_negative_greater_5) {
  s21_decimal val = {{1236, 0, 0, 0}};
  val.bits[3] |= (1 << 16);
  val.bits[3] |= (1u << 31);

  s21_decimal res;
  s21_round(val, &res);

  ck_assert_int_eq(res.bits[0], 124);
  ck_assert_int_eq((res.bits[3] >> 31) & 1, 1);
}
END_TEST

START_TEST(test_round_negative_equal_5) {
  s21_decimal val = {{1235, 0, 0, 0}};
  val.bits[3] |= (1 << 16);
  val.bits[3] |= (1u << 31);

  s21_decimal res;
  s21_round(val, &res);

  ck_assert_int_eq(res.bits[0], 124);
  ck_assert_int_eq((res.bits[3] >> 31) & 1, 1);
}
END_TEST

START_TEST(test_round_negative_equal_5_large) {
  s21_decimal val = {{1245, 0, 0, 0}};
  val.bits[3] |= (1 << 16);
  val.bits[3] |= (1u << 31);

  s21_decimal res;
  s21_round(val, &res);

  ck_assert_int_eq(res.bits[0], 125);
  ck_assert_int_eq((res.bits[3] >> 31) & 1, 1);
}
END_TEST

START_TEST(test_round_zero) {
  s21_decimal val = {{0, 0, 0, 0}};
  val.bits[3] |= (5 << 16);

  s21_decimal res;
  s21_round(val, &res);

  ck_assert_int_eq(res.bits[0], 0);
  ck_assert_int_eq((res.bits[3] >> 31) & 1, 0);
}
END_TEST

START_TEST(test_round_big_number_with_fraction) {
  s21_decimal val = {{0xFFFFFFFF, 0x00000001, 0, 1}};

  s21_decimal res;
  int ret = s21_round(val, &res);

  ck_assert_int_eq(ret, 0);

  ck_assert_int_eq((res.bits[3] >> 16) & 0xFF, 0);

  ck_assert_int_eq((res.bits[3] >> 31) & 1, 0);

  ck_assert_int_eq(res.bits[0] != 0 || res.bits[1] != 0 || res.bits[2] != 0, 1);
}
END_TEST

Suite* s21_round_suite(void) {
  Suite* s = suite_create("s21_round");
  TCase* tc = tcase_create("core");

  tcase_add_test(tc, test_round_positive_no_fraction);
  tcase_add_test(tc, test_round_positive_less_5);
  tcase_add_test(tc, test_round_positive_greater_5);
  tcase_add_test(tc, test_round_positive_equal_5);
  tcase_add_test(tc, test_round_positive_equal_5_large);
  tcase_add_test(tc, test_round_negative_less_5);
  tcase_add_test(tc, test_round_negative_greater_5);
  tcase_add_test(tc, test_round_negative_equal_5);
  tcase_add_test(tc, test_round_negative_equal_5_large);
  tcase_add_test(tc, test_round_big_number_with_fraction);
  tcase_add_test(tc, test_round_zero);

  suite_add_tcase(s, tc);
  return s;
}