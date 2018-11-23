#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHBoxLayout>

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

