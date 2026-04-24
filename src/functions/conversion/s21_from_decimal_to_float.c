#include "../../s21_decimal.h"
#include "../helpers/helpers.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
    int status = CALCULATION_ERROR;

    if (dst) {
        status = SUCCESS;

        double result = 0.0;

        result += src.bits[0];
        result += (double)src.bits[1] * 4294967296.0;
        result += (double)src.bits[2] * 18446744073709551616.0;

        int scale = s21_get_scale(src);
        while (scale > 0) {
            result /= 10.0;
            scale--;
        }

        if (s21_get_sign(src)) {
            result = -result;
        }

        *dst = (float)result;
    }

    return status;
}