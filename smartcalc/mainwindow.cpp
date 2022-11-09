#include "mainwindow.h"

#include "ui_mainwindow.h"

// double num_first;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(digits_number()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(digits_number()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(digits_number()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(digits_number()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(digits_number()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(digits_number()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(digits_number()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(digits_number()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(digits_number()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(digits_number()));
  connect(ui->pushButton_min_plus, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(math_operations()));
  connect(ui->pushButton_minus, SIGNAL(clicked()), this,
          SLOT(math_operations()));
  connect(ui->pushButton_plus, SIGNAL(clicked()), this,
          SLOT(math_operations()));
  connect(ui->pushButton_mul, SIGNAL(clicked()), this, SLOT(math_operations()));

  connect(ui->pushButton_minX, SIGNAL(clicked()), this,
          SLOT(on_pushButton_minX_clicked()));
  connect(ui->pushButton_maxX, SIGNAL(clicked()), this,
          SLOT(on_pushButton_maxX_clicked()));
}

MainWindow::~MainWindow() { delete ui; }

// Числа
void MainWindow::digits_number() {
  std::cout << "test2";
  QPushButton *button = (QPushButton *)sender();
  ui->label_show->setText((ui->label_show->text() + button->text()));
}

// Точка
void MainWindow::on_pushButton_dot_clicked() {
  ui->label_show->setText(ui->label_show->text() + ".");
}

// X
void MainWindow::operations() {
  ui->label_show_x->setText((QString::number(0)));
}

// Операции +,-,*,/
void MainWindow::math_operations() {
  QPushButton *button = (QPushButton *)sender();
  ui->label_show->setText((ui->label_show->text() + button->text()));
}

// AC
void MainWindow::on_pushButton_AC_clicked() { ui->label_show->clear(); }

// Равно
void MainWindow::on_pushButton_equal_clicked() {
  double x = 0.0;
  x = ui->label_show_x->text().toDouble();

  double result = 0.0;

  if (ui->label_show->text().contains('x') &&
      !(ui->label_show_x->text().toDouble(NULL))) {
    bool ok;
    x = QInputDialog::getDouble(this, tr("Введите значение Х"), tr("Х = "), 0.0,
                                -MAXFLOAT, MAXFLOAT, 8, &ok);
    std::cout << x << std::endl;
  }

  // QString x = ui->label_show_x->text();
  QString str = ui->label_show->text();
  int err = terminal((char *)str.toStdString().c_str(), x, &result);
  if (err != 0) {
    std::cout << err;
    //        ui->label_show->setText("Error");
    ui->label_show->setText("err");
  } else {
    ui->label_show->setText((QString::number(result)));
  }
}

void MainWindow::on_pushButton_PushButton_clicked() {
  ui->widget->clearGraphs();
  ui->widget->replot();

  QString str = ui->label_show->text();

  if (!str.isEmpty()) {
    h = 0.1;
    xBegin = ui->label_show_minX->text().toDouble();
    xEnd = ui->label_show_maxX->text().toDouble();
    //        char *expression = (char *)str.toStdString().c_str();
    double y_min = 0;
    double y_max = 0;

    for (X = xBegin; X <= xEnd; X += h) {
      x.push_back(X);
      terminal((char *)str.toStdString().c_str(), X, &Y);
      if (Y < y_min) {
        y_min = Y * 1.1;
      }
      if (Y > y_max) {
        y_max = Y * 1.1;
      }
      y.push_back(Y);
      // std::cout << Y << std::endl;
    }

    if (xBegin < xEnd) {
      ui->widget->xAxis->setRange(xBegin, xEnd);
      ui->widget->yAxis->setRange(y_min, y_max);
    } else {
      ui->widget->xAxis->setRange(xEnd, xBegin);
      ui->widget->yAxis->setRange(y_min, y_max);
    }

    ui->widget->addGraph();
    ui->widget->graph(0)->addData(x, y);
    ui->widget->replot();
    x.clear();
    y.clear();
  } else {
    ui->label_show->setText("err");
    // error
  }
}

void MainWindow::on_pushButton_maxX_clicked() {
  ui->label_show_maxX->setText((QString::number(0)));
}

void MainWindow::on_pushButton_minX_clicked() {
  ui->label_show_minX->setText((QString::number(0)));
}

void MainWindow::on_pushButton_credit_clicked() {
  credit.show();
  // this->close();
}

void MainWindow::on_pushButton_deposit_clicked() {
  deposit.show();
  // this->close();
}
