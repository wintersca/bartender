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
#include "spritesheet.h"

class GameArea : public QSFMLCanvas
{

    Q_OBJECT

public :

    GameArea(QWidget* Parent, const QPoint& Position, const QSize& Size) :
        QSFMLCanvas(Parent, Position, Size) { }

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

    void OnInit();

    void OnUpdate();

    // Positions relative to the center.
    /*
    int verticalPositions[4] = { 69, 169, 269, 369 };
    int horizontalPositions[14] = { 42, 118, 194, 269, 345, 421, 497, 572, 648, 724, 800, 875, 951, 1027 };
    */

    // Positions relative to the top left edge.
    int verticalPositions[4] = { 29, 129, 229, 329 };
    int horizontalPositions[14] = { 12, 88, 164, 239, 315, 391, 467, 542, 618, 694, 770, 845, 921, 997 };


signals:
    void ingredientAdded(Ingredients::Ingredients);

};

#endif // MYCANVAS_H
