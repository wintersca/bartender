#include "recordboard.h"
#include "ui_recordboard.h"
#include <iostream>

RecordBoard::RecordBoard (Controller* controller, QMap<QString, int> records, QWidget *parent ) :
    QDialog(parent),
    ui(new Ui::RecordBoard)
{
    ui->setupUi(this);


    if(records.contains("CustomerDissatisfied")){
        std::cout<< "dis" <<std::endl;
        int value = records.value("CustomerDissatisfied");
        QString valueString= QString::number(value);
        ui->numDissatisfiedLabel->setText(valueString);
    }
    if(records.contains("CustomersSatisfied")){
        std::cout<< "sat" <<std::endl;
        int value = records.value("CustomersSatisfied");
        QString valueString= QString::number(value);
        ui->numSatisfiedLabel->setText(valueString);
    }
    if(records.contains("DrinksServed")){
        std::cout<< "ser" <<std::endl;
        int value = records.value("DrinksServed");
        QString valueString= QString::number(value);
        ui->numServedLabel->setText(valueString);
    }
    if(records.contains("TipCents")&&records.contains("TipDollars")){
        std::cout<< "tip" <<std::endl;
        int centsValue = records.value("TipCents");
        int dollarsValue = records.value("TipDollars");
        QString valueString= QString::number(dollarsValue)+"."+QString::number(centsValue);
        ui->numTipsLabel->setText(valueString);
    }

}

RecordBoard::~RecordBoard()
{
    delete ui;
}



