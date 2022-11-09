#include "s21_smartcalc.h"

//  распределитель для всех функций
int terminal(char *str, double x, double *result) {
  smart *list = NULL;
  int res = 0;
  if (check_list(str) == 0) {
    parser(str, &list, x);
    smart *RPN = polish_notation(list);
    processing_expression(RPN, result);
    clean_pop(&RPN);
  } else {
    res = -1;
  }
  clean_pop(&list);
  return res;
}

int check_list_2(char *str, int ret, int len_str, int i) {
  int count = 1;
  while (count) {
    if (str[0] == '*' || str[0] == '/' || str[0] == '%' || str[0] == '^' ||
        str[0] == ')') {
      ret = -1;
      break;
    }
    if (str[len_str - 1] == '+' || str[len_str - 1] == '-' ||
        str[len_str - 1] == '*' || str[len_str - 1] == '/' ||
        str[len_str - 1] == '%' || str[len_str - 1] == '^' ||
        str[len_str - 1] == '(') {
      ret = -1;
      break;
    }
    if (str[i - 1] == '.' || str[i + 1] == '.') {
      ret = -1;
      break;
    }
    if (str[i] == '(' && str[i + 1] == ')') {
      ret = -1;
      break;
    }
    if (str[i + 1] == '\0') {
      break;
    }
    if (str[i] == '(' || str[i] == ')') {
      int brack_i = 0;
      int brack_j = 0;
      int j = 0;
      while (str[j] != '\0') {
        if (str[j] == '(') {
          brack_i = brack_i + 1;
        }
        if (str[j] == ')') {
          brack_j = brack_j + 1;
        }
        j++;
      }
      if (brack_i != brack_j) {
        ret = -1;
        break;
      }
    }
    if (str[i + 1] != '+' && str[i + 1] != '-' && str[i + 1] != '(' &&
        str[i + 1] != 'x' && !(str[i + 1] >= '0' && str[i + 1] <= '9')) {
      if (str[i + 1] != ')' && (str[i - 1] >= '0' && str[i - 1] <= '9')) {
        ret = 0;
      } else {
        if (str[strlen(str) - 1] == '(') ret = -1;
      }
      break;
    }
    if (i >= 1 && !(is_brackets(str[i - 1])) && !(is_brackets(str[i]))) {
      if (is_operator(str[i - 1])) {
        ret = -1;
      }
    }
    count--;
  }
  return ret;
}

//  проверка
int check_list(char *str) {
  int ret = 0;
  int i = 0;
  int len_str = strlen(str);
  if (len_str > 256) {
    ret = -1;
  }
  while (i < len_str && len_str <= 256 && ret != -1) {
    if ((str[i] >= '0' && str[i] <= '9') || str[i] == '.') {
      if (str[i + 1] == '(') {
        ret = -1;
        break;
      }
      int j = i;
      int dot = 0;
      int count_dot = 0;
      while ((str[j] >= '0' && str[j] <= '9') || str[j] == '.') {
        if (str[j] == '.') {
          dot = dot + 1;
        } else if (dot > 1) {
          ret = -1;
          break;
        }
        if (dot == 1) {
          count_dot = count_dot + 1;
        } else if (count_dot > 7) {
          ret = -1;
          break;
        }
        j = j + 1;
      }
    } else if (is_operator(str[i])) {
      ret = check_list_2(str, ret, len_str, i);
    } else if (is_function(str[i])) {
      if (strncmp(str + i, "cos(", 4) == 0) {
        i = i + 3;
      } else if (strncmp(str + i, "sin(", 4) == 0) {
        i = i + 3;
      } else if (strncmp(str + i, "tan(", 4) == 0) {
        i = i + 3;
      } else if (strncmp(str + i, "acos(", 5) == 0) {
        i = i + 4;
      } else if (strncmp(str + i, "asin(", 5) == 0) {
        i = i + 4;
      } else if (strncmp(str + i, "atan(", 5) == 0) {
        i = i + 4;
      } else if (strncmp(str + i, "sqrt(", 5) == 0) {
        i = i + 4;
      } else if (strncmp(str + i, "ln(", 3) == 0) {
        i = i + 1;
      } else if (strncmp(str + i, "log(", 4) == 0) {
        i = i + 3;
      } else if ('x' == str[i]) {
        ret = 0;
      } else {
        ret = -1;
      }
    } else {
      ret = -1;
      break;
    }
    i++;
  }
  if (str[strlen(str) - 1] == '(') ret = -1;
  return (ret);
}

