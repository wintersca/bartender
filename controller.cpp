#include "controller.h"

int customerType = 0;
int customerMood = 100;
double tipMultiplier = 1.0;
double totalTips = 0;
int difficulty = 0;
int customers[1000];
int turn = 0;
double price = 0;


Controller::Controller(QObject *parent) : QObject(parent)
{
    //set up customer queue change the % to reflect the number of customer types
    srand(static_cast<unsigned int>(time(nullptr)));
    for (unsigned int i = 0; i < 1000; i++)
    {
        customers[i] = rand()%4;
    }
}

/*
 * Helper Methods
 */

void selectRecipe()
{
    //TODO
}

void selectCustomerType()
{
    int customerType = customers[turn];
    switch (customerType)
    {
        case 0 :
        {
            customerMood = 100;
            tipMultiplier = 0.5;
        }
        case 1 :
        {
            customerMood = 100;
            tipMultiplier = 0.3;
        }
        case 2 :
        {
            customerMood = 80;
            tipMultiplier = 0.3;
        }
        case 3 :
        {
            customerMood = 50;
            tipMultiplier = 0.15;
        }
    }
}

bool checkRecipe()
{
    //TODO
}

double calculateTip()
{
    return price*tipMultiplier;
}

void updateTips(double currentTip)
{
    totalTips += currentTip;
}

void shake()
{
    //TODO
}

void blend()
{
    //TODO
}

void createGame()
{
    //TODO
}

void getTrivia(Recipe current)
{
    //TODO
}

/*
 * Signals
 */

void showTrivia(QString trivia);
void updateCustomerMood(int mood);
void updateTipDisplay(int tips);
void updateTimer();
void showRecipe();
void wrongIngredient();
void wrongTool();
void sendObjLocation(std::vector<int> newLocation);

/*
 * Slots
 */

void ingredientAdded(Ingredient ing)
{
    if (!checkRecipe(ing))
        emit wrongIngredient();
}

void selectDifficulty(int val)
{
    difficulty = val;
}

void removeRecipe(QString recipe);
void addRecipe(QString recipe);
void recObjLocation(std::vector<int> location);
void newRecipe(Recipe new);
void drinkServed()
{
    updateTips(calculateTip());
    turn++;
    selectCustomerType();
    Recipe nextDrink = selectRecipe();
    emit updateCustomerMood(customerMood);
    emit showRecipe(nextDrink);
    emit showTrivia(getTrivia(nextDrink));
}



