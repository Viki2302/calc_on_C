#include "credit.h"

#include <QMessageBox>

#include "ui_credit.h"

credit::credit(QWidget *parent) : QWidget(parent), ui(new Ui::credit) {
  ui->setupUi(this);
  ui->lineEdit->setValidator(new QDoubleValidator(this));
  ui->lineEdit_2->setValidator(new QDoubleValidator(this));
  ui->lineEdit_3->setValidator(new QDoubleValidator(this));
}

credit::~credit() { delete ui; }

void credit::on_pushButton_AC_clicked() {
  this->close();
  emit mainwindow();
}

void credit::on_pushButton_2_clicked() {
  ui->textEdit->clear();
  double sum = ui->lineEdit->text().toDouble();
  int data = ui->lineEdit_2->text().toInt();
  double procent = ui->lineEdit_3->text().toDouble();

  int type = ui->radioButton->isChecked() ? 1 : 2;
  data = (ui->comboBox->currentIndex() == 0) ? data : data * 12;

  double mutualpay = 0.0, overpay = 0.0, every_month[data];

  if (sum <= 0 || data <= 0 || procent <= 0) {
    QMessageBox::warning(this, "Error", "Неправильные входные данные");
  } else {
    smart_credit(type, sum, data, procent, &mutualpay, &overpay, every_month);
    ui->lineEdit_6->setText(QString::number(overpay, 'f', 2));
    ui->lineEdit_4->setText(QString::number(mutualpay, 'f', 2));
    ui->textEdit->verticalScrollBar();
    for (int i = 1, j = 0; i <= data; i++, j++) {
      ui->textEdit->insertPlainText("Месяц " + QString::number(i) + ": " +
                                    QString::number(every_month[j], 'f', 2) +
                                    "\n");
      ui->textEdit->textCursor().movePosition(QTextCursor::Start);
    }
  }
}
