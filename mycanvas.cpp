#include "mycanvas.h"

void MyCanvas::OnInit()
{

    // Setup the sprite

    myTexture.loadFromFile("cherry.png");
    mySprite.setTexture(myTexture);
}

//Game loop
void MyCanvas::OnUpdate()
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
               qDebug() << "Mouse is on Sprite!";

    }

    mySprite.move(.0001f, .0001f);

    sf::Vector2f sprite = mySprite.getPosition();
    //qDebug() << "The sprite coordinates are at " << sprite.x << ", " << sprite.y;

    draw(mySprite);
}
