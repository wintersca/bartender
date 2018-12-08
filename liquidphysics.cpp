#include "liquidphysics.h"

LiquidPhysics::LiquidPhysics()
{
    //initalizes the world
    worldAABB.lowerBound.Set(0, 0);
    worldAABB.upperBound.Set(200, 500);
    World = new b2World(b2Vec2(0.0f, 150.f));
    World->SetAllowSleeping(true);

    CreateGround();
    CreateCup();
}


void LiquidPhysics::WorldStep()
{
    World->Step(timeStep, velocityIterations, positionIterations);
}

void LiquidPhysics::GenerateLiquid()
{
    b2CircleShape dynamicCircle;

    // Creating the circle
    dynamicCircle.m_p.Set(0, 0);
    dynamicCircle.m_radius = 4;

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

void LiquidPhysics::GenerateSolid()
{
    b2CircleShape dynamicCircle;

    // Creating the circle
    dynamicCircle.m_p.Set(0, 0);
    dynamicCircle.m_radius = 12;

    b2FixtureDef fixtureDef;
    // properties of the liquid drop
    fixtureDef.shape = &dynamicCircle;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    fixtureDef.restitution = 0.8f;

    float32 pos_y = -200.0f;
    float32 pos_x = 64.f;

    b2BodyDef bodyDef;
    b2Body* body;
    // Body for placing shapes on
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(pos_x, pos_y);
    body = World->CreateBody(&bodyDef);

    // spawn circle on body
    body->CreateFixture(&fixtureDef);
}

void LiquidPhysics::DeleteLiquid()
{
    for (b2Body* body = World->GetBodyList()->GetNext(); body; body = body->GetNext())
    {
        World->DestroyBody(body);
    }
    CreateGround();
    CreateCup();
}

void LiquidPhysics::CreateCup()
{
    b2BodyDef glass;
    glass.type = b2_staticBody;
    glass.position.Set(0,0); //middle, bottom

    Cup = World->CreateBody(&glass);

    // Bottom edge.
    b2EdgeShape edgeShape;
    edgeShape.Set(b2Vec2(24, -18), b2Vec2(95, -18));
    b2FixtureDef glassfixture;
    glassfixture.shape = &edgeShape;

    // Left edge.
    b2EdgeShape edgeShape2;
    edgeShape2.Set(b2Vec2(8, -204), b2Vec2(24, -18));
    b2FixtureDef glassfixture2;
    glassfixture2.shape = &edgeShape2;

    // Right edge.
    b2EdgeShape edgeShape3;
    edgeShape3.Set( b2Vec2(112, -204), b2Vec2(97, -18));
    b2FixtureDef glassfixture3;
    glassfixture3.shape = &edgeShape3;

    Cup->CreateFixture(&glassfixture);
    Cup->CreateFixture(&glassfixture2);
    Cup->CreateFixture(&glassfixture3);
}

void LiquidPhysics::CreateGround()
{
    // Ground placement
    groundBodyDef.position.Set(0.0f, 0.0f);
    groundBody = World->CreateBody(&groundBodyDef);
    groundBox.SetAsBox(500.0f, 10.0f);
    groundBody->CreateFixture(&groundBox, 0.0f);
}
