#include "customdrinkimporter.h"
#include "ui_customdrinkimporter.h"
#include "ingredients.h"
#include <QMetaEnum>

CustomDrinkImporter::CustomDrinkImporter(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CustomDrinkImporter)
{
    ui->setupUi(this);

    stepBoxes = QVector<QComboBox*>(10);
    stepBoxes[0] = ui->stepBox1;
    stepBoxes[1] = ui->stepBox2;
    stepBoxes[2] = ui->stepBox3;
    stepBoxes[3] = ui->stepBox4;
    stepBoxes[4] = ui->stepBox5;
    stepBoxes[5] = ui->stepBox6;
    stepBoxes[6] = ui->stepBox7;
    stepBoxes[7] = ui->stepBox8;
    stepBoxes[8] = ui->stepBox9;
    stepBoxes[9] = ui->stepBox10;

    amountBoxes = QVector<QDoubleSpinBox*>(10);
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
        amountBoxes[i]->setMinimum(0.25);
        amountBoxes[i]->setSingleStep(0.25);
        amountBoxes[i]->setValue(1.0);
    }

    int totalIngredients = Ingredients::TOTALINGREDIENTS;
    for (int box = 0; box < MAXINGREDIENTS; box++)
    {
        stepBoxes[box]->addItem("none");
        for (int ingredient = 0; ingredient < totalIngredients; ingredient++)
        {
            stepBoxes[box]->addItem(Ingredients::All[ingredient]);
        }
    }

    drink = Drink();
}

CustomDrinkImporter::~CustomDrinkImporter()
{
    delete ui;
}

void CustomDrinkImporter::on_buttonBox_accepted()
{
    QVector<Ingredients::Ingredients> includedSteps = QVector<Ingredients::Ingredients>();
    QVector<double> totalOfSteps = QVector<double>();

    // Add all boxes that don't have none selected.
    for (int i = 0; i < MAXINGREDIENTS; i++)
    {
        QString currentText = stepBoxes[i]->currentText();
        if (currentText != "none")
        {
            totalOfSteps.append(amountBoxes[i]->value());

            if (currentText == "Vodka")
            {
                includedSteps.append(Ingredients::Vodka);
            }
            else if (currentText == "Tequila")
            {
                includedSteps.append(Ingredients::Tequila);
            }
            else if (currentText == "Salt")
            {
                includedSteps.append(Ingredients::Salt);
            }
            else if (currentText == "Grand Marnier")
            {
                includedSteps.append(Ingredients::GrandMarnier);
            }
            else if (currentText == "Simple Syrup")
            {
                includedSteps.append(Ingredients::SimpleSyrup);
            }
            else if (currentText == "Angustura")
            {
                includedSteps.append(Ingredients::Angustura);
            }
            else if (currentText == "Bourbon")
            {
                includedSteps.append(Ingredients::Bourbon);
            }
            else if (currentText == "Orange Twist")
            {
                includedSteps.append(Ingredients::OrangeTwist);
            }
            else if (currentText == "Lime Juice")
            {
                includedSteps.append(Ingredients::LimeJuice);
            }
            else if (currentText == "Mint Leaf")
            {
                includedSteps.append(Ingredients::MintLeaf);
            }
            else if (currentText == "White Rum")
            {
                includedSteps.append(Ingredients::WhiteRum);
            }
            else if (currentText == "Sparkling Water")
            {
                includedSteps.append(Ingredients::SparklingWater);
            }
            else if (currentText == "Gin")
            {
                includedSteps.append(Ingredients::Gin);
            }
            else if (currentText == "Tonic Water")
            {
                includedSteps.append(Ingredients::TonicWater);
            }
            else if (currentText == "Orange Juice")
            {
                includedSteps.append(Ingredients::OrangeJuice);
            }
            else if (currentText == "Orange Wedge")
            {
                includedSteps.append(Ingredients::OrangeWedge);
            }
            else if (currentText == "Angostura Bitters")
            {
                includedSteps.append(Ingredients::AngosturaBitters);
            }
            else if (currentText == "Sweet Vermouth")
            {
                includedSteps.append(Ingredients::SweetVermouth);
            }
            else if (currentText == "Lemon Twist")
            {
                includedSteps.append(Ingredients::LemonTwist);
            }
            else if (currentText == "Cherry")
            {
                includedSteps.append(Ingredients::Cherry);
            }
            else if (currentText == "Dry Vermouth")
            {
                includedSteps.append(Ingredients::DryVermouth);
            }
            else if (currentText == "Green Olive")
            {
                includedSteps.append(Ingredients::GreenOlive);
            }
        }
    }

    // Convert to a drink object.
    drink.Name = ui->drinkName->text();
    drink.Trivia.append(ui->drinkTrivia->toPlainText());
    for (int i = 0; i < includedSteps.count(); i++)
    {
        drink.IngredientsMap.insert(includedSteps[i], totalOfSteps[i]);
    }
}

void CustomDrinkImporter::on_buttonBox_rejected()
{
    this->close();
}

void CustomDrinkImporter::on_addAdditionalTrivia_clicked()
{
    drink.Trivia.append(ui->drinkTrivia->toPlainText());
    ui->drinkTrivia->setText("");
}
