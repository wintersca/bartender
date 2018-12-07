#ifndef RECORDBOARD_H
#define RECORDBOARD_H

#include <QDialog>
#include "controller.h"

namespace Ui {
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
