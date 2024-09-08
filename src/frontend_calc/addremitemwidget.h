#ifndef ADDREMITEMWIDGET_H
#define ADDREMITEMWIDGET_H

#include <QDialog>
#include <QListWidget>

namespace Ui {
class AddRemItemWidget;
}

struct AddRemItem {
  int month;
  double sum;
};

class AddRemItemWidget : public QDialog {
  Q_OBJECT

 public:
  explicit AddRemItemWidget(QWidget *parent = nullptr);
  ~AddRemItemWidget();

  AddRemItem show_item(bool &ok);

 private:
  Ui::AddRemItemWidget *ui;

  bool addClicked;

 private slots:
  void add_btn_clicked();
};

#endif  // ADDREMITEMWIDGET_H
