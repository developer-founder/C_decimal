#include "../../s21_decimal.h"
#include <math.h>
#include <float.h>

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
    int status = CALCULATION_ERROR;

    if (dst && !isnan(src) && !isinf(src)) {
        s21_zero(dst);

        if (src == 0.0f) {
            status = SUCCESS;
        } else {
            int sign = (src < 0);
            double tmp = fabs((double)src);

            int scale = 0;

            while (scale < 28 && fabs(tmp - floor(tmp)) > 1e-6) {
                tmp *= 10.0;
                scale++;
            }

            tmp = round(tmp);

            if (tmp <= 7.9228162514264337593543950335e28) {

                dst->bits[0] = (unsigned int)fmod(tmp, pow(2, 32));
                dst->bits[1] = (unsigned int)fmod(tmp / pow(2, 32), pow(2, 32));
                dst->bits[2] = (unsigned int)(tmp / pow(2, 64));

                s21_set_scale(dst, scale);

                s21_set_sign(dst, sign);

                status = SUCCESS;
            }
        }
    }

    return status;
}