#include "gamearea.h"
#include <Box2D/Box2D/Box2D.h>

GameArea::GameArea(QWidget* Parent, const QPoint& Position, const QSize& Size, Controller *ctrlrPtr) :
    QSFMLCanvas(Parent, Position, Size)
{
    controller = ctrlrPtr;

    // to controller
    QObject::connect(this, &GameArea::ingredientAdded,
                     controller, &Controller::checkIngredient);   
   QObject::connect(this, &GameArea::requestMenu,
                     controller, &Controller::menuRequestByGameArea);

    // from controller
    QObject::connect(controller, &Controller::moodToGameArea,
                     this, &GameArea::receiveMood);
    QObject::connect(controller, &Controller::clearDrink,
                     this, &GameArea::drinkServed);
}

void GameArea::GameArea::mousePressEvent(QMouseEvent *e)
{

    sf::Vector2i mouse = sf::Mouse::getPosition(*this);

    // Determine what was selected.
    for (int i = 0; i < Ingredients::ITEMSININGREDIENTS; i++)
    {
        if(ingredientSprites[i].getGlobalBounds().contains(sf::Vector2f(mouse)))
        {
            selected = &ingredientSprites[i];

        }
    }
}

void GameArea::mouseReleaseEvent(QMouseEvent *e)
{

    if (selected)
    {
        // Put the item back on the shelf.
        selected->setPosition(selected->shelfPosition.x(), selected->shelfPosition.y());

        // Check if it was added to the drink.
        sf::Vector2i mouse = sf::Mouse::getPosition(*this);
        if (glassImage.getGlobalBounds().contains(sf::Vector2f(mouse)))
        {
            emit ingredientAdded(selected->ingredient);

            // Create phyics stuff.
            if (selected->ingredient <= Ingredients::Celery)
            {
                // Check if poured or added.
                if (Ingredients::ingredientData[selected->ingredient].action == Ingredients::Action::PourAction)
                {
                    // Spawn drink items
                    liquidPhysics.GenerateLiquid();

                    // Store sprites to represent them.
                    QColor thisColor = Ingredients::ingredientData[selected->ingredient].color;
                    for (int i = 0; i < liquidPhysics.liquidParticles; i++)
                    {
                        liquidShapes.append(sf::CircleShape(8));
                        liquidShapes[newLiquidShapeIndex + i].setFillColor(sf::Color(thisColor.red(), thisColor.green(), thisColor.blue(), 150));
                        liquidShapes[newLiquidShapeIndex + i].setOrigin(4, 4);
                    }
                    newLiquidShapeIndex += liquidPhysics.liquidParticles;
                }
                else
                {
                    liquidPhysics.GenerateSolid();
                    QColor thisColor = Ingredients::ingredientData[selected->ingredient].color;
                    liquidShapes.append(sf::CircleShape(12));
                    liquidShapes[newLiquidShapeIndex].setFillColor(sf::Color(thisColor.red(), thisColor.green(), thisColor.blue(), 255));
                    liquidShapes[newLiquidShapeIndex].setOrigin(4, 4);
                    newLiquidShapeIndex++;
                }
            }
        }
    }

    selected = nullptr;
}

