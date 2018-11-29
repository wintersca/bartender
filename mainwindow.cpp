#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHBoxLayout>
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

    QPixmap recipeAndTips(":/iconImages/images/corkBoard.png");
    recipeAndTips = recipeAndTips.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, recipeAndTips);
    this->setPalette(palette);

    // Set background color of the recipe area.
    QFrame* recipeFrame = ui->recipeFrame;
    QPalette paperPalette = recipeFrame->palette();
    QColor paperColor = QColor(254, 245, 223);
    paperPalette.setColor(QPalette::Background, paperColor);
    recipeFrame->setAutoFillBackground(true);
    recipeFrame->setPalette(paperPalette);
    recipeFrame->update();

    // Set background color of the trivia area.
    QFrame* triviaFrame = ui->triviaFrame;
    triviaFrame->setAutoFillBackground(true);
    triviaFrame->setPalette(paperPalette);
    triviaFrame->update();

    // Set background and text color of tips area.
    QFrame* tipsFrame = ui->tipsFrame;
    QPalette tipsPalette = tipsFrame->palette();
    tipsPalette.setColor(QPalette::Background, QColor(Qt::black));
    tipsPalette.setColor(QPalette::WindowText, QColor(Qt::yellow));
    tipsFrame->setAutoFillBackground(true);
    tipsFrame->setPalette(tipsPalette);
    tipsFrame->update();

    // Controller set up.
    controller = controllerPtr;

    // to controller
    QObject::connect(this, &MainWindow::start,
                     controller, &Controller::startGame);
    // from controller
    QObject::connect(controller, &Controller::sendDrink,
                     this, &MainWindow::receiveDrink);
    QObject::connect(controller, &Controller::sendTime,
                     this, &MainWindow::receiveTime);
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

void MainWindow::receiveDrink(Drink* drink)
{
    //this is for testing and should be removed
    qDebug() << drink->Name;
}

void MainWindow::receiveTime(int currentTime)
{
    //this is for testing and should be removed
    qDebug() << currentTime;
}

// need to emit the startGame signal;
