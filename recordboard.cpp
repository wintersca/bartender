#include "recordboard.h"
#include "ui_recordboard.h"

RecordBoard::RecordBoard (Controller* controller, QMap<QString, int> records, QWidget *parent ) :
    QDialog(parent),
    ui(new Ui::RecordBoard)
{
    ui->setupUi(this);

    if(records.contains("CustomerDissatisfied")){
        int value = records.value("CustomerDissatisfied");
        QString valueString= QString::number(value);
        ui->numDissatisfiedLabel->setText(valueString);
    }
    else
    {
        ui->numDissatisfiedLabel->setText(QString::number(0));
    }

    if(records.contains("CustomersSatisfied")){
        int value = records.value("CustomersSatisfied");
        QString valueString= QString::number(value);
        ui->numSatisfiedLabel->setText(valueString);
    }
    else
    {
        ui->numSatisfiedLabel->setText(QString::number(0));
    }

    if(records.contains("DrinksServed")){
        int value = records.value("DrinksServed");
        QString valueString= QString::number(value);
        ui->numServedLabel->setText(valueString);
    }
    else
    {
        ui->numServedLabel->setText(QString::number(0));
    }

    if(records.contains("TipCents")&&records.contains("TipDollars")){
        int centsValue = records.value("TipCents");
        int dollarsValue = records.value("TipDollars");
        QString valueString= QString::number(dollarsValue)+"."+QString::number(centsValue);
        ui->numTipsLabel->setText(valueString);
    }
    else
    {
        ui->numTipsLabel->setText(QString::number(0));
    }

}

RecordBoard::~RecordBoard()
{
    delete ui;
}



