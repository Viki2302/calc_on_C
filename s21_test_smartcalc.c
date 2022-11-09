#include <check.h>

#include "s21_smartcalc.h"
#include "s21_credit.h"
#include "s21_deposit.h"

START_TEST(calc_test_plus) {
  double result = 0.0;
  double answer = 1.25 + 3.45;
  char *expr = "1.25+3.45";
  terminal(expr, 0.0, &result);
  ck_assert_float_eq(answer, result);
}
END_TEST

START_TEST(calc_test_minus) {
  double result = 0.0;
  double answer = 0.003 - 15.34;
  char *expr = "0.003-15.34";
  terminal(expr, 0.0, &result);
  ck_assert_float_eq(answer, result);
}
END_TEST

START_TEST(calc_test_mult) {
  double result = 0.0;
  double answer = 0.25 * 5;
  char *expr = "0.25*5";
  terminal(expr, 0.0, &result);
  ck_assert_float_eq(answer, result);
}
END_TEST

START_TEST(calc_test_div) {
  double result = 0.0;
  double answer = 0.2 / 5;
  char *expr = "0.2/5";
  terminal(expr, 0.0, &result);
  ck_assert_float_eq(answer, result);
}
END_TEST

START_TEST(calc_test_mod) {
  double result = 0.0;
  double answer = fmod(60, 3.5);
  char *expr = "60%3.5";
  terminal(expr, 0.0, &result);
  ck_assert_float_eq(answer, result);
}
END_TEST

START_TEST(calc_test_pow) {
  double result = 0.0;
  double answer = pow(5, 3.45);
  char *expr = "5^3.45";
  terminal(expr, 0.0, &result);
  ck_assert_float_eq(answer, result);
}
END_TEST

START_TEST(calc_test_brackets) {
  double result = 0.0;
  double answer = (5.23 + 1.25) * (0.25 + 0.001);
  char *expr = "(5.23+1.25)*(0.25+0.001)";
  terminal(expr, 0.0, &result);
  ck_assert_float_eq(answer, result);
}
END_TEST

START_TEST(calc_test_sin) {
  double result = 0.0;
  double answer = sin(0.3 * 0.6);
  char *expr = "sin(0.3*0.6)";
  terminal(expr, 0.0, &result);
  ck_assert_float_eq(answer, result);
}
END_TEST

START_TEST(calc_test_cos) {
  double result = 0.0;
  double answer = cos(0.6 - 0.1 + 0.2 / 0.5);
  char *expr = "cos(0.6-0.1+0.2/0.5)";
  terminal(expr, 0.0, &result);
  ck_assert_float_eq(answer, result);
}
END_TEST

START_TEST(calc_test_tan) {
  double result = 0.0;
  double answer = tan(0.8 / 2);
  char *expr = "tan(0.8/2)";
  terminal(expr, 0.0, &result);
  ck_assert_float_eq(answer, result);
}
END_TEST

START_TEST(calc_test_sqrt) {
  double result = 0.0;
  double answer = sqrt(97.3456);
  char *expr = "sqrt(97.3456)";
  terminal(expr, 0.0, &result);
  ck_assert_float_eq(answer, result);
}
END_TEST

START_TEST(calc_test_ln) {
  double result = 0.0;
  double answer = log(2.5 + 99);
  char *expr = "ln(2.5+99)";
  terminal(expr, 0.0, &result);
  ck_assert_float_eq(answer, result);
}
END_TEST

START_TEST(calc_test_log) {
  double result = 0.0;
  double answer = log10(1.8 + 256.34);
  char *expr = "log(1.8+256.34)";
  terminal(expr, 0.0, &result);
  ck_assert_float_eq(answer, result);
}
END_TEST

START_TEST(calc_test_asin) {
  double result = 0.0;
  double answer = asin(0.34);
  char *expr = "asin(0.34)";
  terminal(expr, 0.0, &result);
  ck_assert_float_eq(answer, result);
}
END_TEST

START_TEST(calc_test_acos) {
  double result = 0.0;
  double answer = acos(-0.83);
  char *expr = "acos(-0.83)";
  terminal(expr, 0.0, &result);
  ck_assert_float_eq(answer, result);
}
END_TEST

START_TEST(calc_test_atan) {
  double result = 0.0;
  double answer = atan(-0.669);
  char *expr = "atan(-0.669)";
  terminal(expr, 0.0, &result);
  ck_assert_float_eq(answer, result);
}
END_TEST

START_TEST(calc_test_1) {
  double result = 0.0;
  double answer = 0.0;
  char *expr = "1-1";
  terminal(expr, 0.0, &result);
  ck_assert_float_eq(answer, result);
}
END_TEST

