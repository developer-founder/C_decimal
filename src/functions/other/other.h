#ifndef OTHER_H
#define OTHER_H

int s21_get_sign(s21_decimal value);
void s21_set_sign(s21_decimal *value, int sign);
void s21_zero(s21_decimal *value);
int s21_get_scale(s21_decimal value);
void s21_set_scale(s21_decimal *value, int scale);
int s21_negate(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_floor(s21_decimal value, s21_decimal *result);

#endif