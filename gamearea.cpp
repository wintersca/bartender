#include "gamearea.h"

void GameArea::GameArea::mousePressEvent(QMouseEvent *e)
{
    qDebug() << "YOU CLICKED THE MOUSE";

    sf::Vector2i mouse = sf::Mouse::getPosition(*this);

    if(mySprite.getGlobalBounds().contains(sf::Vector2f(mouse)))
    {
        selected = &mySprite;

        qDebug() << "Mouse is on Sprite: " << Ingredients::All[mySprite.ingredient];
        emit ingredientAdded(Ingredients::Tequila);

    }

}

void GameArea::mouseReleaseEvent(QMouseEvent *e)
{
    qDebug() << "You let go of the mouse!";

    selected = nullptr;
}

void GameArea::OnInit()
{

    myTexture.loadFromFile("cherry.png");
    mySprite.ingredient = Ingredients::Angustura;
    mySprite.setTexture(myTexture);
    mySprite.setPosition(250.f, 250.f);
    mySprite.setOrigin(mySprite.getGlobalBounds().width / 2, mySprite.getGlobalBounds().height / 2);


    if(!backgroundTexture.loadFromFile("gamePlayBackground.png"))
    {
        qDebug() << "Couldn't load background.";
    }

    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setPosition(0.f, 0.f);

    selected = nullptr;
}

//Game loop
void GameArea::OnUpdate()
{
    // Clear screen
    clear(sf::Color(0, 180, 0));
    sf::Vector2i mouse = sf::Mouse::getPosition(*this);

    if(selected) {
            mySprite.setPosition(mouse.x, mouse.y);
            qDebug() << mouse.x << ", " << mouse.y;
        }

    draw(backgroundSprite);
    draw(mySprite);
}
