#include "recordtracker.h"

QMap<QString, int> RecordTracker::parseGameRecord()
{
    QMap<QString, int> result;
    QXmlStreamReader reader;

    QFile file("../a8-an-educational-app-f18-kathrynriding-1/database/HistoricalGameData.xml");
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        return result;
    }
    else
    {
        reader.setDevice(&file);
        while(reader.isEndDocument())
        {
            QString name = reader.name().toString();
            double amount = reader.readElementText().toDouble();
            result[name] = amount;
            reader.skipCurrentElement();
        }
        file.close();
    }

    return result;
}

void RecordTracker::writeGameRecord(QMap<QString, int> toWrite)
{
    QXmlStreamWriter writer;

    QFile file("../a8-an-educational-app-f18-kathrynriding-1/database/HistoricalGameData.xml");
    if(!file.open(QFile::WriteOnly | QFile::Text))
    {
        throw -1;
    }
    else
    {
        writer.setDevice(&file);
        writer.setAutoFormatting(true);

        writer.writeStartDocument();
        for(QString currentKey: toWrite.keys())
        {
            writer.writeTextElement(currentKey, QString::number(toWrite.value(currentKey)));
        }
        writer.writeEndDocument();
        file.close();
    }

}
