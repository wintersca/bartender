#include "drink.h"

Drink::Drink()
{
    IngredientsMap = QMap<Ingredients::Ingredients, double>();
    trivia = QVector<QString>();
}

Drink::Drink(QString name)
{
    name = name;
    IngredientsMap = QMap<Ingredients::Ingredients, double>();
    trivia = QVector<QString>();
}

