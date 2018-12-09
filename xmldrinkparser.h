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

/**
 * @brief The XMLDrinkParser class is responsible for
 * parsing and writing to the drinks database for a game.
 *
 * Authors: Tristan Bowler and Kathryn Riding
 */
class XMLDrinkParser
{
public:
    XMLDrinkParser();
    ~XMLDrinkParser();

    /**
     * @brief parseXMLDatabase: reads the drink database and returns drink objects.
     * @return
     */
    QVector<Drink*> parseXMLDatabase();

    /**
     * @brief updateXMLDatabase: updates the drink database.
     * @param newDrink
     */
    void updateXMLDatabase(Drink* newDrink);

private:
    QVector<Drink*> drinkDatabase;
    QXmlStreamWriter writer;
    QXmlStreamReader reader;
    QMap<QString, Ingredients::Ingredients> stringsToIngredients;

    /**
     * @brief read: reads drink collection XML object file.
     */
    void read();

    /**
     * @brief readDrinkDatabase: reads drink database XML object file.
     */
    void readDrinkDatabase();

    /**
     * @brief readDrink: reads a drink XML object file.
     */
    void readDrink();

    /**
     * @brief readName: reads a name XML object file.
     * @param drink
     */
    void readName(Drink* drink);

    /**
     * @brief readIngredients: reads an instruction XML object file.
     * @param drink
     */
    void readIngredients(Drink* drink);

    /**
     * @brief readSteps: reads a step in XML object file.
     * @param drink
     */
    void readSteps(Drink* drink);

    /**
     * @brief readTrivia: reads a trivia XML object file.
     * @param drink
     */
    void readTrivia(Drink* drink);

    /**
     * @brief addDrink: adds a drink object to XML file.
     * @param drink
     */
    void addDrink(Drink* drink);

    /**
     * @brief writeXMLDrink: writes the XML drink database.
     * @param current
     */
    void writeXMLDrink(Drink* current);

};

#endif // XMLDRINKPARSER_H
