#include "spritesheet.h"

QVector<IngredientSprite> Spritesheet::makeSprites(QString pathToSheet, int frameCount, int frameWidth, int frameHeight)
{
    QVector<IngredientSprite> sprites;

    sf::Texture texture;
    texture.loadFromFile(pathToSheet.toStdString());

    int imagesInARow = texture.getSize().x/frameWidth;
    int numberOfRows = texture.getSize().y/frameHeight;

    for(int rowCount = 0; rowCount < numberOfRows; rowCount++)
    {
        for(int framePosition = 0; framePosition < imagesInARow; framePosition++)
        {
            if(sprites.length() >= frameCount)
            {
                // edge case if all the rows do not fully contain images
                break;
            }

            IngredientSprite new_sprite;

            new_sprite.setTexture(texture);
            new_sprite.setTextureRect(sf::IntRect(framePosition, rowCount, frameWidth, frameHeight));

            sprites.append(new_sprite);
        }

    }

    return sprites;
}
