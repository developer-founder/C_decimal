#include "../../s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
    int status = CALCULATION_ERROR;

    if (dst) {
        int sign = s21_get_sign(src);

        s21_decimal tmp = src;
        s21_truncate(src, &tmp);

        if (tmp.bits[1] == 0 && tmp.bits[2] == 0) {
            if (!sign) {
                if (tmp.bits[0] <= INT_MAX) {
                    *dst = (int)tmp.bits[0];
                    status = SUCCESS;
                }
            } else {
                if (tmp.bits[0] <= (unsigned int)INT_MAX + 1) {
                    if (tmp.bits[0] == (unsigned int)INT_MAX + 1)
                        *dst = INT_MIN;
                    else
                        *dst = -(int)tmp.bits[0];

                    status = SUCCESS;
                }
            }
        }
    }

    return status;
}