#ifndef SRC_S21_DEPOSIT_H_
#define SRC_S21_DEPOSIT_H_

#include <math.h>
#include <stdio.h>
#include <string.h>

typedef struct list {
  int day;
  int month;
  int year;
  double money;
} list;

void smart_deposit(double sum, int period, double procent, double nalog_procent,
                   int period_pay, int capitalis, list *add_list,
                   list *sub_list, list *start_data, double *result_procent,
                   double *nalog_sum, double *mutual_sum, int size_add,
                   int size_sub);

#endif  // SRC_S21_DEPOSIT_H_
