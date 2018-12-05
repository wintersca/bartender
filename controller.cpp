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

/*
 * interactions with the xml database
 */

QVector<Drink*> Controller::getAllRecipes()
{
    QVector<Drink*> menu = parser->parseXMLDatabase();
    qDebug() << "We have received a vector of recipes from the database";
    return menu;
}

void Controller::updateRecipes(Drink* newRecipe)
{
    parser->updateXMLDatabase(newRecipe);
    menu.append(newRecipe);
    userSpecifiedMenu.append(newRecipe);
    qDebug() << "We have sent a recipe to the database and updated the menu of the game";
}

/*
 * Customer functions
 */

void Controller::newCustomer(unsigned int difficulty)
{
    int rand = static_cast<int>(qFabs(static_cast<int>(QRandomGenerator::global()->generate())));
    selectedCustomer = rand % 5;
    currentHappiness = (rand % 5) + 5 - static_cast<int>(difficulty);
    currentDrink = selectNewRandomDrink();
    for (Step s : currentDrink->getSteps())
        qDebug() << s.getItem();
    moodValueModifier = static_cast<double>(currentHappiness) / 10;
    stepCount = 0;
    addedIngredients.clear();
}

/*
 * Interactions with MainWindow
 */

void Controller::startGame(unsigned int difficultyInit)
{
    difficulty = difficultyInit;
    startRound(difficulty);
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

void Controller::updateTimer(int currentTime)
{
    emit sendTime(currentTime);
}

void Controller::updateTipTotal(int newTipDollars, int newTipCents)
{
    totalTipDollars += newTipDollars;
    totalTipCents += newTipCents;
    emit tipAmountToGame(totalTipDollars, totalTipCents);
}

/*
 * Interactions with GameArea
 */

void Controller::checkIngredient(Ingredients::Ingredients ingredient, double amount)
{
    QVector<Step> steps = currentDrink->getSteps();
    Step currentStep = steps.at(stepCount);
    bool equalAmts = qFabs(amount - currentStep.getAmount()) < 0.01;
    // right ingredient in right order or just a correct ingredient
    if(!addedIngredients.contains(ingredient)) //if haven't previously played ingredient
    {
        if(currentStep.getItem() == ingredient)
            drinkPoints += 2;
        else
        {
            for (Step s : steps)
            {
                if (s.getItem() == ingredient){
                    drinkPoints++;
                    break;
                }
            }
        }
        if(equalAmts)
            drinkPoints++;
        addedIngredients.insert(ingredient, amount);
    }
    else //have previously played ingredient
    {
        if(qFabs(addedIngredients[ingredient] - currentStep.getAmount()) < 0.01) //have already added correct amount
            drinkPoints--; //lose points given for correct amount
        addedIngredients[ingredient] += amount;
    }
    stepCount++;
}

void Controller::menuRequestByGameArea()
{
   emit menuToMainWindow(menu);
}

void Controller::drinkServed()
{
    endRound();
    QTimer::singleShot(3000, this, SLOT(startRound(difficulty)));
}

/*
 * GamePlay
 */

void Controller::startRound(unsigned int difficulty)
{
    newCustomer(difficulty);
    drinkComplexity = currentDrink->IngredientsMap.size();
    drinkPoints = 0;
    timeToCompleteDrink = static_cast<int>(moodValueModifier * 8 * drinkComplexity);
    emit sendDrink(currentDrink);
    emit moodToGameArea(currentHappiness);
    emit sendSelectedCustomer(selectedCustomer);
    if(difficulty != 0) //easy
    {
        timer->start(1000);
        emit sendTime(timeToCompleteDrink);
    }
    else
        emit sendTime(0);
}

void Controller::endRound()
{
    timer->stop();
    endOfRoundHappiness();    
    calculateTip();
    emit moodToGameArea(currentHappiness);
}

void Controller::calculateTip()
{
    if (currentHappiness <= 0)
        return;
    int tip = (drinkPoints) * 10;
    totalTipDollars += tip / 100;
    totalTipCents += tip % 100;
    totalTipDollars += totalTipCents / 100;
    totalTipCents = totalTipCents % 100;
    emit updateTipTotal(totalTipDollars, totalTipCents);
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

void Controller::endOfRoundHappiness()
{
    if (currentHappiness > 0)
    {
        int drinkScore = 100 * drinkPoints / drinkComplexity * 3;
        if (drinkScore == 100)
            currentHappiness += 3;
        else if (drinkScore >= 90)
            currentHappiness += 2;
        else if (drinkScore >= 75)
            currentHappiness += 1;
        else if (drinkScore >= 50)
            currentHappiness += 0;
        else if (drinkScore >= 25)
            currentHappiness -= 1;
        else if (drinkScore >= 10)
            currentHappiness -= 2;
        else if (drinkScore >= 0)
            currentHappiness -= 3;
    }
}

Drink* Controller::selectNewRandomDrink()
{
    int rand = static_cast<int>(qFabs(static_cast<int>(QRandomGenerator::global()->generate())));
    currentDrink = userSpecifiedMenu[rand % userSpecifiedMenu.length()];
    return currentDrink;
}
