#include "controller.h"

// set up controller
Controller::Controller(XMLDrinkParser *parserInit, QObject *parent) : QObject(parent)
{
    parser = parserInit;
    menu = getAllRecipes();
    userSpecifiedMenu = menu;
    for (Drink* drink : menu)
        drink->setSelected(true);
    totalTipDollars = 0;
    totalTipCents = 0;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()),
            this, SLOT(timerUpdate()));
}

QVector<Drink*> Controller::getAllRecipes()
{
    QVector<Drink*> menu = parser->parseXMLDatabase();
    qDebug() << "We have received a vector of recipes from the database";
    return menu;
}

void Controller::menuRequestByGameArea()
{
   emit menuToMainWindow(menu);
}

void Controller::menuRequestedByMainWindow()
{
    emit menuToMainWindow(menu);
}

void Controller::receiveUserSpecifiedMenu(QVector<Drink*> newMenu)
{
    QVector<Drink*> tempMenu;
    for (Drink* drink : newMenu)
    {
        if (drink->getSelected())
            tempMenu.append(drink);
    }
    userSpecifiedMenu = tempMenu;
}

void Controller::updateRecipes(Drink* newRecipe)
{
    parser->updateXMLDatabase(newRecipe);
    menu.append(newRecipe);
    userSpecifiedMenu.append(newRecipe);
    qDebug() << "We have sent a recipe to the database and updated the menu of the game";
}

void Controller::startGame(unsigned int difficultyInit)
{
    difficulty = difficultyInit;
    startRound(difficulty);
}

void Controller::startRound(unsigned int difficulty)
{
    newCustomer(difficulty);
    drinkComplexity = currentDrink->IngredientsMap.size();
    drinkPoints = 0;
    timeToCompleteDrink = static_cast<int>(moodValueModifier * 10 * drinkComplexity);
    emit sendDrink(currentDrink);
    emit moodToGameArea(currentHappiness);
    if(difficulty != 0) //easy
    {
        timer->start(1000);
        emit sendTime(timeToCompleteDrink);
    }
    else
        emit sendTime(0);
}

void Controller::newCustomer(unsigned int difficulty)
{
    int rand = static_cast<int>(qFabs(static_cast<int>(QRandomGenerator::global()->generate())));
    switch(difficulty)
    {
        case 0:
        {
            currentHappiness = (rand % 2) + 4;
            break;
        }
        case 1:
        {
            currentHappiness = (rand % 2) + 3;
            break;
        }
        case 2:
        {
            currentHappiness = (rand % 2) + 2;
            break;
        }
    }
    currentDrink = selectNewRandomDrink();
    for (Step s : currentDrink->getSteps())
        qDebug() << s.getItem();
    moodValueModifier = static_cast<double>(currentHappiness) / 5;
    stepCount = 0;
    addedIngredients.clear();
}

Drink* Controller::selectNewRandomDrink()
{
    int rand = static_cast<int>(qFabs(static_cast<int>(QRandomGenerator::global()->generate())));
    currentDrink = userSpecifiedMenu[rand % userSpecifiedMenu.length()];
    return currentDrink;
}

void Controller::timerUpdate()
{
    if (currentHappiness > 0)
    {
        emit sendTime(timeToCompleteDrink--);
        if (timeToCompleteDrink < 0 && timeToCompleteDrink % static_cast<int>(5*moodValueModifier) == 0)
            emit moodToGameArea(currentHappiness--);
    }
    else
        endRound();
}

void Controller::receiveAmountToAdd(double amount)
{
    ingredientAmount = amount;
}

void Controller::checkIngredient(Ingredients::Ingredients ingredient)
{
    QVector<Step> steps = currentDrink->getSteps();
    Step currentStep = steps.at(stepCount);
    bool equalAmts = qFabs(ingredientAmount - currentStep.getAmount()) < 0.01;
    // right ingredient in right order or just a correct ingredient
    if(!addedIngredients.contains(ingredient)) //if haven't previously played ingredient
    {
        //correct ingredient, order, amount
        if (currentStep.getItem() == ingredient && equalAmts)
            drinkPoints += 3;
        //correct order and ingredient; wrong amount
        else if (currentStep.getItem() == ingredient)
            drinkPoints += 2;
        // ingredient is in the drink, and correct amount, but wrong order
        else if (containsIngredient(ingredient, steps) && outOfOrderAmount(ingredient, steps, ingredientAmount))
            drinkPoints += 2;
        // ingredient is in the drink, wrong amount, wrong order
        else if (containsIngredient(ingredient, steps))
            drinkPoints++;
        // ingredient doesn't go in the drink, lose 3 points
        else
            drinkPoints -= 3;
        addedIngredients.insert(ingredient, ingredientAmount);
    }
    else //have previously played ingredient
    {
        addedIngredients[ingredient] += ingredientAmount;
        // if new amount is correct, get back the point lost or lose a point for another mistake
        if (outOfOrderAmount(ingredient, steps, addedIngredients[ingredient]))
            drinkPoints++;
        else
            drinkPoints--;
    }
    stepCount++;
}

bool Controller::containsIngredient(Ingredients::Ingredients ingredient, QVector<Step> steps)
{
    for (Step s : steps)
    {
        if (s.getItem() == ingredient)
            return true;
    }
    return false;
}

bool Controller::outOfOrderAmount(Ingredients::Ingredients ingredient, QVector<Step> steps, double amount)
{
    for (Step s : steps)
    {
        if (s.getItem() == ingredient && qFabs(amount - s.getAmount()) < 0.01)
            return true;
    }
    return false;
}

void Controller::drinkServed()
{
    endRound();
    QTimer::singleShot(3000, this, SLOT(startRound(difficulty)));
}

void Controller::endRound()
{
    timer->stop();
    endOfRoundHappinessBonus();
    calculateTip();
    standardizeHappiness();
    emit moodToGameArea(currentHappiness);
}

void Controller::endOfRoundHappinessBonus()
{
    if (currentHappiness > 0)       
        currentHappiness += ((5 * drinkPoints) / (drinkComplexity * 3)) - 2;
    qDebug() << "happiness after round: " << currentHappiness;
    moodValueModifier = currentHappiness / 5;
}

void Controller::calculateTip()
{
    if (currentHappiness > 0)
    {
        int tip = static_cast<int>((drinkPoints) * 10 * moodValueModifier);
        totalTipDollars += tip / 100;
        totalTipCents += tip % 100;
        totalTipDollars += totalTipCents / 100;
        totalTipCents = totalTipCents % 100;
        emit updateTipTotal(totalTipDollars, totalTipCents);
    }
}

void Controller::updateTipTotal(int newTipDollars, int newTipCents)
{
    totalTipDollars += newTipDollars;
    totalTipCents += newTipCents;
    emit tipAmountToGame(totalTipDollars, totalTipCents);
}

void Controller::standardizeHappiness()
{
    if (currentHappiness > 5)
        currentHappiness = 5;
}
