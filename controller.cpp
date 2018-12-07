#include "controller.h"

// set up controller
Controller::Controller(XMLDrinkParser *parserInit, QObject *parent) : QObject(parent)
{
    parser = parserInit;
    menu = getAllRecipes();
    userSpecifiedMenu = menu;
    currentDrink = nullptr;
    for (Drink* drink : menu)
        drink->setSelected(true);

    // grab game record if there is one
    QMap<QString, int> historicalData = RecordTracker::parseGameRecord();

    if(historicalData.size() == 0)
    {
        totalTipDollars = 0;
        totalTipCents = 0;
        totalCustomersSatisfied = 0;
        totalCustomersDissatisfied = 0;
        totalDrinksServed = 0;
    }
    else
    {
        for(QString data: historicalData.keys())
        {
            if(data.compare("TipDollars"))
            {
                totalTipDollars = historicalData.value(data);
            }

            if(data.compare("TipCents"))
            {
                totalTipCents = historicalData.value(data);
            }

            if(data.compare("CustomersSatisfied"))
            {
                totalCustomersSatisfied = historicalData.value(data);
            }

            if(data.compare("CustomerDissatisfied"))
            {
                totalCustomersDissatisfied = historicalData.value(data);
            }

            if(data.compare("DrinksServed"))
            {
                totalDrinksServed = historicalData.value(data);
            }
        }
    }
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
    startRound();
}

void Controller::startRound()
{
    newCustomer(difficulty);
    drinkComplexity = currentDrink->IngredientsMap.size();
    drinkPoints = 0;
    timeToCompleteDrink = static_cast<int>(moodValueModifier * 10 * drinkComplexity);
    emit sendDrink(currentDrink);
    emit moodToGameArea(currentHappiness);
    emit enableServe();
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
    qsrand(time(nullptr));
    int rand = static_cast<int>(qFabs(static_cast<int>(qrand())));
    switch(difficulty)
    {
        case 0:
        {
            currentHappiness = (rand % 3) + 3;
            break;
        }
        case 1:
        {
            currentHappiness = (rand % 3) + 2;
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
    qsrand(time(nullptr));
    int rand = static_cast<int>(qFabs(static_cast<int>(qrand())));
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
    if (currentDrink == nullptr)
        return;
    emit requestAmountToAdd();
    QVector<Step> steps = currentDrink->getSteps();
    Step currentStep;
    if (stepCount < steps.length())
        currentStep = steps.at(stepCount);
    bool equalAmts = qFabs(ingredientAmount - currentStep.getAmount()) < 0.01;

    // actions (stir, etc.) don't have amounts and as such are handled differently
    if (ingredient >= 49 && ingredient <= 51)
        handleActionIngredients(steps, currentStep, ingredient);
    // ingredients are added according to recipe
    else if(!addedIngredients.contains(ingredient) && stepCount < steps.length())
    {
        if (currentStep.getItem() == ingredient && equalAmts)
            drinkPoints += 3;
        else if (currentStep.getItem() == ingredient)
            drinkPoints += 2;
        else if (containsIngredient(ingredient, steps) && outOfOrderAmount(ingredient, steps, ingredientAmount))
            drinkPoints += 2;
        else if (containsIngredient(ingredient, steps))
            drinkPoints++;
        else
            drinkPoints -= 3;
        addedIngredients.insert(ingredient, ingredientAmount);
    }
    // ingredients are added out of order
    else
    {
        if (!addedIngredients.contains(ingredient))
            addedIngredients.insert(ingredient, 0);
        addedIngredients[ingredient] += ingredientAmount;
        if (outOfOrderAmount(ingredient, steps, addedIngredients[ingredient]))
            drinkPoints++;
        else
            drinkPoints -= 3;
    }
    stepCount++;
}

void Controller::handleActionIngredients(QVector<Step> steps, Step current, Ingredients::Ingredients ingredient)
{
    if (stepCount < steps.length() && current.getItem() == ingredient)
    {
        drinkPoints += 3;
        addedIngredients.insert(ingredient, 0);
        stepCount++;
    }
    else if (containsIngredient(ingredient, steps) && !addedIngredients.contains(ingredient))
    {
        drinkPoints += 1;
        stepCount++;
    }
    else
        drinkPoints -= 3;
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
    totalDrinksServed++;
    QTimer::singleShot(1000, this, SLOT(startRound()));
    emit clearDrink();
}

void Controller::endRound()
{
    timer->stop();
    endOfRoundHappinessBonus();
    calculateTip();
    standardizeHappiness();
    emit moodToGameArea(currentHappiness);

    totalDrinksServed++;

    // record game data
    QMap<QString, int> toRecord;
    toRecord["TipDollars"] = totalTipDollars;
    toRecord["TipCents"] = totalTipCents;
    toRecord["CustomersSatisfied"] = totalCustomersSatisfied;
    toRecord["CustomerDissatisfied"] = totalCustomersDissatisfied;
    toRecord["DrinksServed"] = totalDrinksServed;

    RecordTracker::writeGameRecord(toRecord);
}

void Controller::endOfRoundHappinessBonus()
{
    if (drinkPoints == 0)
        currentHappiness = 0;
    if (currentHappiness > 0)
        currentHappiness += ((5 * drinkPoints) / (drinkComplexity * 3)) - 2;
    moodValueModifier = currentHappiness / 5;
}

void Controller::calculateTip()
{
    if (currentHappiness > 0)
    {
        int tip = static_cast<int>((drinkPoints) * (10 * moodValueModifier));
        totalTipDollars += tip / 100;
        totalTipCents += tip % 100;
        totalTipDollars += totalTipCents / 100;
        totalTipCents = totalTipCents % 100;
        emit tipAmountToGame(totalTipDollars, totalTipCents);
    }
}

void Controller::standardizeHappiness()
{
    if (currentHappiness > 5)
        currentHappiness = 5;
    else if (currentHappiness < 0)
        currentHappiness = 0;

    // update customer satisfaction counts
    if(currentHappiness >= 3)
        totalCustomersSatisfied++;
    else
        totalCustomersDissatisfied++;
}
