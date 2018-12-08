#ifndef VIEWRECIPES_H
#define VIEWRECIPES_H

#include <QDialog>
#include "drink.h"

namespace Ui {
class ViewRecipes;
}

class ViewRecipes : public QDialog
{
    Q_OBJECT

public:
    explicit ViewRecipes(QVector<Drink*> menu, QWidget *parent = nullptr);
    ~ViewRecipes();

private:
    Ui::ViewRecipes *ui;
    QVector<Drink*> Menu;
};

#endif // VIEWRECIPES_H
