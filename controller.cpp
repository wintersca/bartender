#include "controller.h"


 XMLDrinkParser parser;
Controller::Controller(XMLDrinkParser parserInit, QObject *parent) : QObject(parent)
{
    parser = parserInit;
}

/*slots*/

// receive a new recipe from the custom recipe creator
void Controller::receiveRecipe(Drink newDrink)
{
    //TODO
    Drink d1 = Drink();
    Drink d2 = Drink();
    Drink d3 = Drink();
    d1.Name = "aab";
    d2.Name = "aba";
    d3.Name = "aaa";
    QVector<Drink> drinks;
    drinks.append(d1);
    drinks.append(d2);
    drinks.append(d3);
    std::sort(drinks.begin(), drinks.end());
    for (int i = 0; i < 3; i++)
    {
        qDebug() << drinks[i].Name;
    }
    qDebug() << "We have received a new recipe";
}

// receive a vector of recipes from the database parser
void Controller::getAllRecipes()
{
    //TODO
    parser.parseXMLDatabase();
    qDebug() << "We have received a vector of recipes from the database";
}


/*helpers*/

// send a new drink to the database and add it to the vector of drinks
// we already have.
void Controller::updateDatabase(Drink newRecipe)
{
    parser.updateXMLDatabase(newRecipe);
    qDebug() << "We have sent a recipe to the database";
}

QVector<Drink> Controller::sortRecipes(QVector<Drink> recipes)
{
    //TODO
    qDebug() << "We have sorted the recipes alphabetically";
}

// send a vector of sorted recipes to the game
void Controller::sendUpdatedRecipesToGame(QVector<Drink> sortedDrinks)
{
    //TODO
    qDebug() << "We have sent the sorted recipes to the game";
}
