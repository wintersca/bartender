#include "customdrinkimporter.h"
#include "ui_customdrinkimporter.h"
#include "ingredients.h"
#include "ingredientsmap.h"
#include <QMetaEnum>

CustomDrinkImporter::CustomDrinkImporter(Controller *controller,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CustomDrinkImporter)
{
    //signal to controller
    QObject::connect(this, &CustomDrinkImporter::sendNewRecipe,
                     controller, &Controller::updateRecipes);
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

    // Add all ingredients to the selection boxes.
    int totalIngredients = Ingredients::TOTALINGREDIENTS;
    for (int box = 0; box < MAXINGREDIENTS; box++)
    {
        stepBoxes[box]->addItem("none");
        for (int ingredient = 0; ingredient < totalIngredients; ingredient++)
        {
            QString ingredientName = Ingredients::ingredientData[ingredient].displayString;
            stepBoxes[box]->addItem(ingredientName);
            //stepBoxes[box]->addItem(Ingredients::All[ingredient]);
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


    // Create a dictionary to map strings to enums.
    IngredientsMap ingredientsMap = IngredientsMap();
    QMap<QString, Ingredients::Ingredients> stringsToIngredients = QMap<QString, Ingredients::Ingredients>();
    stringsToIngredients["Vodka"] = Ingredients::Vodka;
    stringsToIngredients["Tequila"] = Ingredients::Tequila;
    stringsToIngredients["Bourbon"] = Ingredients::Bourbon;
    stringsToIngredients["Gin"] = Ingredients::Gin;
    stringsToIngredients["Dark Rum"] = Ingredients::DarkRum;
    stringsToIngredients["White Rum"] = Ingredients::WhiteRum;
    stringsToIngredients["Light Rum"] = Ingredients::LightRum;
    stringsToIngredients["Grand Marnier"] = Ingredients::GrandMarnier;
    stringsToIngredients["Sweet Vermouth"] = Ingredients::SweetVermouth;
    stringsToIngredients["Dry Vermouth"] = Ingredients::DryVermouth;
    stringsToIngredients["Angustura"] = Ingredients::Angustura;
    stringsToIngredients["Tripple Sec"] = Ingredients::TrippleSec;
    stringsToIngredients["Kahlua"] = Ingredients::Kahlua;
    stringsToIngredients["Jagermeister"] = Ingredients::Jagermeister;
    stringsToIngredients["Campari"] = Ingredients::Campari;
    stringsToIngredients["Green Creme de Menthe"] = Ingredients::GreenCremeDeMenthe;
    stringsToIngredients["Creme de Cacao"] = Ingredients::CremeDeCacao;
    stringsToIngredients["Peach Schnapps"] = Ingredients::PeachSchnapps;
    stringsToIngredients["Salt"] = Ingredients::Salt;
    stringsToIngredients["Pepper"] = Ingredients::Pepper;
    stringsToIngredients["Ice"] = Ingredients::Ice;
    stringsToIngredients["Simple Syrup"] = Ingredients::SimpleSyrup;
    stringsToIngredients["Tonic Water"] = Ingredients::TonicWater;
    stringsToIngredients["Sparkling Water"] = Ingredients::SparklingWater;
    stringsToIngredients["Angostura Bitters"] = Ingredients::AngosturaBitters;
    stringsToIngredients["Cola"] = Ingredients::Cola;
    stringsToIngredients["Club Soda"] = Ingredients::ClubSoda;
    stringsToIngredients["Cream"] = Ingredients::Cream;
    stringsToIngredients["Worcestershire Sauce"] = Ingredients::WorcestershireSauce;
    stringsToIngredients["Orange Juice"] = Ingredients::OrangeJuice;
    stringsToIngredients["Lime Juice"] = Ingredients::LimeJuice;
    stringsToIngredients["Lemon Juice"] = Ingredients::LemonJuice;
    stringsToIngredients["Pineapple Juice"] = Ingredients::PineappleJuice;
    stringsToIngredients["Tomato Juice"] = Ingredients::TomatoJuice;
    stringsToIngredients["Cranberry Juice"] = Ingredients::CranberryJuice;
    stringsToIngredients["Orange Wedge"] = Ingredients::OrangeWedge;
    stringsToIngredients["Orange Twist"] = Ingredients::OrangeTwist;
    stringsToIngredients["Lime Wedge"] = Ingredients::LimeWedge;
    stringsToIngredients["Lime Twist"] = Ingredients::LimeTwist;
    stringsToIngredients["Lemon Twist"] = Ingredients::LemonTwist;
    stringsToIngredients["Pineapple Wedge"] = Ingredients::PineappleWedge;
    stringsToIngredients["Cream Of Coconut"] = Ingredients::CreamOfCoconut;
    stringsToIngredients["Ginger Beer"] = Ingredients::GingerBeer;
    stringsToIngredients["Mint Leaf"] = Ingredients::MintLeaf;
    stringsToIngredients["Mint Sprig"] = Ingredients::MintSprig;
    stringsToIngredients["Cherry"] = Ingredients::Cherry;
    stringsToIngredients["Green Olive"] = Ingredients::GreenOlive;
    stringsToIngredients["Celery"] = Ingredients::Celery;
    stringsToIngredients["Nutmeg"] = Ingredients::Nutmeg;
    stringsToIngredients["Shake"] = Ingredients::Shake;
    stringsToIngredients["Stir"] = Ingredients::Stir;
    stringsToIngredients["Muddle"] = Ingredients::Muddle;

    // Add all boxes that don't have none selected.
    for (int i = 0; i < MAXINGREDIENTS; i++)
    {
        QString currentText = stepBoxes[i]->currentText();
        if (currentText != "none")
        {
            totalOfSteps.append(amountBoxes[i]->value());
            includedSteps.append(ingredientsMap.stringsToIngredients[currentText]);
        }
    }

    // Convert to a drink object.

    drink.Name = ui->drinkName->text();
    drink.Trivia.append(ui->drinkTrivia->toPlainText());
    for (int i = 0; i < includedSteps.count(); i++)

    {
        drink.IngredientsMap.insert(includedSteps[i], totalOfSteps[i]);
    }
    emit sendNewRecipe(drink);
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
