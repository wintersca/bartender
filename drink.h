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

    QString Name;
    QVector<QString> Trivia;
    QMap<Ingredients::Ingredients, double> IngredientsMap;

    void setName(QString name);
    void addTrivia(QString triv);
    void addIngredient(Ingredients::Ingredients ingredient, double amount);
    void addStep(QString instruction, Ingredients::Ingredients ingredient, double amount);
    void setSteps(QVector<Step> steps);
    void setSelected(bool select);
    QString getName();
    QVector<QString> getTrivia();
    QMap<Ingredients::Ingredients, double> getTngredients();
    QVector<Step> getSteps();
    bool getSelected();
    void print();
    

private:
    QVector<Step> Steps;
    bool userSelected;

};

#endif // DRINK_H
