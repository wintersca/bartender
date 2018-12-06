#include <QString>
#include <QImage>
#include <QVector>
#include <QFileInfo>

#ifndef SPRITESHEET_H
#define SPRITESHEET_H


class Spritesheet
{
private:
    Spritesheet();

public:
    static QVector<QFileInfo> makeSprites(QString pathToSheet, int frameCount, int frameWidth, int frameHeight);
};

#endif // SPRITESHEET_H
