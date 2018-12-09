#include <QMap>
#include <QString>
#include <QFile>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

#ifndef RECORDTRACKER_H
#define RECORDTRACKER_H

/**
 * @brief The RecordTracker class records game play data for future game use.
 * Author: Kathryn Riding
 */
class RecordTracker
{
    private:
        RecordTracker();

    public:
        /**
         * @brief parseGameRecord: parses current game record if there is one.
         * @return
         */
        static QMap<QString, int> parseGameRecord();

        /**
         * @brief writeGameRecord: writes in new game record as a game is played.
         */
        static void writeGameRecord(QMap<QString, int>);
};

#endif // RECORDTRACKER_H