int calc_fun(char *str, smart **list, double x, int i) {
  if (str[i] == 'x') {
    *list = push(*list, x, 0, num);
  } else if (str[i] == 'c' && str[i + 1] == 'o' && str[i + 2] == 's') {
    *list = push(*list, 0.0, 4, cosinus);
    i = i + 1;
  } else if (str[i] == 's' && str[i + 1] == 'i' && str[i + 2] == 'n') {
    *list = push(*list, 0.0, 4, sinus);
    i = i + 1;
  } else if (str[i] == 't' && str[i + 1] == 'a' && str[i + 2] == 'n') {
    *list = push(*list, 0.0, 4, tangens);
    i = i + 1;
  } else if (str[i] == 'a' && str[i + 1] == 'c' && str[i + 2] == 'o' &&
             str[i + 3] == 's') {
    *list = push(*list, 0.0, 4, arccos);
    i = i + 2;
  } else if (str[i] == 'a' && str[i + 1] == 's' && str[i + 2] == 'i' &&
             str[i + 3] == 'n') {
    *list = push(*list, 0.0, 4, arcsin);
    i = i + 2;
  } else if (str[i] == 'a' && str[i + 1] == 't' && str[i + 2] == 'a' &&
             str[i + 3] == 'n') {
    *list = push(*list, 0.0, 4, arctan);
    i = i + 2;
  } else if (str[i] == 's' && str[i + 1] == 'q' && str[i + 2] == 'r' &&
             str[i + 3] == 't') {
    *list = push(*list, 0.0, 4, sq);
    i = i + 2;
  } else if (str[i] == 'l' && str[i + 1] == 'n') {
    *list = push(*list, 0.0, 4, ln);
  } else if (str[i] == 'l' && str[i + 1] == 'o' && str[i + 2] == 'g') {
    *list = push(*list, 0.0, 4, log_x);
    i = i + 1;
  }
  return i;
}

// парсер
int parser(char *str, smart **list, double x) {
  int ret = 0;
  int i = 0;
  int len_str = strlen(str);
  while (i < len_str) {
    if (str[i] >= '0' && str[i] <= '9') {
      *list = push(*list, atof(str + i), 0, num);
      i = counter(str, i);
    }
    if (is_operator(str[i])) {
      if (str[i] == '+') {
        if (*list == NULL || str[i - 1] == '(') {
          *list = push(*list, atof(str + i), 0, un_plus);
          i = i + 1;
          i = counter(str, i);
        } else {
          *list = push(*list, 0.0, 1, plus);
        }
      }
      if (str[i] == '-') {
        if (*list == NULL || str[i - 1] == '(') {
          if (*list == NULL) {
            *list = push(*list, (atof(str + i)), 0, un_minus);
          } else {
            *list = push(*list, atof(str + i), 0, un_minus);
          }
          i = i + 1;
          i = counter(str, i);
        } else {
          *list = push(*list, 0.0, 1, minus);
        }
      }
      if (str[i] == '*') *list = push(*list, 0.0, 2, mul);
      if (str[i] == '/') *list = push(*list, 0.0, 2, division);
      if (str[i] == '(') *list = push(*list, 0.0, 0, bracket_o);
      if (str[i] == ')') *list = push(*list, 0.0, 0, bracket_c);
      if (str[i] == '%') *list = push(*list, 0.0, 2, div_mod);
      if (str[i] == '^') *list = push(*list, 0.0, 3, power);
    }

    i = calc_fun(str, list, x, i);
    i++;
  }
  return (ret);
}

//  польская нотация
smart *polish_notation(smart *lec) {
  smart *queue = NULL;
  smart *stack = NULL;
  while (lec) {
    if (lec->type == num || lec->type == un_plus ||
        lec->type == un_minus) {  //  Число
      queue = push(queue, lec->value, lec->priority, lec->type);
    } else if (lec->type == bracket_o ||
               lec->priority == 4) {  //  Функция и скобки
      stack = pushstack(stack, lec->value, lec->priority, lec->type);
    } else if (lec->type == bracket_c) {  //  Скобки
      while (stack && stack->type != bracket_o) {
        queue = push(queue, stack->value, stack->priority, stack->type);
        pop(&stack);
      }
      pop(&stack);
    } else if (stack != NULL &&
               stack->priority > lec->priority) {  //  операторы
      queue = push(queue, stack->value, stack->priority, stack->type);
      pop(&stack);
      stack = pushstack(stack, lec->value, lec->priority, lec->type);  //  push
    } else if (stack != NULL && stack->priority == lec->priority) {
      queue = push(queue, stack->value, stack->priority, stack->type);
      pop(&stack);
      stack = pushstack(stack, lec->value, lec->priority, lec->type);  //  push
    } else {
      stack = pushstack(stack, lec->value, lec->priority, lec->type);
    }
    lec = lec->next;
  }
  while (stack) {
    queue = push(queue, stack->value, stack->priority, stack->type);
    smart *tmp = stack;
    stack = stack->next;
    free(tmp);
  }
  clean_pop(&stack);
  return (queue);
}

