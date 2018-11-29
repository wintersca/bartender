#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "controller.h"

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

private slots:
    void on_addCustomDrink_clicked();
    void receiveDrink(Drink* drink);
    void receiveTime(int currentTime);

signals:
    void start(); //TODO put an enum as the parameter



private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
