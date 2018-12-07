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
#include "spritesheet.h"

class GameArea : public QSFMLCanvas
{
    Q_OBJECT

public :

    GameArea(QWidget* Parent, const QPoint& Position, const QSize& Size, Controller *ctrlrPtr);

    void mousePressEvent(QMouseEvent* e);
    void mouseReleaseEvent(QMouseEvent* e);

private :

    QVector<IngredientSprite> ingredientSprites;
    IngredientSprite* selected;
    IngredientSprite glassImage;

    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    QVector<IngredientSprite> faceSprites;
    QVector<sf::Texture> faceTextures;
    int currentMood;

    QVector<sf::Texture> trueIngredientTextures;

    Controller *controller;

    void OnInit();

    //void assignTextures(QVector<QFileInfo>);

    void OnUpdate();

    // Positions relative to the center.

    const int verticalPositions[4] = { 69, 169, 269, 369 };
    const int horizontalPositions[14] = { 42, 118, 194, 269, 345, 421, 497, 572, 648, 724, 800, 875, 951, 1027 };
    const int barVerticalPosition = 596;

signals:
    void ingredientAdded(Ingredients::Ingredients);
    void requestMenu();

public slots:
    void receiveMood(int mood);
    void drinkServed();
};

#endif // MYCANVAS_H
