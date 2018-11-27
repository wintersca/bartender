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
    void updateXMLDatabase(QVector<Drink> newDrinks);
};

#endif // XMLDRINKPARSER_H
