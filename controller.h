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
    void startRound(unsigned int difficulty);
    // from custom Drink Importer

    void updateRecipes(Drink* newRecipe);

    // from gameArea

    void checkIngredient(Ingredients::Ingredients ingredient, double amount);
    void menuRequestByGameArea();
    void drinkServed();

    // from MainWindow

    void menuRequestedByMainWindow();
    void receiveUserSpecifiedMenu(QVector<Drink*> newMenu);
    void startGame(unsigned int difficulty);

signals:
    // to gameArea


    void moodToGameArea(int happinessLevel);
    void triviaToGameArea(QString trivia);
    void sendSelectedCustomer(int customer);

    // to MainWindow

    void menuToMainWindow(QVector<Drink*> menu);
    void sendDrink(Drink* drink);
    void sendTime(int currentTime);
    void tipAmountToGame(int tipDollars, int tipCents);

private:
    Drink* currentDrink;
    int selectedCustomer;
    int currentHappiness;
    int stepCount;
    int errorCount;
    int totalTipDollars;
    int totalTipCents;
    int timeToCompleteDrink;
    int drinkComplexity;
    int drinkPoints;
    unsigned int difficulty;
    double moodValueModifier;
    QVector<Drink*> menu;
    QVector<Drink*> userSpecifiedMenu;
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
    void endOfRoundHappiness();





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
