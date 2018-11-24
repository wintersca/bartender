#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHBoxLayout>
#include "controller.h"
#include "customdrinkimporter.h"

MainWindow::MainWindow(Controller *controller, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    /* template signals TO controller
    QObject::connect(ui->uiElement, &QElementType::action,
                     controller, &controller::socketName);
    QObject::connect(this, &MainWindow::functionName,
                     controller, &controller::socketName);

        template signal FROM controller
    QObject::connect(controller, &controller::signalName,
                     this, &MainWindow::slotName);
    */

    // sent signals

    //received signals
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionAdd_New_Drink_triggered()
{
    CustomDrinkImporter* window = new CustomDrinkImporter(this);
    window->setModal(true);
    window->show();
    window->raise();
    window->activateWindow();
}
