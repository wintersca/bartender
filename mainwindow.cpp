#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHBoxLayout>
#include "customdrinkimporter.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
     Q_INIT_RESOURCE(images);
    this->ui->setupUi(this);
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
