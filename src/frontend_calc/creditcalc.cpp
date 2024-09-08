#include "creditcalc.h"

#include <math.h>

#include <QDateTime>

#include "ui_creditcalc.h"

CreditCalc::CreditCalc(QWidget *parent)
    : QWidget(parent), ui(new Ui::CreditCalc) {
  ui->setupUi(this);
}

CreditCalc::~CreditCalc() { delete ui; }

void CreditCalc::on_pushButton_back_clicked() {
  this->close();
  emit firstWindow();
}

void CreditCalc::on_pushButton_calc_clicked() {
  bool ok1, ok2, ok3;
  double sum = ui->line_sum->text().toDouble(&ok1);
  int time = ui->line_time->text().toInt(&ok2);
  double per = ui->line_per->text().toDouble(&ok3);

  if (ui->radioButton_year->isChecked()) time *= 12;

  if (ok1 && ok2 && ok3 && time > 0 && per >= 0.01) {
    if (ui->ann_checkbox->isChecked()) {
      per /= 1200;

      double kmonth_pay =
          per * pow(1.0 + per, time) / (pow(1.0 + per, time) - 1.0);
      double month_pay = round(sum * kmonth_pay * 100) / 100;
      ui->month_pay_label->setText(QString::number(month_pay, 'g', 15));
      double pay_per = month_pay * time;
      ui->proc_label->setText(QString::number(pay_per - sum, 'g', 15));
      ui->pay_label->setText(QString::number(pay_per, 'g', 15));
    } else {
      double month_pay = sum / time;
      double temp = sum;
      double first_month =
          month_pay + round((sum * per / 100 / 12) * 100) / 100;
      double sum_payd = first_month;

      double last_month = 0;
      for (int i = 1; i < time; ++i) {
        sum -= month_pay;
        last_month = round((month_pay + ((sum)*per / 100 / 12)) * 100) / 100;

        sum_payd = round((sum_payd + last_month) * 100) / 100;
      }
      ui->month_pay_label->setText(QString::number(first_month, 'f', 2) +
                                   " ... " +
                                   QString::number(last_month, 'f', 2));
      ui->proc_label->setText(QString::number(sum_payd - temp, 'f', 2));
      ui->pay_label->setText(QString::number(sum_payd, 'f', 2));
    }
  } else {
    ui->month_pay_label->setText("Ошибка");
    ui->proc_label->setText("вводите");
    ui->pay_label->setText("только цифры");
  }
}

void CreditCalc::on_pushButton_reset_clicked() {
  ui->line_sum->setText("0");
  ui->line_per->setText("0");
  ui->line_time->setText("0");
  ui->month_pay_label->setText("0");
  ui->proc_label->setText("0");
  ui->pay_label->setText("0");
}
