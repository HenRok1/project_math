#ifndef SRC_S21_MATH_H_
#define SRC_S21_MATH_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define S21_INF 1.0 / 0.0
#define S21_NAN 0.0 / 0.0

#define S21_PI 3.1415926535897931159l
#define S21_PI_2 1.5707963267948966l
#define S21_2PI 6.283185307179586l
#define S21_E 2.71828182845904523l
#define S21_LN2 0.69314718055994530l
#define S21_LN10 2.3025850929940456l
#define S21_EPS 1e-99l

#define MAX_LONG_DOUBLE 1.79769313486231571e+308
#define s21_int128 __int128_t

/**
 * Возвращает модуль целочисленного значения
 */
int s21_abs(int x);

/**
 * Возвращает модуль значения c плавающей запятой двойной точности
 */
long double s21_fabs(double x);

/**
 * Возвращает ближайшее целое число не более заданного
 */
long double s21_floor(double x);

/**
 * Возвращает ближайшее целое число не менее заданного
 */
long double s21_ceil(double x);

/**
 * Возвращает остаток от деления чисел с плавающей запятой
 */
long double s21_fmod(double x, double y);

/**
 * Возвращает значение синуса для заданного угла в радианах
 */
long double s21_sin(double x);

/**
 * Возвращает значение косинуса для заданного угла в радианах
 */
long double s21_cos(double x);

/**
 * Возвращает значение тангенса для заданного угла в радианах
 */
long double s21_tan(double x);

/**
 * Возвращает значение арккосинуса для заданного числа
 */
long double s21_acos(double x);

/**
 * Возвращает значение арксинуса для заданного числа
 */
long double s21_asin(double x);

/**
 * Возвращает значение арктангенса для заданного числа
 */
long double s21_atan(double x);

/**
 * Возвращает результат возведения числа base в степень exp
 */
long double s21_pow(double base, double exp);

/**
 * Возвращает результат возведения числа e в степень x
 */
long double s21_exp(double x);

/**
 * Возвращает значение квадратичного корня заданного числа
 */
long double s21_sqrt(double x);

/**
 * Возвращает логарифм заданного числа
 */
long double s21_log(double x);

// additional functions
/**
 * Возвращает признак того, что число не является бесконечностью или NAN
 */
int s21_isfinite(long double x);

/**
 * Возвращает признак является ли число бесконечностью
 */
int s21_isinf(long double x);

/**
 * Возвращает признак того, что передано не число (NAN)
 */
int s21_isnan(long double x);

#endif  // SRC_S21_MATH_H_
