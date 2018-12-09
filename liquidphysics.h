#ifndef LIQUIDPHYSICS_H
#define LIQUIDPHYSICS_H

#include "./Box2D/Box2D/Box2D.h"
#include <QTimer>

/*
 * The this class controls the generation of particles
 * using the box2D physics engine and the deletion of the
 * particles. It also controls making the world of where
 * to generate the particles.
 *
 * Authors: Chloe Josien, Aleana Perry, Alex Smith
 */

class LiquidPhysics
{
public:
    /*
     * creates a basic world and
     * creates the ground and the cup.
     */
    LiquidPhysics();

    /*
     * defines the particles and their properties
     * to help simulate liquid in the game.
     */
    void GenerateLiquid();

    /*
     * generates a particle and defines the
     * properties to simulate a solid in the game
     */
    void GenerateSolid();

    /*
     * Removes all the bodies and recreates the
     * ground and cup afterwards
     */
    void DeleteLiquid();

    /*runs a step in the world updating
     * the velocity and position.
     */
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

    /*
     * creates the world in the shape of our cup
     * in the main game
     */
    void CreateCup();

    /*
     * creates the ground for our particles to land oun
     */
    void CreateGround();
};

#endif // LIQUIDPHYSICS_H