START_TEST(calc_test_2) {
  double result = 0.0;
  double answer = 1 - 2 - 3;
  char *expr = "1-2-3";
  terminal(expr, 0.0, &result);
  ck_assert_float_eq(answer, result);
}
END_TEST

START_TEST(calc_test_3) {
  double result = 0.0;
  double answer = 4 * (-5) + 2.01 / sin(0.01);
  char *expr = "4*(-5)+2.01/sin(0.01)";
  terminal(expr, 0.0, &result);
  ck_assert_float_eq(answer, result);
}
END_TEST

START_TEST(calc_test_4) {
  double result = 0.0;
  double answer = sin(0.1);
  char *expr = "sin(0.1)";
  terminal(expr, 0.0, &result);
  ck_assert_float_eq(answer, result);
}
END_TEST

START_TEST(calc_test_5) {
  double result = 0.0;
  double answer = cos(sin(tan(-0.005)));
  char *expr = "cos(sin(tan(-0.005)))";
  terminal(expr, 0.0, &result);
  ck_assert_float_eq(answer, result);
}
END_TEST

START_TEST(calc_test_inf) {
  double result = 0.0;
  double zero = 0.0;
  double answer = 125 / zero;
  char *expr = "125/0";
  terminal(expr, 0.0, &result);
  ck_assert_float_eq(answer, result);
}
END_TEST

START_TEST(calc_test_big) {
  double result = 0.0;
  double answer = log10(32 + 1) * 7 / 11 * 432 * (sin(2) * 12 - 45 + 4) / 2;
  char *expr = "log(32+1)*7/11*432*(sin(2)*12-45+4)/2";
  terminal(expr, 0.0, &result);
  ck_assert_float_eq(answer, result);
}
END_TEST

START_TEST(test_credit) {
    double sum = 1500000;
    int term = 33;
    double percent = 22.3, payment = 0, overpay = 0, fullsum[term];
    int type = 1;
    smart_credit(type, sum, term, percent, &payment, &overpay, fullsum);
    ck_assert_float_eq_tol(payment, 2020130.00, 2);
    ck_assert_float_eq_tol(overpay, 520129.00, 2);
    ck_assert_float_eq_tol(fullsum[term - 1],  61215.94, 2);
}
END_TEST

START_TEST(credit_2) {
    long double sum = 1000000;
    int term = 21;
    double percent = 9.4, payment = 0, overpay = 0, fullsum[term];
    int type = 0;
    smart_credit(type, sum, term, percent, &payment, &overpay, fullsum);
    ck_assert_float_eq_tol(fullsum[0], 55452.0, 1);
    ck_assert_float_eq_tol(fullsum[term - 1], 47381.90, 1);
    ck_assert_float_eq_tol(overpay, 77650.03, 1);
    ck_assert_float_eq_tol(payment, 1077650.03, 1);
}
END_TEST

int main(void) {
  Suite *s1 = suite_create("Core");
  TCase *tc1_1 = tcase_create("Core");
  SRunner *sr = srunner_create(s1);

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, calc_test_plus);
  tcase_add_test(tc1_1, calc_test_minus);
  tcase_add_test(tc1_1, calc_test_mult);
  tcase_add_test(tc1_1, calc_test_div);
  tcase_add_test(tc1_1, calc_test_mod);
  tcase_add_test(tc1_1, calc_test_pow);
  tcase_add_test(tc1_1, calc_test_brackets);
  tcase_add_test(tc1_1, calc_test_sin);
  tcase_add_test(tc1_1, calc_test_cos);
  tcase_add_test(tc1_1, calc_test_tan);
  tcase_add_test(tc1_1, calc_test_sqrt);
  tcase_add_test(tc1_1, calc_test_ln);
  tcase_add_test(tc1_1, calc_test_log);
  tcase_add_test(tc1_1, calc_test_asin);
  tcase_add_test(tc1_1, calc_test_acos);
  tcase_add_test(tc1_1, calc_test_atan);
  tcase_add_test(tc1_1, calc_test_1);
  tcase_add_test(tc1_1, calc_test_2);
  tcase_add_test(tc1_1, calc_test_3);
  tcase_add_test(tc1_1, calc_test_4);
  tcase_add_test(tc1_1, calc_test_5);
  tcase_add_test(tc1_1, calc_test_inf);
  tcase_add_test(tc1_1, calc_test_big);
  tcase_add_test(tc1_1, test_credit);
  tcase_add_test(tc1_1, credit_2);

  srunner_run_all(sr, CK_ENV);
  srunner_ntests_failed(sr);
  srunner_free(sr);

  return (0);
}
