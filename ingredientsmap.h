#ifndef INGREDIENTSMAP_H
#define INGREDIENTSMAP_H

#include <QMap>
#include "ingredients.h"

class IngredientsMap
{
public:
    IngredientsMap();
    QMap<QString, Ingredients::Ingredients> stringsToIngredients;
};

#endif // INGREDIENTSMAP_H
