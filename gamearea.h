#ifndef MYCANVAS_H
#define MYCANVAS_H

#include <QWidget>
#include <QObject>
#include <QTimer>
#include <SFML/Graphics.hpp>
#include "qsfmlcanvas.h"
#include <QDebug>
#include "ingredients.h"
#include <QMouseEvent>
#include "ingredientsprite.h"
#include "controller.h"

class GameArea : public QSFMLCanvas
{

    Q_OBJECT

public :

    GameArea(QWidget* Parent, const QPoint& Position, const QSize& Size, Controller *ctrlrPtr) :
        QSFMLCanvas(Parent, Position, Size)
    {
        // added signals/slots -CW
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
        QObject::connect(controller, &Controller::triviaToGameArea,
                         this, &GameArea::receiveTrivia);
        QObject::connect(controller, &Controller::sendSelectedCustomer,
                         this, &GameArea::receiveSelectedCustomer);

        controller = ctrlrPtr;
    }

    void mousePressEvent(QMouseEvent* e);
    void mouseReleaseEvent(QMouseEvent* e);

private :

    QVector<IngredientSprite> ingredientSprites;

    sf::Image  myImage;
    IngredientSprite mySprite;
    sf::Texture myTexture;
    sf::Sprite* selected;

    sf::Image backgroundImage;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    Controller *controller;

    void OnInit();

    void OnUpdate();

signals:
    void ingredientAdded(Ingredients::Ingredients, double ammount);
    void drinkServed();
    void requestMenu();

public slots:
    void receiveMood(int mood);
    void receiveTrivia(QString trivia);
    void receiveSelectedCustomer(int customer);
};

#endif // MYCANVAS_H
