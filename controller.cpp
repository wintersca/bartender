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


/*
 * Slots
 */

void Controller::receiveRecipe(QVector<Ingredients::Ingredients> includedIngredients)
{
    //TODO
    // format recipe
    // send recipe to database
}



