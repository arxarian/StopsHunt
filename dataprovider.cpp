#include "dataprovider.h"

#include <QFile>
#include <QTextCodec>
#include <QSettings>
#include <QtDebug>

QList<QPointer<StopItem>> DataProvider::loadModel(QObject *parent)
{
    QFile inFile(":/stops.csv");
    if (!inFile.open(QIODevice::ReadOnly))
    {
        qInfo() << inFile.errorString();
    }

    QList<QPointer<StopItem>> result;

    while (inFile.isOpen() && !inFile.atEnd())
    {
        auto stopItem = QPointer<StopItem>(new StopItem(parent));
        setStopItemFromCSVLine(stopItem, inFile.readLine());
        result.append(stopItem);
    }

    return result;
}

void DataProvider::setStopItemFromCSVLine(QPointer<StopItem> stopItem, const QByteArray& csvLine)
{
    QList<QByteArray> splittedLine = csvLine.split(',');
    if (splittedLine.count() < 3)
    {
        qInfo() << "incorrect data format" << splittedLine;
    }

    const QString name { QTextCodec::codecForMib(106)->toUnicode(splittedLine[0]) };
    const QGeoCoordinate coordinate { splittedLine.at(1).toDouble(), splittedLine.at(2).toDouble() };

    stopItem->setName(name);
    stopItem->setCoordinate(coordinate);
}
