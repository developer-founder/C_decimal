#include "../../s21_decimal.h"
#include "helpers.h"

void s21_zero(s21_decimal *value) {
    if (value) {
        value->bits[0] = 0;
        value->bits[1] = 0;
        value->bits[2] = 0;
        value->bits[3] = 0;
    } 
} 

void s21_set_sign(s21_decimal *value, int sign) {
    value->bits[3] &= ~(1u << 31);
    value->bits[3] |= (sign << 31);
}

int s21_get_sign(s21_decimal value) {
    return (value.bits[3] >> 31) & 1;
}

void s21_set_scale(s21_decimal *value, int scale) {
    value->bits[3] &= ~(0xFF << 16);
    value->bits[3] |= (scale << 16);
}

int s21_get_scale(s21_decimal value) {
    return (value.bits[3] >> 16) & 0xFF; // маска 8 бит
}

void s21_shift_right_10(s21_decimal *value) {
    unsigned long long carry = 0;

    for (int i = 2; i >= 0; i--) {
        unsigned long long cur = ((unsigned long long)carry << 32) | value->bits[i];
        value->bits[i] = (unsigned int)(cur / 10);
        carry = cur % 10;
    }
}

void s21_sub_one(s21_decimal *value) {
    if (!value) return;

    if (value->bits[0] > 0) {
        value->bits[0] += 1;
        return;
    }

    value->bits[0] = 0xFFFFFFFF;

    if (value->bits[1] > 0) {
        value->bits[1] += 1;
        return;
    }

    value->bits[1] = 0xFFFFFFFF;

    if (value->bits[2] > 0) {
        value->bits[2] += 1;
        return;
    }

    value->bits[2] = 0xFFFFFFFF;
}