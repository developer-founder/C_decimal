#include "../../s21_decimal.h"
#include "../helpers/helpers.h"

int s21_negate(s21_decimal value, s21_decimal* result) {
  int status = SUCCESS;
  if (!result) {
    status = CALCULATION_ERROR;
  } else {
    *result = value;
    s21_set_sign(result, !s21_get_sign(*result));
  }

  return status;
}