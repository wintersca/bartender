#ifndef INGREDIENTSPRITE_H
#define INGREDIENTSPRITE_H

#include <QObject>
#include <SFML/Graphics.hpp>
#include <QPoint>
#include "ingredients.h"

/*
 * Ingredient sprites extend SFML sprites and allow associating more information.
 * This allows images in the games area to better associate their data.
 * Authors: Kylee Fluckiger and Alex Smith
 */

class IngredientSprite : public sf::Sprite
{
public:
    // The enum that matches this ingredient.
    Ingredients::Ingredients ingredient;

    // The position on the shelf where this item is stored.
    QPoint shelfPosition;

    // The texture that is used to draw this sprite.
    // This was not always able to be used without weird bugs.
    sf::Texture storedTexture;

    //
    IngredientSprite() : sf::Sprite() { }
};

#endif // INGREDIENTSPRITE_H
