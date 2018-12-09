#include <QString>
#include <QMap>
#include <QVector>
#include "ingredients.h"
#include "step.h"

#ifndef DRINK_H
#define DRINK_H

/**
 * @brief The Drink class is responsible for encapculating
 * drink details.
 *
 * Author: Tristan Bowler
 */
class Drink
{

public:   
    QString Name;
    QVector<QString> Trivia;
    QMap<Ingredients::Ingredients, double> IngredientsMap;

    /**
     * @brief Drink: an empty drink object
     */
    Drink();

    /**
     * @brief Drink: a drink object associated with a name
     * @param name: name to set
     */
    Drink(QString name);

    /**
     * @brief setName: sets a drink object name
     * @param name: name to set
     */
    void setName(QString name);

    /**
     * @brief addTrivia: adds trivia to a drink object
     * @param triv: trivia to add
     */
    void addTrivia(QString triv);

    /**
     * @brief addIngredient: adds ingredient to a drink object
     * @param ingredient: ingredient to add
     * @param amount: amount to add
     */
    void addIngredient(Ingredients::Ingredients ingredient, double amount);

    /**
     * @brief addStep: adds step to a drink object
     * @param instruction: instruction to add
     * @param ingredient: ingredient for instruction
     * @param amount: amount for instruction
     */
    void addStep(QString instruction, Ingredients::Ingredients ingredient, double amount);

    /**
     * @brief setSteps: adds multiple steps to a drink object
     * @param steps: steps to add
     */
    void setSteps(QVector<Step> steps);

    /**
     * @brief setSelected: adjusts whether it gets played in game or not
     * @param select
     */
    void setSelected(bool select);

    /**
     * @brief getName: gets name of drink object.
     * @return
     */
    QString getName();

    /**
     * @brief getTrivia: gets trivia of drink object.
     * @return
     */
    QVector<QString> getTrivia();

    /**
     * @brief getTngredients: gets ingredients of drink object.
     * @return
     */
    QMap<Ingredients::Ingredients, double> getTngredients();

    /**
     * @brief getSteps: gets steps of drink object.
     * @return
     */
    QVector<Step> getSteps();

    /**
     * @brief getSelected: returns whether or not a drink is playable in a game.
     * @return
     */
    bool getSelected();

    /**
     * @brief print: makes drink printable
     */
    void print();
    
private:
    QVector<Step> Steps;
    bool userSelected;
};

#endif // DRINK_H
