#include "s21_tests.h"

START_TEST(test_floor_positive_no_fraction) {
    s21_decimal val = {{123, 0, 0, 0}};
    val.bits[3] |= (0 << 16);

    s21_decimal res;

    int ret = s21_floor(val, &res);

    ck_assert_int_eq(ret, 0);
    ck_assert_int_eq(res.bits[0], 123);
}
END_TEST

START_TEST(test_floor_positive_with_fraction) {
    s21_decimal val = {{12345, 0, 0, 0}};
    val.bits[3] |= (2 << 16);

    s21_decimal res;

    int ret = s21_floor(val, &res);

    ck_assert_int_eq(ret, 0);
    ck_assert_int_eq(res.bits[0], 123);
}
END_TEST

START_TEST(test_floor_negative_with_fraction) {
    s21_decimal val = {{12345, 0, 0, 0}};
    val.bits[3] |= (2 << 16);
    val.bits[3] |= (1u << 31);

    s21_decimal res;

    int ret = s21_floor(val, &res);

    ck_assert_int_eq(ret, 0);
    ck_assert_int_eq(res.bits[0], 124);
}
END_TEST

START_TEST(test_floor_negative_no_fraction) {
    s21_decimal val = {{123, 0, 0, 0}};
    val.bits[3] |= (1u << 31);

    s21_decimal res;

    int ret = s21_floor(val, &res);

    ck_assert_int_eq(ret, 0);
    ck_assert_int_eq(res.bits[0], 123);
}
END_TEST

START_TEST(test_floor_zero) {
    s21_decimal val = {{0, 0, 0, 0}};
    val.bits[3] |= (5 << 16);

    s21_decimal res;

    int ret = s21_floor(val, &res);

    ck_assert_int_eq(ret, 0);
    ck_assert_int_eq(res.bits[0], 0);
}
END_TEST

START_TEST(test_floor_negative_with_fraction_overflow) {
    s21_decimal val = {{4294967295u, 4294967295u, 4294967295u, 0}};
    val.bits[3] |= (1 << 16);
    val.bits[3] |= (1u << 31);
    
    s21_decimal res;
    
    int ret = s21_floor(val, &res);
    
    ck_assert_int_eq(ret, CALCULATION_ERROR);
}
END_TEST

Suite *s21_floor_suite(void) {
    Suite *s = suite_create("s21_floor");
    TCase *tc = tcase_create("core");

    tcase_add_test(tc, test_floor_positive_no_fraction);
    tcase_add_test(tc, test_floor_positive_with_fraction);
    tcase_add_test(tc, test_floor_negative_with_fraction);
    tcase_add_test(tc, test_floor_negative_no_fraction);
    tcase_add_test(tc, test_floor_zero);
    tcase_add_test(tc, test_floor_negative_with_fraction_overflow);

    suite_add_tcase(s, tc);
    return s;
}