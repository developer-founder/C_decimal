#ifndef HELPERS_H
#define HELPERS_H

#include "../../s21_decimal.h"

int s21_get_scale(s21_decimal value);
int s21_get_sign(s21_decimal value);
void s21_set_scale(s21_decimal *value, int scale);
void s21_set_sign(s21_decimal *value, int sign);
void s21_zero(s21_decimal *value);
unsigned long long s21_shift_right_10(s21_decimal *value);
int s21_add_one(s21_decimal *value);

#endif