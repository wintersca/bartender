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

    timer = new QTimer();
    worldAABB.lowerBound.Set(0, 0);
    worldAABB.upperBound.Set(200, 500);
    World = new b2World(b2Vec2(0.0f, -10.0f));
    World->SetAllowSleeping(true);

    groundBodyDef.position.Set(0.0f, -10.0f);

    groundBody = World->CreateBody(&groundBodyDef);



    groundBox.SetAsBox(50.0f, 10.0f);
    groundBody->CreateFixture(&groundBox, 0.0f);



    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(0.0f, 100.0f);
    body = World->CreateBody(&bodyDef);

    dynamicCircle.m_p.Set(0, 0);
    dynamicCircle.m_radius = 5;


    fixtureDef.shape = &dynamicCircle;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;

    body->CreateFixture(&fixtureDef);

    // Basically connect in Controller whenever the screen has to update to the step function of the Liquid Physics so it can move along too.
    //connect(this->timer, SIGNAL(timeout()), this, SLOT(WorldStep()));
   // timer->start(12);
}


void LiquidPhysics::WorldStep()
{
    World->Step(timeStep, velocityIterations, positionIterations);
    //b2Vec2 position = body->GetPosition();
    //qDebug() << position.x << " " << position.y << "/n";
    // signal to controller to update the screen
}

// For drawing on the main screen
//void MainWindow::paintEvent(QPaintEvent *) {
//    // Create a painter
//    QPainter painter(this);
//    QPen pen(Qt::black); Or whatever color we need for the drink
//    pen.setWidth(10);
//    painter.setPen(pen);

//    b2Vec2 position = body->GetPosition();

//    QRect rect(200 - position.x, 200 - position.y, 5 , 5);
//    painter.fillEllipse(rect);

//}
