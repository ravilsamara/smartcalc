#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "creditcalc.h"
#include "graph.h"

extern "C" {
#include "../backend_calc/s21_smartcalc.h"
}

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
  Graph *sWindow;
  CreditCalc *tWindow;

 private slots:
  void digits_input();
  void on_pushButtonResetClicked();
  void on_pushButtonResultClicked();
  void on_pushButton_delete_clicked();
  void on_pushButtonGRAPHClicked();
  void on_pushButton_CREDIT_clicked();
};

#endif  // MAINWINDOW_H
