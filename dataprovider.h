
#pragma once

#include <QPointer>

#include "stopitem.h"

class DataProvider
{
public:
    DataProvider() = default;

    static QList<QPointer<StopItem>> loadModel(QObject* parent = nullptr);

private:
    static void setStopItemFromCSVLine(QPointer<StopItem> stopItem, const QByteArray &csvLine);
};
