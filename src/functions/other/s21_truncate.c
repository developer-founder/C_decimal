#include "../../s21_decimal.h"
#include "../helpers/helpers.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
    int code = SUCCESS;
    if (!result) {
        code = CALCULATION_ERROR;
    } else {
        *result = value;
        int scale = s21_get_scale(value);

        while (scale > 0) {
            s21_shift_right_10(result);
            scale -= 1;
        }

        s21_set_scale(result, 0);
    }

    return code;
}