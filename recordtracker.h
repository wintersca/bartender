#include <QMap>
#include <QString>
#include <QFile>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

#ifndef RECORDTRACKER_H
#define RECORDTRACKER_H

/**
 * @brief The RecordTracker class
 */
class RecordTracker
{
    private:
        /**
         * @brief RecordTracker
         */
        RecordTracker();

    public:
        /**
         * @brief parseGameRecord
         * @return
         */
        static QMap<QString, int> parseGameRecord();

        /**
         * @brief writeGameRecord
         */
        static void writeGameRecord(QMap<QString, int>);
};

#endif // RECORDTRACKER_H
