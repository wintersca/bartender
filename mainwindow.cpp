#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHBoxLayout>
#include "customdrinkimporter.h"
#include "gamearea.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->ui->setupUi(this);

    GameArea* SFMLView = new GameArea(this, QPoint(20, 20), QSize(1000, 1000));
    //ui->verticalLayout->addWidget(SFMLView);
    ui->widgetLayout->addWidget(SFMLView);

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
