#include "addremitemwidget.h"

#include "ui_addremitemwidget.h"

AddRemItemWidget::AddRemItemWidget(QWidget* parent)
    : QDialog(parent), ui(new Ui::AddRemItemWidget) {
  ui->setupUi(this);

  addClicked = false;

  connect(ui->addBtn, SIGNAL(clicked()), this, SLOT(add_btn_clicked()));
}

AddRemItemWidget::~AddRemItemWidget() { delete ui; }

AddRemItem AddRemItemWidget::show_item(bool& ok) {
  this->exec();

  bool isMonthOk = false;
  bool isSumOk = false;

  int month = ui->monthEdit->text().toInt(&isMonthOk);
  double sum = ui->sumEdit->text().toDouble(&isSumOk);

  ok = addClicked && isMonthOk && isSumOk;

  AddRemItem res;
  res.month = month;
  res.sum = sum;
  return res;
}

void AddRemItemWidget::add_btn_clicked() {
  addClicked = true;
  close();
}
