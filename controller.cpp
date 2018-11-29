#include "controller.h"

QVector<Drink*> menu;
XMLDrinkParser *parser;
Controller::Controller(XMLDrinkParser *parserInit, QObject *parent) : QObject(parent)
{
    parser = parserInit;
    menu = getAllRecipes();
    emit menuToGame(menu);

}

/*slots*/

// receive a vector of recipes from the database parser
QVector<Drink*> Controller::getAllRecipes()
{
    QVector<Drink*> menu = parser->parseXMLDatabase();
    qDebug() << "We have received a vector of recipes from the database";
    return menu;
}

// send a new drink to the database and add it to the vector of drinks we already have.
void Controller::updateRecipes(Drink* newRecipe)
{
    parser->updateXMLDatabase(newRecipe);
    menu.append(newRecipe);
    qDebug() << "We have sent a recipe to the database and updated the menu of the game";
}

void Controller::newCustomer()
{
    qDebug() << "Received request for a new customer";
    srand(static_cast<unsigned int>(time(nullptr)));
    stepCount = 0;
    currentHappiness = rand()%5 + 4; // start at happiness of 4 - 8
    currentDrink = menu.at(rand()%(menu.length()));
    int drinkComplexity = currentDrink->IngredientsMap.size();
    emit customerHappinessToGame(currentHappiness);
    emit customerDrinkToGame(currentDrink);
    QVector<QString> trivia = currentDrink->getTrivia();
    QString currentTrivia = trivia.at(rand()%trivia.length());
    emit triviaToGame(currentTrivia);
    customerPatience = drinkComplexity * 5000 / currentHappiness; //how long before happiness level drops. I gave each step 5 sec
    QTimer::singleShot(customerPatience, this, SLOT(decreaseHappiness()));

}

void Controller::decreaseHappiness()
{
    currentHappiness--;
    if(currentHappiness == 0)
    {
        qDebug() << "Customer happiness:0 customer left";
        emit customerLeft();
    }
    else
    {
        qDebug() << "Customer happiness:" << currentHappiness;
        emit customerHappinessToGame(currentHappiness);
        QTimer::singleShot(customerPatience, this, SLOT(decreaseHappiness()));
    }

}

void Controller::addedIngredient(Ingredients::Ingredients ingredient, double amount)
{
    QVector<Step> steps = currentDrink->getSteps();
    Step currentStep = steps.at(stepCount);
    bool isCorrectIngredient = false;
    if(currentStep.getItem() == ingredient && currentStep.getAmount() == amount)
        isCorrectIngredient = true;
    stepCount++;
    emit ingredientVerificationToGame(isCorrectIngredient);

}

void Controller::calculateTip()
{
    int drinkComplexity = currentDrink->IngredientsMap.size();
    double tip = (drinkComplexity - errorCount) * .25; //you get 25 cent tip per correct step
}


/*helpers*/




