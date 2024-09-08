#include "s21_smartcalc.h"

int s21_from_qt_calculator(const char *str, double x, double *result) {
  int err = OK;
  err = s21_str_is_valid(str);
  if (!err) {
    lexema *input = NULL;
    err = s21_convert_to_stack(str, x, &input);
    if (!err) {
      lexema *inverse_input = NULL;
      err = s21_inverse_stack(&input, &inverse_input);

      if (!err) {
        lexema *rpn_ready = NULL;
        err = s21_rpn(&inverse_input, &rpn_ready);
        if (!err) {
          err = s21_calculator(&rpn_ready, result);
        }
        s21_clear_stack(&rpn_ready);
      }
      s21_clear_stack(&inverse_input);
    }
    s21_clear_stack(&input);
  }
  return err;
}

int s21_calculator(lexema **inverse_rpn_ready, double *result) {
  int err = OK;
  lexema *stack = NULL;
  while (*inverse_rpn_ready && err == OK) {
    lexema *current = *inverse_rpn_ready;
    *inverse_rpn_ready = (*inverse_rpn_ready)->next;

    if (current->type == LEXEMA_NUMBER) {
      // Если число, помещаем в стек
      err = s21_push(&stack, current->value, LEXEMA_NUMBER, 0);
    } else {
      // Оператор или функция, выполняем вычисление
      if (current->type == LEXEMA_SIN || current->type == LEXEMA_COS ||
          current->type == LEXEMA_TAN || current->type == LEXEMA_ACOS ||
          current->type == LEXEMA_ASIN || current->type == LEXEMA_ATAN ||
          current->type == LEXEMA_SQRT || current->type == LEXEMA_LN ||
          current->type == LEXEMA_LOG) {
        // Тригонометрические функции и другие функции
        if (stack) {
          double val = stack->value;
          err = s21_pop(&stack);
          *result = s21_calculate(val, 0, current);
          err = s21_push(&stack, *result, LEXEMA_NUMBER, 0);
        } else {
          err = INVALID_EXPRESSION;
        }
      } else {
        // Бинарные операторы
        if (stack && stack->next) {
          double val2 = stack->value;
          double val1 = stack->next->value;
          err = s21_pop(&stack);
          err = s21_pop(&stack);
          *result = s21_calculate(val1, val2, current);
          err = s21_push(&stack, *result, LEXEMA_NUMBER, 0);
        } else {
          err = INVALID_EXPRESSION;
        }
      }
    }

    free(current);
  }

  if (stack && !stack->next) {
    // В стеке должен остаться только один элемент - результат вычислений
    *result = stack->value;
  } else {
    err = INVALID_EXPRESSION;
  }
  s21_clear_stack(&stack);
  return err;
}

double s21_calculate(double val1, double val2, lexema *element) {
  double result = 0.0;
  if (element->type == LEXEMA_PLUS)
    result = val1 + val2;
  else if (element->type == LEXEMA_MINUS)
    result = val1 - val2;
  else if (element->type == LEXEMA_MUL)
    result = val1 * val2;
  else if (element->type == LEXEMA_DIV)
    result = val1 / val2;
  else if (element->type == LEXEMA_POW)
    result = pow(val1, val2);
  else if (element->type == LEXEMA_MOD)
    result = fmod(val1, val2);
  else if (element->type == LEXEMA_SIN) {
    result = sin(val1);
  } else if (element->type == LEXEMA_COS)
    result = cos(val1);
  else if (element->type == LEXEMA_TAN)
    result = tan(val1);
  else if (element->type == LEXEMA_ACOS)
    result = acos(val1);
  else if (element->type == LEXEMA_ASIN)
    result = asin(val1);
  else if (element->type == LEXEMA_ATAN) {
    result = atan(val1);
  } else if (element->type == LEXEMA_SQRT)
    result = sqrt(val1);
  else if (element->type == LEXEMA_LN)
    result = log(val1);
  else if (element->type == LEXEMA_LOG)
    result = log10(val1);
  return result;
}
