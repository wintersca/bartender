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
    w.show();

    return a.exec();
}
