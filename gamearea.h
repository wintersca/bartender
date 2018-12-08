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
#include "./Box2D/Box2D/Box2D.h"
#include "spritesheet.h"
#include "liquidphysics.h"
#include <QMutex>

/*
 * The GameArea class extends QSFMLCanvas to provide a Qt frame for SFML drawing and
 * events. It is specifically implemented to hold all game sprites and data for
 * the Mixologist game.
 *
 * Authors: Kylee Fluckiger & Alex Smith
 */
class GameArea : public QSFMLCanvas
{
    Q_OBJECT

public :

    GameArea(QWidget* Parent, const QPoint& Position, const QSize& Size, Controller *ctrlrPtr);

    void mousePressEvent(QMouseEvent* e);
    void mouseReleaseEvent(QMouseEvent* e);

private :

    QVector<IngredientSprite> ingredientSprites;    //Tracks all ingredient sprites for the game.
    IngredientSprite* selected;                     //Tracks the currently selected ingredient sprite.
    IngredientSprite glassImage;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    QVector<IngredientSprite> faceSprites;          //Holds all the faces for the customers.
    QVector<sf::Texture> faceTextures;              //Textures for ^^
    int currentMood;                                //Used to determine which customer face to display.
    QVector<sf::Texture> trueIngredientTextures;    //Textures for real ingredient sprites.
    Controller *controller;                         //Reference to a Controller object for gameplay.
    LiquidPhysics liquidPhysics;                    //Instantiation of our liquid physics engine.
    QVector<sf::CircleShape> liquidShapes;          //Sprites for generated physics animation.
    int newLiquidShapeIndex;                        //Track newly created physics sprite instances.
    QMutex lock;                                    //Helps keep physics generation sequential and correct.

    void OnInit();
    void OnUpdate();

    // Positions relative to the center.
    const int verticalPositions[4] = { 69, 169, 269, 369 };
    const int horizontalPositions[14] = { 42, 118, 194, 269, 345, 421, 497, 572, 648, 724, 800, 875, 951, 1027 };
    const int barVerticalPosition = 596;

    // Phyics positions.
    const int physicsOffSetVertical = 690;
    const int physicsOffsetHorizontal = 469;

signals:
    void ingredientAdded(Ingredients::Ingredients);     //Emits which ingredient was dropped in glass.

public slots:
    void receiveMood(int mood);
    void drinkServed();
};

#endif // MYCANVAS_H

