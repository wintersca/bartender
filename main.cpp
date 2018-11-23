#include "mainwindow.h"
#include <QApplication>
#include "gamearea.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    GameArea* SFMLView = new GameArea(w.centralWidget(), QPoint(20, 20), QSize(500, 500));
    SFMLView->show();
    w.show();

    return a.exec();
}
