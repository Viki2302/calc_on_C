#ifndef CREDIT_H
#define CREDIT_H

#include <QWidget>

//#ifdef __cplusplus
extern "C" {
//#endif
#include "../s21_credit.h"
//#ifdef __cplusplus
}
//#endif

namespace Ui {
class credit;
}

class credit : public QWidget {
  Q_OBJECT

 signals:
  void mainwindow();

 public:
  explicit credit(QWidget *parent = nullptr);
  ~credit();

 private slots:
  void on_pushButton_AC_clicked();

  void on_pushButton_2_clicked();

 private:
  Ui::credit *ui;
};

#endif  // CREDIT_H
