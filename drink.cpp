#include "drink.h"

Drink::Drink()
{
    IngredientsMap = QMap<Ingredients::Ingredients, double>();

    Trivia = QVector<QString>();

}

Drink::Drink(QString name)
{

    Name = name;
    IngredientsMap = QMap<Ingredients::Ingredients, double>();
    Trivia = QVector<QString>();

}

