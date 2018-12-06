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
#include "spritesheet.h"

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
    IngredientSprite* selected;
    IngredientSprite glassImage;

    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    QVector<IngredientSprite> faceSprites;
    QVector<sf::Texture> faceTextures;
    int currentMood;

    QVector<sf::Texture> trueIngredientTextures;

    /*
    sf::Texture textureVodka;
    sf::Texture textureTequila;
    sf::Texture textureBourbon;
    sf::Texture textureGin;
    sf::Texture textureDarkRum;
    sf::Texture textureWhiteRum;
    sf::Texture textureLightRum;
    sf::Texture textureGrandMarnier;
    sf::Texture textureSweetVermouth;
    sf::Texture textureDryVermouth;
    sf::Texture textureTrippleSec;
    sf::Texture textureKahlua;
    sf::Texture textureJagermeister;
    sf::Texture textureCampari;
    sf::Texture textureGreenCremeDeMenthe;
    sf::Texture textureCremeDeCacao;
    sf::Texture texturePeachSchnapps;

    sf::Texture textureSalt;
    sf::Texture textureMargaritaSalt;
    sf::Texture texturePepper;
    sf::Texture textureNutmeg;
    sf::Texture textureice;

    sf::Texture textureTonicWater;
    sf::Texture textureSparklingWater;
    sf::Texture textureClubSoda;
    sf::Texture textureCola;
    sf::Texture textureSimpleSyrup;
    sf::Texture textureCream;
    sf::Texture textureAngosturaBitters;
    sf::Texture textureWorcestershireSauce;
    sf::Texture textureCreamOfCoconut;
    sf::Texture textureGingerBeer;

    sf::Texture textureOrangeJuice;
    sf::Texture textureLimeJuice;
    sf::Texture textureLemonJuice;
    sf::Texture texturePineappleJuice;
    sf::Texture textureTomatoJuice;
    sf::Texture textureCranberryJuice;

    sf::Texture textureOrangeWedge;
    sf::Texture textureOrangeTwist;
    sf::Texture textureLimeWedge;
    sf::Texture textureLimeTwist;
    sf::Texture textureLemonTwist;
    sf::Texture texturePineappleWedge;
    sf::Texture textureMintLeaf;
    sf::Texture textureMintSprig;
    sf::Texture textureCherry;
    sf::Texture textureGreenOlive;
    sf::Texture textureCelery;
    */

    void OnInit();

    //void assignTextures(QVector<QFileInfo>);

    void OnUpdate();

    // Positions relative to the center.

    const int verticalPositions[4] = { 69, 169, 269, 369 };
    const int horizontalPositions[14] = { 42, 118, 194, 269, 345, 421, 497, 572, 648, 724, 800, 875, 951, 1027 };
    const int barVerticalPosition = 596;

    /*
    // Positions relative to the top left edge.
    int verticalPositions[4] = { 29, 129, 229, 329 };
    int horizontalPositions[14] = { 12, 88, 164, 239, 315, 391, 467, 542, 618, 694, 770, 845, 921, 997 };
    */

signals:
    void ingredientAdded(Ingredients::Ingredients);

};

#endif // MYCANVAS_H
