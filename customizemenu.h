#ifndef CUSTOMIZEMENU_H
#define CUSTOMIZEMENU_H

#include <QDialog>
#include "drink.h"
#include "controller.h"

/*
 * Customize menu allows the user to limit the drinks customers can order.
 * This allows the user to practice a set number of drinks.
 * Author: Alex Smith
 */

namespace Ui {
class CustomizeMenu;
}

class CustomizeMenu : public QDialog
{
    Q_OBJECT

public:
    explicit CustomizeMenu(Controller *controller, QVector<Drink*> menu, QWidget *parent = nullptr);
    ~CustomizeMenu();

private:
    Ui::CustomizeMenu *ui;

    // The menu that is modified and returned.
    QVector<Drink*> Menu;

    // A copy of the menu in case the user wants to discard their changes.
    QVector<Drink*> GivenMenu;

    // Fills out both combo boxes with the selected and unselected drinks.
    void AddDrinksToBoxes();

signals:
    // Send the modified menu to the controller.
    void sendUserSpecifiedMenu(QVector<Drink*> newMenu);

private slots:
    // Move the selected drink to the unselected box.
    void on_removeDrink_clicked();

    // Move the unselected drink to the selected box.
    void on_addDrink_clicked();

    // Send the controller the modified menu.
    void on_buttonBox_accepted();

    // Discard the changes and send the controller the origin menu.
    void on_buttonBox_rejected();
};

#endif // CUSTOMIZEMENU_H
