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

extern QVector<Drink> menu;
extern XMLDrinkParser parser;
class Controller : public QObject
{
    Q_OBJECT

public:
    explicit Controller(XMLDrinkParser parser, QObject *parent = nullptr);
public slots:
    void updateRecipes(Drink newRecipe);
signals:
    void submitNewRecipes(Drink newDrink);
    void recipesToGame(QVector<Drink> menu);

private:

QVector<Drink> sortRecipes(QVector<Drink> recipes);
QVector<Drink> getAllRecipes();

};

#endif // CONTROLLER_H








/* template signals TO controller
 * all of these go in the class you are connecting with, not the controller.
 *
   QObject::connect(ui->uiElement, &QElementType::action,
                    controller, &Controller::socketName);
   QObject::connect(this, &MainWindow::functionName,
                    controller, &Controller::socketName);


   template signal FROM controller

   QObject::connect(controller, &Controller::signalName,
                    this, &MainWindow::slotName);
*/
