#include "gamearea.h"

GameArea::GameArea(QWidget* Parent, const QPoint& Position, const QSize& Size, Controller *ctrlrPtr) :
    QSFMLCanvas(Parent, Position, Size)
{
    controller = ctrlrPtr;
    // to controller
    QObject::connect(this, &GameArea::ingredientAdded,
                     controller, &Controller::checkIngredient);
    QObject::connect(this, &GameArea::drinkServed,
                     controller, &Controller::drinkServed);
    QObject::connect(this, &GameArea::requestMenu,
                     controller, &Controller::menuRequestByGameArea);

    // from controller
    QObject::connect(controller, &Controller::moodToGameArea,
                     this, &GameArea::receiveMood);
}

void GameArea::GameArea::mousePressEvent(QMouseEvent *e)
{
    qDebug() << "YOU CLICKED THE MOUSE";

    sf::Vector2i mouse = sf::Mouse::getPosition(*this);

    // Determine what was selected.
    for (int i = 0; i < Ingredients::ITEMSININGREDIENTS; i++)
    {
        if(ingredientSprites[i].getGlobalBounds().contains(sf::Vector2f(mouse)))
        {
            selected = &ingredientSprites[i];

            //qDebug() << "Mouse is on Sprite: " << Ingredients::ingredientData[ingredientSprites[i].ingredient].displayString;

        }
    }
}

void GameArea::mouseReleaseEvent(QMouseEvent *e)
{
    qDebug() << "You let go of the mouse!";

    if (selected)
    {
        // Put the item back on the shelf.
        selected->setPosition(selected->shelfPosition.x(), selected->shelfPosition.y());

        // Check if it was added to the drink.
        sf::Vector2i mouse = sf::Mouse::getPosition(*this);
        if (glassImage.getGlobalBounds().contains(sf::Vector2f(mouse)))
        {
            qDebug() << "Added to drink" << selected->ingredient << "\n";
            emit ingredientAdded(selected->ingredient);
        }
    }

    selected = nullptr;
}

