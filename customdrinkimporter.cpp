#include "customdrinkimporter.h"
#include "ui_customdrinkimporter.h"
#include "ingredients.h"
#include <QMetaEnum>

CustomDrinkImporter::CustomDrinkImporter(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CustomDrinkImporter)
{
    ui->setupUi(this);

    const int MAXINGREDIENTS = 10;

    ingredientBoxes = QVector<QComboBox*>(10);
    ingredientBoxes[0] = ui->ingredientBox1;
    ingredientBoxes[1] = ui->ingredientBox2;
    ingredientBoxes[2] = ui->ingredientBox3;
    ingredientBoxes[3] = ui->ingredientBox4;
    ingredientBoxes[4] = ui->ingredientBox5;
    ingredientBoxes[5] = ui->ingredientBox6;
    ingredientBoxes[6] = ui->ingredientBox7;
    ingredientBoxes[7] = ui->ingredientBox8;
    ingredientBoxes[8] = ui->ingredientBox9;
    ingredientBoxes[9] = ui->ingredientBox10;

    amountBoxes = QVector<QSpinBox*>(10);
    amountBoxes[0] = ui->amountBox1;
    amountBoxes[1] = ui->amountBox2;
    amountBoxes[2] = ui->amountBox3;
    amountBoxes[3] = ui->amountBox4;
    amountBoxes[4] = ui->amountBox5;
    amountBoxes[5] = ui->amountBox6;
    amountBoxes[6] = ui->amountBox7;
    amountBoxes[7] = ui->amountBox8;
    amountBoxes[8] = ui->amountBox9;
    amountBoxes[9] = ui->amountBox10;

    int totalIngredients = Ingredients::TOTALINGREDIENTS;
    for (int box = 0; box < MAXINGREDIENTS; box++)
    {
        for (int ingredient = 0; ingredient < totalIngredients; ingredient++)
        {
            ingredientBoxes[box]->addItem(Ingredients::All[ingredient]);
        }
    }
}

CustomDrinkImporter::~CustomDrinkImporter()
{
    delete ui;
}
