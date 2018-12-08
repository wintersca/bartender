#include "viewrecipes.h"
#include "ui_viewrecipes.h"

ViewRecipes::ViewRecipes(QVector<Drink*> menu, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ViewRecipes)
{
    ui->setupUi(this);

    Menu = menu;

    // Arrays of labels.


    // Fill in the names of drinks box.
    for (int i = 0; i < Menu.length(); i++)
    {
        ui->allRecipes->addItem(Menu[i]->Name);
    }
}

ViewRecipes::~ViewRecipes()
{
    delete ui;
}
