#include "s21_smartcalc.h"

int s21_rpn(lexema **inverse_input, lexema **rpn_ready) {
  int err = OK;
  lexema *stack = NULL;
  lexema *output = NULL;

  while (*inverse_input && err == OK) {
    lexema *current = *inverse_input;
    *inverse_input = current->next;

    switch (current->type) {
      case LEXEMA_X:
      case LEXEMA_NUMBER:
        err = s21_push(&output, current->value, LEXEMA_NUMBER, 0);
        break;

      case LEFT_S:
        err =
            s21_push(&stack, current->value, current->type, current->priority);
        break;
      case LEXEMA_POW:
      case LEXEMA_SIN:
      case LEXEMA_COS:
      case LEXEMA_TAN:
      case LEXEMA_ACOS:
      case LEXEMA_ASIN:
      case LEXEMA_ATAN:
      case LEXEMA_SQRT:
      case LEXEMA_LN:
      case LEXEMA_LOG:
        err =
            s21_push(&stack, current->value, current->type, current->priority);
        break;

      case LEXEMA_MUL:
      case LEXEMA_DIV:
      case LEXEMA_PLUS:
      case LEXEMA_MINUS:
      case LEXEMA_MOD:
        while (stack && stack->type != LEFT_S &&
               (current->priority < stack->priority ||
                (current->priority == stack->priority &&
                 current->type != LEXEMA_POW))) {
          err = s21_push(&output, stack->value, stack->type, stack->priority);
          err = s21_pop(&stack);
        }
        err =
            s21_push(&stack, current->value, current->type, current->priority);
        break;

      case RIGHT_S:
        while (stack && stack->type != LEFT_S) {
          err = s21_push(&output, stack->value, stack->type, stack->priority);
          err = s21_pop(&stack);
        }
        if (stack && stack->type == LEFT_S) {
          err = s21_pop(&stack);
          if (stack &&
              (stack->type >= LEXEMA_SIN && stack->type <= LEXEMA_LOG)) {
            err = s21_push(&output, stack->value, stack->type, stack->priority);
            err = s21_pop(&stack);
          }
        } else {
          err = MISMATCHED_PARENTHESES;
        }
        break;

      default:
        err = UNKNOWN_LEXEMA;
        break;
    }

    free(current);
  }

  while (stack) {
    if (stack->type == LEFT_S) {
      err = MISMATCHED_PARENTHESES;
      break;
    }
    err = s21_push(&output, stack->value, stack->type, stack->priority);
    err = s21_pop(&stack);
  }

  while (output && err == OK) {
    lexema *current = output;
    output = current->next;

    err = s21_push(rpn_ready, current->value, current->type, current->priority);
    free(current);
  }

  s21_clear_stack(&stack);

  return err;
}
