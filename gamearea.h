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
#include "./Box2D/Box2D/Box2D.h"

class GameArea : public QSFMLCanvas
{

    Q_OBJECT

public :

    GameArea(QWidget* Parent, const QPoint& Position, const QSize& Size) :
        QSFMLCanvas(Parent, Position, Size) { }

    void mousePressEvent(QMouseEvent* e);
    void mouseReleaseEvent(QMouseEvent* e);
    void pouring();

private :

    QVector<IngredientSprite> ingredientSprites;

    sf::Image  myImage;
    IngredientSprite mySprite;
    sf::Texture myTexture;
    sf::Sprite* selected;

    sf::Image backgroundImage;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    void OnInit();

    void OnUpdate();

signals:
    void ingredientAdded(Ingredients::Ingredients);

};

#endif // MYCANVAS_H
