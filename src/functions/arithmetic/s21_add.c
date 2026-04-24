#include "../../s21_decimal.h"
#include "../helpers/helpers.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int status = CALCULATION_ERROR;

    if (result) {
        *result = (s21_decimal){{0, 0, 0, 0}};
        status = SUCCESS;

        int sign1 = s21_get_sign(value_1);
        int sign2 = s21_get_sign(value_2);

        int scale1 = s21_get_scale(value_1);
        int scale2 = s21_get_scale(value_2);

        while (scale1 < scale2) {
            s21_mul_10(&value_1);
            scale1++;
        }

        while (scale2 < scale1) {
            s21_mul_10(&value_2);
            scale2++;
        }

        s21_set_scale(&value_1, scale1);
        s21_set_scale(&value_2, scale2);

        if (sign1 != sign2) {
            if (s21_abs_compare(value_1, value_2) >= 0) {
                s21_sub_abs(value_1, value_2, result);
                s21_set_sign(result, sign1);
            } else {
                s21_sub_abs(value_2, value_1, result);
                s21_set_sign(result, sign2);
            }

        } else {
            unsigned long long carry = 0;

            for (int i = 0; i < 3; i++) {
                unsigned long long sum =
                    (unsigned long long)value_1.bits[i] +
                    value_2.bits[i] + carry;

                result->bits[i] = (unsigned int)sum;
                carry = sum >> 32;
            }

            if (carry) {
                status = 1;
            }

            s21_set_scale(result, scale1);
            s21_set_sign(result, sign1);
        }
    }

    return status;
}