#include "stopitem.h"

StopItem::StopItem(QObject *parent) : QObject(parent) {}

QString StopItem::name() const
{
    return m_name;
}

QGeoCoordinate StopItem::coordinate() const
{
    return m_coordinate;
}

qint32 StopItem::distance() const
{
    return m_distance;
}

bool StopItem::taken() const
{
    return m_taken;
}

void StopItem::setName(QString name)
{
    if (m_name == name)
        return;

    m_name = name;
    emit nameChanged(m_name);
}

void StopItem::setCoordinate(QGeoCoordinate coordinate)
{
    if (m_coordinate == coordinate)
        return;

    m_coordinate = coordinate;
    emit coordinateChanged(m_coordinate);
}

void StopItem::setDistance(qint32 distance)
{
    if (m_distance == distance)
        return;

    m_distance = distance;
    emit distanceChanged(m_distance);
}

void StopItem::setTaken(bool taken)
{
    if (m_taken == taken)
        return;

    m_taken = taken;
    emit takenChanged(m_taken);
}
