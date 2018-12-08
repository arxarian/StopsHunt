#ifndef POSITIONMANAGER_H
#define POSITIONMANAGER_H

#include <QGeoPositionInfo>
#include <QGeoPositionInfoSource>
#include <QObject>
#include <QPointer>

class PositionManager : public QObject
{
    Q_OBJECT
public:
    explicit PositionManager(QObject *parent = nullptr);
    void Start();

signals:
    void PositionUpdated(QGeoPositionInfo oPositionInfo);

private slots:
    void OnUpdateTimeout();

private:
    QPointer<QGeoPositionInfoSource> m_pPositionSource;
};

#endif // POSITIONMANAGER_H
