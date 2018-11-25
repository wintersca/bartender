#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QString>
#include <QVector>
#include "gamearea.h"
#include "ingredients.h"
#include "qsfmlcanvas.h"


extern int customerType;
extern int customerMood;
extern double tipMultiplier;
extern double totalTips;
extern int difficulty;
extern int customers[];
extern int turn;
extern double price;

class Controller : public QObject
{
public:
    explicit Controller(QObject *parent = nullptr);
    void selectCustomerType();
    bool checkRecipe(QString ingredient);
    void calculateTip(int customerMood, int customerType);
    void updateTips(double currentTip);
    void shake();
    void blend();
    void createGame();




signals:
    void showTrivia(QString trivia);
    void updateCustomerMood(int mood);
    void updateTipDisplay();
    void updateTimer();
    void showRecipe();
    void wrongIngredient();
    void wrongTool();
    void sendObjLocation(std::vector<int> newLocation);
    //QString getTrivia(Recipe current);


public slots:
    void ingredientAdded(QString ingredient);
    void selectDifficulty(int difficulty);
    void removeRecipe(QString recipe);
    void addRecipe(QString recipe);
    void recObjLocation(std::vector<int> location);
    void drinkServed();
    void receiveRecipe(QVector<Ingredients::Ingredients>);

};

#endif // CONTROLLER_H
