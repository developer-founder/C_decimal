#include "../../s21_decimal.h"
#include "../helpers/helpers.h"

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int status = CALCULATION_ERROR;

    if (result) {
        *result = (s21_decimal){{0, 0, 0, 0}};

        int is_zero =
            (value_2.bits[0] == 0 &&
             value_2.bits[1] == 0 &&
             value_2.bits[2] == 0);

        if (is_zero) {
            status = 1;
        } else {
            status = SUCCESS;

            int sign = s21_get_sign(value_1) ^ s21_get_sign(value_2);

            int scale = s21_get_scale(value_1) - s21_get_scale(value_2);

            s21_set_sign(&value_1, 0);
            s21_set_sign(&value_2, 0);

            s21_decimal current = {{0, 0, 0, 0}};
            s21_decimal res = {{0, 0, 0, 0}};

            for (int i = 95; i >= 0; i--) {
                unsigned long long bit =
                    (value_1.bits[i / 32] >> (i % 32)) & 1;

                for (int k = 2; k >= 0; k--) {
                    unsigned long long carry = 0;

                    if (k > 0 && (current.bits[k - 1] & 0x80000000)) {
                        carry = 1;
                    }

                    current.bits[k] = (current.bits[k] << 1) | carry;
                }

                current.bits[0] |= bit;

                if (s21_abs_compare(current, value_2) >= 0) {
                    s21_sub_abs(current, value_2, &current);
                    res.bits[i / 32] |= (1u << (i % 32));
                }
            }

            *result = res;

            s21_set_scale(result, scale);
            s21_set_sign(result, sign);
        }
    }

    return status;
}