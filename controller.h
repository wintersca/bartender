#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QString>
#include <QVector>
#include <QMap>
#include "drink.h"
#include "gamearea.h"
#include "ingredients.h"
#include "ingredientsprite.h"
#include "qsfmlcanvas.h"
#include "xmldrinkparser.h"

extern QMap<int, Drink> menu;
extern XMLDrinkParser parser;
class Controller : public QObject
{
public:
    explicit Controller(XMLDrinkParser parser, QObject *parent = nullptr);
public slots:
        void receiveRecipe(Drink newDrink);
private:
void updateDatabase(Drink newRecipe);
QVector<Drink> sortRecipes(QVector<Drink> recipes);
void sendUpdatedRecipesToGame(QVector<Drink> sortedDrinks);
void getAllRecipes();
signals:
    void submitNewRecipes(Drink newDrink);
    void recipesToGame(QVector<Drink>);
};

#endif // CONTROLLER_H

/* template signals TO controller
 *
   QObject::connect(ui->uiElement, &QElementType::action,
                    controller, &Controller::socketName);
   QObject::connect(this, &MainWindow::functionName,
                    controller, &Controller::socketName);


   template signal FROM controller

   QObject::connect(controller, &Controller::signalName,
                    this, &MainWindow::slotName);
*/
