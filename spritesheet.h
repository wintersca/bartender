#include <QString>
#include <QImage>
#include <QVector>
#include <SFML/Graphics.hpp>

#ifndef SPRITESHEET_H
#define SPRITESHEET_H


class Spritesheet
{
private:
    Spritesheet();

public:
    static QVector<sf::Sprite*> makeSprites(QString pathToSheet, int frameCount, int frameWidth, int frameHeight);
};

#endif // SPRITESHEET_H
