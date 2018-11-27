#include <QVector>
#include <QFile>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <drink.h>
#include <controller.h>

#ifndef XMLDRINKPARSER_H
#define XMLDRINKPARSER_H


class XMLDrinkParser
{
public:
    XMLDrinkParser();
    void parseXMLDatabase();
private slots:
    void updateXMLDatabase(QVector<Drink> newDrinks);
signals:
    void sendAllRecipes(QVector<Drink> allDrinks);
};

#endif // XMLDRINKPARSER_H
