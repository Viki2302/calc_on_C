#include "s21_deposit.h"

int days_in_month(int month) {
  int days = 0;
  if (month == 2) {
    days = 28;
  } else if (month == 4 || month == 6 || month == 9 || month == 11) {
    days = 30;
  } else {
    days = 31;
  }
  return days;
}

void without_capitalisation(double sum, int period, double procent,
                            double nalog_procent, list *add_list,
                            list *sub_list, list *start_data,
                            double *result_procent, double *nalog_sum,
                            double *mutual_sum, int size_add, int size_sub) {
  int index_add = 0, index_sub = 0;
  for (int i = start_data[0].month; i < start_data[0].month + period; i++) {
    double temp = 0;
    int index = i % 12;
    int days_in_year = (start_data[0].year % 4 == 0) ? 366 : 365;
    if (add_list[index_add].month == index && size_add > 0) {
      temp = add_list[index_add].money;
      index_add++;
    }
    if (sub_list[index_sub].month == index && size_sub > 0) {
      temp = -1 * sub_list[index_sub].money;
      index_sub++;
    }
    sum += temp;
    *result_procent += (sum * procent * days_in_month(index)) / days_in_year;
    if (index == 0) start_data[0].year += 1;
  }
  *mutual_sum = *result_procent + sum;
  *nalog_sum = *result_procent * nalog_procent;
}

void with_capitalisation(double sum, int period, double procent,
                         double nalog_procent, int period_pay, int capitalis,
                         list *add_list, list *sub_list, list *start_data,
                         double *result_procent, double *nalog_sum,
                         double *mutual_sum, int size_add, int size_sub) {
  int index_add = 0, index_sub = 0;
  double temp_procent = 0, sum_start = sum;
  double sum_add = 0, sum_sub = 0;
  for (int i = start_data[0].month, count = 0;
       i <= start_data[0].month + period; i++, count++) {
    int days_in_year = (start_data[0].year % 4 == 0) ? 366 : 365;
    int index = i % 12;
    double temp = 0;
    if ((capitalis == 1) || (capitalis == 2 && count == 3) ||
        (capitalis == 3 && count == 12)) {
      sum += round(temp_procent * 100) / 100.;
      temp_procent = 0;
      count = 0;
    }

    if ((period_pay == 1) || (period_pay == 2 && count == 3) ||
        (period_pay == 3 && count == 12)) {
      sum = sum_start;
      count = 0;
    }

    if (add_list[index_add].month == index && size_add > 0) {
      temp += add_list[index_add].money;
      sum_add += add_list[index_add].money;
      index_add++;
    }

    if (sub_list[index_sub].month == index && size_sub > 0) {
      temp -= sub_list[index_sub].money;
      sum_sub += sub_list[index_sub].money;
      index_sub++;
    }
    sum += temp;
    temp_procent += (sum * procent * days_in_month(index)) / days_in_year;
    if (index == 0) start_data[0].year += 1;
  }
  *mutual_sum = sum;
  *result_procent = *mutual_sum - sum_start - sum_add + sum_sub;
  *nalog_sum = *result_procent * nalog_procent;
}

void smart_deposit(double sum, int period, double procent, double nalog_procent,
                   int period_pay, int capitalis, list *add_list,
                   list *sub_list, list *start_data, double *result_procent,
                   double *nalog_sum, double *mutual_sum, int size_add,
                   int size_sub) {
  procent /= 100;
  nalog_procent /= 100;
  if (capitalis == 0) {
    without_capitalisation(sum, period, procent, nalog_procent, add_list,
                           sub_list, start_data, result_procent, nalog_sum,
                           mutual_sum, size_add, size_sub);
  } else {
    with_capitalisation(sum, period, procent, nalog_procent, period_pay,
                        capitalis, add_list, sub_list, start_data,
                        result_procent, nalog_sum, mutual_sum, size_add,
                        size_sub);
  }
}
