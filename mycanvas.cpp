#include "mycanvas.h"

void GameArea::OnInit()
{

    myTexture.loadFromFile("cherry.png");
    mySprite.setTexture(myTexture);
    mySprite.setPosition(250.f, 250.f);
    mySprite.setOrigin(mySprite.getGlobalBounds().width / 2, mySprite.getGlobalBounds().height / 2);
}

//Game loop
void GameArea::OnUpdate()
{
    // Clear screen
    clear(sf::Color(0, 180, 0));

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        // left click...
        //qDebug() << "You clicked the left button!";
        sf::Vector2i mouse = sf::Mouse::getPosition(*this);
        //qDebug() << "The mouse coordinates are at " << mouse.x << ", " << mouse.y;

        if(mySprite.getGlobalBounds().contains(sf::Vector2f(mouse)))
        {
            qDebug() << "Mouse is on Sprite!";
            emit ingredientAdded(Ingredients::Tequila);

            //mySprite.setOrigin(mouse.x - (mySprite.getPosition().x - mySprite.getOrigin().x),
                           //mouse.y - (mySprite.getPosition().y - mySprite.getOrigin().y));
            mySprite.setPosition(mouse.x, mouse.y);
            qDebug() << mouse.x << ", " << mouse.y;
        }

    }

    draw(mySprite);
}
