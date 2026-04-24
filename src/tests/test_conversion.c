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

Suite *s21_conversion_suite(void) {
    Suite *s = suite_create("conversion");
    TCase *tc = tcase_create("core");

    tcase_add_test(tc, test_int_to_decimal_positive);
    tcase_add_test(tc, test_int_to_decimal_negative);
    tcase_add_test(tc, test_int_to_decimal_zero);
    tcase_add_test(tc, test_int_max);

    tcase_add_test(tc, test_decimal_to_int_basic);
    tcase_add_test(tc, test_decimal_to_int_with_scale);
    tcase_add_test(tc, test_decimal_to_int_negative);
    tcase_add_test(tc, test_decimal_to_int_overflow);

    suite_add_tcase(s, tc);
    return s;
}