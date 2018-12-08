#ifndef VIEWRECIPES_H
#define VIEWRECIPES_H

#include <QDialog>
#include "drink.h"
#include <QLabel>

namespace Ui {
class ViewRecipes;
}

class ViewRecipes : public QDialog
{
    Q_OBJECT

public:
    explicit ViewRecipes(QVector<Drink*> menu, QWidget *parent = nullptr);
    ~ViewRecipes();

private slots:
    void on_allRecipes_activated(const QString &arg1);

private:
    Ui::ViewRecipes *ui;
    QVector<Drink*> Menu;
    QVector<QLabel*> stepsInDrink;
    QVector<QLabel*> amountsInDrink;
    QVector<QLabel*> unitsInDrink;
    QVector<QLabel*> ingredientsInDrink;
};

#endif // VIEWRECIPES_H