// Constructor.
void GameArea::OnInit()
{
    // Get the sprites.
    QVector<QFileInfo> ingredientFilePaths = Spritesheet::makeSprites("../a8-an-educational-app-f18-kathrynriding-1/images/ingredientsSheet.png", 49, 60, 80);
    ingredientSprites = QVector<IngredientSprite>();

    trueIngredientTextures = QVector<sf::Texture>(Ingredients::TRUEINGREDIENTS);
    //assignTextures(ingredientFilePaths);

    // Create all ingredient sprite objects. This included tools.
    //int ingredientIndex = 0;
    for (int i = 0; i < Ingredients::TRUEINGREDIENTS; i++)
    {
        // Add all images.
        ingredientSprites.append(IngredientSprite());
        trueIngredientTextures[i].loadFromFile(ingredientFilePaths[i].absoluteFilePath().toStdString());
        ingredientSprites[i].setTexture(trueIngredientTextures[i]);

        /*
        // Add all images.
        ingredientSprites.append(IngredientSprite());
        ingredientSprites[i].storedTexture.loadFromFile(ingredientFilePaths[i].absoluteFilePath().toStdString());
        ingredientSprites[i].setTexture(ingredientSprites[i].storedTexture);
        */

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
    QVector<QFileInfo> faceFilePaths = Spritesheet::makeSprites("../a8-an-educational-app-f18-kathrynriding-1/images/facesSheet.png", 6, 200, 200);
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
    currentMood = 0;

    // Load the background image.
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

    draw(backgroundSprite);
    draw(glassImage);

    // Draw the current face.
    draw(faceSprites[currentMood]);

    // Update the position of a clicked item.
    if(selected)
    {
        selected->setPosition(mouse.x, mouse.y);
        //qDebug() << mouse.x << ", " << mouse.y;
    }

    // Draw all ingredients and tools.
    for (int i = 0; i < Ingredients::ITEMSININGREDIENTS; i++)
    {
        draw(ingredientSprites[i]);
    }


}

void GameArea::receiveMood(int mood)
{
    currentMood = mood;
}

/*
void GameArea::assignTextures(QVector<QFileInfo> sprites)
{
    ingredientSprites = QVector<IngredientSprite>();

    for(QFileInfo current: sprites){
       ingredientSprites.append(IngredientSprite());
    }

    textureVodka.loadFromFile(sprites.at(0).absoluteFilePath().toStdString());
    textureTequila.loadFromFile(sprites.at(1).absoluteFilePath().toStdString());
    textureBourbon.loadFromFile(sprites.at(2).absoluteFilePath().toStdString());
    textureGin.loadFromFile(sprites.at(3).absoluteFilePath().toStdString());
    textureDarkRum.loadFromFile(sprites.at(4).absoluteFilePath().toStdString());
    textureWhiteRum.loadFromFile(sprites.at(5).absoluteFilePath().toStdString());
    textureLightRum.loadFromFile(sprites.at(6).absoluteFilePath().toStdString());
    textureGrandMarnier.loadFromFile(sprites.at(7).absoluteFilePath().toStdString());
    textureSweetVermouth.loadFromFile(sprites.at(8).absoluteFilePath().toStdString());
    textureDryVermouth.loadFromFile(sprites.at(9).absoluteFilePath().toStdString());
    textureTrippleSec.loadFromFile(sprites.at(10).absoluteFilePath().toStdString());
    textureKahlua.loadFromFile(sprites.at(11).absoluteFilePath().toStdString());
    textureJagermeister.loadFromFile(sprites.at(12).absoluteFilePath().toStdString());
    textureCampari.loadFromFile(sprites.at(13).absoluteFilePath().toStdString());
    textureGreenCremeDeMenthe.loadFromFile(sprites.at(14).absoluteFilePath().toStdString());
    textureCremeDeCacao.loadFromFile(sprites.at(15).absoluteFilePath().toStdString());
    texturePeachSchnapps.loadFromFile(sprites.at(16).absoluteFilePath().toStdString());

    textureSalt.loadFromFile(sprites.at(17).absoluteFilePath().toStdString());
    textureMargaritaSalt.loadFromFile(sprites.at(18).absoluteFilePath().toStdString());
    texturePepper.loadFromFile(sprites.at(19).absoluteFilePath().toStdString());
    textureNutmeg.loadFromFile(sprites.at(20).absoluteFilePath().toStdString());
    textureice.loadFromFile(sprites.at(21).absoluteFilePath().toStdString());

    textureTonicWater.loadFromFile(sprites.at(22).absoluteFilePath().toStdString());
    textureSparklingWater.loadFromFile(sprites.at(23).absoluteFilePath().toStdString());
    textureClubSoda.loadFromFile(sprites.at(24).absoluteFilePath().toStdString());
    textureCola.loadFromFile(sprites.at(25).absoluteFilePath().toStdString());
    textureSimpleSyrup.loadFromFile(sprites.at(26).absoluteFilePath().toStdString());
    textureCream.loadFromFile(sprites.at(27).absoluteFilePath().toStdString());
    textureAngosturaBitters.loadFromFile(sprites.at(28).absoluteFilePath().toStdString());
    textureWorcestershireSauce.loadFromFile(sprites.at(29).absoluteFilePath().toStdString());
    textureCreamOfCoconut.loadFromFile(sprites.at(30).absoluteFilePath().toStdString());
    textureGingerBeer.loadFromFile(sprites.at(31).absoluteFilePath().toStdString());

    textureOrangeJuice.loadFromFile(sprites.at(32).absoluteFilePath().toStdString());
    textureLimeJuice.loadFromFile(sprites.at(33).absoluteFilePath().toStdString());
    textureLemonJuice.loadFromFile(sprites.at(34).absoluteFilePath().toStdString());
    texturePineappleJuice.loadFromFile(sprites.at(35).absoluteFilePath().toStdString());
    textureTomatoJuice.loadFromFile(sprites.at(36).absoluteFilePath().toStdString());
    textureCranberryJuice.loadFromFile(sprites.at(37).absoluteFilePath().toStdString());

    textureOrangeWedge.loadFromFile(sprites.at(38).absoluteFilePath().toStdString());
    textureOrangeTwist.loadFromFile(sprites.at(39).absoluteFilePath().toStdString());
    textureLimeWedge.loadFromFile(sprites.at(40).absoluteFilePath().toStdString());
    textureLimeTwist.loadFromFile(sprites.at(41).absoluteFilePath().toStdString());
    textureLemonTwist.loadFromFile(sprites.at(42).absoluteFilePath().toStdString());
    texturePineappleWedge.loadFromFile(sprites.at(43).absoluteFilePath().toStdString());
    textureMintLeaf.loadFromFile(sprites.at(44).absoluteFilePath().toStdString());
    textureMintSprig.loadFromFile(sprites.at(45).absoluteFilePath().toStdString());
    textureCherry.loadFromFile(sprites.at(46).absoluteFilePath().toStdString());
    textureGreenOlive.loadFromFile(sprites.at(47).absoluteFilePath().toStdString());
    textureCelery.loadFromFile(sprites.at(48).absoluteFilePath().toStdString());

    ingredientSprites[0].setTexture(textureVodka);
    ingredientSprites[1].setTexture(textureTequila);
    ingredientSprites[2].setTexture(textureBourbon);
    ingredientSprites[3].setTexture(textureGin);
    ingredientSprites[4].setTexture(textureDarkRum);
    ingredientSprites[5].setTexture(textureWhiteRum);
    ingredientSprites[6].setTexture(textureLightRum);
    ingredientSprites[7].setTexture(textureGrandMarnier);
    ingredientSprites[8].setTexture(textureSweetVermouth);
    ingredientSprites[9].setTexture(textureDryVermouth);
    ingredientSprites[10].setTexture(textureTrippleSec);
    ingredientSprites[11].setTexture(textureKahlua);
    ingredientSprites[12].setTexture(textureJagermeister);
    ingredientSprites[13].setTexture(textureCampari);
    ingredientSprites[14].setTexture(textureGreenCremeDeMenthe);
    ingredientSprites[15].setTexture(textureCremeDeCacao);
    ingredientSprites[16].setTexture(texturePeachSchnapps);

    ingredientSprites[17].setTexture(textureSalt);
    ingredientSprites[18].setTexture(textureMargaritaSalt);
    ingredientSprites[19].setTexture(texturePepper);
    ingredientSprites[20].setTexture(textureNutmeg);
    ingredientSprites[21].setTexture(textureice);

    ingredientSprites[22].setTexture(textureTonicWater);
    ingredientSprites[23].setTexture(textureSparklingWater);
    ingredientSprites[24].setTexture(textureClubSoda);
    ingredientSprites[25].setTexture(textureCola);
    ingredientSprites[26].setTexture(textureSimpleSyrup);
    ingredientSprites[27].setTexture(textureCream);
    ingredientSprites[28].setTexture(textureAngosturaBitters);
    ingredientSprites[29].setTexture(textureWorcestershireSauce);
    ingredientSprites[30].setTexture(textureCreamOfCoconut);
    ingredientSprites[31].setTexture(textureGingerBeer);

    ingredientSprites[32].setTexture(textureOrangeJuice);
    ingredientSprites[33].setTexture(textureLimeJuice);
    ingredientSprites[34].setTexture(textureLemonJuice);
    ingredientSprites[35].setTexture(texturePineappleJuice);
    ingredientSprites[36].setTexture(textureTomatoJuice);
    ingredientSprites[37].setTexture(textureCranberryJuice);

    ingredientSprites[38].setTexture(textureOrangeWedge);
    ingredientSprites[39].setTexture(textureOrangeTwist);
    ingredientSprites[40].setTexture(textureLimeWedge);
    ingredientSprites[41].setTexture(textureLimeTwist);
    ingredientSprites[42].setTexture(textureLemonTwist);
    ingredientSprites[43].setTexture(texturePineappleWedge);
    ingredientSprites[44].setTexture(textureMintLeaf);
    ingredientSprites[45].setTexture(textureMintSprig);
    ingredientSprites[46].setTexture(textureCherry);
    ingredientSprites[47].setTexture(textureGreenOlive);
    ingredientSprites[48].setTexture(textureCelery);
}
*/
