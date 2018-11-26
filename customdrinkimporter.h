#ifndef CUSTOMDRINKIMPORTER_H
#define CUSTOMDRINKIMPORTER_H

#include <QDialog>
#include <QVector>
#include <QComboBox>
#include <QSpinBox>
#include "drink.h"

namespace Ui {
class CustomDrinkImporter;
}

class CustomDrinkImporter : public QDialog
{
    Q_OBJECT

public:
    explicit CustomDrinkImporter(QWidget *parent = nullptr);
    ~CustomDrinkImporter();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_addAdditionalTrivia_clicked();

private:
    Ui::CustomDrinkImporter *ui;
    QVector<QComboBox*> ingredientBoxes;
    QVector<QSpinBox*> amountBoxes;
    const int MAXINGREDIENTS = 10;
    Drink drink;
};

#endif // CUSTOMDRINKIMPORTER_H