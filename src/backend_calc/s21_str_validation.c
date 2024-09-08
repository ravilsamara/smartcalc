#include <stdio.h>

#include "s21_smartcalc.h"

int s21_str_is_valid(const char *str) {
  int err = OK;
  int open = 0, close = 0;
  int len = strlen(str);
  err = s21_initial_verification(str, len);
  if (!err) {
    for (int i = 0; i < len && err == 0; i++) {
      s21_arithmetic_is_valid(str, &err, i);
      s21_brackets_is_valid(str, &err, i);
      s21_functions_is_valid(str, &err, &open, &close, &i, len);
    }
  }
  if (!err) {
    s21_sum_brackets_is_valid(&err, open, close);
  }
  return err;
}

int s21_initial_verification(const char *str, int len) {
  int err_initial_verification = 0;
  if (len == 0) {
    err_initial_verification = EMPTY_MATH_E;
  } else if (len > MAX_STR_LEN) {
    err_initial_verification = MORE_THAN_255;
  } else if ((str[0] == '+' && len == 1) || (str[0] == '-' && len == 1) ||
             str[0] == '*' || str[0] == '/' || str[0] == '^' || str[0] == 'm' ||
             str[0] == ')' || (str[0] == '(' && len == 1)) {
    err_initial_verification = INVALID_MATH_E;
  }
  return err_initial_verification;
}
void s21_arithmetic_is_valid(const char *str, int *err, int i) {
  if (i < (int)strlen(str) - 1) {
    if ((str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/' ||
         str[i] == '^') &&
        (str[i + 1] == '+' || str[i + 1] == '-' || str[i + 1] == '*' ||
         str[i + 1] == '/' || str[i + 1] == '^')) {
      *err = INVALID_MATH_E;
    } else if (str[i] == '/' && str[i + 1] == '0') {
      *err = DIVISION_BY_ZERO;
    }
  } else if ((i == (int)strlen(str) - 1) &&
             (str[i] == '+' || str[i] == '-' || str[i] == '*' ||
              str[i] == '/' || str[i] == '^')) {
    *err = INVALID_MATH_E;
  }
}

void s21_brackets_is_valid(const char *str, int *err, int i) {
  if (i < (int)strlen(str) - 1) {
    if ((str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/' ||
         str[i] == '^' || str[i] == '(') &&
        str[i + 1] == ')') {
      *err = INVALID_MATH_E;
    }
  }
}

void s21_functions_is_valid(const char *str, int *err, int *open, int *close,
                            int *i, int len) {
  if (str[*i] == '.') {
    *i = *i;
  } else if (str[*i] == 'x') {
    *i = *i;
  } else if (str[*i] >= '0' && str[*i] <= '9') {
    *i = *i;
  } else if (str[*i] == '+' || str[*i] == '-' || str[*i] == '*' ||
             str[*i] == '/' || str[*i] == '^') {
    *i = *i;
  } else if (str[*i] == '(') {
    *open = *open + 1;
  } else if (str[*i] == ')') {
    *close = *close + 1;
  } else if ((*i < len - 3) &&
             (str[*i] == 'm' && str[*i + 1] == 'o' && str[*i + 2] == 'd') &&
             (str[*i + 3] >= '0' && str[*i + 3] <= '9') &&
             (str[*i - 1] >= '0' && str[*i - 1] <= '9')) {
    *i = *i + 2;
  } else if ((*i < len - 3) && str[*i] == 'c' && str[*i + 1] == 'o' &&
             str[*i + 2] == 's' && str[*i + 3] == '(') {
    *i = *i + 2;
  } else if ((*i < len - 3) && str[*i] == 's' && str[*i + 1] == 'i' &&
             str[*i + 2] == 'n' && str[*i + 3] == '(') {
    *i = *i + 2;
  } else if ((*i < len - 3) && str[*i] == 't' && str[*i + 1] == 'a' &&
             str[*i + 2] == 'n' && str[*i + 3] == '(') {
    *i = *i + 2;
  } else if ((*i < len - 4) && str[*i] == 'a' && str[*i + 1] == 'c' &&
             str[*i + 2] == 'o' && str[*i + 3] == 's' && str[*i + 4] == '(') {
    *i = *i + 3;
  } else if ((*i < len - 4) && str[*i] == 'a' && str[*i + 1] == 's' &&
             str[*i + 2] == 'i' && str[*i + 3] == 'n' && str[*i + 4] == '(') {
    *i = *i + 3;
  } else if ((*i < len - 4) && str[*i] == 'a' && str[*i + 1] == 't' &&
             str[*i + 2] == 'a' && str[*i + 3] == 'n' && str[*i + 4] == '(') {
    *i = *i + 3;
  } else if ((*i < len - 4) && str[*i] == 's' && str[*i + 1] == 'q' &&
             str[*i + 2] == 'r' && str[*i + 3] == 't' && str[*i + 4] == '(') {
    *i = *i + 3;
  } else if ((*i < len - 2) && str[*i] == 'l' && str[*i + 1] == 'n' &&
             str[*i + 2] == '(') {
    *i = *i + 1;
  } else if ((*i < len - 3) && str[*i] == 'l' && str[*i + 1] == 'o' &&
             str[*i + 2] == 'g' && str[*i + 3] == '(') {
    *i = *i + 2;
  } else {
    *err = INVALID_MATH_E;
  }
  if (!*err && *close > *open) *err = INVALID_MATH_E;
}

void s21_sum_brackets_is_valid(int *err, int open, int close) {
  if (*err == 0 && open != close) {
    *err = INVALID_MATH_E;
  }
}