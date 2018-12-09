#ifndef INGREDIENTSMAP_H
#define INGREDIENTSMAP_H

#include <QMap>
#include "ingredients.h"

/*
 * The ingredients map provides a map to translate strings to ingredient enums.
 * This is a class so it can be used by multiple other classes.
 * Author: Alex Smith
 */

class IngredientsMap
{
public:
    IngredientsMap();

    // A map of QStrings to ingredient enums.
    QMap<QString, Ingredients::Ingredients> stringsToIngredients;
};

#endif // INGREDIENTSMAP_H
