#ifndef LIQUIDPHYSICS_H
#define LIQUIDPHYSICS_H

//#include <QMainWindow>
#include "./Box2D/Box2D/Box2D.h"
#include <QTimer>

class LiquidPhysics
{
public:
    LiquidPhysics();
    void GenerateLiquid();
    void GenerateSolid();
    void DeleteLiquid();
    void WorldStep();

    b2World* World;
    int liquidParticles = 20;
    b2Body* Cup;
    b2Body* groundBody;

signals:

private:
    b2AABB worldAABB;
    QTimer* timer;
    b2BodyDef groundBodyDef;
    b2PolygonShape groundBox;
    float32 timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 6;
    int32 positionIterations = 2;

    void CreateCup();
    void CreateGround();
};

#endif // LIQUIDPHYSICS_H
