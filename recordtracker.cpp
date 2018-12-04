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
        while(reader.isEndDocument())
        {
            QString name = reader.name().toString();
            double amount = reader.readElementText().toDouble();
            result[name] = amount;
            reader.skipCurrentElement();
        }
        file.close();
    }

    for(QString current: result.keys()){
       std::cout << current.toStdString() << std::endl;
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
        for(QString currentKey: toWrite.keys())
        {
            writer.writeTextElement(currentKey, QString::number(toWrite.value(currentKey)));
        }
        writer.writeEndDocument();
        file.close();
    }

}
