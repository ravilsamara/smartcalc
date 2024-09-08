#include "depositcalc.h"

#include <QDateTime>

#include "ui_depositcalc.h"

DepositCalc::DepositCalc(QWidget* parent)
    : QWidget(parent), ui(new Ui::DepositCalc) {
  ui->setupUi(this);

  addsItems = QList<AddRemItem>();
  remsItems = QList<AddRemItem>();

  connect(ui->pushButton_add_sum, SIGNAL(clicked()), this,
          SLOT(add_adds_btn_clicked()));
  connect(ui->pushButton_delete_sum, SIGNAL(clicked()), this,
          SLOT(add_rems_btn_clicked()));
  connect(ui->removeSelectedBtnAdd, SIGNAL(clicked()), this,
          SLOT(remove_selected_btn_add_clicked()));
  connect(ui->removeSelectedBtnRem, SIGNAL(clicked()), this,
          SLOT(remove_selected_btn_rem_clicked()));
  connect(ui->pushButton_calculate, SIGNAL(clicked()), this,
          SLOT(on_pushButton_calculate_clicked()));
}

DepositCalc::~DepositCalc() { delete ui; }

void DepositCalc::add_adds_btn_clicked() {
  bool isOk = false;

  AddRemItemWidget* newItem = new AddRemItemWidget(this);
  auto item = newItem->show_item(isOk);

  if (isOk) {
    addsItems.push_back(item);
    ui->listWidget_add->addItem(
        "Через " + QString::number(item.month) +
        " месяцев. Сумма: " + QString::number(item.sum));
  }
}

void DepositCalc::add_rems_btn_clicked() {
  bool isOk = false;

  AddRemItemWidget* newItem = new AddRemItemWidget(this);
  auto item = newItem->show_item(isOk);
  item.sum *= -1;

  if (isOk) {
    remsItems.push_back(item);
    ui->listWidget_revome->addItem(
        "Через " + QString::number(item.month) +
        " месяцев. Сумма: " + QString::number(item.sum));
  }
}

void DepositCalc::remove_selected_btn_add_clicked() {
  auto adds = ui->listWidget_add->selectedItems();

  for (auto addItem : adds) {
    addsItems.removeAt(ui->listWidget_add->row(addItem));
    delete addItem;
  }
}

void DepositCalc::remove_selected_btn_rem_clicked() {
  auto rems = ui->listWidget_revome->selectedItems();

  for (auto remItem : rems) {
    remsItems.removeAt(ui->listWidget_revome->row(remItem));
    delete remItem;
  }
}

double DepositCalc::get_adds_by_month(int month, int current_month) {
  double addsSum = 0.0;
  double remsSum = 0.0;

  for (auto addItem : addsItems) {
    if (addItem.month + current_month == month) addsSum += addItem.sum;
  }

  for (auto remItem : remsItems) {
    if (remItem.month + current_month == month) remsSum += remItem.sum;
  }

  return addsSum + remsSum;
}

void DepositCalc::on_pushButton_reset_clicked() {
  ui->lineEdit_sum->setText("0");
  ui->lineEdit_srok->setText("0");
  ui->lineEdit_procent->setText("0");
  ui->sum_end->setText("0");
  ui->sum_proc->setText("0");
  ui->sum_tax->setText("0");
  ui->lineEdit_tax->setText("13");
}

void DepositCalc::on_pushButton_back_clicked() {
  this->close();
  emit firstWindow();
}

void DepositCalc::calculateMonthlyInterest(double& sum, int time, double per,
                                           double& proc_sum,
                                           double& proc_sum_temp,
                                           double& tax_sum, double sum_no_tax,
                                           double tax_per, int current_month) {
  double sum_temp = sum;

  for (int i = current_month; i < time; i++) {
    sum_temp = sum_temp + get_adds_by_month(i, current_month);
    sum = sum + get_adds_by_month(i, current_month);
    double sum_per_month = sum_temp * (per / 100) / 365 * 30.4;
    sum_temp = sum_temp + sum_per_month;
    proc_sum = proc_sum + sum_per_month;
    proc_sum_temp = proc_sum_temp + sum_per_month;

    if (i % 12 == 0) {
      if (proc_sum_temp > sum_no_tax) {
        tax_sum = tax_sum + (proc_sum_temp - sum_no_tax) * tax_per;
        proc_sum_temp = 0;
      }
    }
  }

  if (proc_sum_temp > sum_no_tax) {
    tax_sum = tax_sum + (proc_sum_temp - sum_no_tax) * tax_per;
  }
}

void DepositCalc::calculateYearInterest(double& sum, int time, double per,
                                        double& proc_sum, double& proc_sum_temp,
                                        double& tax_sum, double sum_no_tax,
                                        double tax_per, int current_month) {
  if (time <= 12) {
    for (int i = current_month; i < time; i++) {
      sum = sum + get_adds_by_month(i, current_month);
    }
    calculateWithoutOptions(sum, time, per, proc_sum, tax_sum, sum_no_tax,
                            tax_per);
  } else {
    time = time + current_month;
    int time_tmp = time;
    double sum_temp = sum;
    for (int i = current_month; i < time; i++) {
      sum_temp = sum_temp + get_adds_by_month(i, current_month);
      sum = sum + get_adds_by_month(i, current_month);
      if (i % 12 == 0) {
        double sum_per_yaer =
            sum_temp * (per / 100) / 365.25 * 12 / 12 * 365.25;
        sum_temp = sum_temp + sum_per_yaer;
        proc_sum = proc_sum + sum_per_yaer;
        proc_sum_temp = proc_sum_temp + sum_per_yaer;
        time_tmp = time_tmp - 12;
        if (proc_sum_temp > sum_no_tax && time_tmp > 12) {
          tax_sum = tax_sum + (proc_sum_temp - sum_no_tax) * tax_per;
          proc_sum_temp = 0;
        }

      } else if (time_tmp != 0 && time_tmp < 12) {
        time_tmp = time_tmp - current_month;
        double proc_sum_temp_temp = 0;
        double tax_sum_temp;
        calculateWithoutOptions(sum_temp, time_tmp, per, proc_sum_temp_temp,
                                tax_sum_temp, sum_no_tax, tax_per);
        proc_sum = proc_sum + proc_sum_temp_temp;
        proc_sum_temp = proc_sum_temp + proc_sum_temp_temp;
        i = time;
      }
    }
    if (proc_sum_temp > sum_no_tax) {
      tax_sum = tax_sum + (proc_sum_temp - sum_no_tax) * tax_per;
    }
  }
}

