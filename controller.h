#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QString>
#include <QVector>
#include <QMap>
#include <QRandomGenerator>
#include <QtMath>
#include "drink.h"
#include "gamearea.h"
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
    void updateRecipes(Drink* newRecipe);
    void newCustomer();
    void addedIngredient(Ingredients::Ingredients ingredient, double amount);
    void decreaseHappiness();
    void calculateTip(); //when drink is served
    void startGame(unsigned int difficulty);
signals:
    void submitNewRecipes(Drink* newDrink);
    void menuToGame(QVector<Drink*> menu);
    void newCustomerToGame(int happinessLevel, Drink* drink);
    void customerHappinessToGame(int happinessLevel);
    void customerLeft();
    void sendDrink(Drink* drink);
    void triviaToGame(QString trivia);
    void ingredientVerificationToGame(bool isCorrect);
    void tipAmountToGame(double tip);
    void sendTime(int currentTime);


private:
    Drink* currentDrink;
    int customerPatience;
    int currentHappiness;
    int stepCount;
    int errorCount;
    QVector<Drink*> menu;
    XMLDrinkParser *parser;
    QVector<Drink*> getAllRecipes();
    void updateTimer(int currentTime);

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
