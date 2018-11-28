#include "xmldrinkparser.h"
#include <iostream>

XMLDrinkParser::XMLDrinkParser()
{

    stringsToIngredients = QMap<QString, Ingredients::Ingredients>();

        stringsToIngredients["Vodka"] = Ingredients::Vodka;
        stringsToIngredients["Tequila"] = Ingredients::Tequila;
        stringsToIngredients["Bourbon"] = Ingredients::Bourbon;
        stringsToIngredients["Gin"] = Ingredients::Gin;
        stringsToIngredients["Dark Rum"] = Ingredients::DarkRum;
        stringsToIngredients["White Rum"] = Ingredients::WhiteRum;
        stringsToIngredients["Light Rum"] = Ingredients::LightRum;
        stringsToIngredients["Grand Marnier"] = Ingredients::GrandMarnier;
        stringsToIngredients["Sweet Vermouth"] = Ingredients::SweetVermouth;
        stringsToIngredients["Dry Vermouth"] = Ingredients::DryVermouth;
        stringsToIngredients["Tripple Sec"] = Ingredients::TrippleSec;
        stringsToIngredients["Kahlua"] = Ingredients::Kahlua;
        stringsToIngredients["Jagermeister"] = Ingredients::Jagermeister;
        stringsToIngredients["Campari"] = Ingredients::Campari;
        stringsToIngredients["Green Creme de Menthe"] = Ingredients::GreenCremeDeMenthe;
        stringsToIngredients["Creme de Cacao"] = Ingredients::CremeDeCacao;
        stringsToIngredients["Peach Schnapps"] = Ingredients::PeachSchnapps;
        stringsToIngredients["Salt"] = Ingredients::Salt;
        stringsToIngredients["Pepper"] = Ingredients::Pepper;
        stringsToIngredients["Ice"] = Ingredients::Ice;
        stringsToIngredients["Simple Syrup"] = Ingredients::SimpleSyrup;
        stringsToIngredients["Tonic Water"] = Ingredients::TonicWater;
        stringsToIngredients["Sparkling Water"] = Ingredients::SparklingWater;
        stringsToIngredients["Angostura Bitters"] = Ingredients::AngosturaBitters;
        stringsToIngredients["Cola"] = Ingredients::Cola;
        stringsToIngredients["Club Soda"] = Ingredients::ClubSoda;
        stringsToIngredients["Cream"] = Ingredients::Cream;
        stringsToIngredients["Worcestershire Sauce"] = Ingredients::WorcestershireSauce;
        stringsToIngredients["Orange Juice"] = Ingredients::OrangeJuice;
        stringsToIngredients["Lime Juice"] = Ingredients::LimeJuice;
        stringsToIngredients["Lemon Juice"] = Ingredients::LemonJuice;
        stringsToIngredients["Pineapple Juice"] = Ingredients::PineappleJuice;
        stringsToIngredients["Tomato Juice"] = Ingredients::TomatoJuice;
        stringsToIngredients["Cranberry Juice"] = Ingredients::CranberryJuice;
        stringsToIngredients["Orange Wedge"] = Ingredients::OrangeWedge;
        stringsToIngredients["Orange Twist"] = Ingredients::OrangeTwist;
        stringsToIngredients["Lime Wedge"] = Ingredients::LimeWedge;
        stringsToIngredients["Lime Twist"] = Ingredients::LimeTwist;
        stringsToIngredients["Lemon Twist"] = Ingredients::LemonTwist;
        stringsToIngredients["Pineapple Wedge"] = Ingredients::PineappleWedge;
        stringsToIngredients["Cream Of Coconut"] = Ingredients::CreamOfCoconut;
        stringsToIngredients["Ginger Beer"] = Ingredients::GingerBeer;
        stringsToIngredients["Mint Leaf"] = Ingredients::MintLeaf;
        stringsToIngredients["Mint Sprig"] = Ingredients::MintSprig;
        stringsToIngredients["Cherry"] = Ingredients::Cherry;
        stringsToIngredients["Green Olive"] = Ingredients::GreenOlive;
        stringsToIngredients["Celery"] = Ingredients::Celery;
        stringsToIngredients["Nutmeg"] = Ingredients::Nutmeg;
        stringsToIngredients["Shake"] = Ingredients::Shake;
        stringsToIngredients["Stir"] = Ingredients::Stir;
        stringsToIngredients["Muddle"] = Ingredients::Muddle;
        stringsToIngredients["Margarita Salt"]=Ingredients::MargaritaSalt;

}

