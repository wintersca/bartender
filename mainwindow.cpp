#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHBoxLayout>
#include "gamearea.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->ui->setupUi(this);

    GameArea* SFMLView = new GameArea(this, QPoint(20, 20), QSize(1000, 1000));
    ui->widgetLayout->addWidget(SFMLView);

}

MainWindow::~MainWindow()
{
    delete ui;
}
