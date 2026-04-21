#include "../../s21_decimal.h"

void s21_set_scale(s21_decimal *value, int scale) {
    value->bits[3] &= ~(0xFF << 16);
    value->bits[3] |= (scale << 16);
}