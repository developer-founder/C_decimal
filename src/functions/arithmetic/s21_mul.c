#include "../../s21_decimal.h"
#include "../helpers/helpers.h"

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal* result) {
  int status = CALCULATION_ERROR;

  if (result) {
    *result = (s21_decimal){{0, 0, 0, 0}};
    status = SUCCESS;

    int sign = s21_get_sign(value_1) ^ s21_get_sign(value_2);

    int scale = s21_get_scale(value_1) + s21_get_scale(value_2);

    s21_set_sign(&value_1, 0);
    s21_set_sign(&value_2, 0);

    s21_decimal res = {{0, 0, 0, 0}};

    for (int i = 0; i < 96; i++) {
      if ((value_2.bits[i / 32] >> (i % 32)) & 1) {
        s21_decimal temp = value_1;

        for (int j = 0; j < i; j++) {
          unsigned long long carry = 0;

          for (int k = 0; k < 3; k++) {
            unsigned long long cur =
                ((unsigned long long)temp.bits[k] << 1) | carry;

            temp.bits[k] = (unsigned int)cur;
            carry = cur >> 32;
          }
        }

        unsigned long long carry = 0;

        for (int k = 0; k < 3; k++) {
          unsigned long long sum =
              (unsigned long long)res.bits[k] + temp.bits[k] + carry;

          res.bits[k] = (unsigned int)sum;
          carry = sum >> 32;
        }
      }
    }

    *result = res;

    s21_set_scale(result, scale);
    s21_set_sign(result, sign);
  }

  return status;
}