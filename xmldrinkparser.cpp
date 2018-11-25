#include "xmldrinkparser.h"
#include <iostream>

XMLDrinkParser::XMLDrinkParser()
{

}

QVector<Drink> XMLDrinkParser::parseXMLDatabase()
{
    QVector<Drink> result;

    QXmlStreamReader reader;
    QFile file("./database/DrinkDatabase.xml");
    if(file.open(QIODevice::ReadOnly))
    {
        reader.setDevice(&file);
        while(!reader.isEndDocument())
        {
            if(reader.isStartElement())
            {
                std::cout << reader.name().toString().toStdString() << std::endl;
            }
        }
    }
    else
    {

    }
    return result;
}

void XMLDrinkParser::updateXMLDatabase(QVector<Drink> newDrinks)
{

}
