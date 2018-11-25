#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHBoxLayout>
#include "controller.h"
#include "customdrinkimporter.h"
#include "gamearea.h"

Controller *controller;
MainWindow::MainWindow(Controller *controllerPtr, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->ui->setupUi(this);

    GameArea* SFMLView = new GameArea(this, QPoint(20, 20), QSize(1000, 1000));
    //ui->verticalLayout->addWidget(SFMLView);
    ui->widgetLayout->addWidget(SFMLView);

    QPixmap recipeAndTips(":/iconImages/images/barBackground.png");
    recipeAndTips = recipeAndTips.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, recipeAndTips);
    this->setPalette(palette);

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
    if (controller == nullptr)
    {
        controller = new Controller();
    }
    else
        controller = controllerPtr;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addCustomDrink_clicked()
{
    CustomDrinkImporter* window = new CustomDrinkImporter(controller, this);
    window->setModal(true);
    window->show();
    window->raise();
    window->activateWindow();
}
