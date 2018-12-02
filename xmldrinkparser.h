#include <QVector>
#include <QFile>
#include <QDir>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QMap>
#include <ingredients.h>
#include "ingredientsmap.h"
#include "drink.h"

#ifndef XMLDRINKPARSER_H
#define XMLDRINKPARSER_H



class XMLDrinkParser
{
    public:
        XMLDrinkParser();
        ~XMLDrinkParser();
        QVector<Drink*> parseXMLDatabase();
        void updateXMLDatabase(Drink* newDrink);

    private:
        QVector<Drink*> drinkDatabase;
        QXmlStreamWriter writer;
        QXmlStreamReader reader;
        QMap<QString, Ingredients::Ingredients> stringsToIngredients;
        void read();
        void readDrinkDatabase();
        void readDrink();
        void readName(Drink* drink);
        void readIngredients(Drink* drink);
        void readSteps(Drink* drink);
        void readTrivia(Drink* drink);
        void addDrink(Drink* drink);
        void writeXMLDrink(Drink* current);

};

#endif // XMLDRINKPARSER_H
