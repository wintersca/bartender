#ifndef MYCANVAS_H
#define MYCANVAS_H

#include <QWidget>
#include <QObject>
#include <QTimer>
#include <SFML/Graphics.hpp>
#include "qsfmlcanvas.h"
#include <QDebug>

class MyCanvas : public QSFMLCanvas
{
public :

    MyCanvas(QWidget* Parent, const QPoint& Position, const QSize& Size) :
    QSFMLCanvas(Parent, Position, Size)
    {

    }

private :

    void OnInit()
    {

        // Setup the sprite

        myTexture.loadFromFile("cherry.png");
        mySprite.setTexture(myTexture);

//        sf::Texture texture;
//        if(!texture.loadFromFile("cherry.png"))
//               qDebug() << "Failed to load the lemon!";

//        texture.setSmooth(true);
//        mySprite.setTexture(texture);

//        sf::IntRect rect = mySprite.getTextureRect();
//        mySprite.setOrigin(rect.width, rect.height);
    }

    void OnUpdate()
    {
        // Clear screen
        sf::RenderWindow::clear(sf::Color(0, 180, 0));
        draw(mySprite);
    }

    sf::Image  myImage;
    sf::Sprite mySprite;
    sf::Texture myTexture;
};

#endif // MYCANVAS_H
