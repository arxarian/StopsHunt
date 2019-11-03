
#pragma once

#include <QGeoPositionInfo>
#include <QGeoPositionInfoSource>
#include <QObject>
#include <QPointer>

class PositionManager : public QObject
{
    Q_OBJECT
public:
    explicit PositionManager(QObject *parent = nullptr);

    void start();

signals:
    void positionUpdated(QGeoPositionInfo positionInfo);

private slots:
    void onUpdateTimeout();

private:
    QPointer<QGeoPositionInfoSource> m_positionSource;
};
