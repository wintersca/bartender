#ifndef DRINK_H
#define DRINK_H

#include <QString>
#include <QMap>
#include "ingredients.h"

class Drink
{
public:
    Drink(QString name);
    QString Name;
    QMap<Ingredients::Ingredients, int> IngredientsMap;
};

#endif // DRINK_H
