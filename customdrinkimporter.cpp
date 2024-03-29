#include "customdrinkimporter.h"

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
    int totalIngredients = Ingredients::ITEMSININGREDIENTS;
    for (int box = 0; box < MAXINGREDIENTS; box++)
    {
        stepBoxes[box]->addItem("none");
        for (int ingredient = 0; ingredient < totalIngredients; ingredient++)
        {
            QString ingredientName = Ingredients::ingredientData[ingredient].displayString;
            stepBoxes[box]->addItem(ingredientName);
        }
    }
}

CustomDrinkImporter::~CustomDrinkImporter()
{
    delete ui;
}

void CustomDrinkImporter::on_buttonBox_accepted()
{
    QVector<Ingredients::Ingredients> includedSteps = QVector<Ingredients::Ingredients>();
    QVector<double> totalOfSteps = QVector<double>();
    QVector<Step> steps = QVector<Step>();

    // Create a dictionary to map strings to enums.
    IngredientsMap ingredientsMap = IngredientsMap();
    QMap<QString, Ingredients::Ingredients> stringsToIngredients = ingredientsMap.stringsToIngredients;

    // Add all boxes that don't have none selected.
    for (int i = 0; i < MAXINGREDIENTS; i++)
    {
        QString currentText = stepBoxes[i]->currentText();
        if (currentText != "none")
        {
            QString instruction = QString();
            double amount = amountBoxes[i]->value();
            Ingredients::Ingredients ingredient = ingredientsMap.stringsToIngredients[currentText];
            Ingredients::IngredientData data=Ingredients::ingredientData[ingredient];
            QString action;
            if(data.action==Ingredients::Action::PourAction){
                action = "Pour";
                instruction+=  QString::number(i+1)+ ". " + action + " " + QString::number(amount) + " " +data.unit + " " +data.displayString;
            }
            else if(data.action==Ingredients::Action::AddAction){
                action = "Add";
                if(data.unit == "cubes"){
                    instruction+=QString::number(i+1)+ ". " + action + " "  + data.displayString;
                    amount = 1;
                }else{
                    instruction+=QString::number(i+1)+ ". " + action + " " + QString::number(amount) + " " +data.unit + " " +data.displayString;
                }
            }
            else if(data.action==Ingredients::Action::ShakeAction){
                action = "Shake";
                instruction =QString::number(i+1)+ ". " + action;
                amount=0;
            }
            else if(data.action==Ingredients::Action::StirAction){
                action = "Stir";
                instruction =QString::number(i+1)+ ". " + action;
                amount=0;
            }
            else if(data.action==Ingredients::Action::MuddleAction){
                action = "Muddle";
                instruction =QString::number(i+1)+ ". " + action;
                amount=0;
            }

            totalOfSteps.append(amount);
            includedSteps.append(ingredient);
            Step step= Step(instruction, ingredient,  amount);

            steps.push_back(step);
        }
    }

    // Convert to a drink object.
    drink.Name = "*"+ui->drinkName->text();
    drink.Trivia.append(ui->drinkTrivia->toPlainText());
    for (int i = 0; i < includedSteps.count(); i++)
    {
        drink.IngredientsMap.insert(includedSteps[i], totalOfSteps[i]);
    }
    drink.setSteps(steps);
    emit sendNewRecipe(&drink);
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
