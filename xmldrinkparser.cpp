#include "xmldrinkparser.h"
#include "ingredientsmap.h"

XMLDrinkParser::XMLDrinkParser()
{
    IngredientsMap ingredientsMap = IngredientsMap();
    stringsToIngredients = ingredientsMap.stringsToIngredients;
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
}

void XMLDrinkParser::updateXMLDatabase(Drink* newDrink)
{
    QFile file("../a8-an-educational-app-f18-kathrynriding-1/database/DrinkDatabase.xml");
    if(!file.open(QFile::WriteOnly | QFile::Text))
    {
        throw -1;
    }
    else
    {
        writer.setDevice(&file);
        writer.setAutoFormatting(true);

        writer.writeStartDocument();
        writer.writeStartElement("collection");
        for(Drink* current: drinkDatabase)
        {
            writeXMLDrink(current);
        }

        writeXMLDrink(newDrink);

        writer.writeEndElement();
        writer.writeEndDocument();
        file.close();
    }
}

void XMLDrinkParser::writeXMLDrink(Drink* current)
{
    writer.writeStartElement("drink");
    writer.writeTextElement("name", current->getName());
    writer.writeStartElement("ingredients");

    QMap<Ingredients::Ingredients, double> ingredients = current->getTngredients();
    for(QMap<Ingredients::Ingredients, double>::iterator it = ingredients.begin(); it != ingredients.end(); ++it)
    {
        writer.writeStartElement("ingredient");
        writer.writeAttribute("name", Ingredients::ingredientData[it.key()].displayString);
        writer.writeAttribute("amount", QString::number(ingredients.value(it.key())));
        writer.writeEndElement();
    }

    writer.writeEndElement();
    writer.writeStartElement("actions");

    QVector<Step> actions = current->getSteps();
    for(Step action : actions)
    {
        writer.writeStartElement("action");
        writer.writeAttribute("instruction", action.getInstruction());
        writer.writeAttribute("item", Ingredients::ingredientData[action.getItem()].displayString);
        writer.writeAttribute("amount", QString::number(action.getAmount()));
        writer.writeEndElement();
    }

    writer.writeEndElement();
    writer.writeStartElement("trivia_details");
    QVector<QString> triviaList = current->getTrivia();
    for(QString trivia : triviaList)
    {
        writer.writeStartElement("trivia");
        writer.writeAttribute("description", trivia);
        writer.writeEndElement();
    }

    writer.writeEndElement();
    writer.writeEndElement();
}


