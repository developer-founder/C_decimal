#include "../../s21_decimal.h"
#include "../helpers/helpers.h"

int s21_round(s21_decimal value, s21_decimal* result) {
  int status = CALCULATION_ERROR;

  if (result) {
    status = SUCCESS;

    int scale = s21_get_scale(value);

    *result = value;

    int last_digit = 0;

    if (scale > 0) {
      s21_decimal tmp = value;

      last_digit = s21_shift_right_10(&tmp);

      s21_truncate(value, result);
    }

    if (last_digit >= 5) {
      if (s21_add_one(result)) {
        status = CALCULATION_ERROR;
      }
    }

    s21_set_scale(result, 0);
  }

  return status;
}