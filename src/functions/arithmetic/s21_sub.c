#include "../../s21_decimal.h"
#include "../helpers/helpers.h"

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal* result) {
  int status = CALCULATION_ERROR;

  if (result) {
    status = SUCCESS;

    int sign1 = s21_get_sign(value_1);
    int sign2 = s21_get_sign(value_2);

    if (sign1 != sign2) {
      s21_negate_internal(&value_2);
      status = s21_add(value_1, value_2, result);
    } else {
      int cmp = s21_abs_compare(value_1, value_2);

      if (cmp == 0) {
        *result = (s21_decimal){{0, 0, 0, 0}};
      } else if (cmp > 0) {
        s21_sub_abs(value_1, value_2, result);
        s21_set_sign(result, sign1);
      } else {
        s21_sub_abs(value_2, value_1, result);
        s21_set_sign(result, !sign1);
      }
    }
  }

  return status;
}