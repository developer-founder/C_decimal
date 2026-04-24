#include "s21_tests.h"

START_TEST(test_sub_simple) {
  s21_decimal a = {{300, 0, 0, 0}};
  s21_decimal b = {{100, 0, 0, 0}};
  s21_decimal res;

  s21_sub(a, b, &res);

  ck_assert_int_eq(res.bits[0], 200);
}
END_TEST

START_TEST(test_sub_to_zero) {
  s21_decimal a = {{100, 0, 0, 0}};
  s21_decimal b = {{100, 0, 0, 0}};
  s21_decimal res;

  s21_sub(a, b, &res);

  ck_assert_int_eq(res.bits[0], 0);
}
END_TEST

START_TEST(test_sub_negative_result) {
  s21_decimal a = {{100, 0, 0, 0}};
  s21_decimal b = {{200, 0, 0, 0}};
  s21_decimal res;

  s21_sub(a, b, &res);

  ck_assert_int_eq(res.bits[0], 100);
  ck_assert_int_eq((res.bits[3] >> 31) & 1, 1);
}
END_TEST

START_TEST(test_sub_negative_minus_negative) {
  s21_decimal a = {{200, 0, 0, 0}};
  s21_decimal b = {{100, 0, 0, 0}};

  a.bits[3] |= (1u << 31);
  b.bits[3] |= (1u << 31);

  s21_decimal res;
  s21_sub(a, b, &res);

  ck_assert_int_eq(res.bits[0], 100);
  ck_assert_int_eq((res.bits[3] >> 31) & 1, 1);
}
END_TEST

START_TEST(test_sub_scale) {
  s21_decimal a = {{1234, 0, 0, 0}};  // 123.4
  s21_decimal b = {{123, 0, 0, 0}};   // 12.3

  a.bits[3] = (1 << 16);
  b.bits[3] = (1 << 16);

  s21_decimal res;
  s21_sub(a, b, &res);

  ck_assert_int_eq(res.bits[0], 1111);
}
END_TEST

#include "s21_tests.h"

// Существующие тесты остаются...

// ТЕСТ 1: Покрывает строки 14-15 (sign1 != sign2)
// Вычитание положительного и отрицательного = сложение
START_TEST(test_sub_positive_minus_negative) {
  s21_decimal a = {{100, 0, 0, 0}};  // +100
  s21_decimal b = {{50, 0, 0, 0}};   // -50

  b.bits[3] |= (1u << 31);  // делаем b отрицательным

  s21_decimal res;
  s21_sub(a, b, &res);

  // 100 - (-50) = 100 + 50 = 150
  ck_assert_int_eq(res.bits[0], 150);
  ck_assert_int_eq((res.bits[3] >> 31) & 1, 0);  // положительный
}
END_TEST

// ТЕСТ 2: Покрывает строки 14-15 (другой вариант)
// Вычитание отрицательного из отрицательного = сложение с разными знаками
START_TEST(test_sub_negative_minus_positive) {
  s21_decimal a = {{100, 0, 0, 0}};  // -100
  s21_decimal b = {{50, 0, 0, 0}};   // +50

  a.bits[3] |= (1u << 31);  // a отрицательный
  // b положительный

  s21_decimal res;
  s21_sub(a, b, &res);

  // -100 - 50 = -150
  ck_assert_int_eq(res.bits[0], 150);
  ck_assert_int_eq((res.bits[3] >> 31) & 1, 1);  // отрицательный
}
END_TEST

// ТЕСТ 3: Покрывает cmp < 0 (у вас уже есть test_sub_negative_result)
// Но давайте явно проверим знак результата
START_TEST(test_sub_abs_compare_less) {
  s21_decimal a = {{50, 0, 0, 0}};   // 50
  s21_decimal b = {{100, 0, 0, 0}};  // 100

  s21_decimal res;
  s21_sub(a, b, &res);

  // 50 - 100 = -50
  ck_assert_int_eq(res.bits[0], 50);
  ck_assert_int_eq((res.bits[3] >> 31) & 1, 1);  // отрицательный
}
END_TEST

// ТЕСТ 4: Разные знаки с разными масштабами
START_TEST(test_sub_opposite_signs_with_scale) {
  s21_decimal a = {{1234, 0, 0, 0}};  // +12.34 (scale 2)
  s21_decimal b = {{567, 0, 0, 0}};   // -5.67 (scale 2)

  a.bits[3] = 2 << 16;                 // scale = 2
  b.bits[3] = (2 << 16) | (1u << 31);  // scale = 2, sign = negative

  s21_decimal res;
  s21_sub(a, b, &res);

  // 12.34 - (-5.67) = 18.01
  ck_assert_int_eq(res.bits[0], 1801);
  ck_assert_int_eq((res.bits[3] >> 16) & 0xFF, 2);  // scale = 2
  ck_assert_int_eq((res.bits[3] >> 31) & 1, 0);     // положительный
}
END_TEST

// ТЕСТ 5: NULL указатель
START_TEST(test_sub_null_result) {
  s21_decimal a = {{100, 0, 0, 0}};
  s21_decimal b = {{50, 0, 0, 0}};

  int status = s21_sub(a, b, NULL);

  ck_assert_int_eq(status, CALCULATION_ERROR);
}
END_TEST

// ТЕСТ 6: Сложный случай с разными масштабами и разными знаками (для покрытия
// s21_add внутри s21_sub)
START_TEST(test_sub_opposite_signs_diff_scales) {
  s21_decimal a = {{1000, 0, 0, 0}};  // +10.00 (scale 2)
  s21_decimal b = {{5, 0, 0, 0}};     // -0.5 (scale 1)

  a.bits[3] = 2 << 16;                 // scale = 2
  b.bits[3] = (1 << 16) | (1u << 31);  // scale = 1, negative

  s21_decimal res;
  s21_sub(a, b, &res);

  // 10.00 - (-0.5) = 10.50
  ck_assert_int_eq(res.bits[0], 1050);
}
END_TEST

// Обновленная suite
Suite* s21_sub_suite(void) {
  Suite* s = suite_create("sub");
  TCase* tc = tcase_create("core");

  // Существующие тесты
  tcase_add_test(tc, test_sub_simple);
  tcase_add_test(tc, test_sub_to_zero);
  tcase_add_test(tc, test_sub_negative_result);
  tcase_add_test(tc, test_sub_negative_minus_negative);
  tcase_add_test(tc, test_sub_scale);

  // НОВЫЕ тесты для покрытия
  tcase_add_test(tc, test_sub_positive_minus_negative);    // строки 14-15
  tcase_add_test(tc, test_sub_negative_minus_positive);    // строки 14-15
  tcase_add_test(tc, test_sub_abs_compare_less);           // строка 25
  tcase_add_test(tc, test_sub_opposite_signs_with_scale);  // комбинация
  tcase_add_test(tc, test_sub_null_result);  // строка 7 (result == NULL)
  tcase_add_test(
      tc, test_sub_opposite_signs_diff_scales);  // дополнительное покрытие

  suite_add_tcase(s, tc);
  return s;
}