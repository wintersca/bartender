#include "controller.h"

QVector<Drink> menu;
XMLDrinkParser parser;
Controller::Controller(XMLDrinkParser parserInit, QObject *parent) : QObject(parent)
{
    parser = parserInit;
    menu = sortRecipes(getAllRecipes());
    emit recipesToGame(menu);

}

/*slots*/

// receive an unsorted vector of recipes from the database parser
QVector<Drink> Controller::getAllRecipes()
{
    QVector<Drink> unsortedMenu = parser.parseXMLDatabase();
    qDebug() << "We have received a vector of recipes from the database";
    return unsortedMenu;
}

// send a new drink to the database and add it to the vector of drinks we already have.
void Controller::updateRecipes(Drink newRecipe)
{
    parser.updateXMLDatabase(newRecipe);
    menu.append(newRecipe);
    QVector<Drink> sortedMenu = sortRecipes(menu);
    emit recipesToGame(sortedMenu);
    qDebug() << "We have sent a recipe to the database and updated the menu of the game";
}

/*helpers*/

QVector<Drink> Controller::sortRecipes(QVector<Drink> recipes)
{
    std::sort(recipes.begin(), recipes.end());
    qDebug() << "We have sorted the recipes alphabetically";
    return recipes;
}


