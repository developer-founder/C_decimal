#include "../../s21_decimal.h"

void s21_zero(s21_decimal *value) {
    if (value) {
        value->bits[0] = 0;
        value->bits[1] = 0;
        value->bits[2] = 0;
        value->bits[3] = 0;
    } 
} 