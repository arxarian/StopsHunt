#include <QGeoPositionInfoSource>
#include <QDebug>

#include "positionmanager.h"

constexpr qint32 PositionUpdateTime_ms = 1000;

PositionManager::PositionManager(QObject *parent) : QObject(parent)
{
    m_positionSource = QGeoPositionInfoSource::createDefaultSource(this);

    if (m_positionSource == nullptr)
    {
        qInfo("no position source available");
    }
    else
    {
        connect(m_positionSource, &QGeoPositionInfoSource::positionUpdated, this, &PositionManager::positionUpdated);
        connect(m_positionSource, &QGeoPositionInfoSource::updateTimeout, this, &PositionManager::onUpdateTimeout);
        m_positionSource->setUpdateInterval(PositionUpdateTime_ms);

        qInfo() << "position sources found:" << m_positionSource->availableSources();
    }
}

void PositionManager::start()
{
    if (m_positionSource)
    {
        m_positionSource->startUpdates();
    }
}

void PositionManager::onUpdateTimeout()
{
    qDebug() << "update failed";
}
