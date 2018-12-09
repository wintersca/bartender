#ifndef CUSTOMDRINKIMPORTER_H
#define CUSTOMDRINKIMPORTER_H

#include <QDialog>
#include <QVector>
#include <QComboBox>
#include <QSpinBox>
#include <QMetaEnum>
#include "drink.h"
#include "controller.h"
#include "ui_customdrinkimporter.h"
#include "ingredients.h"
#include "ingredientsmap.h"
#include "step.h"

/*
 * The drink importer allows the user to specify custom drinks using the given ingredients.
 * Drinks created here are added to the XML database and can be used when opening the game later.
 * Author: Alex Smith
 */

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
    // The drink that the user created is sent to the database, and the window is closed.
    void on_buttonBox_accepted();

    // The drink the user created is ignored and the window is closed.
    void on_buttonBox_rejected();

    // The current trivia is saved and the box for trivia is cleared.
    void on_addAdditionalTrivia_clicked();

private:
    Ui::CustomDrinkImporter *ui;

    // All combo boxes to show available ingredients.
    QVector<QComboBox*> stepBoxes;

    // All spin boxes to select amounts of an ingredient.
    QVector<QDoubleSpinBox*> amountBoxes;

    // The maximum possible ingredients in a drink.
    const int MAXINGREDIENTS = 10;

    // The drink object that is sent to the controller.
    Drink drink;

signals:
    void sendNewRecipe(Drink* drink);
};

#endif // CUSTOMDRINKIMPORTER_H
