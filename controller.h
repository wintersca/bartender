#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QString>
#include "customdrinkimporter.h"
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
    Recipe selectRecipe();
    void selectCustomerType();
    bool checkRecipe();
    void calculateTip(int customerMood, int customerType);
    void updateTips(double currentTip);
    void shake();
    void blend();
    void createGame();
    QString getTrivia(Recipe current);



signals:
    void showTrivia(QString trivia);
    void updateCustomerMood(int mood);
    void updateTipDisplay();
    void updateTimer();
    void showRecipe();
    void wrongIngredient();
    void wrongTool();
    void sendObjLocation(std::vector<int> newLocation);


public slots:
    void ingredientAdded(Ingredient ing);
    void selectDifficulty(int difficulty);
    void removeRecipe(QString recipe);
    void addRecipe(QString recipe);
    void recObjLocation(std::vector<int> location);
    void newRecipe(Recipe new);
    void drinkServed();

};

#endif // CONTROLLER_H
