#include "mainwindow.h"
#include <QApplication>
#include "gamearea.h"
#include "controller.h"
#include "xmldrinkparser.h"
int main(int argc, char *argv[])
{
    Controller *c = new Controller();
    XMLDrinkParser xml;
    xml.parseXMLDatabase();
    QApplication a(argc, argv);
    MainWindow w(c);
    w.show();

    return a.exec();
}


