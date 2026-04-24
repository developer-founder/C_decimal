#include "../../s21_decimal.h"
#include "../helpers/helpers.h"

int s21_floor(s21_decimal value, s21_decimal* result) {
  int status = CALCULATION_ERROR;

  if (result) {
    status = SUCCESS;

    int scale = s21_get_scale(value);
    int sign = s21_get_sign(value);

    s21_decimal tmp;
    s21_truncate(value, &tmp);

    if (sign && scale > 0) {
      if (value.bits[0] == 0xFFFFFFFF && value.bits[1] == 0xFFFFFFFF &&
          value.bits[2] == 0xFFFFFFFF) {
        status = CALCULATION_ERROR;
      } else {
        s21_decimal copy = tmp;

        if (s21_add_one(&copy)) {
          status = CALCULATION_ERROR;
        } else {
          tmp = copy;
        }
      }
    }

    *result = tmp;
  }

  return status;
}