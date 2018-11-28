#ifndef DRINK_H
#define DRINK_H

#include <QString>
#include <QMap>
#include <QVector>
#include "ingredients.h"
#include "step.h"

class Drink
{
public:
    Drink();
    Drink(QString name);
    void setName(QString name);
    void addTrivia(QString triv);
    void addIngredient(Ingredients::Ingredients ingredient, double amount);
    void addAction(QString instruction, Ingredients::Ingredients ingredient, double amount);
    void setSelected(bool select);
    QString getName();
    QVector<QString> getTrivia();
    QMap<Ingredients::Ingredients, double> getTngredients();
    QVector<Step> getActions();
    bool getSelected();

    //To make private and fix
    QString name;
    QVector<QString> trivia;
    QMap<Ingredients::Ingredients, double> IngredientsMap;
    QVector<Step> steps;
    bool userSelected;
private:

};

#endif // DRINK_H
