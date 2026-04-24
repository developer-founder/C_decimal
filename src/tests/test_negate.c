#include "s21_tests.h"

START_TEST(test_negate_positive) {
    s21_decimal val = {{123, 0, 0, 0}};
    s21_decimal res;

    int ret = s21_negate(val, &res);

    ck_assert_int_eq(ret, 0);
    ck_assert_int_eq(res.bits[0], 123);
    ck_assert_int_eq((res.bits[3] >> 31) & 1, 1);
}
END_TEST

START_TEST(test_negate_negative) {
    s21_decimal val = {{123, 0, 0, 0}};
    val.bits[3] |= (1u << 31);

    s21_decimal res;
    int ret = s21_negate(val, &res);

    ck_assert_int_eq(ret, 0);
    ck_assert_int_eq((res.bits[3] >> 31) & 1, 0);
}
END_TEST

START_TEST(test_negate_zero) {
    s21_decimal val = {{0, 0, 0, 0}};
    s21_decimal res;

    int ret = s21_negate(val, &res);

    ck_assert_int_eq(ret, 0);
    ck_assert_int_eq(res.bits[0], 0);
    ck_assert_int_eq(res.bits[1], 0);
    ck_assert_int_eq(res.bits[2], 0);
}
END_TEST

START_TEST(test_negate_negative_zero) {
    s21_decimal val = {{0, 0, 0, 0}};
    val.bits[3] |= (1u << 31);

    s21_decimal res;
    int ret = s21_negate(val, &res);

    ck_assert_int_eq(ret, 0);
    ck_assert_int_eq((res.bits[3] >> 31) & 1, 0);
}
END_TEST

START_TEST(test_negate_preserve_scale) {
    s21_decimal val = {{123, 0, 0, 0}};
    val.bits[3] |= (5 << 16); // scale = 5

    s21_decimal res;
    s21_negate(val, &res);

    ck_assert_int_eq((res.bits[3] >> 16) & 0xFF, 5);
}
END_TEST

Suite *s21_negate_suite(void) {
    Suite *s = suite_create("s21_negate");
    TCase *tc = tcase_create("core");

    tcase_add_test(tc, test_negate_positive);
    tcase_add_test(tc, test_negate_negative);
    tcase_add_test(tc, test_negate_zero);
    tcase_add_test(tc, test_negate_negative_zero);
    tcase_add_test(tc, test_negate_preserve_scale);

    suite_add_tcase(s, tc);
    return s;
}