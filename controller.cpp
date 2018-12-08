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
        easyTotalTipDollars = 0;
        medTotalTipDollars = 0;
        hardTotalTipDollars = 0;
        easyTotalTipCents = 0;
        medTotalTipCents = 0;
        hardTotalTipCents = 0;
        easyTotalCustomersSatisfied = 0;
        medTotalCustomersSatisfied = 0;
        hardTotalCustomersSatisfied = 0;
        easyTotalCustomersDissatisfied = 0;
        medTotalCustomersDissatisfied = 0;
        hardTotalCustomersDissatisfied = 0;
        easyTotalDrinksServed = 0;
        medTotalDrinksServed = 0;
        hardTotalDrinksServed = 0;
    }
    else
    {
        for(QString data: historicalData.keys())
        {
            if(data.compare("EasyTipDollars"))
            {
                easyTotalTipDollars = historicalData.value(data);
            }
            if(data.compare("EasyTipCents"))
            {
                easyTotalTipCents = historicalData.value(data);
            }
            if(data.compare("EasyCustomersSatisfied"))
            {
                easyTotalCustomersSatisfied = historicalData.value(data);
            }
            if(data.compare("EasyCustomerDissatisfied"))
            {
                easyTotalCustomersDissatisfied = historicalData.value(data);
            }
            if(data.compare("EasyDrinksServed"))
            {
                easyTotalDrinksServed = historicalData.value(data);
            }
            if(data.compare("MedTipDollars"))
            {
                medTotalTipDollars = historicalData.value(data);
            }
            if(data.compare("MedTipCents"))
            {
                medTotalTipCents = historicalData.value(data);
            }
            if(data.compare("MedCustomersSatisfied"))
            {
                medTotalCustomersSatisfied = historicalData.value(data);
            }
            if(data.compare("MedCustomerDissatisfied"))
            {
                medTotalCustomersDissatisfied = historicalData.value(data);
            }
            if(data.compare("MedDrinksServed"))
            {
                medTotalDrinksServed = historicalData.value(data);
            }
            if(data.compare("HardTipDollars"))
            {
                hardTotalTipDollars = historicalData.value(data);
            }
            if(data.compare("HardTipCents"))
            {
                hardTotalTipCents = historicalData.value(data);
            }
            if(data.compare("HardCustomersSatisfied"))
            {
                hardTotalCustomersSatisfied = historicalData.value(data);
            }
            if(data.compare("HardCustomerDissatisfied"))
            {
                hardTotalCustomersDissatisfied = historicalData.value(data);
            }
            if(data.compare("HardDrinksServed"))
            {
                hardTotalDrinksServed = historicalData.value(data);
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

void Controller::menuInfoRequestedByMainWindow()
{
    emit menuInfoToMainWindow(menu);
}

void Controller::recordsRequestedByMainWindow()
{
    QMap<QString, int> historicalData = RecordTracker::parseGameRecord();
    emit recordsToMainWindow(historicalData);
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
}

void Controller::startGame(unsigned int difficultyInit)
{
    difficulty = difficultyInit;
    emit clearDrink();
    if(difficulty==0){
        emit tipAmountToGame(easyTotalTipCents, easyTotalTipDollars);
    }else if (difficulty ==1){
        emit tipAmountToGame(medTotalTipCents, medTotalTipDollars);
    }else{
        emit tipAmountToGame(hardTotalTipCents, hardTotalTipDollars);
    }
    startRound();
}

void Controller::startRound()
{
    newCustomer(difficulty);
    drinkComplexity = currentDrink->getSteps().length();
    drinkPoints = 0;
    timeToCompleteDrink = static_cast<int>(moodValueModifier * 15 * drinkComplexity);
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
    if (currentHappiness >= 0)
    {
        emit sendTime(timeToCompleteDrink--);
        if (timeToCompleteDrink < 0 && timeToCompleteDrink % static_cast<int>(5*moodValueModifier) == 0)
            emit moodToGameArea(currentHappiness--);
    }
    else
        emit sendTime(timeToCompleteDrink--);
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
    QTimer::singleShot(1000, this, SLOT(startRound()));
    emit clearDrink();
}

void Controller::endRound()
{
    timer->stop();
    endOfRoundHappinessBonus();
    // record game data
    QMap<QString, int> toRecord;
    if(difficulty==0)
    {
        calculateTip(easyTotalTipDollars, easyTotalTipCents);
        easyTotalDrinksServed++;
    }
    else if(difficulty==1)
    {
        calculateTip(medTotalTipDollars, medTotalTipCents);
        medTotalDrinksServed++;
    }
    else
    {
        (hardTotalTipDollars, hardTotalTipCents);
        hardTotalDrinksServed++;
    }


    toRecord["EasyTipDollars"] = easyTotalTipDollars;
    toRecord["EasyTipCents"] = easyTotalTipCents;
    toRecord["EasyCustomersSatisfied"] = easyTotalCustomersSatisfied;
    toRecord["EasyCustomerDissatisfied"] = easyTotalCustomersDissatisfied;
    toRecord["EasyDrinksServed"] = easyTotalDrinksServed;

    toRecord["MedTipDollars"] = medTotalTipDollars;
    toRecord["MedTipCents"] = medTotalTipCents;
    toRecord["MedCustomersSatisfied"] = medTotalCustomersSatisfied;
    toRecord["MedCustomerDissatisfied"] = medTotalCustomersDissatisfied;
    toRecord["MedDrinksServed"] = medTotalDrinksServed;

    toRecord["HardTipDollars"] = hardTotalTipDollars;
    toRecord["HardTipCents"] = hardTotalTipCents;
    toRecord["HardCustomersSatisfied"] = hardTotalCustomersSatisfied;
    toRecord["HardCustomerDissatisfied"] = hardTotalCustomersDissatisfied;
    toRecord["HardDrinksServed"] = hardTotalDrinksServed;

    RecordTracker::writeGameRecord(toRecord);
    standardizeHappiness();
    emit moodToGameArea(currentHappiness);
}

void Controller::endOfRoundHappinessBonus()
{
    if (drinkPoints <= 0)
        currentHappiness = 0;
    if (currentHappiness > 0)
        currentHappiness += ((5 * drinkPoints) / (drinkComplexity * 3)) - 2;
    moodValueModifier = currentHappiness / 5;
}

void Controller::calculateTip(int &dollars, int &cents)
{
    if (currentHappiness > 0)
    {
        int tip = static_cast<int>(drinkPoints * 10 * moodValueModifier);
        dollars += tip / 100;
        cents += tip % 100;
        dollars += cents / 100;
        cents = cents % 100;
        emit tipAmountToGame(dollars, cents);
        if(difficulty==0){
            easyTotalTipDollars+= dollars;
            easyTotalTipCents+= cents;
        }else if (difficulty ==1){
            medTotalTipDollars += dollars;
            medTotalTipCents+= cents;
        }else{
            hardTotalTipDollars+=dollars;
            hardTotalTipCents+=cents;
        }
    }
}

void Controller::standardizeHappiness()
{
    if (currentHappiness > 5)
        currentHappiness = 5;
    else if (currentHappiness < 0)
        currentHappiness = 0;

    // update customer satisfaction counts
    if(difficulty==0)
        {
            if(currentHappiness >= 3)
                easyTotalCustomersSatisfied++;
            else
                easyTotalCustomersDissatisfied++;

        }
    else if(difficulty==1)
        {
            if(currentHappiness >= 3)
                medTotalCustomersSatisfied++;
            else
                medTotalCustomersDissatisfied++;

        }
    else
        {
            if(currentHappiness >= 3)
                hardTotalCustomersSatisfied++;
            else
                hardTotalCustomersDissatisfied++;

        }

}


