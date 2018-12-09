#include <QString>
#include <QImage>
#include <QVector>
#include <QFileInfo>

#ifndef SPRITESHEET_H
#define SPRITESHEET_H

/**
 * @brief The Spritesheet class
 * Responsible for parsing a spritesheet into sprites for animation.
 *
 * Author: Kathryn Riding
 */
class Spritesheet
{

private:
    Spritesheet();

public:
    /**
     * @brief makeSprites: parses a spritesheet into separate sprite images.
     * @param pathToSheet: path to spritesheet
     * @param frameCount: number of frames
     * @param frameWidth: frame width
     * @param frameHeight: frame height
     * @return list of file info where images were saved.
     */
    static QVector<QFileInfo> makeSprites(QString pathToSheet, int frameCount, int frameWidth, int frameHeight);
};

#endif // SPRITESHEET_H
