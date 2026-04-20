#include "../s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
    int sign = 0;
    if (dst == NULL) {
        return 1;
    }

    dst->bits[0] = 0;
    dst->bits[1] = 0;
    dst->bits[2] = 0;
    dst->bits[3] = 0;

    if (src < 0) {
        sign = 1;
        // dst->bits[0] = -src; здесь может быть переполнение, поэтому сделаем по-другому
        dst->bits[0] = (unsigned int)(-src);
    } else {
        dst->bits[0] = (unsigned int)(src);
    }

    if (sign) {
        dst->bits[3] |= (1u << 31); // побитовый сдвиг
    }

    return 0;
}