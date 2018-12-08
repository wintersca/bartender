#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QString>
#include <QVector>
#include <QMap>
#include <QtMath>
#include <QDebug>
#include "drink.h"
#include "ingredients.h"
#include "ingredientsprite.h"
#include "qsfmlcanvas.h"
#include "xmldrinkparser.h"
#include "recordtracker.h"

class Controller : public QObject
{
    Q_OBJECT

public:
    explicit Controller(XMLDrinkParser *parser, QObject *parent = nullptr);
public slots:
    void timerUpdate();
    void startRound();

    // from custom Drink Importer
    void updateRecipes(Drink* newRecipe);

    // from gameArea
    void checkIngredient(Ingredients::Ingredients ingredient);
    void menuRequestByGameArea();


    // from MainWindow
    void menuRequestedByMainWindow();
    void menuInfoRequestedByMainWindow();
    void receiveUserSpecifiedMenu(QVector<Drink*> newMenu);
    void startGame(unsigned int difficulty);
    void receiveAmountToAdd(double amount);
    void drinkServed();
    void recordsRequestedByMainWindow();

signals:
    // to gameArea
    void moodToGameArea(int happinessLevel);
    void clearDrink();

    // to MainWindow
    void menuToMainWindow(QVector<Drink*> menu);
    void menuInfoToMainWindow(QVector<Drink*> menu);
    void recordsToMainWindow(QMap<QString, int>);
    void sendDrink(Drink* drink);
    void sendTime(int currentTime);
    void tipAmountToGame(int tipDollars, int tipCents);
    void requestAmountToAdd();
    void enableServe();

private:
    Drink* currentDrink;
    int currentHappiness;
    int standardizedHappiness;
    int stepCount;
    int easyTotalTipDollars;
    int medTotalTipDollars;
    int hardTotalTipDollars;
    int easyTotalTipCents;
    int medTotalTipCents;
    int hardTotalTipCents;
    int easyTotalCustomersSatisfied;
    int medTotalCustomersSatisfied;
    int hardTotalCustomersSatisfied;
    int easyTotalCustomersDissatisfied;
    int medTotalCustomersDissatisfied;
    int hardTotalCustomersDissatisfied;
    int easyTotalDrinksServed;
    int medTotalDrinksServed;
    int hardTotalDrinksServed;
    int timeToCompleteDrink;
    int drinkComplexity;
    int drinkPoints;
    unsigned int difficulty;
    double moodValueModifier;
    double ingredientAmount;
    QVector<Drink*> menu;
    QVector<Drink*> userSpecifiedMenu;
    QMap<Ingredients::Ingredients,double> addedIngredients;
    XMLDrinkParser *parser;
    QTimer *timer;
    QString trivia;

    //helper methods

    void calculateTip(int &dollars, int &cents); //when drink is served
    void decreaseHappiness();
    void endRound();
    QVector<Drink*> getAllRecipes();
    void newCustomer(unsigned int difficulty);
    Drink* selectNewRandomDrink();
    void updateTimer(int currentTime);
    void handleActionIngredients(QVector<Step> steps, Step current, Ingredients::Ingredients ingredient);
    void endOfRoundHappinessBonus();
    void standardizeHappiness();
    bool containsIngredient(Ingredients::Ingredients ingredient, QVector<Step> steps);
    bool outOfOrderAmount(Ingredients::Ingredients ingredient, QVector<Step> steps, double amount);
};

#endif // CONTROLLER_H
