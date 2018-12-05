#include "spritesheet.h"

QVector<QFileInfo> Spritesheet::makeSprites(QString pathToSheet, int frameCount, int frameWidth, int frameHeight)
{
    QVector<QFileInfo> spriteFiles;
    QFileInfo file(pathToSheet);

    QImage spritesheet(pathToSheet);

    int imagesInARow = spritesheet.width() / frameWidth;
    int numberOfRows = spritesheet.height() / frameHeight;

    int imageCount = 1;

    for(int framePosition = 0; framePosition < imagesInARow; framePosition++)
    {
        for(int rowCount = 0; rowCount < numberOfRows; rowCount++)
        {
            if(spriteFiles.length() >= frameCount)
            {
                // edge case if all the rows do not fully contain images
                break;
            }

            QString directory = file.absolutePath();
            directory.append("/");
            directory.append(QString::number(imageCount));
            directory.append(".png");

            QImage newSprite = spritesheet.copy(rowCount*frameWidth, framePosition*frameHeight, frameWidth, frameHeight);
            newSprite.save(directory);

            spriteFiles.append(directory);

            imageCount++;
        }
    }

    return spriteFiles;
}