// результат
double processing_expression(smart *queue, double *res) {
  smart *stack = NULL;
  double tmp = 0.0;
  while (queue) {
    if (queue->type == num || queue->type == 19 || queue->type == 20)
      stack = pushstack(stack, queue->value, queue->priority, queue->type);
    if (queue->type >= 2 && queue->type <= 7) {
      if (queue->type == plus) tmp = stack->next->value + stack->value;
      if (queue->type == minus) tmp = stack->next->value - stack->value;
      if (queue->type == mul) tmp = stack->next->value * stack->value;
      if (queue->type == division) tmp = stack->next->value / stack->value;
      if (queue->type == div_mod) tmp = fmod(stack->next->value, stack->value);
      if (queue->type == power) tmp = pow(stack->next->value, stack->value);
      pop(&stack);
      pop(&stack);
      stack = pushstack(stack, tmp, 0, num);
      tmp = 0;
    }

    if (queue->type >= 10 && queue->type <= 18) {
      if (queue->type == cosinus) tmp = cos(stack->value);
      if (queue->type == sinus) tmp = sin(stack->value);
      if (queue->type == tangens) tmp = tan(stack->value);
      if (queue->type == arccos) tmp = acos(stack->value);
      if (queue->type == arcsin) tmp = asin(stack->value);
      if (queue->type == arctan) tmp = atan(stack->value);
      if (queue->type == sq) tmp = sqrt(stack->value);
      if (queue->type == ln) tmp = log(stack->value);
      if (queue->type == log_x) tmp = log10(stack->value);
      pop(&stack);
      stack = pushstack(stack, tmp, 0, num);
      tmp = 0;
    }
    queue = queue->next;
  }
  *res = stack->value;
  clean_pop(&stack);
  return (0);
}

int counter(char *str, int i) {
  while ((str[i] >= '0' && str[i] <= '9') || str[i] == '.') {
    i = i + 1;
  }
  return (i);
}

int priority_type(smart *tmp, int priority, int count) {
  while (tmp) {
    if (tmp->priority > priority) {
      printf("%d", count);
      count = count + 1;
    }
    tmp = tmp->next;
  }
  return count;
}

void clean_pop(smart **head) {
  while (*head) {
    if (head) {
      if (*head) {
        smart *tmp = (*head);
        *head = (*head)->next;
        free(tmp);
      }
    }
  }
}

smart *push(smart *head, double data, int priority, int type) {
  smart *tmp = (smart *)calloc(1, sizeof(smart));
  tmp->value = data;
  tmp->priority = priority;
  tmp->type = type;
  if (head == NULL && tmp) {
    tmp->next = NULL;
    (head) = tmp;
  } else if (tmp) {
    smart *last = head;
    while (last->next) {
      last = last->next;
    }
    last->next = tmp;
    tmp->next = NULL;
  }
  return head;
}

smart *pushstack(smart *head, double data, int priority, int type) {
  smart *tmp = (smart *)calloc(1, sizeof(smart));
  tmp->value = data;
  tmp->priority = priority;
  tmp->type = type;
  if (head && tmp) {
    tmp->next = (head);
  } else {
    tmp->next = NULL;
  }
  return tmp;
}

void pop(smart **head) {
  if (head) {
    if (*head) {
      smart *tmp = (*head);
      *head = (*head)->next;
      free(tmp);
    }
  }
}

void print_linked_list(smart *head) {
  smart *tmp = head;

  if (tmp) {
    while (tmp) {
      printf("value = %lf\n", tmp->value);
      printf("priority = %d\n", tmp->priority);
      printf("type = %d\n", tmp->type);
      printf("\n");
      tmp = tmp->next;
    }
  }
}

// int main () {
//    char str[256] = "1.1+1";
//    double x = 1.0;
//    double result = 0.0;
//    terminal(str, x, &result);
//    //smart *list = NULL;
//   printf("%lf", result);
//    //print_linked_list(list);
//    return 0;
// }
