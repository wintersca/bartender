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
    void addAction(QString instruction, Ingredients::Ingredients ingredient, double amount);
    void setSelected(bool select);
    QString getName();
    QVector<QString> getTrivia();
    QMap<Ingredients::Ingredients, double> getTngredients();
    QVector<Step> getActions();
    bool getSelected();

    
    QVector<Step> Steps;
    bool userSelected;
private:


};

#endif // DRINK_H
