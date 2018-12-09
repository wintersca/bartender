#include <QMainWindow>
#include <QLabel>
#include <SFML/Audio.hpp>
#include <QHBoxLayout>
#include <QTime>
#include <random>
#include "controller.h"
#include "ui_mainwindow.h"
#include "customdrinkimporter.h"
#include "gamearea.h"
#include "customizemenu.h"
#include "helpmenu.h"
#include "recordboard.h"
#include "viewrecipes.h"

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/**
 * The main window is the main place to interact with the game.
 * It contains the gameplay area where drawing in SFML is handled.
 * It also handles creating all the pop up windows.
 * Most data about the current state of the game is displayed here.
 * Author: Alex Smith
 */

extern Controller *controller;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(Controller *controller, QWidget *parent = nullptr);
    ~MainWindow();

// Mapping difficulty settings to unsigned integers.
private:
    enum Difficulty : unsigned int
    {
        easy,
        medium,
        hard
    };

    // What difficulty is selected in the UI.
    unsigned int currentDifficulty;

    // The background music.
    sf::Music bgm;

private slots:
    /**
     * @brief receiveDrink: The UI receives a drink and displays it's name, steps, and one of its trivia.
     * @param drink: drink to receive
     */
    void receiveDrink(Drink* drink);

    /**
     * @brief receiveTime: The UI receives the time left to make a drink and displays it.
     * If negative it is displayed in red.
     * @param currentTime: current game time
     */
    void receiveTime(int currentTime);

    /**
     * @brief receiveMenu: The UI receives all the drinks and opens a widnow to modify the drinks on the menu.
     * @param menu: menu to receive
     */
    void receiveMenu(QVector<Drink*> menu);

    /**
     * @brief receiveMenuInfo: The UI receives all the drinks and opens a menu to display
     * information about how to make them.
     * @param menu: menu info to receive
     */
    void receiveMenuInfo(QVector<Drink*> menu);

    /**
     * @brief receiveTips: The UI receives the total tips the player has earned and displays them.
     * @param tipDollars
     * @param tipCents
     */
    void receiveTips(int tipDollars, int tipCents);

    /**
     * @brief receiveRecords: The UI receives stats about how well the player has played the game.
     * A window is opened to display them.
     * @param records
     */
    void receiveRecords(QMap<QString, int> records);

    /**
     * @brief requestAmountToAdd: The Controller requests how much of an ingredient is being added to a drink.
     */
    void requestAmountToAdd();

    /**
     * @brief enableServe: The button to serve a drink is enabled by the controller.
     */
    void enableServe();

    /**
     * @brief on_actionEdit_Available_Drinks_triggered: A button in the menu is pressed to modify what drinks are on the menu.
     * The menu is requested from the controller.
     */
    void on_actionEdit_Available_Drinks_triggered();

    /**
     * @brief on_actionCreat_Custom_Drink_triggered: A button is pressed to open the window to make a custom drink.
     */
    void on_actionCreat_Custom_Drink_triggered();

    /**
     * @brief on_actionEasy_triggered: Easy difficulty was selected. It is greyed out.
     */
    void on_actionEasy_triggered();

    /**
     * @brief on_actionMedium_triggered: Medium difficulty was selected. It is greyed out.
     */
    void on_actionMedium_triggered();

    /**
     * @brief on_actionHard_triggered: Hard difficulty was selected. It is greyed out.
     */
    void on_actionHard_triggered();

    /**
     * @brief on_actionStart_triggered: The user requested to start the game.
     * The controller is sent the current difficulty.
     */
    void on_actionStart_triggered();

    /**
     * @brief on_serveButton_clicked: The button to finish making a drink is clicked.
     * The controller then checks its correctness.
     */
    void on_serveButton_clicked();

    /**
     * @brief on_actionAbout_triggered: The user clicked to open a window to view information about how the game works.
     */
    void on_actionAbout_triggered();

    /**
     * @brief on_actionView_Record_Board_triggered: The user requested to view stats about how they have been playing the game.
     */
    void on_actionView_Record_Board_triggered();

    /**
     * @brief on_actionAll_Recipes_triggered: The user requested to view information about all the drinks in the database.
     */
    void on_actionAll_Recipes_triggered();

signals:
    /**
     * @brief start: Telling the controller the game is starting and sending the difficulty.
     * @param difficulty: starting difficulty
     */
    void start(unsigned int difficulty);

    /**
     * @brief requestMenu: Requesting all information about drinks, to allow modifying what can be ordered.
     */
    void requestMenu();

    /**
     * @brief requestMenuInfo: Requesting all information about drinks, to allow you user to view this information easily.
     */
    void requestMenuInfo();

    /**
     * @brief requestRecords: Request stats about how the user is playing the game, so this can be view by the user.
     */
    void requestRecords();

    /**
     * @brief sendAmountToAdd: Telling the controller how much of an ingredient was added to a drink.
     * @param amount to add
     */
    void sendAmountToAdd(double amount);

    /**
     * @brief drinkServed: Telling the controller that the user is done making a drink.
     */
    void drinkServed();

private:
    Ui::MainWindow *ui;
    // All the labels that are used to display the steps of making a drink.
    QVector<QLabel*> stepsInDrink;
};

#endif // MAINWINDOW_H
