#ifndef INGREDIENTSPRITE_H
#define INGREDIENTSPRITE_H

#include <QObject>
#include <SFML/Graphics.hpp>
#include <QPoint>
#include "ingredients.h"

class IngredientSprite : public sf::Sprite
{

public:
    Ingredients::Ingredients ingredient;
    QPoint shelfPosition;

    IngredientSprite() : sf::Sprite() { }


};

#endif // INGREDIENTSPRITE_H
