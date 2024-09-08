#ifndef CREDITCALC_H
#define CREDITCALC_H

#include <QWidget>

namespace Ui {
class CreditCalc;
}

class CreditCalc : public QWidget {
  Q_OBJECT

 public:
  explicit CreditCalc(QWidget *parent = nullptr);
  ~CreditCalc();

 signals:
  void firstWindow();

 private slots:
  void on_pushButton_back_clicked();
  void on_pushButton_reset_clicked();
  void on_pushButton_calc_clicked();

 private:
  Ui::CreditCalc *ui;
};

#endif  // CREDITCALC_H
