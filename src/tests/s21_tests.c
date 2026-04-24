#include "s21_tests.h"

int main(void) {
  int failed = 0;
  SRunner* sr = srunner_create(NULL);

  srunner_add_suite(sr, s21_from_int_to_decimal_suite());
  srunner_add_suite(sr, s21_negate_suite());
  srunner_add_suite(sr, s21_truncate_suite());
  srunner_add_suite(sr, s21_floor_suite());
  srunner_add_suite(sr, s21_round_suite());
  srunner_add_suite(sr, s21_compare_suite());
  srunner_add_suite(sr, s21_conversion_suite());
  srunner_add_suite(sr, s21_sub_suite());
  srunner_add_suite(sr, s21_add_suite());
  srunner_add_suite(sr, s21_mul_suite());
  srunner_add_suite(sr, s21_div_suite());

  srunner_run_all(sr, CK_NORMAL);
  failed = srunner_ntests_failed(sr);

  srunner_free(sr);

  return failed ? EXIT_FAILURE : EXIT_SUCCESS;
}