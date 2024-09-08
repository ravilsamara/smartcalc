#ifndef S21_SMARTCALC_H
#define S21_SMARTCALC_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 255

//Для проверки входного математического выражения
#define OK 0              //
#define INVALID_MATH_E 1  // некорректная выражение
#define EMPTY_MATH_E 2    // пустое выражение
#define MORE_THAN_255 3  // выражение содержит более 255 символов
#define DIVISION_BY_ZERO 4  // Деление на ноль

//Для проверки стека
#define STACK_OVERFLOW 10
#define STACK_UNDERFLOW 11

//Ошибки при конвертации
#define DIGIT_INVALID_CONVERTATION 12
#define CONVERT_WORD_FUNCTION_ERR 13

//  Ошибки при RPN
#define MISMATCHED_PARENTHESES 14
#define UNKNOWN_LEXEMA 16

//Ошибки при калькуляции
#define INVALID_EXPRESSION 15

int s21_str_is_valid(const char *str_math_expression);
int s21_initial_verification(const char *str_math_expression, int len);
void s21_arithmetic_is_valid(const char *str, int *err, int i);
void s21_brackets_is_valid(const char *str, int *err, int i);
void s21_functions_is_valid(const char *s, int *err, int *open, int *close,
                            int *i, int len);
void s21_sum_brackets_is_valid(int *err, int open, int close);

typedef enum {
  LEFT_S = 1,
  RIGHT_S = 2,
  LEXEMA_PLUS = 3,
  LEXEMA_MINUS = 4,
  LEXEMA_MUL = 5,
  LEXEMA_DIV = 6,
  LEXEMA_POW = 7,
  LEXEMA_MOD = 8,
  LEXEMA_UNAR_PLUS = 9,
  LEXEMA_UNAR_MINUS = 10,
  LEXEMA_COS = 11,
  LEXEMA_SIN = 12,
  LEXEMA_TAN = 13,
  LEXEMA_ACOS = 14,
  LEXEMA_ASIN = 15,
  LEXEMA_ATAN = 16,
  LEXEMA_SQRT = 17,
  LEXEMA_LN = 18,
  LEXEMA_LOG = 19,
  LEXEMA_X = 20,
  LEXEMA_NUMBER = 21,

} lexeme_type;

typedef struct N {
  double value;  // для чисел
  int priority;  // 1(" + - ") 2(" * /") 3(" mod ^") 4("sin cos ...") 5(" ( )")
  lexeme_type type;
  struct N *next;
} lexema;

int s21_push(lexema **head, double value, int type, int priority);
int s21_peek(lexema **head, lexema *top_stack_element);
int s21_pop(lexema **head);

int s21_from_qt_calculator(const char *str, double x, double *result);

int s21_convert_to_stack(const char *str, double x, lexema **input);

int s21_inverse_stack(lexema **input, lexema **inverse_input);
int s21_rpn(lexema **inverse_input, lexema **rpn_ready);
int s21_calculator(lexema **inverse_rpn_ready, double *result);
double s21_calculate(double val1, double val2, lexema *element);
void s21_clear_stack(lexema **head);

#endif  // S21_SMARTCALC_H
