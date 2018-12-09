#include <QDialog>
#include "drink.h"
#include <QLabel>

#ifndef VIEWRECIPES_H
#define VIEWRECIPES_H

/**
 * View Recipes allows the user an easy way to view information about how all drinks are made.
 * This makes the game more educational by providing a reference to make drinks in real life.
 * All drinks in the database including custom drinks can be selected.
 * This displays all information about making them. So it doesn't include trivia.
 * Author: Alex Smith
 */

namespace Ui
{
class ViewRecipes;
}

class ViewRecipes : public QDialog
{
    Q_OBJECT

public:
    explicit ViewRecipes(QVector<Drink*> menu, QWidget *parent = nullptr);
    ~ViewRecipes();

private slots:
    void on_allRecipes_currentIndexChanged(int index);

private:
    Ui::ViewRecipes *ui;

    // All the drinks in the game.
    QVector<Drink*> Menu;

    // All the labels to display the steps.
    QVector<QLabel*> stepsInDrink;

    // All the labels to display the amounts.
    QVector<QLabel*> amountsInDrink;

    // All the labels to display the units.
    QVector<QLabel*> unitsInDrink;

    // All the labels to display the ingredient names.
    QVector<QLabel*> ingredientsInDrink;
};

#endif // VIEWRECIPES_H
