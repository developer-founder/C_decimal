#include "../../s21_decimal.h"
#include "../helpers/helpers.h"

int s21_from_int_to_decimal(int src, s21_decimal* dst) {
  int status = CALCULATION_ERROR;
  int sign = 0;

  if (dst) {
    status = SUCCESS;
    s21_zero(dst);

    if (src < 0) {
      sign = 1;
      dst->bits[0] = (unsigned int)(-src);
    } else {
      dst->bits[0] = (unsigned int)(src);
    }

    if (sign) {
      dst->bits[3] |= (1u << 31);
    }
  }

  return status;
}