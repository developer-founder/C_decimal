#include "s21_tests.h"

START_TEST(test_truncate_simple) {
    s21_decimal val = {{12345, 0, 0, 0}};
    val.bits[3] |= (2 << 16);

    s21_decimal res;
    int ret = s21_truncate(val, &res);

    ck_assert_int_eq(ret, 0);
    ck_assert_int_eq(res.bits[0], 123);
    ck_assert_int_eq((res.bits[3] >> 16) & 0xFF, 0);
}
END_TEST

START_TEST(test_truncate_no_scale) {
    s21_decimal val = {{12345, 0, 0, 0}};

    s21_decimal res;
    int ret = s21_truncate(val, &res);

    ck_assert_int_eq(ret, 0);
    ck_assert_int_eq(res.bits[0], 12345);
}
END_TEST

START_TEST(test_truncate_zero) {
    s21_decimal val = {{0, 0, 0, 0}};
    val.bits[3] |= (5 << 16);

    s21_decimal res;
    int ret = s21_truncate(val, &res);

    ck_assert_int_eq(ret, 0);
    ck_assert_int_eq(res.bits[0], 0);
    ck_assert_int_eq((res.bits[3] >> 16) & 0xFF, 0);
}
END_TEST

START_TEST(test_truncate_large_scale) {
    s21_decimal val = {{1, 0, 0, 0}};
    val.bits[3] |= (5 << 16);

    s21_decimal res;
    int ret = s21_truncate(val, &res);

    ck_assert_int_eq(ret, 0);
    ck_assert_int_eq(res.bits[0], 0);
}
END_TEST

START_TEST(test_truncate_negative) {
    s21_decimal val = {{12345, 0, 0, 0}};
    val.bits[3] |= (2 << 16);
    val.bits[3] |= (1u << 31);

    s21_decimal res;
    int ret = s21_truncate(val, &res);

    ck_assert_int_eq(ret, 0);
    ck_assert_int_eq(res.bits[0], 123);
    ck_assert_int_eq((res.bits[3] >> 31) & 1, 1);
}
END_TEST

START_TEST(test_truncate_preserve_sign_zero) {
    s21_decimal val = {{0, 0, 0, 0}};
    val.bits[3] |= (3 << 16);
    val.bits[3] |= (1u << 31);

    s21_decimal res;
    int ret = s21_truncate(val, &res);

    ck_assert_int_eq(ret, 0);
    ck_assert_int_eq(res.bits[0], 0);
}
END_TEST

Suite *s21_truncate_suite(void) {
    Suite *s = suite_create("s21_truncate");
    TCase *tc = tcase_create("core");

    tcase_add_test(tc, test_truncate_simple);
    tcase_add_test(tc, test_truncate_no_scale);
    tcase_add_test(tc, test_truncate_zero);
    tcase_add_test(tc, test_truncate_large_scale);
    tcase_add_test(tc, test_truncate_negative);
    tcase_add_test(tc, test_truncate_preserve_sign_zero);

    suite_add_tcase(s, tc);
    return s;
}