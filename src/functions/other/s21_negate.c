#include "../../s21_decimal.h"
#include "../helpers/helpers.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
    int code = SUCCESS;
    if (!result) {
        code = CALCULATION_ERROR;
    } else {
        *result = value;
        s21_set_sign(result, !s21_get_sign(*result));
    }

    return code;
}