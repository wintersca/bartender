#include "mainwindow.h"
#include <QApplication>
#include "gamearea.h"
#include "xmldrinkparser.h"

int main(int argc, char *argv[])
{
    XMLDrinkParser xml;
    xml.parseXMLDatabase();
    QApplication a(argc, argv);
    MainWindow w;
    //GameArea* SFMLView = new GameArea(w.centralWidget(), QPoint(20, 20), QSize(1000, 1000));
    //SFMLView->show();
    w.show();

    return a.exec();
}
