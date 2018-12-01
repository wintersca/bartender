#include <QMap>
#include <QString>

#ifndef RECORDTRACKER_H
#define RECORDTRACKER_H


class RecordTracker
{
private:
    RecordTracker();
public:
    QMap<QString, double> parseGameRecord();
    void writeGameRecord(QMap<QString, double>);
};

#endif // RECORDTRACKER_H
