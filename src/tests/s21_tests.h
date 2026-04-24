#ifndef S21_TESTS_H
#define S21_TESTS_H

#include <check.h>
#include <stdlib.h>

#include "../s21_decimal.h"

Suite *s21_from_int_to_decimal_suite(void);
Suite *s21_negate_suite(void);
Suite *s21_truncate_suite(void);
Suite *s21_floor_suite(void);
Suite *s21_round_suite(void);
Suite *s21_compare_suite(void);
Suite *s21_conversion_suite(void);
Suite *s21_sub_suite(void);
Suite *s21_add_suite(void);
Suite *s21_mul_suite(void);
Suite *s21_div_suite(void);

#endif