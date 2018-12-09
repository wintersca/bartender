#include <QDialog>
#include "controller.h"

#ifndef RECORDBOARD_H
#define RECORDBOARD_H

/**
 * RecordBoard compiles and shows historical records of gameplay.
 * Authors: Tristan Bowler & Kathryn Riding
 */
namespace Ui
{
    class RecordBoard;
}

class RecordBoard : public QDialog
{
    Q_OBJECT

public:
    explicit RecordBoard(Controller* controller, QMap<QString, int> records, QWidget *parent = nullptr);
    ~RecordBoard();


private:
    Ui::RecordBoard *ui;
};

#endif // RECORDBOARD_H
