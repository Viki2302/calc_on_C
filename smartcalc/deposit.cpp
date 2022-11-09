#include "deposit.h"

#include <QMessageBox>

#include "ui_deposit.h"

deposit::deposit(QWidget* parent) : QWidget(parent), ui(new Ui::deposit) {
  ui->setupUi(this);
  ui->lineEdit->setValidator(new QDoubleValidator(this));
  ui->lineEdit_2->setValidator(new QDoubleValidator(this));
  ui->lineEdit_3->setValidator(new QDoubleValidator(this));
  ui->lineEdit_4->setValidator(new QDoubleValidator(this));
  ui->add->setValidator(new QDoubleValidator(this));
  ui->sub->setValidator(new QDoubleValidator(this));
}

deposit::~deposit() { delete ui; }

void deposit::on_pushButton_AC_clicked() { this->close(); }

void deposit::on_run_clicked() {
  double sum = ui->lineEdit->text().toDouble();
  int period = ui->lineEdit_2->text().toInt();
  period = (ui->month_or_year->currentIndex() == 0) ? period : period * 12;
  double procent = ui->lineEdit_3->text().toDouble();
  double nalog_procent = ui->lineEdit_4->text().toDouble();

  list start_data[1];
  std::string text_start_data = ui->date->text().toStdString() + " 0 руб.";

  int period_pay = ui->period->currentIndex();
  int capitalis = ui->capitalis->currentIndex();

  int size_add = ui->add_list->document()->lineCount();
  size_add = (size_add == 1) ? size_add : size_add - 1;
  int size_sub = ui->sub_list->document()->lineCount();
  size_sub = (size_sub == 1) ? size_sub : size_sub - 1;

  list add[size_add];
  std::string text_add = ui->add_list->toPlainText().toStdString();

  list sub[size_sub];
  std::string text_sub = ui->sub_list->toPlainText().toStdString();

  if (sum <= 0 || period <= 0 || procent <= 0 || nalog_procent < 0) {
    QMessageBox::warning(this, "Error", "Неправильные входные данные");
  } else {
    double result_procent = 0, nalog_sum = 0, mutual_sum = 0;
    smart_deposit(sum, period, procent, nalog_procent, period_pay, capitalis,
                  add, sub, start_data, &result_procent, &nalog_sum,
                  &mutual_sum, size_add, size_sub);

    ui->result_procent->setText(QString::number(result_procent, 'f', 2));
    ui->nalog_sum->setText(QString::number(nalog_sum, 'f', 2));
    ui->mutual_sum->setText(QString::number(mutual_sum, 'f', 2));
  }
}

void deposit::on_add_add_clicked() {
  ui->add_list->insertPlainText(ui->add_date->text() + " " + ui->add->text() +
                                " руб.\n");
}

void del(QTextEdit* list) {
  QTextCursor cursor = list->textCursor();
  cursor.movePosition(QTextCursor::End);
  cursor.select(QTextCursor::LineUnderCursor);
  cursor.removeSelectedText();
  cursor.deletePreviousChar();
  list->setTextCursor(cursor);
}

void deposit::on_del_add_clicked() {
  del(ui->add_list);
  del(ui->add_list);
  if (!(ui->add_list->document()->isEmpty()))
    ui->add_list->insertPlainText("\n");
}

void deposit::on_sub_sub_clicked() {
  ui->sub_list->insertPlainText(ui->sub_date->text() + " " + ui->sub->text() +
                                " руб.\n");
}

void deposit::on_sub_sub_2_clicked() {
  del(ui->sub_list);
  del(ui->sub_list);
  if (!(ui->sub_list->document()->isEmpty()))
    ui->sub_list->insertPlainText("\n");
}
