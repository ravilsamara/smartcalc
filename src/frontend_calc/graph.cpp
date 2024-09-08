#include "graph.h"

#include <QMessageBox>

#include "mainwindow.h"
#include "ui_graph.h"

Graph::Graph(QWidget *parent) : QWidget(parent), ui(new Ui::Graph) {
  ui->setupUi(this);
}

Graph::~Graph() { delete ui; }

void Graph::on_pushButton_clicked() {
  ui->widget->clearGraphs();
  int err = 0;
  double result = 0.0;
  QString screen_result = ui->new_graph->text();
  QByteArray mass_chars = screen_result.toLocal8Bit();
  char *ptr_mass_chars = mass_chars.data();
  xBegin = ui->line_xMin->text().toDouble();
  xEnd = ui->line_xMax->text().toDouble();
  yBegin = xBegin;
  yEnd = xEnd;
  if (xBegin < -1000000.0) xBegin = -1000000.0;
  if (yBegin < -1000000.0) yBegin = -1000000.0;
  if (xEnd > 1000000.0) xEnd = 1000000.0;
  if (yEnd > 1000000.0) yEnd = 1000000.0;
  ui->widget->xAxis->setRange(xBegin, xEnd);
  ui->widget->yAxis->setRange(yBegin, yEnd);
  ui->widget->xAxis->setLabel("x");
  ui->widget->yAxis->setLabel("y");
  accuracy_x(xBegin, xEnd, &step);
  N = (xEnd - xBegin) / step + 2;

  for (X = xBegin; X <= xEnd; X += step) {
    x.push_back(X);
    err = s21_from_qt_calculator(ptr_mass_chars, X, &result);
    if (err == 0 && result >= yBegin && result <= yEnd) {
      y.push_back(result);
    } else {
      y.push_back(NAN);
    }
  }
  ui->widget->addGraph();
  ui->widget->graph(0)->addData(x, y);
  ui->widget->replot();

  ui->widget->setInteraction(QCP::iRangeZoom, true);
  ui->widget->setInteraction(QCP::iRangeDrag, true);

  x.clear();
  y.clear();
}

void Graph::on_pushButton_back_clicked() {
  this->close();
  emit firstWindow();
}

void Graph::accuracy_x(double xBegin, double xEnd, double *step) {
  if (xEnd - xBegin <= 10)
    *step = 0.00001;
  else if (xEnd - xBegin <= 100)
    *step = 0.0001;
  else if (xEnd - xBegin <= 1000)
    *step = 0.001;
  else if (xEnd - xBegin <= 10000)
    *step = 0.01;
  else if (xEnd - xBegin <= 100000)
    *step = 0.1;
  else if (xEnd - xBegin > 100000)
    *step = 0.5;
}