void DepositCalc::calculateDefault(double& sum, int time, double per,
                                   double& proc_sum, double& proc_sum_temp,
                                   double& tax_sum, double sum_no_tax,
                                   double tax_per, int current_month) {
  int time_tmp = time;
  double sum_temp = sum;
  int real_month_count = 0;
  for (int i = current_month; i < time; i++) {
    sum_temp = sum_temp + get_adds_by_month(i, current_month);
    sum = sum + get_adds_by_month(i, current_month);
    real_month_count++;
    if (i % 12 == 0) {
      double sum_per_yaer =
          sum_temp * (per / 100) / 365.25 * real_month_count / 12 * 365.25;
      proc_sum = proc_sum + sum_per_yaer;
      proc_sum_temp = proc_sum_temp + sum_per_yaer;
      time_tmp = time_tmp - 12;
      if (proc_sum_temp > sum_no_tax) {
        tax_sum = tax_sum + (proc_sum_temp - sum_no_tax) * tax_per;
        proc_sum_temp = 0;
        real_month_count = 0;
      }
    } else if (time_tmp != 0 && time_tmp < 12) {
      time_tmp = time_tmp - 1;
      double proc_sum_temp_temp = 0;
      double tax_sum_temp;
      calculateWithoutOptions(sum_temp, time_tmp, per, proc_sum_temp_temp,
                              tax_sum_temp, sum_no_tax, tax_per);
      proc_sum = proc_sum + proc_sum_temp_temp;
      proc_sum_temp = proc_sum_temp + proc_sum_temp_temp;
      if (proc_sum_temp_temp > sum_no_tax) {
        tax_sum = tax_sum + (proc_sum_temp_temp - sum_no_tax) * tax_per;
      }
      i = time;
    }
  }
}

void DepositCalc::calculateWithoutOptions(double& sum, int time, double per,
                                          double& proc_sum, double& tax_sum,
                                          double sum_no_tax, double tax_per) {
  proc_sum = sum * (per / 100) / 365.25 * time / 12 * 365.25;
  if (proc_sum > sum_no_tax) {
    tax_sum = (proc_sum - sum_no_tax) * tax_per;
  }
}

int DepositCalc::getCurrentMonth() {
  // Получение текущего времени
  auto currentTime = std::chrono::system_clock::now();

  // Преобразование времени в структуру tm
  std::time_t time = std::chrono::system_clock::to_time_t(currentTime);
  std::tm* localTime = std::localtime(&time);

  // Получение текущего месяца
  int currentMonth = localTime->tm_mon +
                     1;  // tm_mon - месяцы считаются с 0, поэтому добавляем 1

  return currentMonth;
}

void DepositCalc::on_pushButton_calculate_clicked() {
  bool ok1, ok2, ok3, ok4;
  double sum = ui->lineEdit_sum->text().toDouble(&ok1);
  int time = ui->lineEdit_srok->text().toInt(&ok2);
  double per = ui->lineEdit_procent->text().toDouble(&ok3);
  double tax_per = ui->lineEdit_tax->text().toDouble(&ok4);
  int current_month = getCurrentMonth();
  current_month++;
  if (ui->radioButton_year->isChecked()) time *= 12;
  tax_per = tax_per / 100;

  if (ok1 && ok2 && ok3 && ok4 && time > 0 && per >= 0.01) {
    double tax_sum = 0;
    double proc_sum = 0;
    double proc_sum_temp = 0;
    double sum_no_tax = NO_TAX;
    if (ui->checkBox_kap_proc->isChecked()) {
      if (ui->radioButton_permonth->isChecked()) {
        time = time + current_month;
        calculateMonthlyInterest(sum, time, per, proc_sum, proc_sum_temp,
                                 tax_sum, sum_no_tax, tax_per, current_month);
      } else if (ui->radioButton_peryear->isChecked()) {
        calculateYearInterest(sum, time, per, proc_sum, proc_sum_temp, tax_sum,
                              sum_no_tax, tax_per, current_month);
      }

    } else {
      time = time + current_month;
      if (time <= 12) {
        for (int i = current_month; i < time; i++) {
          sum = sum + get_adds_by_month(i, current_month);
        }
        calculateWithoutOptions(sum, time, per, proc_sum, tax_sum, sum_no_tax,
                                tax_per);
      } else {
        calculateDefault(sum, time, per, proc_sum, proc_sum_temp, tax_sum,
                         sum_no_tax, tax_per, current_month);
      }
    }
    sum = sum + proc_sum;

    ui->sum_proc->setText(QString::number(proc_sum, 'f', 2));
    ui->sum_end->setText(QString::number(sum, 'f', 2));
    ui->sum_tax->setText(QString::number(tax_sum, 'f', 2));
    ui->sum_minus_tax->setText(QString::number(proc_sum - tax_sum, 'f', 2));
  } else {
    ui->sum_proc->setText("Ошибка");
    ui->sum_tax->setText("вводите");
    ui->sum_end->setText("только цифры");
  }
}
