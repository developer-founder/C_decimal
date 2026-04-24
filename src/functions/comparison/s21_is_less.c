#include "../../s21_decimal.h"
#include "../helpers/helpers.h"

int s21_is_less(s21_decimal a, s21_decimal b) { return s21_compare(a, b) < 0; }