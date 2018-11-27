#include "controller.h"

Controller::Controller(QObject *parent) : QObject(parent)
{

}

/*slots*/

// receive a new recipe from the custom recipe creator
void Controller::receiveRecipe(Drink newDrink)
{
    //TODO
    qDebug() << "We have received a new recipe";
}

// receive a vector of recipes from the database parser
void Controller::getAllRecipes(QVector<Drink> allDrinks)
{
    //TODO
    qDebug() << "We have received a vector of recipes from the database";
}


/*helpers*/

// send a new drink to the database and add it to the vector of drinks
// we already have.
void Controller::updateDatabase(Drink newRecipe)
{
    //TODO
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
