#include "../../s21_decimal.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
    *result = value;
    int sign = s21_get_sign(value);
    s21_set_sign(result, !sign);
    return 0;
}