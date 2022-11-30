#include "s21_math.h"

// Arithmetic funtions

int s21_abs(int x) { return x < 0 ? -x : x; }

long double s21_fabs(double x) { return x < 0 ? -x : x; }

// Auxilary functions

long double s21_floor(double x) {
  long double res = x;
  if (s21_isfinite(x)) {
    res = (s21_int128)x;
    if (res > x) {
      res -= 1;
    }
  }
  return res;
}

long double s21_ceil(double x) {
  double res = x;
  int temp = res;
  if (s21_isinf(x))
    res = x;
  else if (x != x)
    res = S21_NAN;
  else if (temp == res)
    res = temp;
  else if (res < 0)
    res = temp;
  else
    res = temp + 1;
  return res;
}

long double s21_fmod(double x, double y) {
  long double res = S21_NAN;
  if (s21_isinf(y)) {
    if (s21_isfinite(x)) {
      res = x;
    }
  } else if (s21_isinf(x)) {
    res = S21_NAN;
  } else if (y == 0) {
    res = S21_NAN;
  } else if (y) {
    long long int quot = x / y;
    res = x - quot * y;
  }
  return res;
}

long double s21_sin(double x) {
  long double res = 0;
  if (!s21_isfinite(x)) {
    res = S21_NAN;
  } else {
    x = s21_fmod(x, S21_2PI);
    long double prev = 0.0l;
    long double fact;
    int k = 0;
    do {
      fact = 1.0;
      for (register int i = 1; i <= 2 * k + 1; i++) fact *= i;
      prev = res;
      res += s21_pow(-1, k) * s21_pow(x, 2 * k + 1) / fact;
      k++;
    } while (s21_fabs(res - prev) > 1e-18);
  }
  return res;
}

long double s21_cos(double x) {
  long double res = 0;
  if (!s21_isfinite(x)) {
    res = S21_NAN;
  } else {
    res = s21_sin(S21_PI_2 - x);
  }
  return res;
}

long double s21_tan(double x) {
  long double res = 0;
  if (!s21_isfinite(x))
    res = S21_NAN;
  else
    res = s21_sin(x) / s21_cos(x);
  return res;
}

long double s21_acos(double x) {
  long double res = 0;
  if (-1 > x || x > 1 || !s21_isfinite(x))
    res = S21_NAN;
  else
    res = S21_PI_2 - s21_asin(x);
  return res;
}

long double s21_asin(double x) {
  long double res = 0;
  if (-1 > x || x > 1 || !s21_isfinite(x))
    res = S21_NAN;
  else
    res = s21_atan(x / s21_sqrt(1 - (x * x)));
  return res;
}

long double s21_atan(double x) {
  long double res = 0;
  if (s21_isnan(x))
    res = S21_NAN;
  else {
    if (x == S21_INF || x == -S21_INF) {
      res = x < 0 ? -S21_PI / 2 : S21_PI / 2;
    } else if (-1. < x && x < 1.) {
      for (register int i = 0; i < 80; i++) {
        res += ((s21_pow(-1, i) * s21_pow(x, 1 + (2 * i))) / (1 + (2 * i)));
      }
    } else {
      for (register int i = 0; i < 80; i++) {
        res += ((s21_pow(-1, i) * s21_pow(x, -1 - (2 * i))) / (1 + (2 * i)));
      }
      res = S21_PI * s21_sqrt(x * x) / (2 * x) - res;
    }
  }
  return res;
}

long double s21_pow(double base, double exps) {
  long double n = base;
  long double res = 0;
  if ((base == 0) && (s21_isnan(exps))) {
    res = S21_NAN;
  } else if ((base == 0) && (exps < 0)) {
    res = S21_INF;
  } else if ((base == S21_INF) && (exps < 0)) {
    res = 0;
  } else if ((base == -1) && (exps == -S21_INF)) {
    res = 1;
  } else {
    if (exps == 0) {
      res = 1;
    } else {
      if (base == 0) {
        res = 0;
      } else {
        if (n < 0) {
          res = s21_exp(exps * s21_log(-n));
          if (s21_fmod(exps, 2) != 0) {
            res = res * -1;
          }
        } else {
          res = s21_exp(exps * s21_log(n));
        }
      }
    }
  }
  return res;
}

long double s21_exp(double x) {
  long double result = 1;
  long double temp = 1;
  long double i = 1;
  int flag = 0;
  if (x < 0) {
    x *= -1;
    flag = 1;
  }
  while (s21_fabs(result) > S21_EPS) {
    result *= x / i++;
    temp += result;
    if (temp > MAX_LONG_DOUBLE) {
      temp = S21_INF;
      break;
    }
  }
  if (flag == 1) {
    if (temp > MAX_LONG_DOUBLE)
      temp = 0;
    else
      temp = 1. / temp;
  }
  return temp > MAX_LONG_DOUBLE ? S21_INF : temp;
}

long double s21_sqrt(double x) {
  long double res;
  if (x < 0) {
    res = S21_NAN;
  } else {
    res = x / 2;
    while (s21_isfinite(x) && s21_fabs(x - res * res) > 1e-18)
      res = (res + x / res) * 0.5;
  }
  return res;
}

long double s21_log(double x) {
  register int ex_pow = 0;
  long double res = 0;
  long double result = 0, compare = result;
  if ((x < 0) || (s21_isnan(x))) {
    res = S21_NAN;
  } else if (x == 0) {
    res = -S21_INF;
  } else if ((s21_isinf(x))) {
    res = S21_INF;
  } else {
    if (res == 0) {
      for (; x >= S21_E; x /= S21_E, ex_pow++) continue;
      for (register int i = 0; i < 100; i++) {
        compare = result;
        result = compare + 2 * (x - s21_exp(compare)) / (x + s21_exp(compare));
      }
      res = result + ex_pow;
    }
  }
  return res;
}

int s21_isfinite(long double x) {
  return x == x && x < S21_INF && x > -S21_INF;
}

int s21_isinf(long double x) { return x == S21_INF || x == -S21_INF; }

int s21_isnan(long double x) { return !(x == x); }
