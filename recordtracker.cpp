#include "recordtracker.h"
#include <iostream>

QMap<QString, double> RecordTracker::parseGameRecord()
{
    QMap<QString, double> result;

    QXmlStreamReader reader;
    QFile file("../a8-an-educational-app-f18-kathrynriding-1/database/HistoricalGameData.xml");
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        throw -1;
    }
    else
    {
        reader.setDevice(&file);
        while(reader.readNextStartElement())
        {
            result[reader.name().toString()] = reader.attributes().value(reader.name().toString()).toDouble();
        }
        file.close();
    }

    return result;
}

void RecordTracker::writeGameRecord(QMap<QString, double> toWrite)
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
        writer.writeStartElement("Historical");
        for(QString currentKey: toWrite.keys())
        {
            writer.writeStartElement(currentKey);
            writer.writeAttribute(currentKey, QString::number(toWrite.value(currentKey)));
            writer.writeEndElement();
        }
        writer.writeEndElement();
        writer.writeEndDocument();
        file.close();
    }

}
