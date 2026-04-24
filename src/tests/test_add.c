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
    s21_decimal a = {{1234, 0, 0, 0}}; // 123.4
    s21_decimal b = {{123, 0, 0, 0}};   // 12.3

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

Suite *s21_add_suite(void) {
    Suite *s = suite_create("add");
    TCase *tc = tcase_create("core");

    tcase_add_test(tc, test_add_simple);
    tcase_add_test(tc, test_add_with_carry);
    tcase_add_test(tc, test_add_scale);

    tcase_add_test(tc, test_add_negative);
    tcase_add_test(tc, test_add_opposite_sign);

    suite_add_tcase(s, tc);
    return s;
}