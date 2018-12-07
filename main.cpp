#include "mainwindow.h"
#include <QApplication>
#include "gamearea.h"
#include "controller.h"
#include "xmldrinkparser.h"
//#include <Box2D/Box2D/Box2D.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    XMLDrinkParser* xml = new XMLDrinkParser();
    Controller *c = new Controller(xml);
    MainWindow w(c);
    w.show();
    return a.exec();
}
