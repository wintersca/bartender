#include <QVector>
#include <QFile>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <drink.h>

#ifndef XMLDRINKPARSER_H
#define XMLDRINKPARSER_H


class XMLDrinkParser
{
public:
    XMLDrinkParser();
    QVector<Drink> parseXMLDatabase();
    void updateXMLDatabase(Drink newDrink);
};

#endif // XMLDRINKPARSER_H
