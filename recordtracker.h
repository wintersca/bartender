#include <QMap>
#include <QString>
#include <QFile>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

#ifndef RECORDTRACKER_H
#define RECORDTRACKER_H


class RecordTracker
{
private:
    RecordTracker();
public:
    static QMap<QString, double> parseGameRecord();
    static void writeGameRecord(QMap<QString, double>);
};

#endif // RECORDTRACKER_H
