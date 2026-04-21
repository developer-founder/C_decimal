#include "../../s21_decimal.h"

void s21_set_sign(s21_decimal *value, int sign) {
    value->bits[3] &= ~(1u << 31);
    value->bits[3] |= (sign << 31);
}