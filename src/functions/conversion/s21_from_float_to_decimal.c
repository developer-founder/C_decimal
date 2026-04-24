#include "../../s21_decimal.h"

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
    int status = SUCCESS;
    int sign = 0;

    if (!dst) {
        status = CALCULATION_ERROR;
    } else {
        if (src < 0) {
            sign = 1;
        } else {

        }
    }

    return status;
}