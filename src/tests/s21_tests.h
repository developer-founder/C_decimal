#ifndef S21_TESTS_H
#define S21_TESTS_H

#include <check.h>
#include <stdlib.h>

#include "../s21_decimal.h"

// suites
Suite *s21_from_int_to_decimal_suite(void);
Suite *s21_negate_suite(void);
Suite *s21_truncate_suite(void);
Suite *s21_floor_suite(void);

#endif