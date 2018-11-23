#include "mycanvas.h"

void MyCanvas::OnInit()
{

    // Setup the sprite

    myTexture.loadFromFile("cherry.png");
    mySprite.setTexture(myTexture);
}

void MyCanvas::OnUpdate()
{
    // Clear screen
    sf::RenderWindow::clear(sf::Color(0, 180, 0));

    mySprite.move(.01, .01);

    draw(mySprite);
}
