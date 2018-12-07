#include "recordboard.h"
#include "ui_recordboard.h"

RecordBoard::RecordBoard (Controller* controller, QMap<QString, int> records, QWidget *parent ) :
    QDialog(parent),
    ui(new Ui::RecordBoard)
{
    ui->setupUi(this);
}

RecordBoard::~RecordBoard()
{
    delete ui;
}
