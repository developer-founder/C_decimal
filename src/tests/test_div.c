#include "s21_tests.h"

START_TEST(test_div_simple) {
    s21_decimal a = {{200, 0, 0, 0}};
    s21_decimal b = {{10, 0, 0, 0}};
    s21_decimal res;

    s21_div(a, b, &res);

    ck_assert_int_eq(res.bits[0], 20);
}
END_TEST

START_TEST(test_div_self) {
    s21_decimal a = {{123, 0, 0, 0}};
    s21_decimal res;

    s21_div(a, a, &res);

    ck_assert_int_eq(res.bits[0], 1);
}
END_TEST

START_TEST(test_div_negative) {
    s21_decimal a = {{200, 0, 0, 0}};
    s21_decimal b = {{10, 0, 0, 0}};

    a.bits[3] |= (1u << 31);

    s21_decimal res;
    s21_div(a, b, &res);

    ck_assert_int_eq(res.bits[0], 20);
    ck_assert_int_eq((res.bits[3] >> 31) & 1, 1);
}
END_TEST

START_TEST(test_div_both_negative) {
    s21_decimal a = {{200, 0, 0, 0}};
    s21_decimal b = {{10, 0, 0, 0}};

    a.bits[3] |= (1u << 31);
    b.bits[3] |= (1u << 31);

    s21_decimal res;
    s21_div(a, b, &res);

    ck_assert_int_eq(res.bits[0], 20);
    ck_assert_int_eq((res.bits[3] >> 31) & 1, 0);
}
END_TEST

START_TEST(test_div_zero_divisor) {
    s21_decimal a = {{100, 0, 0, 0}};
    s21_decimal b = {{0, 0, 0, 0}};
    s21_decimal res;

    int ret = s21_div(a, b, &res);

    ck_assert_int_eq(ret, 1);
}
END_TEST

START_TEST(test_div_no_fraction) {
    s21_decimal a = {{100, 0, 0, 0}};
    s21_decimal b = {{25, 0, 0, 0}};
    s21_decimal res;

    s21_div(a, b, &res);

    ck_assert_int_eq(res.bits[0], 4);
}
END_TEST

Suite *s21_div_suite(void) {
    Suite *s = suite_create("div");
    TCase *tc = tcase_create("core");

    tcase_add_test(tc, test_div_simple);
    tcase_add_test(tc, test_div_self);
    tcase_add_test(tc, test_div_negative);
    tcase_add_test(tc, test_div_both_negative);
    tcase_add_test(tc, test_div_zero_divisor);
    tcase_add_test(tc, test_div_no_fraction);

    suite_add_tcase(s, tc);
    return s;
}