#include <QString>
#include <QImage>
#include <QVector>
#include <SFML/Graphics.hpp>
#include "ingredientsprite.h"

#ifndef SPRITESHEET_H
#define SPRITESHEET_H


class Spritesheet
{
private:
    Spritesheet();

public:
    static QVector<IngredientSprite> makeSprites(QString pathToSheet, int frameCount, int frameWidth, int frameHeight);
};

#endif // SPRITESHEET_H
