#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QString>
#include <QVector>
#include <QMap>
#include <QRandomGenerator>
#include <QtMath>
#include <QDebug>
#include "drink.h"
#include "ingredients.h"
#include "ingredientsprite.h"
#include "qsfmlcanvas.h"
#include "xmldrinkparser.h"


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
    void receiveUserSpecifiedMenu(QVector<Drink*> newMenu);
    void startGame(unsigned int difficulty);
    void receiveAmountToAdd(double amount);
    void drinkServed();

signals:
    // to gameArea
    void moodToGameArea(int happinessLevel);
    void clearDrink();

    // to MainWindow
    void menuToMainWindow(QVector<Drink*> menu);
    void sendDrink(Drink* drink);
    void sendTime(int currentTime);
    void tipAmountToGame(int tipDollars, int tipCents);
    void requestAmountToAdd();

private:
    Drink* currentDrink;
    int currentHappiness;
    int standardizedHappiness;
    int stepCount;
    int totalTipDollars;
    int totalTipCents;
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

    void calculateTip(); //when drink is served
    void decreaseHappiness();
    void endRound();
    QVector<Drink*> getAllRecipes();
    void newCustomer(unsigned int difficulty);
    Drink* selectNewRandomDrink();
    void updateTimer(int currentTime);
    void updateTipTotal(int newTipDollars, int newTipCents);
    void endOfRoundHappinessBonus();
    void standardizeHappiness();
    bool containsIngredient(Ingredients::Ingredients ingredient, QVector<Step> steps);
    bool outOfOrderAmount(Ingredients::Ingredients ingredient, QVector<Step> steps, double amount);





};

#endif // CONTROLLER_H








/* template signals TO controller
 * all of these go in the class you are connecting with, not the controller.
 *
   QObject::connect(ui->uiElement, &QElementType::action,
                    controller, &Controller::socketName);
   QObject::connect(this, &MainWindow::functionName,
                    controller, &Controller::socketName);


   template signal FROM controller

   QObject::connect(controller, &Controller::signalName,
                    this, &MainWindow::slotName);
*/
