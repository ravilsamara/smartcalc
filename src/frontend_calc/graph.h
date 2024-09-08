#ifndef GRAPH_H
#define GRAPH_H

#include <QVector>
#include <QWidget>

namespace Ui {
class Graph;
}

class Graph : public QWidget {
  Q_OBJECT

 public:
  explicit Graph(QWidget *parent = nullptr);
  ~Graph();

 private slots:
  void on_pushButton_clicked();

  void on_pushButton_back_clicked();
  void accuracy_x(double xBegin, double xEnd, double *step);

 signals:
  void firstWindow();

 private:
  Ui::Graph *ui;
  double xBegin, xEnd, step, X;
  double yBegin, yEnd;
  int N;
  QVector<double> x, y;
};

#endif  // GRAPH_H
