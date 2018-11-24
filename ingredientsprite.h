#ifndef INGREDIENTSPRITE_H
#define INGREDIENTSPRITE_H

#include <QObject>
#include <SFML/Graphics.hpp>
#include "ingredients.h"

class IngredientSprite : public sf::Sprite
{

public:
    Ingredients::Ingredients ingredient;

    IngredientSprite() : sf::Sprite() { }


};

#endif // INGREDIENTSPRITE_H
