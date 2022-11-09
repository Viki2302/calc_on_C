#ifndef SRC_S21_SMARTCALC_H_
#define SRC_S21_SMARTCALC_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define is_number(ch) 0 <= ch &&ch >= 9
#define is_operator(ch)                                            \
  ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%' || \
      ch == '^' || ch == '(' || ch == ')'
#define is_function(ch) \
  ch == 'c' || ch == 's' || ch == 't' || ch == 'a' || ch == 'l' || ch == 'x'

#define is_brackets(ch) ch == '(' || ch == ')'

typedef struct smartcalc {
  double value;
  int priority;
  int type;
  struct smartcalc *next;
} smart;

typedef enum Type {
  num,
  x_value,
  plus,
  minus,
  mul,
  division,
  div_mod,
  power,
  bracket_o,
  bracket_c,
  cosinus,
  sinus,
  tangens,
  arccos,
  arcsin,
  arctan,
  sq,
  ln,
  log_x,
  un_minus,
  un_plus,
} t_type;

smart *push(smart *head, double data, int priority, int type);
int terminal(char *str, double x, double *result);
int parser(char *str, smart **list, double x);
smart *polish_notation(smart *lec);
void pop(smart **head);
void print_linked_list(smart *head);
smart *pushstack(smart *head, double data, int priority, int type);
double processing_expression(smart *queue, double *res);
int counter(char *str, int i);
int check_list(char *str);
void clean_pop(smart **head);
int calc_fun(char *str, smart **list, double x, int i);
int check_list_2(char *str, int ret, int len_str, int i);

#endif  // SRC_S21_SMARTCALC_H_
