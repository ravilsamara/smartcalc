#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  sWindow = new Graph();
  connect(sWindow, &Graph::firstWindow, this, &MainWindow::show);
  tWindow = new CreditCalc();
  connect(tWindow, &CreditCalc::firstWindow, this, &MainWindow::show);

  connect(ui->n0_Btn, SIGNAL(clicked()), this, SLOT(digits_input()));
  connect(ui->n1_Btn, SIGNAL(clicked()), this, SLOT(digits_input()));
  connect(ui->n2_Btn, SIGNAL(clicked()), this, SLOT(digits_input()));
  connect(ui->n3_Btn, SIGNAL(clicked()), this, SLOT(digits_input()));
  connect(ui->n4_Btn, SIGNAL(clicked()), this, SLOT(digits_input()));
  connect(ui->n5_Btn, SIGNAL(clicked()), this, SLOT(digits_input()));
  connect(ui->n6_Btn, SIGNAL(clicked()), this, SLOT(digits_input()));
  connect(ui->n7_Btn, SIGNAL(clicked()), this, SLOT(digits_input()));
  connect(ui->n8_Btn, SIGNAL(clicked()), this, SLOT(digits_input()));
  connect(ui->n9_Btn, SIGNAL(clicked()), this, SLOT(digits_input()));

  connect(ui->mul_Btn, SIGNAL(clicked()), this, SLOT(digits_input()));
  connect(ui->div_Btn, SIGNAL(clicked()), this, SLOT(digits_input()));
  connect(ui->plus_Btn, SIGNAL(clicked()), this, SLOT(digits_input()));
  connect(ui->minus_Btn, SIGNAL(clicked()), this, SLOT(digits_input()));

  connect(ui->ac_Btn, SIGNAL(clicked()), this,
          SLOT(on_pushButtonResetClicked()));

  connect(ui->dot_Btn, SIGNAL(clicked()), this, SLOT(digits_input()));
  connect(ui->open_Bkt_Btn, SIGNAL(clicked()), this, SLOT(digits_input()));
  connect(ui->close_Bkt_Btn, SIGNAL(clicked()), this, SLOT(digits_input()));

  connect(ui->sin_Btn, SIGNAL(clicked()), this, SLOT(digits_input()));
  connect(ui->cos_Btn, SIGNAL(clicked()), this, SLOT(digits_input()));
  connect(ui->tan_Btn, SIGNAL(clicked()), this, SLOT(digits_input()));
  connect(ui->acos_Btn, SIGNAL(clicked()), this, SLOT(digits_input()));
  connect(ui->asin_Btn, SIGNAL(clicked()), this, SLOT(digits_input()));
  connect(ui->atan_Btn, SIGNAL(clicked()), this, SLOT(digits_input()));
  connect(ui->ln_Btn, SIGNAL(clicked()), this, SLOT(digits_input()));
  connect(ui->log_Btn, SIGNAL(clicked()), this, SLOT(digits_input()));
  connect(ui->pow_Btn, SIGNAL(clicked()), this, SLOT(digits_input()));
  connect(ui->mod_Btn, SIGNAL(clicked()), this, SLOT(digits_input()));
  connect(ui->sqrt_Btn, SIGNAL(clicked()), this, SLOT(digits_input()));

  connect(ui->X_Btn, SIGNAL(clicked()), this, SLOT(digits_input()));

  connect(ui->compute_Btn, SIGNAL(clicked()), this,
          SLOT(on_pushButtonResultClicked()));
  connect(ui->draw_Btn, SIGNAL(clicked()), this,
          SLOT(on_pushButtonGRAPHClicked()));
  connect(ui->pushButton_CREDIT, SIGNAL(clicked()), this,
          SLOT(on_pushButton_CREDIT_clicked()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::digits_input() {
  QPushButton *button = (QPushButton *)sender();
  QString input_text = button->text();
  if (ui->editCalc->text() == "0" && input_text != ".") {
    ui->editCalc->setText(input_text);
  } else {
    ui->editCalc->setText(ui->editCalc->text() + input_text);
  }
  if (input_text == "sqrt" || input_text == "cos" || input_text == "sin" ||
      input_text == "tan" || input_text == "acos" || input_text == "asin" ||
      input_text == "atan" || input_text == "log" || input_text == "ln") {
    ui->editCalc->setText(ui->editCalc->text() + "(");
  }
  if (input_text == "<") {
    on_pushButton_delete_clicked();
  }
}

void MainWindow::on_pushButtonResetClicked() {
  ui->editCalc->setText("0");
  ui->editX->setText("0");
}
void MainWindow::on_pushButtonResultClicked() {
  int err = 0;
  double result = 0.0;
  QString result_string;
  QString screen_result = ui->editCalc->text();
  QByteArray mass_chars = screen_result.toLocal8Bit();
  char *ptr_mass_chars = mass_chars.data();
  bool ok1;
  double x = ui->editX->text().toDouble(&ok1);
  err = s21_from_qt_calculator(ptr_mass_chars, x, &result);

  switch (err) {
    case OK: {
      QString result_string = QString::number(result, 'g', 15);
      ui->editCalc->setText(result_string);
      break;
    }
    case INVALID_MATH_E:
      ui->editCalc->setText("Некорректное выражение");
      break;
    case EMPTY_MATH_E:
      ui->editCalc->setText("Пустая строка");
      break;
    case MORE_THAN_255:
      ui->editCalc->setText("Выражение превышает 255 символов");
      break;
    case DIVISION_BY_ZERO:
      ui->editCalc->setText("Деление на ноль");
      break;
    case STACK_OVERFLOW:
      ui->editCalc->setText("STACK_OVERFLOW во время работы стека");
      break;

    case STACK_UNDERFLOW:
      ui->editCalc->setText("STACK_UNDERFLOW во время работы стека");
      break;

    case DIGIT_INVALID_CONVERTATION:
      ui->editCalc->setText(
          "Ошибка при конвертации: DIGIT_INVALID_CONVERTATION");
      break;

    case CONVERT_WORD_FUNCTION_ERR:
      ui->editCalc->setText(
          "Ошибка при конвертации: CONVERT_WORD_FUNCTION_ERR");
      break;

    case MISMATCHED_PARENTHESES:
      ui->editCalc->setText("Ошибка при RPN: MISMATCHED_PARENTHESES");
      break;

    case UNKNOWN_LEXEMA:
      ui->editCalc->setText("Ошибка при RPN: UNKNOWN_LEXEMA");
      break;

    case INVALID_EXPRESSION:
      ui->editCalc->setText("Ошибка при калькуляции: INVALID_EXPRESSION");
      break;
    default:
      ui->editCalc->setText("ERROR");
      break;
  }
}

void MainWindow::on_pushButton_delete_clicked() {
  QString screen_result = ui->editCalc->text();
  screen_result.chop(1);
  ui->editCalc->setText(screen_result);
}

void MainWindow::on_pushButtonGRAPHClicked() {
  sWindow->show();
  this->close();
}

void MainWindow::on_pushButton_CREDIT_clicked() {
  tWindow->show();
  this->close();
}


