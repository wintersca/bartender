#include "mainwindow.h"
#include <QApplication>
#include "gamearea.h"
#include "customdrinkimporter.h"
#include "controller.h"

int main(int argc, char *argv[])
{
    Controller *controller = new Controller();
    QApplication a(argc, argv);
    MainWindow w;

    MainWindow w(controller);
    GameArea* SFMLView = new GameArea(w.centralWidget(), QPoint(20, 20), QSize(500, 500));
    SFMLView->show();
    w.show();

    // Showing this by default for testing.
    CustomDrinkImporter* window = new CustomDrinkImporter(controller);
    window->setModal(true);
    window->show();
    window->raise();
    window->activateWindow();


    return a.exec();
}
