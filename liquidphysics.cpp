#include "liquidphysics.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "Box2D/Box2D/Box2D.h"
#include <QTimer>
#include <QPainter>
#include <QPen>
#include <QDebug>

LiquidPhysics::LiquidPhysics()
{
    worldAABB.lowerBound.Set(0, 0);
    worldAABB.upperBound.Set(200, 500);
    World = new b2World(b2Vec2(0.0f, 9.8f));
    World->SetAllowSleeping(true);

    // Ground placement
    groundBodyDef.position.Set(0.0f, 0.0f);
    groundBody = World->CreateBody(&groundBodyDef);
    groundBox.SetAsBox(500.0f, 10.0f);
    groundBody->CreateFixture(&groundBox, 0.0f);

    CreateCup();
    // Basically connect in Controller whenever the screen has to update to the step function of the Liquid Physics so it can move along too.
    //connect(this->timer, SIGNAL(timeout()), this, SLOT(WorldStep()));
}


void LiquidPhysics::WorldStep()
{
    World->Step(timeStep, velocityIterations, positionIterations);
    //b2Vec2 position = body->GetPosition();
    //qDebug() << position.x << " " << position.y << "/n";
    // signal to controller to update the screen
}

void LiquidPhysics::GenerateLiquid()
{
    b2CircleShape dynamicCircle;

    // Creating the circle
    dynamicCircle.m_p.Set(0, 0);
    dynamicCircle.m_radius = 5;

    b2FixtureDef fixtureDef;
    // properties of the liquid drop
    fixtureDef.shape = &dynamicCircle;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    fixtureDef.restitution = 0.8f;

    float32 pos_y = -200.0f;
    float32 pos_x = 64.f;

    for (int i = 0; i < liquidParticles; i++)
    {
        b2BodyDef bodyDef;
        b2Body* body;
        // Body for placing shapes on
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(pos_x, pos_y);
        body = World->CreateBody(&bodyDef);

        int tempx = ((int)pos_x + 1);
        pos_x = tempx;
        int tempy = ((int)pos_y - 5);
        pos_y = tempy;

        // spawn circle on body
        body->CreateFixture(&fixtureDef);
    }
}

void LiquidPhysics::DeleteLiquid()
{
    for (b2Body* body = World->GetBodyList()->GetNext(); body;)
    {
        if (body->GetUserData() != NULL) {
             b2Body* next = body->GetNext();  // remember next body before *b gets destroyed
             World->DestroyBody(body); // do I need to destroy fixture as well(and how?) or it does that for me?
             body = next;  // go to next body
          }
    }
    //Add ground back afterwards
    groundBodyDef.position.Set(0.0f, -10.0f);

    groundBody = World->CreateBody(&groundBodyDef);

    groundBox.SetAsBox(50.0f, 10.0f);
    groundBody->CreateFixture(&groundBox, 0.0f);
    //Add cup back
    CreateCup();
}

void LiquidPhysics::CreateCup()
{
    b2BodyDef glass;
    glass.type = b2_staticBody;
    glass.position.Set(0,0); //middle, bottom

    b2Body* Cup = World->CreateBody(&glass);

    // Bottom edge.
    b2EdgeShape edgeShape;
    edgeShape.Set(b2Vec2(24, -20), b2Vec2(95, -20));
    b2FixtureDef glassfixture;
    glassfixture.shape = &edgeShape;

    // Left edge.
    b2EdgeShape edgeShape2;
    edgeShape2.Set(b2Vec2(8, -204), b2Vec2(24, -20));
    b2FixtureDef glassfixture2;
    glassfixture2.shape = &edgeShape2;

    // Right edge.
    b2EdgeShape edgeShape3;
    edgeShape3.Set( b2Vec2(110, -204), b2Vec2(95, -20));
    b2FixtureDef glassfixture3;
    glassfixture3.shape = &edgeShape3;

    Cup->CreateFixture(&glassfixture);
    Cup->CreateFixture(&glassfixture2);
    Cup->CreateFixture(&glassfixture3);
}
