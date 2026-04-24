#include "s21_tests.h"

START_TEST(test_sub_simple) {
    s21_decimal a = {{300, 0, 0, 0}};
    s21_decimal b = {{100, 0, 0, 0}};
    s21_decimal res;

    s21_sub(a, b, &res);

    ck_assert_int_eq(res.bits[0], 200);
}
END_TEST

START_TEST(test_sub_to_zero) {
    s21_decimal a = {{100, 0, 0, 0}};
    s21_decimal b = {{100, 0, 0, 0}};
    s21_decimal res;

    s21_sub(a, b, &res);

    ck_assert_int_eq(res.bits[0], 0);
}
END_TEST

START_TEST(test_sub_negative_result) {
    s21_decimal a = {{100, 0, 0, 0}};
    s21_decimal b = {{200, 0, 0, 0}};
    s21_decimal res;

    s21_sub(a, b, &res);

    ck_assert_int_eq(res.bits[0], 100);
    ck_assert_int_eq((res.bits[3] >> 31) & 1, 1);
}
END_TEST

START_TEST(test_sub_negative_minus_negative) {
    s21_decimal a = {{200, 0, 0, 0}};
    s21_decimal b = {{100, 0, 0, 0}};

    a.bits[3] |= (1u << 31);
    b.bits[3] |= (1u << 31);

    s21_decimal res;
    s21_sub(a, b, &res);

    ck_assert_int_eq(res.bits[0], 100);
    ck_assert_int_eq((res.bits[3] >> 31) & 1, 1);
}
END_TEST

START_TEST(test_sub_scale) {
    s21_decimal a = {{1234, 0, 0, 0}}; // 123.4
    s21_decimal b = {{123, 0, 0, 0}};  // 12.3

    a.bits[3] = (1 << 16);
    b.bits[3] = (1 << 16);

    s21_decimal res;
    s21_sub(a, b, &res);

    ck_assert_int_eq(res.bits[0], 1111);
}
END_TEST

Suite *s21_sub_suite(void) {
    Suite *s = suite_create("sub");
    TCase *tc = tcase_create("core");

    tcase_add_test(tc, test_sub_simple);
    tcase_add_test(tc, test_sub_to_zero);

    tcase_add_test(tc, test_sub_negative_result);
    tcase_add_test(tc, test_sub_negative_minus_negative);

    tcase_add_test(tc, test_sub_scale);

    suite_add_tcase(s, tc);
    return s;
}