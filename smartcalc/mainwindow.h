#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <credit.h>
#include <deposit.h>

#include <QMainWindow>
#include <QVector>
#include <QtMath>
#include <iostream>

#ifdef __cplusplus
extern "C" {
#endif
#include "../s21_smartcalc.h"
#ifdef __cplusplus
}
#endif

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow *ui;
  double xBegin, xEnd, h;
  int N;
  int count;
  double X = 0.0;
  double Y = 0.0;
  credit credit;
  deposit deposit;

  QVector<double> x, y;

 private slots:
  void digits_number();
  void on_pushButton_dot_clicked();
  void operations();
  void on_pushButton_AC_clicked();
  void on_pushButton_equal_clicked();
  void math_operations();
  void on_pushButton_PushButton_clicked();
  void on_pushButton_maxX_clicked();
  void on_pushButton_minX_clicked();
  //    void on_pushButton_div_clicked();
  void on_pushButton_credit_clicked();
  void on_pushButton_deposit_clicked();
};
#endif  // MAINWINDOW_H
