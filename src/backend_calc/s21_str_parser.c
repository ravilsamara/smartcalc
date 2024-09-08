#include "s21_smartcalc.h"

int s21_push(lexema **head, double value, int type, int priority) {
  int err = OK;
  lexema *stack_element = (lexema *)malloc(sizeof(lexema));
  if (stack_element != NULL) {
    stack_element->value = value;
    stack_element->type = type;
    stack_element->priority = priority;
    stack_element->next = (*head);
    (*head) = stack_element;
  } else {
    err = STACK_OVERFLOW;
  }
  return err;
}

int s21_pop(lexema **stack) {
  if (*stack == NULL) {
    return STACK_UNDERFLOW;
  }

  lexema *temp = *stack;
  *stack = (*stack)->next;
  free(temp);

  return OK;
}

int s21_convert_digit(int *i, const char *str, lexema **input) {
  int control = 0, err = OK;
  char *start_digit = (char *)str + *i;

  while (str[*i] >= '0' && str[*i] <= '9') {
    (*i)++;
    if (str[*i] == '.') {
      (*i)++;
      control++;
    }
  }
  if (control <= 1) {
    double res = 0.0;
    sscanf(start_digit, "%lf", &res);
    err = s21_push(input, res, LEXEMA_NUMBER, 0);
  } else {
    err = DIGIT_INVALID_CONVERTATION;
  }
  return err;
}

int s21_convert_sign(int i, const char *str, lexema **input) {
  int err = 0;
  if (str[i] == '+') {
    err = s21_push(input, 0, LEXEMA_PLUS, 1);
  } else if (str[i] == '-') {
    err = s21_push(input, 0, LEXEMA_MINUS, 1);
  } else if (str[i] == '/') {
    err = s21_push(input, 0, LEXEMA_DIV, 2);
  } else if (str[i] == '*') {
    err = s21_push(input, 0, LEXEMA_MUL, 2);
  } else if (str[i] == '^') {
    err = s21_push(input, 0, LEXEMA_POW, 3);
  }
  return err;
}

int s21_convert_word(int *i, const char *str, lexema **input) {
  int err = OK;
  if (str[*i] == 'm' && str[*i + 1] == 'o' && str[*i + 2] == 'd') {
    err = s21_push(input, 0, LEXEMA_MOD, 3);
    *i = *i + 2;
  } else if (str[*i] == 's' && str[*i + 1] == 'q' && str[*i + 2] == 'r' &&
             str[*i + 3] == 't') {
    err = s21_push(input, 0, LEXEMA_SQRT, 4);
    *i = *i + 3;
  } else if (str[*i] == 'c' && str[*i + 1] == 'o' && str[*i + 2] == 's') {
    err = s21_push(input, 0, LEXEMA_COS, 4);
    *i = *i + 2;
  } else if (str[*i] == 's' && str[*i + 1] == 'i' && str[*i + 2] == 'n') {
    err = s21_push(input, 0, LEXEMA_SIN, 4);
    *i = *i + 2;
  } else if (str[*i] == 't' && str[*i + 1] == 'a' && str[*i + 2] == 'n') {
    err = s21_push(input, 0, LEXEMA_TAN, 4);
    *i = *i + 2;
  } else if (str[*i] == 'a') {
    if (str[*i + 1] == 'c' && str[*i + 2] == 'o' && str[*i + 3] == 's') {
      err = s21_push(input, 0, LEXEMA_ACOS, 4);
    } else if (str[*i + 1] == 's' && str[*i + 2] == 'i' && str[*i + 3] == 'n') {
      err = s21_push(input, 0, LEXEMA_ASIN, 4);
    } else if (str[*i + 1] == 't' && str[*i + 2] == 'a' && str[*i + 3] == 'n') {
      err = s21_push(input, 0, LEXEMA_ATAN, 4);
    }

    *i = *i + 3;
  } else if (str[*i] == 'l') {
    if (str[*i + 1] == 'o' && str[*i + 2] == 'g') {
      err = s21_push(input, 0, LEXEMA_LOG, 4);
      *i = *i + 2;
    } else if (str[*i + 1] == 'n') {
      err = s21_push(input, 0, LEXEMA_LN, 4);
      *i = *i + 1;
    }
  } else {
    err = CONVERT_WORD_FUNCTION_ERR;
  }
  return err;
}

int s21_convert_to_stack(const char *str, double x, lexema **input) {
  int err = OK, len = (int)strlen(str);
  for (int i = 0; i < len && !err; i++) {
    if (str[i] != ' ') {
      if (i == 0 && str[0] == '+') {
        // err = s21_push(input, 0, LEXEMA_UNAR_PLUS, 0);
        i++;
      }
      if (i == 0 && str[0] == '-') {
        err = s21_push(input, 0, LEXEMA_NUMBER, 0);
        err = s21_push(input, 0, LEXEMA_MINUS, 1);
        i++;
      }

      if (str[i] == 'x') {
        err = s21_push(input, x, LEXEMA_X, 0);
      }
      if (str[i] >= '0' && str[i] <= '9') {
        err = s21_convert_digit(&i, str, input);
      }
      if (str[i] == '+' || str[i] == '-' || str[i] == '/' || str[i] == '*' ||
          str[i] == '^') {
        err = s21_convert_sign(i, str, input);
      }
      if (str[i] == 'm' || str[i] == 's' || str[i] == 'c' || str[i] == 't' ||
          str[i] == 'a' || str[i] == 'l') {
        err = s21_convert_word(&i, str, input);
      }
      if (str[i] == ')' || str[i] == '(') {
        if (str[i] == ')') {
          err = s21_push(input, 0, RIGHT_S, 5);
        } else if ((str[i] == '(') && (str[i + 1] == '-')) {
          err = s21_push(input, 0, LEFT_S, 5);
          err = s21_push(input, 0, LEXEMA_NUMBER, 0);
          err = s21_push(input, 0, LEXEMA_MINUS, 1);
          i++;
        } else if ((str[i] == '(') && (str[i + 1] == '+')) {
          i++;
        } else if (str[i] == '(') {
          err = s21_push(input, 0, LEFT_S, 5);
        }
      }
    }
  }
  return err;
}

void s21_clear_stack(lexema **head) {
  lexema *current = *head;
  while (current != NULL) {
    lexema *temp = current;
    current = current->next;
    free(temp);
  }
  *head = NULL;
}

int s21_inverse_stack(lexema **input, lexema **inverse_input) {
  int err = OK;
  lexema *current = *input;
  lexema *top_el = NULL;

  while (current && err == OK) {
    top_el = current;
    current = current->next;

    err =
        s21_push(inverse_input, top_el->value, top_el->type, top_el->priority);
  }

  return err;
}
