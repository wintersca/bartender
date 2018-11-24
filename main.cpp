#include "mainwindow.h"
#include <QApplication>
#include "gamearea.h"
#include "customdrinkimporter.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    //GameArea* SFMLView = new GameArea(w.centralWidget(), QPoint(20, 20), QSize(1000, 1000));
    //SFMLView->show();
    w.show();

    // Showing this by default for testing.
    CustomDrinkImporter* window = new CustomDrinkImporter();
    window->setModal(true);
    window->show();
    window->raise();
    window->activateWindow();

    return a.exec();
}
