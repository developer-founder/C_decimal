#include "../../s21_decimal.h"
#include "../helpers/helpers.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
    int code = CALCULATION_ERROR;
    if (result) {
        code = SUCCESS;

        int scale = s21_get_scale(value);
        int sign = s21_get_sign(value);

        *result = value;

        s21_truncate(value, result);

        if (sign && scale > 0) {
            s21_sub_one(result);
        }
    }

    return code;
}