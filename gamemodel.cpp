#include "gamemodel.h"

GameModel::GameModel()
{

}

void GameModel::startGame()
{

}

void GameModel::endGame()
{

}

void GameModel::addDrink(Drink* toAdd)
{

}

void GameModel::removeDrink(Drink* toRemove)
{

}

bool GameModel::isCorrectStep(Step stepToCheck)
{
    return false;
}

int GameModel::getTip()
{
    return accumulatedTips;
}

int GameModel::getSatisfiedCustomers()
{
    return customersSatisfied;
}

int GameModel::getDissatisfiedCustomers()
{
    return customersDissatisfied;
}

void GameModel::updateSatisfiedCustomers()
{

}

void GameModel::updateDissatisfiedCustomers()
{

}

int GameModel::getDrinksMadeRight()
{
    return drinksMadeRight;
}

int GameModel::getDrinksMadeWrong()
{
    return drinksMadeWrong;
}

void GameModel::updateDrinksMadeRight()
{

}

void GameModel::updateDrinksMadeWrong()
{

}
