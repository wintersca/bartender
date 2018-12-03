#include "gamearea.h"

GameArea::GameArea(QWidget* Parent, const QPoint& Position, const QSize& Size, Controller *ctrlrPtr) :
    QSFMLCanvas(Parent, Position, Size)
{
    controller = ctrlrPtr;
    // to controller
    QObject::connect(this, &GameArea::ingredientAdded,
                     controller, &Controller::checkIngredient);
    QObject::connect(this, &GameArea::drinkServed,
                     controller, &Controller::drinkServed);

    /***************************************************************
     *  not sure if this is going to controller or mainWindow

    QObject::connect(this, &GameArea::requestMenu,
                     controller, &Controller::menuRequestByGameArea);
    *****************************************************************/

    // from controller
    QObject::connect(controller, &Controller::moodToGameArea,
                     this, &GameArea::receiveMood);
    QObject::connect(controller, &Controller::sendSelectedCustomer,
                     this, &GameArea::receiveSelectedCustomer);
}

void GameArea::GameArea::mousePressEvent(QMouseEvent *e)
{
    qDebug() << "YOU CLICKED THE MOUSE";

    sf::Vector2i mouse = sf::Mouse::getPosition(*this);

    if(mySprite.getGlobalBounds().contains(sf::Vector2f(mouse)))
    {
        selected = &mySprite;

        qDebug() << "Mouse is on Sprite: " << Ingredients::ingredientData[mySprite.ingredient].displayString;
        emit ingredientAdded(Ingredients::Tequila, 1);

    }

}

void GameArea::mouseReleaseEvent(QMouseEvent *e)
{
    qDebug() << "You let go of the mouse!";

    selected = nullptr;
}

void GameArea::OnInit()
{

    myTexture.loadFromFile("../a8-an-educational-app-f18-kathrynriding-1/images/cherry.png");
    mySprite.ingredient = Ingredients::DarkRum;

    mySprite.setTexture(myTexture);
    mySprite.setPosition(250.f, 250.f);
    mySprite.setOrigin(mySprite.getGlobalBounds().width / 2, mySprite.getGlobalBounds().height / 2);

    if(!backgroundTexture.loadFromFile("../a8-an-educational-app-f18-kathrynriding-1/images/gamePlayBackground.png"))
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

void GameArea::receiveMood(int mood)
{
    //TODO
}
void GameArea::receiveTrivia(QString trivia)
{
    //TODO
}
void GameArea::receiveSelectedCustomer(int customer)
{
    //TODO
}
