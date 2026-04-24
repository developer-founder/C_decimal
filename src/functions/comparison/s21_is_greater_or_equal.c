#include "../../s21_decimal.h"
#include "../helpers/helpers.h"

int s21_is_greater_or_equal(s21_decimal a, s21_decimal b) {
    return s21_compare(a, b) >= 0;
}