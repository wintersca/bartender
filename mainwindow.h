#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include "controller.h"
#include <SFML/Audio.hpp>

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

private:
    enum Difficulty : unsigned int
    {
        easy,
        medium,
        hard
    };
    unsigned int currentDifficulty;
    sf::Music bgm;

private slots:
    void receiveDrink(Drink* drink);
    void receiveTime(int currentTime);
    void receiveMenu(QVector<Drink*> menu);
    void receiveMenuInfo(QVector<Drink*> menu);
    void receiveTips(int tipDollars, int tipCents);
    void receiveRecords(QMap<QString, int> records);
    void requestAmountToAdd();
    void enableServe();

    void on_actionEdit_Available_Drinks_triggered();
    void on_actionCreat_Custom_Drink_triggered();

    void on_actionEasy_triggered();
    void on_actionMedium_triggered();
    void on_actionHard_triggered();
    void on_actionStart_triggered();

    void on_serveButton_clicked();

    void on_actionAbout_triggered();

    void on_actionView_Record_Board_triggered();

    void on_actionAll_Recipes_triggered();

signals:
    void start(unsigned int difficulty); //TODO put an enum as the parameter
    void requestMenu();
    void requestMenuInfo();
    void requestRecords();
    void sendAmountToAdd(double amount);
    void drinkServed();


private:
    Ui::MainWindow *ui;
    //QVector<QLabel*> ingredientAmountLabels;
    //QVector<QLabel*> ingredientNameLabels;
    //QVector<QLabel*> ingredientUnitLabels;
    QVector<QLabel*> stepsInDrink;
};

#endif // MAINWINDOW_H
