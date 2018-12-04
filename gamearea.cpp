#include "gamearea.h"

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

// Constructor.
void GameArea::OnInit()
{
    // Get the sprites.
    QVector<sf::Sprite> spritesFromSheet = Spritesheet::makeSprites("../a8-an-educational-app-f18-kathrynriding-1/images/ingredientsSheet.png", 49, 60, 80);

    // Create all ingredient sprite objects.
    int ingredientIndex = 0;
    ingredientSprites = QVector<IngredientSprite>();
    for (sf::Sprite current: spritesFromSheet)
    {
        // grab texture from sheet
        IngredientSprite ingredient;
        ingredient.setTexture(*current.getTexture());
        ingredient.setTextureRect(current.getTextureRect());

        // assign ingredient name
        ingredient.ingredient = (Ingredients::Ingredients)ingredientIndex;
        ingredientIndex++;

        ingredientSprites.append(ingredient);
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

    // Set starting positions.
    for (int i = 0; i < 49; i++)
    {
        ingredientSprites[i].setPosition(ingredientSprites[i].shelfPosition.x(), ingredientSprites[i].shelfPosition.y());
    }

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

    // Draw all ingredients.
    for (int i = 0; i < 49; i++)
    {
        draw(ingredientSprites[i]);
    }
}
