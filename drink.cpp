#include "drink.h"

Drink::Drink(QString name)
{
    Name = name;
    IngredientsMap = QMap<Ingredients::Ingredients, int>();
}
