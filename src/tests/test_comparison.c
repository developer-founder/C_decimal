#include "s21_tests.h"

START_TEST(test_equal_simple) {
    s21_decimal a = {{123, 0, 0, 0}};
    s21_decimal b = {{123, 0, 0, 0}};

    ck_assert_int_eq(s21_is_equal(a, b), 1);
}
END_TEST

START_TEST(test_equal_diff) {
    s21_decimal a = {{123, 0, 0, 0}};
    s21_decimal b = {{124, 0, 0, 0}};

    ck_assert_int_eq(s21_is_equal(a, b), 0);
}
END_TEST

START_TEST(test_equal_with_sign) {
    s21_decimal a = {{123, 0, 0, 0}};
    s21_decimal b = {{123, 0, 0, 0}};

    a.bits[3] |= (1u << 31);
    b.bits[3] |= (1u << 31);

    ck_assert_int_eq(s21_is_equal(a, b), 1);
}
END_TEST

START_TEST(test_less_simple) {
    s21_decimal a = {{100, 0, 0, 0}};
    s21_decimal b = {{200, 0, 0, 0}};

    ck_assert_int_eq(s21_is_less(a, b), 1);
}
END_TEST

START_TEST(test_greater_simple) {
    s21_decimal a = {{300, 0, 0, 0}};
    s21_decimal b = {{200, 0, 0, 0}};

    ck_assert_int_eq(s21_is_greater(a, b), 1);
}
END_TEST

START_TEST(test_less_equal_scale) {
    s21_decimal a = {{1230, 0, 0, 0}};
    s21_decimal b = {{123, 0, 0, 0}};

    a.bits[3] = (1 << 16);

    ck_assert_int_eq(s21_is_equal(a, b), 1);
}
END_TEST

START_TEST(test_negative_less) {
    s21_decimal a = {{100, 0, 0, 0}};
    s21_decimal b = {{100, 0, 0, 0}};

    a.bits[3] |= (1u << 31);

    ck_assert_int_eq(s21_is_less(a, b), 1);
}
END_TEST

START_TEST(test_negative_greater_logic) {
    s21_decimal a = {{50, 0, 0, 0}};
    s21_decimal b = {{100, 0, 0, 0}};

    a.bits[3] |= (1u << 31);
    b.bits[3] |= (1u << 31);

    ck_assert_int_eq(s21_is_greater(a, b), 1);
}
END_TEST

START_TEST(test_is_greater_or_equal_true) {
    s21_decimal a = {{100, 0, 0, 0}};
    s21_decimal b = {{50, 0, 0, 0}};
    
    int result = s21_is_greater_or_equal(a, b);
    
    ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_is_greater_or_equal_equal) {
    s21_decimal a = {{100, 0, 0, 0}};
    s21_decimal b = {{100, 0, 0, 0}};
    
    int result = s21_is_greater_or_equal(a, b);
    
    ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_is_greater_or_equal_false) {
    s21_decimal a = {{50, 0, 0, 0}};
    s21_decimal b = {{100, 0, 0, 0}};
    
    int result = s21_is_greater_or_equal(a, b);
    
    ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_is_not_equal_true) {
    s21_decimal a = {{100, 0, 0, 0}};
    s21_decimal b = {{50, 0, 0, 0}};
    
    int result = s21_is_not_equal(a, b);
    
    ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_is_not_equal_false) {
    s21_decimal a = {{100, 0, 0, 0}};
    s21_decimal b = {{100, 0, 0, 0}};
    
    int result = s21_is_not_equal(a, b);
    
    ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_is_not_equal_different_scales) {
    s21_decimal a = {{100, 0, 0, 0}};  // 1.00
    s21_decimal b = {{10, 0, 0, 0}};   // 1.0
    
    a.bits[3] = 2 << 16;
    b.bits[3] = 1 << 16;
    
    int result = s21_is_not_equal(a, b);
    
    ck_assert_int_eq(result, 0);  // 1.00 == 1.0
}
END_TEST

START_TEST(test_is_less_or_equal_true) {
    s21_decimal a = {{50, 0, 0, 0}};
    s21_decimal b = {{100, 0, 0, 0}};
    
    int result = s21_is_less_or_equal(a, b);
    
    ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_is_less_or_equal_equal) {
    s21_decimal a = {{100, 0, 0, 0}};
    s21_decimal b = {{100, 0, 0, 0}};
    
    int result = s21_is_less_or_equal(a, b);
    
    ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_is_less_or_equal_false) {
    s21_decimal a = {{100, 0, 0, 0}};
    s21_decimal b = {{50, 0, 0, 0}};
    
    int result = s21_is_less_or_equal(a, b);
    
    ck_assert_int_eq(result, 0);
}
END_TEST

Suite *s21_compare_suite(void) {
    Suite *s = suite_create("compare");
    TCase *tc = tcase_create("core");

    tcase_add_test(tc, test_equal_simple);
    tcase_add_test(tc, test_equal_diff);
    tcase_add_test(tc, test_equal_with_sign);

    tcase_add_test(tc, test_less_simple);
    tcase_add_test(tc, test_greater_simple);
    tcase_add_test(tc, test_less_equal_scale);

    tcase_add_test(tc, test_negative_less);
    tcase_add_test(tc, test_negative_greater_logic);

    tcase_add_test(tc, test_is_greater_or_equal_true);
    tcase_add_test(tc, test_is_greater_or_equal_equal);
    tcase_add_test(tc, test_is_greater_or_equal_false);

    tcase_add_test(tc, test_is_not_equal_true);
    tcase_add_test(tc, test_is_not_equal_false);
    tcase_add_test(tc, test_is_not_equal_different_scales);

    tcase_add_test(tc, test_is_less_or_equal_true);
    tcase_add_test(tc, test_is_less_or_equal_equal);
    tcase_add_test(tc, test_is_less_or_equal_false);

    suite_add_tcase(s, tc);
    return s;
}