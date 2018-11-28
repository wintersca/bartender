#include "controller.h"

QVector<Drink*> menu;
XMLDrinkParser *parser;
Controller::Controller(XMLDrinkParser *parserInit, QObject *parent) : QObject(parent)
{
    parser = parserInit;
    menu = sortRecipes(getAllRecipes());
    emit menuToGame(menu);

}

/*slots*/

// receive an unsorted vector of recipes from the database parser
QVector<Drink*> Controller::getAllRecipes()
{
    QVector<Drink*> unsortedMenu = parser->parseXMLDatabase();
    qDebug() << "We have received a vector of recipes from the database";
    return unsortedMenu;
}

// send a new drink to the database and add it to the vector of drinks we already have.
void Controller::updateRecipes(Drink* newRecipe)
{
    parser->updateXMLDatabase(newRecipe);
    menu.append(newRecipe);
    QVector<Drink*> sortedMenu = sortRecipes(menu);
    emit menuToGame(sortedMenu);
    qDebug() << "We have sent a recipe to the database and updated the menu of the game";
}

void Controller::newCustomer()
{
    currentHappiness = qrand()%5 + 4; // start at happiness of 4 - 8
    currentDrink = menu.at(qrand()%(menu.length()));
    int drinkComplexity = currentDrink->IngredientsMap.size();
    emit customerHappinessToGame(currentHappiness);
    emit customerDrinkToGame(currentDrink);
    // TODO: pick a trivia, ^^^ parse and send separately?
    customerPatience = drinkComplexity * 5000 / currentHappiness; //how long before happiness level drops
    QTimer::singleShot(customerPatience, this, SLOT(decreaseHappiness()));
    qDebug() << "Received request for a new customer";
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

void Controller::addedIngredient(Ingredients::Ingredients ingredient)
{
    if(currentDrink->IngredientsMap.contains(ingredient))
    {
        //TODO: check amount
    }
}


/*helpers*/

QVector<Drink*> Controller::sortRecipes(QVector<Drink*> recipes)
{
    std::sort(recipes.begin(), recipes.end());
    qDebug() << "We have sorted the recipes alphabetically";
    return recipes;
}


