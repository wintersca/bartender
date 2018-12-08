#include "spritesheet.h"

QVector<QFileInfo> Spritesheet::makeSprites(QString pathToSheet, int frameCount, int frameWidth, int frameHeight)
{
    QVector<QFileInfo> spriteFiles;
    QFileInfo file(pathToSheet);

    QImage spritesheet(pathToSheet);

    int imagesInARow = spritesheet.width() / frameWidth;
    int numberOfRows = spritesheet.height() / frameHeight;

    int imageCount = 1;

    for(int rowCount = 0; rowCount < numberOfRows; rowCount++)
    {
        for(int columnCount = 0; columnCount < imagesInARow; columnCount++)
        {
            if(spriteFiles.length() > frameCount)
            {
                break;
            }

            QString directory = file.absolutePath();
            directory.append("/");
            directory.append(QString::number(imageCount));
            directory.append(".png");

            QImage newSprite = spritesheet.copy(columnCount*frameWidth, rowCount*frameHeight, frameWidth, frameHeight);
            newSprite.save(directory);

            spriteFiles.append(directory);

            imageCount++;
        }
    }

    return spriteFiles;
}
