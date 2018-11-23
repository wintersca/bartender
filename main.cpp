#include "mainwindow.h"
#include <QApplication>
#include "mycanvas.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    GameArea* SFMLView = new GameArea(&w, QPoint(20, 20), QSize(360, 360));
    SFMLView->show();
    w.show();

    return a.exec();
}
