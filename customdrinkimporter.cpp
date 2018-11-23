#include "customdrinkimporter.h"
#include "ui_customdrinkimporter.h"
#include "ingredients.h"
#include <QMetaEnum>
#include "drink.h"

CustomDrinkImporter::CustomDrinkImporter(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CustomDrinkImporter)
{
    ui->setupUi(this);

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

    // Set bounds of quantity boxes.
    for (int i = 0; i < MAXINGREDIENTS; i++)
    {
        amountBoxes[i]->setMinimum(1);
    }

    int totalIngredients = Ingredients::TOTALINGREDIENTS;
    for (int box = 0; box < MAXINGREDIENTS; box++)
    {
        ingredientBoxes[box]->addItem("none");
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

void CustomDrinkImporter::on_buttonBox_accepted()
{
    QVector<Ingredients::Ingredients> includedIngredients = QVector<Ingredients::Ingredients>();
    QVector<int> totalOfIngredients = QVector<int>();

    // Add all boxes that don't have none selected.
    for (int i = 0; i < MAXINGREDIENTS; i++)
    {
        QString currentText = ingredientBoxes[i]->currentText();
        if (currentText != "none")
        {
            totalOfIngredients.append(amountBoxes[i]->value());

            if (currentText == "Vodka")
            {
                includedIngredients.append(Ingredients::Vodka);
            }
            else if (currentText == "Tequila")
            {
                includedIngredients.append(Ingredients::Tequila);
            }
            else if (currentText == "Salt")
            {
                includedIngredients.append(Ingredients::Salt);
            }
            else if (currentText == "Grand Marnier")
            {
                includedIngredients.append(Ingredients::GrandMarnier);
            }
            else if (currentText == "Simple Syrup")
            {
                includedIngredients.append(Ingredients::SimpleSyrup);
            }
            else if (currentText == "Angustura")
            {
                includedIngredients.append(Ingredients::Angustura);
            }
            else if (currentText == "Bourbon")
            {
                includedIngredients.append(Ingredients::Bourbon);
            }
            else if (currentText == "Orange Twist")
            {
                includedIngredients.append(Ingredients::OrangeTwist);
            }
            else if (currentText == "Lime Juice")
            {
                includedIngredients.append(Ingredients::LimeJuice);
            }
            else if (currentText == "Mint Leaf")
            {
                includedIngredients.append(Ingredients::MintLeaf);
            }
            else if (currentText == "White Rum")
            {
                includedIngredients.append(Ingredients::WhiteRum);
            }
            else if (currentText == "Sparkling Water")
            {
                includedIngredients.append(Ingredients::SparklingWater);
            }
            else if (currentText == "Gin")
            {
                includedIngredients.append(Ingredients::Gin);
            }
            else if (currentText == "Tonic Water")
            {
                includedIngredients.append(Ingredients::TonicWater);
            }
            else if (currentText == "Orange Juice")
            {
                includedIngredients.append(Ingredients::OrangeJuice);
            }
            else if (currentText == "Orange Wedge")
            {
                includedIngredients.append(Ingredients::OrangeWedge);
            }
            else if (currentText == "Angostura Bitters")
            {
                includedIngredients.append(Ingredients::AngosturaBitters);
            }
            else if (currentText == "Sweet Vermouth")
            {
                includedIngredients.append(Ingredients::SweetVermouth);
            }
            else if (currentText == "Lemon Twist")
            {
                includedIngredients.append(Ingredients::LemonTwist);
            }
            else if (currentText == "Cherry")
            {
                includedIngredients.append(Ingredients::Cherry);
            }
            else if (currentText == "Dry Vermouth")
            {
                includedIngredients.append(Ingredients::DryVermouth);
            }
            else if (currentText == "Green Olive")
            {
                includedIngredients.append(Ingredients::GreenOlive);
            }
        }
    }

    // Convert to a drink object.
    Drink drink = Drink(ui->drinkName->text());
    for (int i = 0; i < includedIngredients.count(); i++)
    {
        drink.IngredientsMap.insert(includedIngredients[i], totalOfIngredients[i]);
    }
    drink.Trivia.append(ui->drinkTrivia->toPlainText());
    int test = 0;
}

void CustomDrinkImporter::on_buttonBox_rejected()
{
    this->close();
}