XMLDrinkParser::~XMLDrinkParser()
{
    for(Drink* drink : drinkDatabase)
    {
        delete drink;
    }
}

QVector<Drink*> XMLDrinkParser::parseXMLDatabase()
{
    QFile file("../a8-an-educational-app-f18-kathrynriding-1/database/DrinkDatabase.xml");
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        throw -1;
    }
    else
    {
        reader.setDevice(&file);
        read();
    }

    return drinkDatabase;
}

void XMLDrinkParser::read()
{
    if(reader.readNextStartElement())
    {
        if(reader.name()=="collection")
        {
            readDrinkDatabase();
        }
        else
        {
            throw -1;
        }
    }
}

void XMLDrinkParser::readDrinkDatabase()
{
    while(reader.readNextStartElement())
    {
        if(reader.name()=="drink")
        {
            readDrink();
        }
        else
        {
            reader.skipCurrentElement();
        }
    }
}

void XMLDrinkParser::readDrink()
{
    Drink* drink = new Drink();
    readName(drink);

    while(reader.readNextStartElement())
    {
        if(reader.name()=="ingredients")
        {
            readIngredients(drink);
        }
        else if(reader.name()=="actions")
        {
            readSteps(drink);
        }
        else if(reader.name()=="trivia_details")
        {
            readTrivia(drink);
        }
        else
        {
            reader.skipCurrentElement();
        }
    }

    addDrink(drink);
}

void XMLDrinkParser::readName(Drink* drink)
{
    reader.readNextStartElement();
    QString name = reader.readElementText();
    drink->setName(name);
}

void XMLDrinkParser::readIngredients(Drink* drink)
{
    bool test=reader.readNextStartElement();
    while(test)
    {
        QString skip = reader.name().toString();
        if(reader.name()=="ingredient")
        {
            const QString name = reader.attributes().value("name").toString();
            double amt = reader.attributes().value("amount").toDouble();
            drink->addIngredient(stringsToIngredients.value(name), amt);
        }
        reader.skipCurrentElement();
        test=reader.readNextStartElement();
        skip = reader.name().toString();
    }
}

void XMLDrinkParser::readSteps(Drink* drink)
{
    while(reader.readNextStartElement())
    {
        if(reader.name()=="action")
        {
            QString inst = reader.attributes().value("instruction").toString();
            const QString item = reader.attributes().value("item").toString();
            double amt = reader.attributes().value("amount").toDouble();
            drink->addStep(inst, stringsToIngredients.value(item), amt);
        }
        reader.skipCurrentElement();
    }
}

void XMLDrinkParser::readTrivia(Drink* drink)
{
    while(reader.readNextStartElement())
    {
        if(reader.name()=="trivia")
        {
            QString triv = reader.attributes().value("description").toString();
            drink->addTrivia(triv);
        }
        reader.skipCurrentElement();
    }
}

void XMLDrinkParser::addDrink(Drink* drink)
{
    drinkDatabase.push_back(drink);
    drink->print();
}

void XMLDrinkParser::updateXMLDatabase(Drink* newDrink)
{

        //xmlWriter.setAutoFormatting(true);
        //xmlWriter.writeStartDocument();

        //xmlWriter.writeStartElement("LAMPS");

        //xmlWriter.writeStartElement("LIGHT1");
        //xmlWriter.writeTextElement("State", "statevalue" );
        //xmlWriter.writeTextElement("Room", "roomvalue");
        //xmlWriter.writeTextElement("Potencial", "potencialvalue");

    //xmlWriter.writeEndElement();

    QFile file("../a8-an-educational-app-f18-kathrynriding-1/database/DrinkDatabase.xml");
    if(!file.open(QFile::WriteOnly | QFile::Text))
    {
        throw -1;
    }
    else
    {
        writer.setDevice(&file);
        writer.setAutoFormatting(true);
    }

}
