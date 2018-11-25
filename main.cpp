#include "mainwindow.h"
#include <QApplication>
#include "gamearea.h"
#include "controller.h"

int main(int argc, char *argv[])
{
    Controller *c = new Controller();
    QApplication a(argc, argv);
    MainWindow w(c);

    //GameArea* SFMLView = new GameArea(w.centralWidget(), QPoint(20, 20), QSize(1000, 1000));
    //SFMLView->show();
    w.show();

    return a.exec();
}
