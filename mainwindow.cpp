#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHBoxLayout>
#include <QTime>
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

    // Set style of timer area.
    QFrame* timerFrame = ui->timerFrame;
    QPalette timerPalette = timerFrame->palette();
    timerPalette.setColor(QPalette::Background, QColor(Qt::gray));
    timerFrame->setAutoFillBackground(true);
    timerFrame->setPalette(timerPalette);
    timerFrame->update();

    // Set defaul difficulty
    currentDifficulty = Difficulty::medium;
    ui->menuDifficulty->actions().at(0)->setEnabled(true);
    ui->menuDifficulty->actions().at(1)->setEnabled(false);
    ui->menuDifficulty->actions().at(2)->setEnabled(true);

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

void MainWindow::receiveDrink(Drink* drink)
{
    //this is for testing and should be removed
    qDebug() << drink->Name;
}

void MainWindow::receiveTime(int currentTime)
{
    QTime time(0, 0, currentTime);
    QString timeString = time.toString("m:ss");
    ui->timeLeft->setText(timeString);

    //this is for testing and should be removed
    qDebug() << currentTime;
}

void MainWindow::on_actionEdit_Available_Drinks_triggered()
{

}

void MainWindow::on_actionCreat_Custom_Drink_triggered()
{
    CustomDrinkImporter* window = new CustomDrinkImporter(controller, this);
    window->setModal(true);
    window->show();
    window->raise();
    window->activateWindow();
}

/******* Edit difficulty *****************/

void MainWindow::on_actionEasy_triggered()
{
    currentDifficulty = Difficulty::easy;
    ui->menuDifficulty->actions().at(0)->setEnabled(false);
    ui->menuDifficulty->actions().at(1)->setEnabled(true);
    ui->menuDifficulty->actions().at(2)->setEnabled(true);
}

void MainWindow::on_actionMedium_triggered()
{
    currentDifficulty = Difficulty::medium;
    ui->menuDifficulty->actions().at(0)->setEnabled(true);
    ui->menuDifficulty->actions().at(1)->setEnabled(false);
    ui->menuDifficulty->actions().at(2)->setEnabled(true);
}

void MainWindow::on_actionHard_triggered()
{
    currentDifficulty = Difficulty::hard;
    ui->menuDifficulty->actions().at(0)->setEnabled(true);
    ui->menuDifficulty->actions().at(1)->setEnabled(true);
    ui->menuDifficulty->actions().at(2)->setEnabled(false);
}

void MainWindow::on_actionStart_triggered()
{
    emit start(currentDifficulty);

    // Testing
    //receiveTime(30);
}
