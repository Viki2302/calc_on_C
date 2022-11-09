#ifndef DEPOSIT_H
#define DEPOSIT_H

#include <QWidget>

//#ifdef __cplusplus
extern "C" {
//#endif
#include "../s21_deposit.h"
//#ifdef __cplusplus
}
//#endif

namespace Ui {
class deposit;
}

class deposit : public QWidget {
  Q_OBJECT

 signals:
  void mainwindow();

 public:
  explicit deposit(QWidget *parent = nullptr);
  ~deposit();

 private slots:
  void on_pushButton_AC_clicked();

  void on_run_clicked();

  void on_add_add_clicked();

  void on_del_add_clicked();

  void on_sub_sub_clicked();

  void on_sub_sub_2_clicked();

 private:
  Ui::deposit *ui;
};

#endif  // DEPOSIT_H
