#ifndef HELPMENU_H
#define HELPMENU_H

#include <QDialog>

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
