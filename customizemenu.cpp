#include "customizemenu.h"
#include "ui_customizemenu.h"

CustomizeMenu::CustomizeMenu(Controller *controller, QVector<Drink*> menu, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CustomizeMenu)
{
    ui->setupUi(this);

    Menu = menu;

    // Fill in the boxes.
    for (int i = 0; i < menu.length(); i++)
    {
        ui->usedDrinks->addItem(menu[i]->Name);
    }

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

void CustomizeMenu::on_removeDrink_clicked()
{
    // Figure out what drink was selected.
    // Remove that drink from the vector.
    Menu.remove(ui->usedDrinks->currentIndex());

    // Clear the items in the usedDrinks menu.
    ui->usedDrinks->clear();

    // Add the items in the vector to the usedDrinks menu.
    for (int i = 0; i < Menu.length(); i++)
    {
        ui->usedDrinks->addItem(Menu[i]->Name);
    }
}

void CustomizeMenu::on_addDrink_clicked()
{

}

void CustomizeMenu::on_buttonBox_accepted()
{
    emit sendUserSpecifiedMenu(Menu);
}

void CustomizeMenu::on_buttonBox_rejected()
{
    emit sendUserSpecifiedMenu(GivenMenu);
}
