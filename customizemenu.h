#ifndef CUSTOMIZEMENU_H
#define CUSTOMIZEMENU_H

#include <QDialog>
#include "drink.h"
#include "controller.h"

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
    QVector<Drink*> Menu;
    QVector<Drink*> GivenMenu;
    void AddDrinksToBoxes();

signals:
    void sendUserSpecifiedMenu(QVector<Drink*> newMenu);
private slots:

    void on_removeDrink_clicked();
    void on_addDrink_clicked();
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
};

#endif // CUSTOMIZEMENU_H
