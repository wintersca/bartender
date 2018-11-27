#ifndef DRINK_H
#define DRINK_H

#include <QString>
#include <QMap>
#include <QVector>
#include "ingredients.h"

class Drink
{
public:
    Drink();
    Drink(QString name);
    QString Name;
    QVector<QString> Trivia;
    QMap<Ingredients::Ingredients, double> IngredientsMap;
};

#endif // DRINK_H
