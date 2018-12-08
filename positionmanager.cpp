#include <QGeoPositionInfoSource>
#include <QDebug>

#include "positionmanager.h"

PositionManager::PositionManager(QObject *parent) : QObject(parent)
{
    m_pPositionSource = QGeoPositionInfoSource::createDefaultSource(this);

    if (m_pPositionSource == nullptr)
    {
        qInfo("failed source");
    }
    else
    {
        connect(m_pPositionSource, &QGeoPositionInfoSource::positionUpdated, this, &PositionManager::PositionUpdated);
        connect(m_pPositionSource, &QGeoPositionInfoSource::updateTimeout, this, &PositionManager::OnUpdateTimeout);
        m_pPositionSource->setUpdateInterval(1000);

        qInfo() << "sources found:" << m_pPositionSource->availableSources();
    }
}

void PositionManager::Start()
{
    if (m_pPositionSource)
    {
        m_pPositionSource->startUpdates();
    }
}

void PositionManager::OnUpdateTimeout()
{
    qDebug() << "update failed";
}
