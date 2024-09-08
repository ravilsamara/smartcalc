#ifndef DEPOSITCALC_H
#define DEPOSITCALC_H

#include <QWidget>
#include <chrono>
#include <iostream>

#include "addremitemwidget.h"
#define NO_TAX 160000

namespace Ui {
class DepositCalc;
}

class DepositCalc : public QWidget {
  Q_OBJECT

 public:
  explicit DepositCalc(QWidget* parent = nullptr);
  ~DepositCalc();

 signals:
  void firstWindow();

 private slots:
  void on_pushButton_back_clicked();
  void on_pushButton_reset_clicked();
  // void on_pushButton_calc_clicked();

  void on_pushButton_calculate_clicked();
  void calculateMonthlyInterest(double& sum, int time, double per,
                                double& proc_sum, double& proc_sum_temp,
                                double& tax_sum, double sum_no_tax,
                                double tax_per, int current_month);
  void calculateYearInterest(double& sum, int time, double per,
                             double& proc_sum, double& proc_sum_temp,
                             double& tax_sum, double sum_no_tax, double tax_per,
                             int current_month);
  void calculateDefault(double& sum, int time, double per, double& proc_sum,
                        double& proc_sum_temp, double& tax_sum,
                        double sum_no_tax, double tax_per, int current_month);
  void calculateWithoutOptions(double& sum, int time, double per,
                               double& proc_sum, double& tax_sum,
                               double sum_no_tax, double tax_per);
  void add_adds_btn_clicked();
  void add_rems_btn_clicked();
  void remove_selected_btn_add_clicked();
  void remove_selected_btn_rem_clicked();
  double get_adds_by_month(int month, int current_month);
  int getCurrentMonth();

 private:
  Ui::DepositCalc* ui;
  QList<AddRemItem> addsItems;
  QList<AddRemItem> remsItems;
};

#endif  // DEPOSITCALC_H
