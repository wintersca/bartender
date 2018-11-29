#include "mainwindow.h"
#include <QApplication>
#include "gamearea.h"
#include "controller.h"
#include "xmldrinkparser.h"
int main(int argc, char *argv[])
{
    XMLDrinkParser* xml = new XMLDrinkParser();
    xml->parseXMLDatabase();
    QApplication a(argc, argv);
    Controller *c = new Controller(xml);
    MainWindow w(c);
    w.show();
    return a.exec();
}
