#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHBoxLayout>
#include <QTime>
#include "customdrinkimporter.h"
#include "gamearea.h"
#include <random>
#include "customizemenu.h"

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

    // Set default difficulty
    currentDifficulty = Difficulty::medium;
    ui->menuDifficulty->actions().at(0)->setEnabled(true);
    ui->menuDifficulty->actions().at(1)->setEnabled(false);
    ui->menuDifficulty->actions().at(2)->setEnabled(true);

    // Build array of labels for displaying ingredients.
    ingredientAmountLabels = QVector<QLabel*>(10);
    ingredientAmountLabels[0] = ui->ingredientAmount1;
    ingredientAmountLabels[1] = ui->ingredientAmount2;
    ingredientAmountLabels[2] = ui->ingredientAmount3;
    ingredientAmountLabels[3] = ui->ingredientAmount4;
    ingredientAmountLabels[4] = ui->ingredientAmount5;
    ingredientAmountLabels[5] = ui->ingredientAmount6;
    ingredientAmountLabels[6] = ui->ingredientAmount7;
    ingredientAmountLabels[7] = ui->ingredientAmount8;
    ingredientAmountLabels[8] = ui->ingredientAmount9;
    ingredientAmountLabels[9] = ui->ingredientAmount10;

    ingredientNameLabels = QVector<QLabel*>(10);
    ingredientNameLabels[0] = ui->ingredientName1;
    ingredientNameLabels[1] = ui->ingredientName2;
    ingredientNameLabels[2] = ui->ingredientName3;
    ingredientNameLabels[3] = ui->ingredientName4;
    ingredientNameLabels[4] = ui->ingredientName5;
    ingredientNameLabels[5] = ui->ingredientName6;
    ingredientNameLabels[6] = ui->ingredientName7;
    ingredientNameLabels[7] = ui->ingredientName8;
    ingredientNameLabels[8] = ui->ingredientName9;
    ingredientNameLabels[9] = ui->ingredientName10;

    ingredientUnitLabels = QVector<QLabel*>(10);
    ingredientUnitLabels[0] = ui->ingredientUnit1;
    ingredientUnitLabels[1] = ui->ingredientUnit2;
    ingredientUnitLabels[2] = ui->ingredientUnit3;
    ingredientUnitLabels[3] = ui->ingredientUnit4;
    ingredientUnitLabels[4] = ui->ingredientUnit5;
    ingredientUnitLabels[5] = ui->ingredientUnit6;
    ingredientUnitLabels[6] = ui->ingredientUnit7;
    ingredientUnitLabels[7] = ui->ingredientUnit8;
    ingredientUnitLabels[8] = ui->ingredientUnit9;
    ingredientUnitLabels[9] = ui->ingredientUnit10;

    // Clear the ingredients text.
    ui->drinkName->setText("");
    ui->triviaLabel->setText("");
    for (int i = 0; i < 10; i++)
    {
        ingredientAmountLabels[i]->setText("");
        ingredientNameLabels[i]->setText("");
        ingredientUnitLabels[i]->setText("");
    }

    // Set up the amounts to pour box.
    ui->amountToAdd->setMinimum(0.25);
    ui->amountToAdd->setSingleStep(0.25);
    ui->amountToAdd->setValue(1.0);

    // Controller set up.
    controller = controllerPtr;

    // to controller
    QObject::connect(this, &MainWindow::start,
                     controller, &Controller::startGame);
    QObject::connect(this, &MainWindow::requestMenu,
                      controller, &Controller::menuRequestedByMainWindow);
    QObject::connect(this, &MainWindow::sendAmountToAdd,
                      controller, &Controller::receiveAmountToAdd);

    // from controller
    QObject::connect(controller, &Controller::sendDrink,
                     this, &MainWindow::receiveDrink);
    QObject::connect(controller, &Controller::sendTime,
                     this, &MainWindow::receiveTime);
    QObject::connect(controller, &Controller::menuToMainWindow,
                     this, &MainWindow::receiveMenu);
    QObject::connect(controller, &Controller::tipAmountToGame,
                     this, &MainWindow::receiveTips);
    QObject::connect(controller, &Controller::requestAmountToAdd,
                     this, &MainWindow::requestAmountToAdd);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::receiveDrink(Drink* drink)
{
    ui->drinkName->setText(drink->Name);

    // Clear the old ingredients.
    for (int i = 0; i < 10; i++)
    {
        ingredientAmountLabels[i]->setText("");
        ingredientNameLabels[i]->setText("");
        ingredientUnitLabels[i]->setText("");
    }

    // Display all the ingredients.
    int ingredientIndex = 0;
    QMapIterator<Ingredients::Ingredients, double> i(drink->IngredientsMap);
    while (i.hasNext())
    {
        i.next();
        // Display amount
        ingredientAmountLabels[ingredientIndex]->setText(QString::number(i.value()));

        // Display name.
        QString ingredientName = Ingredients::ingredientData[i.key()].displayString;
        ingredientNameLabels[ingredientIndex]->setText(ingredientName);

        // Display units.
        QString ingredientUnits = Ingredients::ingredientData[i.key()].unit;
        ingredientUnitLabels[ingredientIndex]->setText(ingredientUnits);

        ingredientIndex++;
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

    //TODO: display menu so user can edit
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

    //this is for testing and should be removed
    qDebug() << currentTime;
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

    // Testing
    //receiveTime(-30);
    //receiveTips(73, 47);
}
