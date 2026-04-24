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
    return (value.bits[3] >> 16) & 0xFF;
}

unsigned long long s21_shift_right_10(s21_decimal *value) {
    unsigned long long carry = 0;

    for (int i = 2; i >= 0; i--) {
        unsigned long long cur = ((unsigned long long)carry << 32) | value->bits[i];
        value->bits[i] = (unsigned int)(cur / 10);
        carry = cur % 10;
    }

    return carry;
}

int s21_add_one(s21_decimal *v) {
    int status = SUCCESS;

    if (!v) {
        status = CALCULATION_ERROR;
    } else if (v->bits[0] == 0xFFFFFFFF &&
               v->bits[1] == 0xFFFFFFFF &&
               v->bits[2] == 0xFFFFFFFF) {
        status = CALCULATION_ERROR;
    } else {
        if (v->bits[0] < 0xFFFFFFFF) {
            v->bits[0]++;
        } else {
            v->bits[0] = 0;

            if (v->bits[1] < 0xFFFFFFFF) {
                v->bits[1]++;
            } else {
                v->bits[1] = 0;
                v->bits[2]++;
            }
        }
    }

    return status;
}

int s21_mul_10(s21_decimal *v) {
    int status = 0;

    if (!v) {
        status = 1;
    } else {
        unsigned long long carry = 0;

        for (int i = 0; i < 3; i++) {
            unsigned long long cur =
                (unsigned long long)v->bits[i] * 10 + carry;

            v->bits[i] = (unsigned int)cur;
            carry = cur >> 32;
        }

        if (carry) {
            status = 1;
        }
    }

    return status;
}

int s21_compare(s21_decimal a, s21_decimal b) {
    int result = 0;

    int sign_a = s21_get_sign(a);
    int sign_b = s21_get_sign(b);

    if (sign_a != sign_b) {
        result = sign_a ? -1 : 1;
    } else {
        int scale_a = s21_get_scale(a);
        int scale_b = s21_get_scale(b);

        while (scale_a < scale_b) {
            s21_mul_10(&a);
            scale_a++;
        }

        while (scale_b < scale_a) {
            s21_mul_10(&b);
            scale_b++;
        }

        for (int i = 2; i >= 0; i--) {
            if (a.bits[i] != b.bits[i]) {
                if (sign_a == 0)
                    result = (a.bits[i] > b.bits[i]) ? 1 : -1;
                else
                    result = (a.bits[i] > b.bits[i]) ? -1 : 1;

                break;
            }
        }
    }

    return result;
}

int s21_abs_compare(s21_decimal a, s21_decimal b) {
    for (int i = 2; i >= 0; i--) {
        if (a.bits[i] != b.bits[i]) {
            return (a.bits[i] > b.bits[i]) ? 1 : -1;
        }
    }
    return 0;
}

int s21_sub_abs(s21_decimal a, s21_decimal b, s21_decimal *res) {
    unsigned long long borrow = 0;

    for (int i = 0; i < 3; i++) {
        unsigned long long x = a.bits[i];
        unsigned long long y = b.bits[i] + borrow;

        if (x < y) {
            res->bits[i] = (unsigned int)((1ULL << 32) + x - y);
            borrow = 1;
        } else {
            res->bits[i] = (unsigned int)(x - y);
            borrow = 0;
        }
    }

    return 0;
}

void s21_negate_internal(s21_decimal *v) {
    if (v) {
        v->bits[3] ^= (1u << 31);
    }
}