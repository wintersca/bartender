#ifndef MYCANVAS_H
#define MYCANVAS_H

#include <QWidget>
#include <QObject>
#include <QTimer>
#include <SFML/Graphics.hpp>
#include "qsfmlcanvas.h"
#include <QDebug>
#include "ingredients.h"

class GameArea : public QSFMLCanvas
{

    Q_OBJECT

public :

    GameArea(QWidget* Parent, const QPoint& Position, const QSize& Size) :
        QSFMLCanvas(Parent, Position, Size) { }

private :

    sf::Image  myImage;
    sf::Sprite mySprite;
    sf::Texture myTexture;

    void OnInit();

    void OnUpdate();

signals:
    void ingredientAdded(Ingredients::Ingredients);

};

#endif // MYCANVAS_H
