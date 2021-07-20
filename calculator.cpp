#include "calculator.h"
#include "ui_calculator.h"


double CalcVal = 0.0;

bool addTrigger = false;
bool subTrigger = false;
bool mulTrigger = false;
bool divTrigger = false;
bool andTrigger = false;
bool orTrigger = false;
bool norTrigger = false;
bool xorTrigger = false;
bool equalsSignPressedPreviously = false;



Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
{
    ui->setupUi(this);
    ui->Display->setText(QString::number(CalcVal));

    for (size_t i = 0; i < 11; ++i) {
        QPushButton *ptr = Calculator::findChild<QPushButton*>("Button" + QString::number(i));
        connect( ptr, SIGNAL(released()), this, SLOT(NumButtonPressed()));
    }
    connect(ui->ButtonAdd, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->ButtonMul, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->ButtonSub, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->ButtonDiv, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->ButtonEquals, SIGNAL(released()), this, SLOT(EqualsButtonPressed()));
    connect(ui->ButtonClear, SIGNAL(released()), this, SLOT(ClearButtonPressed()));
}

Calculator::~Calculator() {
    delete ui;
}

void Calculator::NumButtonPressed() {
 QPushButton *button = (QPushButton*)sender();
 QString buttonValue = button->text();
 QString displayText = ui->Display->text();

 if (displayText.toDouble() == 0 || displayText.toDouble() == 0.0) {
     ui->Display->setText(buttonValue);
 } else {
     QString newValue = displayText + buttonValue;
     double newValueDouble = newValue.toDouble();

     ui->Display->setText(QString::number(newValueDouble, 'g', 16));
   }
   equalsSignPressedPreviously = false;
}

void Calculator::MathButtonPressed() {
    addTrigger = false;
    subTrigger = false;
    mulTrigger = false;
    divTrigger = false;
    equalsSignPressedPreviously = false;

    CalcVal = ui->Display->text().toDouble();

    QPushButton* button = (QPushButton*)sender();
    if(QString::compare(button->text(), "+", Qt::CaseInsensitive) == 0) {
        addTrigger = true;
        ui->Display->setText("+");
    } else if(QString::compare(button->text(), "-", Qt::CaseInsensitive) == 0) {
        subTrigger = true;
        ui->Display->setText("-");
    } else if(QString::compare(button->text(), "*", Qt::CaseInsensitive) == 0) {
        mulTrigger = true;
        ui->Display->setText("x");
    } else if(QString::compare(button->text(), "/", Qt::CaseInsensitive) == 0) {
        divTrigger = true;
        ui->Display->setText("÷");
    }
}

void Calculator::EqualsButtonPressed() {
    double solution = ui->Display->text().toDouble();
    if(addTrigger){
        solution += CalcVal;
    } else if (subTrigger) {
        solution = CalcVal - solution;
    } else if (mulTrigger) {
        solution *= CalcVal;
      } else if (divTrigger) {
        solution = CalcVal / solution;
    }
    if (!equalsSignPressedPreviously) {
         CalcVal = solution;
         equalsSignPressedPreviously = true;
    } else {
        ui->Display->setText(QString::number(0.0));
    }

    ui->Display->setText(QString::number(solution));
}

void Calculator::ClearButtonPressed() {
     addTrigger = false;
     subTrigger = false;
     mulTrigger = false;
     divTrigger = false;
     andTrigger = false;
     orTrigger = false;
     norTrigger = false;
     xorTrigger = false;
    ui->Display->setText(QString::number(0.0));
}

