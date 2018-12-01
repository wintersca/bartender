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
        emit customerHappinessToGame(currentHappiness);
        QTimer::singleShot(customerPatience, this, SLOT(decreaseHappiness()));
    }
}

void Controller::newCustomer()
{
    qDebug() << "Received request for a new customer";
    srand(static_cast<unsigned int>(time(nullptr)));
    stepCount = 0;
    currentHappiness = QRandomGenerator::global()->generate()%5 + 4; // start at happiness of 4 - 8
    currentDrink = menu.at(QRandomGenerator::global()->generate()%(menu.length()));
    int drinkComplexity = currentDrink->IngredientsMap.size();
    emit customerHappinessToGame(currentHappiness);
    emit sendDrink(currentDrink);
    QVector<QString> trivia = currentDrink->getTrivia();
    QString currentTrivia = trivia.at(rand()%trivia.length());
    emit triviaToGame(currentTrivia);
    customerPatience = drinkComplexity * 5000 / currentHappiness; //how long before happiness level drops. I gave each step 5 sec
    QTimer::singleShot(customerPatience, this, SLOT(decreaseHappiness()));
}

/*
 * Interactions with MainWindow
 */

void Controller::startGame(unsigned int difficulty)
{
    qDebug() << "current difficulty is " << difficulty << "\n";
    setUpRound(difficulty);
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

void Controller::setUpRound(unsigned int difficulty)
{
    /* TODO:
     * create a new customer
     * create a new timer
     * calculate time to make drink (3 seconds per ingredient * mood modifier)
     * calculate tip modifier
     * select a random recipe
     * send customer entering animation to gameArea
     * send random recipe trivia to gameArea
     * send time to main window every second
     * send drink to main window
     */
}

void Controller::endRound()
{
    /* TODO:
     * calculate tip
     * send final mood sprite to game area (1 second)
     * send customer leaving animation to game area (2 seconds?)
     * send tip to Main Window (wait 1 second)
     * call setUpRound
     */
}

void Controller::calculateTip()
{
    int drinkComplexity = currentDrink->IngredientsMap.size();
    double tip = (drinkComplexity - errorCount) * .25; //you get 25 cent tip per correct step
    int tipDollars = 0; // calculate these
    int tipCents = 0;
    emit updateTipTotal(tipDollars, tipCents);
}
