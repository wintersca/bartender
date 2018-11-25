#ifndef CUSTOMDRINKIMPORTER_H
#define CUSTOMDRINKIMPORTER_H

#include <QDialog>
#include <QVector>
#include <QComboBox>
#include <QSpinBox>
#include "controller.h"
#include "ingredients.h"
#include "drink.h"

namespace Ui {
class CustomDrinkImporter;
}

class CustomDrinkImporter : public QDialog
{
    Q_OBJECT

public:
    explicit CustomDrinkImporter(Controller *controller, QWidget *parent = nullptr);
    ~CustomDrinkImporter();

private slots:
    void on_buttonBox_accepted();


signals:
    void sendRecipe(QVector<Ingredients::Ingredients> includedIngredients);
    void on_buttonBox_rejected();


private:
    Ui::CustomDrinkImporter *ui;
    QVector<QComboBox*> ingredientBoxes;
    QVector<QSpinBox*> amountBoxes;
    const int MAXINGREDIENTS = 10;
};

#endif // CUSTOMDRINKIMPORTER_H
