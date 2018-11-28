#include "controller.h"

Controller::Controller(QObject *parent) : QObject(parent)
{

}


// slots
void Controller::receiveRecipe(Drink newDrink)
{
    qDebug() << "We have received a new recipe";
}

// signals

// helpers
