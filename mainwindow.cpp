#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHBoxLayout>
#include <QTime>
#include "customdrinkimporter.h"
#include "gamearea.h"
#include <random>
#include "customizemenu.h"
#include <SFML/Audio.hpp>
#include "helpmenu.h"
#include "recordboard.h"
#include "viewrecipes.h"


Controller *controller;
MainWindow::MainWindow(Controller *controllerPtr, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->ui->setupUi(this);
    // Controller set up.
    controller = controllerPtr;

    GameArea* SFMLView = new GameArea(this, QPoint(20, 20), QSize(1000, 1000), controller);
    //ui->verticalLayout->addWidget(SFMLView);
    ui->widgetLayout->addWidget(SFMLView);

    QPixmap recipeAndTips(":/iconImages/images/corkBoard.png");
    recipeAndTips = recipeAndTips.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, recipeAndTips);
    this->setPalette(palette);

    //setup music
    bgm.openFromFile("../a8-an-educational-app-f18-kathrynriding-1/audio/mixologist_BGM.wav");
    bgm.setLoop(true);
    bgm.play();


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

    // Set default difficulty
    currentDifficulty = Difficulty::medium;
    ui->menuDifficulty->actions().at(0)->setEnabled(true);
    ui->menuDifficulty->actions().at(1)->setEnabled(false);
    ui->menuDifficulty->actions().at(2)->setEnabled(true);

    // Labels for displaying the steps of a drink.
    stepsInDrink = QVector<QLabel*>(10);
    stepsInDrink[0] = ui->step1;
    stepsInDrink[1] = ui->step2;
    stepsInDrink[2] = ui->step3;
    stepsInDrink[3] = ui->step4;
    stepsInDrink[4] = ui->step5;
    stepsInDrink[5] = ui->step6;
    stepsInDrink[6] = ui->step7;
    stepsInDrink[7] = ui->step8;
    stepsInDrink[8] = ui->step9;
    stepsInDrink[9] = ui->step10;

    // Clear the ingredients text.
    ui->drinkName->setText("");
    ui->triviaLabel->setText("");
    for (int i = 0; i < 10; i++)
    {
        stepsInDrink[i]->setText("");
    }

    // Set up the amounts to pour box.
    ui->amountToAdd->setMinimum(0.25);
    ui->amountToAdd->setSingleStep(0.25);
    ui->amountToAdd->setValue(1.0);

    // Disable the serve drink button
    ui->serveButton->setEnabled(false);

    // Set background color of the menu bar.
    ui->menuBar->setAutoFillBackground(true);
    ui->menuBar->setPalette(paperPalette);
    ui->menuBar->update();


    // to controller
    QObject::connect(this, &MainWindow::start,
                     controller, &Controller::startGame);
    QObject::connect(this, &MainWindow::requestMenu,
                      controller, &Controller::menuRequestedByMainWindow);
    QObject::connect(this, &MainWindow::requestMenuInfo,
                      controller, &Controller::menuInfoRequestedByMainWindow);
    QObject::connect(this, &MainWindow::sendAmountToAdd,
                      controller, &Controller::receiveAmountToAdd);
    QObject::connect(this, &MainWindow::drinkServed,
                      controller, &Controller::drinkServed);
    QObject::connect(this, &MainWindow::requestRecords,
                      controller, &Controller::recordsRequestedByMainWindow);

    // from controller
    QObject::connect(controller, &Controller::sendDrink,
                     this, &MainWindow::receiveDrink);
    QObject::connect(controller, &Controller::sendTime,
                     this, &MainWindow::receiveTime);
    QObject::connect(controller, &Controller::menuToMainWindow,
                     this, &MainWindow::receiveMenu);
    QObject::connect(controller, &Controller::menuInfoToMainWindow,
                     this, &MainWindow::receiveMenuInfo);
    QObject::connect(controller, &Controller::tipAmountToGame,
                     this, &MainWindow::receiveTips);
    QObject::connect(controller, &Controller::requestAmountToAdd,
                     this, &MainWindow::requestAmountToAdd);
    QObject::connect(controller, &Controller::enableServe,
                     this, &MainWindow::enableServe);
    QObject::connect(controller, &Controller::recordsToMainWindow,
                     this, &MainWindow::receiveRecords);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::receiveDrink(Drink* drink)
{
    ui->drinkName->setText(drink->Name);
    // Clear the steps
    for (int i = 0; i < 10; i++)
    {
        stepsInDrink[i]->setText("");
    }
    // Display all the ingredients.
    // Check that the difficulty isn't set to hard.
    if (currentDifficulty != Difficulty::hard)
    {
        int ingredientIndex = 0;
        //QMapIterator<Ingredients::Ingredients, double> i(drink->Steps->);

        QVector<Step> steps = drink->getSteps();

        for (int i = 0; i < steps.length(); i++)
        {
            stepsInDrink[i]->setText(steps[i].getInstruction());
        }
    }


    // Display the trivia.
    // Pick a random trivia string.
    int totalTriva = drink->Trivia.length();
    unsigned long randomSeed = static_cast<unsigned long>(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> distribution(0, totalTriva - 1);
    std::default_random_engine randomEngine;
    randomEngine.seed(randomSeed);
    int randomIndex = distribution(randomEngine);
    //randomIndex--;
    QString triviaString = drink->Trivia[randomIndex];
    // Create a string that has new lines to display the trivia on multiple lines.
    QStringList wordsInTrivia = triviaString.split(" ", QString::SkipEmptyParts);
    int wordsOnLine = 0;
    QString displayString = "";
    for (int i = 0; i < wordsInTrivia.length(); i++)
    {
        int lettersInWord = wordsInTrivia[i].length();
        if (wordsOnLine + lettersInWord <= 28)
        {
            // Just add a word.
            displayString.append(wordsInTrivia[i]);
            displayString.append(" ");
            wordsOnLine += lettersInWord + 1;
        }
        else
        {
            // Need a new line.
            displayString.append("\n");
            displayString.append(wordsInTrivia[i]);
            displayString.append(" ");
            wordsOnLine = lettersInWord + 1;
        }
    }

    // Show trivia.
    ui->triviaLabel->setText(displayString);
}

void MainWindow::receiveMenu(QVector<Drink*> menu)
{
    CustomizeMenu* window = new CustomizeMenu(controller, menu, this);
    window->setModal(true);
    window->show();
    window->raise();
    window->activateWindow();
}

void MainWindow::receiveTime(int currentTime)
{
    // Deal with negative time left.
    QFrame* timerFrame = ui->timerFrame;
    QPalette timerPalette = timerFrame->palette();
    if (currentTime < 0)
    {
        timerPalette.setColor(QPalette::WindowText, QColor(Qt::red));
        currentTime *= -1;
    }
    else
    {
        timerPalette.setColor(QPalette::WindowText, QColor(Qt::black));
    }
    timerFrame->setPalette(timerPalette);
    timerFrame->update();

    // Format the string.
    QTime time(0, 0, currentTime);
    QString timeString = time.toString("m:ss");
    ui->timeLeft->setText(timeString);
}

void MainWindow::receiveTips(int tipDollars, int tipCents)
{
    // Buld string.
    QString tipsString = "$";
    tipsString.append(QString::number(tipDollars));
    tipsString.append(".");
    tipsString.append(QString::number(tipCents));

    ui->tipsAmount->setText(tipsString);
}

void MainWindow::requestAmountToAdd()
{
    emit sendAmountToAdd(ui->amountToAdd->value());
}

void MainWindow::on_actionEdit_Available_Drinks_triggered()
{
    emit requestMenu(); // added so you can see the current menu
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
    ui->serveButton->setEnabled(true);
}

void MainWindow::on_serveButton_clicked()
{
    ui->serveButton->setEnabled(false);
    emit drinkServed();
}

void MainWindow::enableServe()
{
    ui->serveButton->setEnabled(true);
}

void MainWindow::on_actionAbout_triggered()
{
    HelpMenu* window = new HelpMenu();
    window->setModal(true);
    window->show();
    window->raise();
    window->activateWindow();
}

void MainWindow::on_actionView_Record_Board_triggered()
{
    emit requestRecords();
}

void MainWindow::receiveRecords(QMap<QString, int> records)
{
    RecordBoard* window = new RecordBoard(controller, records, this);
    window->setModal(true);
    window->show();
    window->raise();
    window->activateWindow();
}


void MainWindow::on_actionAll_Recipes_triggered()
{
    emit requestMenuInfo();
}

void MainWindow::receiveMenuInfo(QVector<Drink*> menu)
{
    ViewRecipes* window = new ViewRecipes(menu, this);
    window->setModal(true);
    window->show();
    window->raise();
    window->activateWindow();
}
