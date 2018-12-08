#include "recordboard.h"
#include "ui_recordboard.h"

RecordBoard::RecordBoard (Controller* controller, QMap<QString, int> records, QWidget *parent ) :
    QDialog(parent),
    ui(new Ui::RecordBoard)
{
    int totalCustomersSatisfied = 0;
    int totalCustomersDissatisfied = 0;
    int totalDrinksServed = 0;
    int totalDollars = 0;
    int totalCents = 0;

    ui->setupUi(this);

    if(records.contains("EasyTipDollars")&&records.contains("EasyTipCents"))
    {
        int dollar = records.value("EasyTipDollars");
        int cents = records.value("EasyTipCents");
        totalDollars = totalDollars + dollar;
        totalCents = totalCents + cents;

        QString valueString;
        if(cents == 0)
        {
            valueString= "$"+QString::number(dollar)+".00";
        }
        else if(cents < 10)
        {
            valueString= "$"+QString::number(dollar)+".0"+QString::number(cents);
        }
        else
        {
            valueString= "$"+QString::number(dollar)+"."+QString::number(cents);
        }

        ui->easyNumTipsLabel->setText(valueString);

    }
    else
    {
        ui->easyNumTipsLabel->setText("$0.00");
    }

    if(records.contains("EasyCustomersSatisfied"))
    {
        int value = records.value("EasyCustomersSatisfied");
        totalCustomersSatisfied = totalCustomersSatisfied + value;
        QString valueString= QString::number(value);
        ui->easyNumSatisfiedLabel->setText(valueString);
    }
    else
    {
        ui->easyNumSatisfiedLabel->setText(0);
    }

    if(records.contains("EasyCustomerDissatisfied"))
    {
        int value = records.value("EasyCustomerDissatisfied");
        totalCustomersDissatisfied = totalCustomersDissatisfied + value;
        QString valueString= QString::number(value);
        ui->easyNumDissatisfiedLabel->setText(valueString);
    }
    else
    {
        ui->easyNumDissatisfiedLabel->setText(0);
    }

    if(records.contains("EasyDrinksServed"))
    {
        int value = records.value("EasyDrinksServed");
        totalDrinksServed = totalDrinksServed + value;
        QString valueString= QString::number(value);
        ui->easyNumServedLabel->setText(valueString);
    }
    else
    {
        ui->easyNumServedLabel->setText(0);
    }

    if(records.contains("MedTipDollars")&&records.contains("MedTipCents"))
    {
        int dollar = records.value("MedTipDollars");
        int cents = records.value("MedTipCents");
        totalDollars = totalDollars + dollar;
        totalCents = totalCents + cents;

        QString valueString;
        if(cents == 0)
        {
            valueString= "$"+QString::number(dollar)+".00";
        }
        else if(cents < 10)
        {
            valueString= "$"+QString::number(dollar)+".0"+QString::number(cents);
        }
        else
        {
            valueString= "$"+QString::number(dollar)+"."+QString::number(cents);
        }

        ui->mediumNumTipsLabel->setText(valueString);

    }
    else
    {
        ui->mediumNumTipsLabel->setText("$0.00");
    }

    if(records.contains("MedCustomersSatisfied"))
    {
        int value = records.value("MedCustomersSatisfied");
        totalCustomersSatisfied = totalCustomersSatisfied + value;
        QString valueString= QString::number(value);
        ui->mediumNumSatisfiedLabel->setText(valueString);
    }
    else
    {
        ui->mediumNumSatisfiedLabel->setText(0);
    }

    if(records.contains("MedCustomerDissatisfied"))
    {
        int value = records.value("MedCustomerDissatisfied");
        totalCustomersDissatisfied = totalCustomersDissatisfied + value;
        QString valueString= QString::number(value);
        ui->mediumNumDissatisfiedLabel->setText(valueString);
    }
    else
    {
        ui->mediumNumDissatisfiedLabel->setText(0);
    }

    if(records.contains("MedDrinksServed"))
    {
        int value = records.value("MedDrinksServed");
        totalDrinksServed = totalDrinksServed + value;
        QString valueString= QString::number(value);
        ui->mediumNumServedLabel->setText(valueString);
    }
    else
    {
        ui->mediumNumServedLabel->setText(0);
    }

    if(records.contains("HardTipDollars")&&records.contains("HardTipCents"))
    {
        int dollar = records.value("HardTipDollars");
        int cents = records.value("HardTipCents");
        totalDollars = totalDollars + dollar;
        totalCents = totalCents + cents;

        QString valueString;
        if(cents == 0)
        {
            valueString= "$"+QString::number(dollar)+".00";
        }
        else if(cents < 10)
        {
            valueString= "$"+QString::number(dollar)+".0"+QString::number(cents);
        }
        else
        {
            valueString= "$"+QString::number(dollar)+"."+QString::number(cents);
        }

        ui->mediumNumTipsLabel->setText(valueString);

    }
    else
    {
        ui->mediumNumTipsLabel->setText("$0.00");
    }

    if(records.contains("HardCustomersSatisfied"))
    {
        int value = records.value("HardCustomersSatisfied");
        totalCustomersSatisfied = totalCustomersSatisfied + value;
        QString valueString= QString::number(value);
        ui->hardNumSatisfiedLabel->setText(valueString);
    }
    else
    {
        ui->hardNumSatisfiedLabel->setText(0);
    }

    if(records.contains("HardCustomerDissatisfied"))
    {
        int value = records.value("HardCustomerDissatisfied");
        totalCustomersDissatisfied = totalCustomersDissatisfied + value;
        QString valueString= QString::number(value);
        ui->hardNumDissatisfiedLabel->setText(valueString);
    }
    else
    {
        ui->hardNumDissatisfiedLabel->setText(0);
    }

    if(records.contains("HardDrinksServed"))
    {
        int value = records.value("HardDrinksServed");
        totalDrinksServed = totalDrinksServed + value;
        QString valueString= QString::number(value);
        ui->hardNumServedLabel->setText(valueString);
    }
    else
    {
        ui->hardNumServedLabel->setText(0);
    }

    if(totalCents >= 100)
    {
        int divisor = totalCents/100;
        totalCents = totalCents - (100*divisor);
        totalDollars = totalDollars+divisor;
    }

    if(totalCents == 0)
    {
        QString valueString= "$"+QString::number(totalDollars)+".00";
        ui->totalNumTipsLabel->setText(valueString);
    }
    else if (totalCents < 10)
    {
        QString valueString= "$"+QString::number(totalDollars)+".0"+QString::number(totalCents);
        ui->totalNumTipsLabel->setText(valueString);
    }
    else
    {
        QString valueString= "$"+QString::number(totalDollars)+"."+QString::number(totalCents);
        ui->totalNumTipsLabel->setText(valueString);
    }

    ui->totalNumSatisfiedLabel->setText(QString::number(totalCustomersSatisfied));
    ui->totalnumDissatisfiedLabel->setText(QString::number(totalCustomersDissatisfied));
    ui->totalNumServedLabel->setText(QString::number(totalDrinksServed));
}

RecordBoard::~RecordBoard()
{
    delete ui;
}



