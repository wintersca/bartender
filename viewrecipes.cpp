#include "viewrecipes.h"
#include "ui_viewrecipes.h"

ViewRecipes::ViewRecipes(QVector<Drink*> menu, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ViewRecipes)
{
    ui->setupUi(this);

    Menu = menu;

    // Arrays of labels.
    // Labels for displaying the steps of a drink.
    stepsInDrink = QVector<QLabel*>(10);
    stepsInDrink[0] = ui->step1;
    stepsInDrink[1] = ui->step2;
    stepsInDrink[2] = ui->step3;
    stepsInDrink[3] = ui->step4;
    stepsInDrink[4] = ui->step5;
    stepsInDrink[5] = ui->step6;
    stepsInDrink[6] = ui->step7;
    stepsInDrink[7] = ui->step8;
    stepsInDrink[8] = ui->step9;
    stepsInDrink[9] = ui->step10;

    amountsInDrink = QVector<QLabel*>(10);
    amountsInDrink[0] = ui->amount1;
    amountsInDrink[1] = ui->amount2;
    amountsInDrink[2] = ui->amount3;
    amountsInDrink[3] = ui->amount4;
    amountsInDrink[4] = ui->amount5;
    amountsInDrink[5] = ui->amount6;
    amountsInDrink[6] = ui->amount7;
    amountsInDrink[7] = ui->amount8;
    amountsInDrink[8] = ui->amount9;
    amountsInDrink[9] = ui->amount10;

    unitsInDrink = QVector<QLabel*>(10);
    unitsInDrink[0] = ui->unit1;
    unitsInDrink[1] = ui->unit2;
    unitsInDrink[2] = ui->unit3;
    unitsInDrink[3] = ui->unit4;
    unitsInDrink[4] = ui->unit5;
    unitsInDrink[5] = ui->unit6;
    unitsInDrink[6] = ui->unit7;
    unitsInDrink[7] = ui->unit8;
    unitsInDrink[8] = ui->unit9;
    unitsInDrink[9] = ui->unit10;

    ingredientsInDrink = QVector<QLabel*>(10);
    ingredientsInDrink[0] = ui->ingredient1;
    ingredientsInDrink[1] = ui->ingredient2;
    ingredientsInDrink[2] = ui->ingredient3;
    ingredientsInDrink[3] = ui->ingredient4;
    ingredientsInDrink[4] = ui->ingredient5;
    ingredientsInDrink[5] = ui->ingredient6;
    ingredientsInDrink[6] = ui->ingredient7;
    ingredientsInDrink[7] = ui->ingredient8;
    ingredientsInDrink[8] = ui->ingredient9;
    ingredientsInDrink[9] = ui->ingredient10;

    // Fill in the names of drinks box.
    for (int i = 0; i < Menu.length(); i++)
    {
        ui->allRecipes->addItem(Menu[i]->Name);
    }
}

ViewRecipes::~ViewRecipes()
{
    delete ui;
}

// Display all information.
void ViewRecipes::on_allRecipes_currentIndexChanged(int index)
{
    // Clear all data
    for (int i = 0; i < 10; i++)
    {
        stepsInDrink[i]->setText("");
        amountsInDrink[i]->setText("");
        unitsInDrink[i]->setText("");
        ingredientsInDrink[i]->setText("");
    }

    // Get the drink.
    Drink* drink = Menu[index];

    // Fill in steps.
    QVector<Step> steps = drink->getSteps();
    for (int i = 0; i < steps.length(); i++)
    {
        stepsInDrink[i]->setText(steps[i].getInstruction());
    }

    int ingredientIndex = 0;
    QMapIterator<Ingredients::Ingredients, double> i(drink->IngredientsMap);
    while (i.hasNext())
    {
        i.next();
        // Display amount
        amountsInDrink[ingredientIndex]->setText(QString::number(i.value()));

        // Display units.
        QString ingredientUnits = Ingredients::ingredientData[i.key()].unit;
        unitsInDrink[ingredientIndex]->setText(ingredientUnits);

        // Display name.
        QString ingredientName = Ingredients::ingredientData[i.key()].displayString;
        ingredientsInDrink[ingredientIndex]->setText(ingredientName);

        ingredientIndex++;
    }
}
