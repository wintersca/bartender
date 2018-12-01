#include <QVector>
#include <drink.h>
#include <step.h>
#include <recordtracker.h>

#ifndef GAMEMODEL_H
#define GAMEMODEL_H


class GameModel
{
private:
    QVector<Drink*> allDrinks;
    Drink* currentDrink;
    Step currentStep;
    double accumulatedTips;
    int customersSatisfied;
    int customersDissatisfied;
    int drinksMadeRight;
    int drinksMadeWrong;

public:
    GameModel();
    void startGame();
    void endGame();
    void addDrink(Drink* toAdd);
    void removeDrink(Drink* toRemove);
    bool isCorrectStep(Step stepToCheck);
    int getTip();
    int getSatisfiedCustomers();
    int getDissatisfiedCustomers();
    void updateSatisfiedCustomers();
    void updateDissatisfiedCustomers();
    int getDrinksMadeRight();
    int getDrinksMadeWrong();
    void updateDrinksMadeRight();
    void updateDrinksMadeWrong();

};

#endif // GAMEMODEL_H
