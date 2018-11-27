#include "xmldrinkparser.h"
#include <iostream>

XMLDrinkParser::XMLDrinkParser()
{
//    //signal to controller
//    QObject::connect(this, &XMLDrinkParser::sendAllRecipes,
//                     controller, &Controller::getAllRecipes);
//    //signal from controller
//    QObject::connect(controller, &Controller::submitNewRecipes,
//                     this, &XMLDrinkParser::updateXMLDatabase);
}

void XMLDrinkParser::parseXMLDatabase()
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
    //emit sendAllRecipes(result);
}

void XMLDrinkParser::updateXMLDatabase(QVector<Drink> newDrinks)
{

}
