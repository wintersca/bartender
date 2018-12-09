#include "customizemenu.h"
#include "ui_customizemenu.h"

CustomizeMenu::CustomizeMenu(Controller *controller, QVector<Drink*> menu, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CustomizeMenu)
{
    ui->setupUi(this);

    Menu = menu;

    AddDrinksToBoxes();

    // Make a copy of the given menu in case cancel is pressed.
    GivenMenu = QVector<Drink*>(menu);

    //signal to controller
    QObject::connect(this, &CustomizeMenu::sendUserSpecifiedMenu,
                      controller, &Controller::receiveUserSpecifiedMenu);
}

CustomizeMenu::~CustomizeMenu()
{
    delete ui;
}

void CustomizeMenu::AddDrinksToBoxes()
{
    // Fill in the boxes.
    for (int i = 0; i < Menu.length(); i++)
    {
        if (Menu[i]->getSelected())
        {
            ui->usedDrinks->addItem(Menu[i]->Name);
        }
        else
        {
            ui->removedDrinks->addItem(Menu[i]->Name);
        }
    }
}

void CustomizeMenu::on_removeDrink_clicked()
{
    // Figure out what drink was selected.
    for (int i = 0; i < Menu.length(); i++)
    {
        if (!QString::compare(Menu[i]->Name, ui->usedDrinks->currentText(), Qt::CaseSensitive))
        {
            // Set that drink to unselected.
            Menu[i]->setSelected(false);
            break;
        }
    }

    // Clear the items in the menus.
    ui->usedDrinks->clear();
    ui->removedDrinks->clear();

    // Re pepulate the menus.
    AddDrinksToBoxes();
}

void CustomizeMenu::on_addDrink_clicked()
{
    // Figure out what drink was selected.
    for (int i = 0; i < Menu.length(); i++)
    {
        if (!QString::compare(Menu[i]->Name, ui->removedDrinks->currentText(), Qt::CaseSensitive))
        {
            // Set that drink to selected.
            Menu[i]->setSelected(true);
            break;
        }
    }

    // Clear the items in the menus.
    ui->usedDrinks->clear();
    ui->removedDrinks->clear();

    // Re pepulate the menus.
    AddDrinksToBoxes();
}

void CustomizeMenu::on_buttonBox_accepted()
{
    emit sendUserSpecifiedMenu(Menu);
}

void CustomizeMenu::on_buttonBox_rejected()
{
    emit sendUserSpecifiedMenu(GivenMenu);
}
