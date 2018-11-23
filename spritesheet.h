#include <QString>
#include <QImage>
#include <QVector>

#ifndef SPRITESHEET_H
#define SPRITESHEET_H


class spritesheet
{
private:
    spritesheet();

public:
    QVector<QImage> makeQImages(QString pathToImage);
    void makeTextures(QString pathToImage);
};

#endif // SPRITESHEET_H
