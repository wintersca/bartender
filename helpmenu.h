#include <QDialog>

#ifndef HELPMENU_H
#define HELPMENU_H

/**
 * The help menu displays information about how the game is played.
 * It also explains how the game can be modified.
 * Author: Alex Smith.
 */

namespace Ui {
class HelpMenu;
}

class HelpMenu : public QDialog
{
    Q_OBJECT

public:
    explicit HelpMenu(QWidget *parent = nullptr);
    ~HelpMenu();

private:
    Ui::HelpMenu *ui;
};

#endif // HELPMENU_H
