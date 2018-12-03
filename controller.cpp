#include "controller.h"

// set up controller
Controller::Controller(XMLDrinkParser *parserInit, QObject *parent) : QObject(parent)
{
    parser = parserInit;
    menu = getAllRecipes();
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
    qDebug() << "We have sent a recipe to the database and updated the menu of the game";
}

/*
 * Customer functions
 */

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
        QTimer::singleShot(customerPatience, this, SLOT(decreaseHappiness()));
    }
}

void Controller::newCustomer(unsigned int difficulty)
{
    // easy->(0, 1, 2)<- hard
    qDebug() << "Received request for a new customer";
    int rand = static_cast<int>(qFabs(static_cast<int>(qrand())));
    currentHappiness = (rand % 5) + 5 - static_cast<int>(difficulty);
    qDebug() << "current happiness: " << currentHappiness;
    qDebug() << "menu size: " << menu.length() << " drink index: " << rand % menu.length();
    currentDrink = menu[rand % menu.length()];
    moodValueModifier = static_cast<double>(currentHappiness) / 10;
    qDebug() << "mood Modifier: " << moodValueModifier;
}

/*
 * Interactions with MainWindow
 */

void Controller::startGame(unsigned int difficultyInit)
{
    qDebug() << "current difficulty is " << difficulty << "\n";
    difficulty = difficultyInit;
    startRound(difficulty);
}

void Controller::menuRequestedByMainWindow()
{
    emit menuToMainWindow(menu);
}

void Controller::receiveUserSpecifiedMenu(QVector<Drink*> newMenu)
{
    menu = newMenu;
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

void Controller::addedIngredient(Ingredients::Ingredients ingredient, double amount)
{
    QVector<Step> steps = currentDrink->getSteps();
    Step currentStep = steps.at(stepCount);
    bool isCorrectIngredient = false;
    bool equalAmts = qFabs(amount - currentStep.getAmount()) < 0.01;
    if(currentStep.getItem() == ingredient && equalAmts)
        isCorrectIngredient = true;
    stepCount++;
    emit ingredientVerificationToGame(isCorrectIngredient);

}

void Controller::menuRequestByGameArea()
{
    emit menuToGameArea(menu);
}

/*
 * GamePlay
 */

void Controller::startRound(unsigned int difficulty)
{
    newCustomer(difficulty);
    drinkComplexity = currentDrink->IngredientsMap.size();
    qDebug() << "Drink complexity: " << drinkComplexity;
    timeToCompleteDrink = static_cast<int>(moodValueModifier * 5 * drinkComplexity);
    qDebug() << "Time to complete: " << timeToCompleteDrink;
    emit sendDrink(currentDrink);
    emit sendTime(timeToCompleteDrink);
    timer->start(1000);
    /* TODO:
     * send customer entering animation to gameArea
     * send random recipe trivia to gameArea
     */
}

void Controller::endRound()
{
    timer->stop();
    calculateTip();
    /* TODO:

     * send final mood sprite to game area (1 second)
     * send customer leaving animation to game area (2 seconds?)
     * send tip to Main Window (wait 1 second)
     * call setUpRound
     */
}

void Controller::calculateTip()
{
    if (currentHappiness <= 0)
        return;
    int tip = (drinkComplexity - errorCount) * 25; //you get 25 cent tip per correct step
    totalTipDollars += tip / 100;
    totalTipCents += tip % 100;
    totalTipDollars += totalTipCents / 100;
    totalTipCents = totalTipCents % 100;
    emit updateTipTotal(totalTipDollars, totalTipCents);
}

void Controller::timerUpdate()
{
    if (currentHappiness <= 0)
    {
        endRound();
        return;
    }
    emit sendTime(timeToCompleteDrink--);
    qDebug() << "Time sent to mainWindow: " << timeToCompleteDrink;
    qDebug() << "CurrentHappiness: " << currentHappiness;
    if (timeToCompleteDrink < 0)
    {
        if (timeToCompleteDrink % static_cast<int>(5*moodValueModifier) == 0)
        {
            currentHappiness--;
        }
    }
}