// Constructor.
void GameArea::OnInit()
{
    // Get the ingredient sprites.
    QVector<QFileInfo> ingredientFilePaths = Spritesheet::makeSprites("../a8-an-educational-app-f18-kathrynriding-1/images/ingredients/ingredientsSheet.png", 49, 60, 80);
    ingredientSprites = QVector<IngredientSprite>();

    trueIngredientTextures = QVector<sf::Texture>(Ingredients::TRUEINGREDIENTS);

    // Create all ingredient sprite objects. This included tools.
    for (int i = 0; i < Ingredients::TRUEINGREDIENTS; i++)
    {
        // Add all images.
        ingredientSprites.append(IngredientSprite());
        trueIngredientTextures[i].loadFromFile(ingredientFilePaths[i].absoluteFilePath().toStdString());
        ingredientSprites[i].setTexture(trueIngredientTextures[i]);


        // Center
        ingredientSprites[i].setOrigin(ingredientSprites[i].getGlobalBounds().width / 2, ingredientSprites[i].getGlobalBounds().height / 2);

        // assign ingredient name
        ingredientSprites[i].ingredient = (Ingredients::Ingredients)i;
    }

    // Give all sprites positions.
    // Add core boozes.
    for (int i = 0; i < 7; i++)
    {
        ingredientSprites[i].shelfPosition = QPoint(horizontalPositions[i + 7], verticalPositions[3]);
    }
    // Add liquours
    for (int i = 0; i < 10; i++)
    {
        ingredientSprites[i + 7].shelfPosition = QPoint(horizontalPositions[i + 4], verticalPositions[2]);
    }
    // Add kitchen basics.
    for (int i = 0; i < 5; i++)
    {
        ingredientSprites[i + 17].shelfPosition = QPoint(horizontalPositions[i], verticalPositions[3]);
    }
    // Add non alcoholic liquids.
    for (int i = 0; i < 10; i++)
    {
        ingredientSprites[i + 22].shelfPosition = QPoint(horizontalPositions[i + 4], verticalPositions[0]);
    }
    // Add fruit juices.
    ingredientSprites[32].shelfPosition = QPoint(horizontalPositions[0], verticalPositions[0]);
    ingredientSprites[33].shelfPosition = QPoint(horizontalPositions[1], verticalPositions[0]);
    ingredientSprites[34].shelfPosition = QPoint(horizontalPositions[0], verticalPositions[1]);
    ingredientSprites[35].shelfPosition = QPoint(horizontalPositions[1], verticalPositions[1]);
    ingredientSprites[36].shelfPosition = QPoint(horizontalPositions[0], verticalPositions[2]);
    ingredientSprites[37].shelfPosition = QPoint(horizontalPositions[1], verticalPositions[2]);

    // Add fruits and vegtables
    for (int i = 0; i < 11; i++)
    {
        ingredientSprites[i + 38].shelfPosition = QPoint(horizontalPositions[i + 3], verticalPositions[1]);
    }

    // Add the tools.
    ingredientSprites.append(IngredientSprite());
    ingredientSprites[Ingredients::Shake].storedTexture.loadFromFile("../a8-an-educational-app-f18-kathrynriding-1/images/shakerLid.png");
    ingredientSprites[Ingredients::Shake].shelfPosition = QPoint(785, barVerticalPosition);

    ingredientSprites.append(IngredientSprite());
    ingredientSprites[Ingredients::Stir].storedTexture.loadFromFile("../a8-an-educational-app-f18-kathrynriding-1/images/stirSpoon.png");
    ingredientSprites[Ingredients::Stir].shelfPosition = QPoint(918, barVerticalPosition);

    ingredientSprites.append(IngredientSprite());
    ingredientSprites[Ingredients::Muddle].storedTexture.loadFromFile("../a8-an-educational-app-f18-kathrynriding-1/images/muddler.png");
    ingredientSprites[Ingredients::Muddle].shelfPosition = QPoint(1020, barVerticalPosition);

    for (int i = Ingredients::Shake; i <= (int)Ingredients::Muddle; i++)
    {
        ingredientSprites[i].setTexture(ingredientSprites[i].storedTexture);
        ingredientSprites[i].setOrigin(ingredientSprites[i].getGlobalBounds().width / 2, ingredientSprites[i].getGlobalBounds().height / 2);
        ingredientSprites[i].ingredient = (Ingredients::Ingredients)i;
    }

    // Set starting positions of ingredients and tools.
    for (int i = 0; i < Ingredients::ITEMSININGREDIENTS; i++)
    {
        ingredientSprites[i].setPosition(ingredientSprites[i].shelfPosition.x(), ingredientSprites[i].shelfPosition.y());
    }

    // Load the glass image.
    glassImage.storedTexture.loadFromFile("../a8-an-educational-app-f18-kathrynriding-1/images/glass.png");
    glassImage.setTexture(glassImage.storedTexture);
    glassImage.setOrigin(glassImage.getGlobalBounds().width / 2, glassImage.getGlobalBounds().height / 2);
    glassImage.setPosition(534, barVerticalPosition);

    // Load the face images.
    QVector<QFileInfo> faceFilePaths = Spritesheet::makeSprites("../a8-an-educational-app-f18-kathrynriding-1/images/customer/facesSheet.png", 6, 200, 200);
    faceSprites = QVector<IngredientSprite>();
    faceTextures = QVector<sf::Texture>(6);
    for (int i = 0; i < 6; i++)
    {
        faceSprites.append(IngredientSprite());
        faceTextures[i].loadFromFile(faceFilePaths[i].absoluteFilePath().toStdString());
        faceSprites[i].setTexture(faceTextures[i]);
        faceSprites[i].setOrigin(faceSprites[i].getGlobalBounds().width / 2, faceSprites[i].getGlobalBounds().height / 2);
        faceSprites[i].setPosition(114, barVerticalPosition);
    }
    currentMood = 5;

    // Load the background image.
    backgroundTexture.loadFromFile("../a8-an-educational-app-f18-kathrynriding-1/images/gameplayBackground.png");
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setPosition(0.f, 0.f);

    selected = nullptr;

    // Phyics set up.
    liquidPhysics = LiquidPhysics();
    newLiquidShapeIndex = 0;

}

//Game loop
void GameArea::OnUpdate()
{
    // Clear screen
    clear(sf::Color(0, 180, 0));
    sf::Vector2i mouse = sf::Mouse::getPosition(*this);

    draw(backgroundSprite);
    draw(glassImage);

    // Draw the current face.
    draw(faceSprites[currentMood]);

    // Update the position of a clicked item.
    if(selected)
    {
        selected->setPosition(mouse.x, mouse.y);
    }

    // Draw all ingredients and tools.
    for (int i = 0; i < Ingredients::ITEMSININGREDIENTS; i++)
    {
        draw(ingredientSprites[i]);
    }

    // Update the physics
    liquidPhysics.WorldStep();

    // Draw liquid items.
    lock.lock();
    int i = newLiquidShapeIndex - 1;
    b2Body* BodyIterator = liquidPhysics.World->GetBodyList();
    for (; BodyIterator; BodyIterator = BodyIterator->GetNext())
    {
        if (BodyIterator != liquidPhysics.Cup && BodyIterator != liquidPhysics.groundBody)
        {
            if (i < newLiquidShapeIndex && i >= 0)
            {
                liquidShapes[i].setPosition(physicsOffsetHorizontal +  BodyIterator->GetPosition().x, physicsOffSetVertical + BodyIterator->GetPosition().y);
                draw(liquidShapes[i]);
                i--;
            }
        }
    }
    lock.unlock();
}

void GameArea::receiveMood(int mood)
{
    currentMood = mood;
}

void GameArea::drinkServed()
{

    lock.lock();

    liquidPhysics.DeleteLiquid();
    newLiquidShapeIndex = 0;
    liquidShapes.clear();

    lock.unlock();

}
