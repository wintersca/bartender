#include "gamearea.h"

void GameArea::pouring(){
    b2Vec2 gravity(0.0f, 9.8f);

    //construct world
    b2World world(gravity);

    //set textures??

    //ground body
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, -10.0f);

    b2Body* groundbody = world.CreateBody(&groundBodyDef);

    b2CircleShape  groundCircle;

    groundbody->CreateFixture(&groundCircle,0.0f);

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(0.0f, 4.0f);
    b2Body* body = world.CreateBody(&bodyDef);

    b2CircleShape dynamicCircle;

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicCircle;

    fixtureDef.density = 1.0f;
    body->CreateFixture(&fixtureDef);

    float32 timestep = 1.0f/60.0f;
    int32 velcocityIterations =6;
    int32 positionIterations = 2;

    world.Step(timestep,velcocityIterations,positionIterations);

}

void GameArea::GameArea::mousePressEvent(QMouseEvent *e)
{
    qDebug() << "YOU CLICKED THE MOUSE";

    sf::Vector2i mouse = sf::Mouse::getPosition(*this);

    if(mySprite.getGlobalBounds().contains(sf::Vector2f(mouse)))
    {
        selected = &mySprite;

        qDebug() << "Mouse is on Sprite: " << Ingredients::ingredientData[mySprite.ingredient].displayString;
        emit ingredientAdded(Ingredients::Tequila);

    }

}

void GameArea::mouseReleaseEvent(QMouseEvent *e)
{
    qDebug() << "You let go of the mouse!";

    selected = nullptr;
}

void GameArea::OnInit()
{

    myTexture.loadFromFile("../a8-an-educational-app-f18-kathrynriding-1/images/cherry.png");
    mySprite.ingredient = Ingredients::DarkRum;

    mySprite.setTexture(myTexture);
    mySprite.setPosition(250.f, 250.f);
    mySprite.setOrigin(mySprite.getGlobalBounds().width / 2, mySprite.getGlobalBounds().height / 2);

    if(!backgroundTexture.loadFromFile("../a8-an-educational-app-f18-kathrynriding-1/images/gamePlayBackground.png"))
    {
        qDebug() << "Couldn't load background.";
    }
  
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setPosition(0.f, 0.f);

    selected = nullptr;
}

//Game loop
void GameArea::OnUpdate()
{
    // Clear screen
    clear(sf::Color(0, 180, 0));
    sf::Vector2i mouse = sf::Mouse::getPosition(*this);

    if(selected) {
            mySprite.setPosition(mouse.x, mouse.y);
            qDebug() << mouse.x << ", " << mouse.y;
        }

    draw(backgroundSprite);
    draw(mySprite);
}
