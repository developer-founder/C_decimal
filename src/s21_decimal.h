#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H

typedef struct {
    int bits[4];
} s21_decimal;

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

#endif