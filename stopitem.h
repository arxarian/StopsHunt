
#pragma once

#include <QGeoCoordinate>
#include <QObject>

class StopItem : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QGeoCoordinate coordinate READ coordinate WRITE setCoordinate NOTIFY coordinateChanged)
    Q_PROPERTY(qint32 distance READ distance WRITE setDistance NOTIFY distanceChanged)
    Q_PROPERTY(bool taken READ taken WRITE setTaken NOTIFY takenChanged)

public:
    explicit StopItem(QObject *parent = nullptr);

    QString name() const;
    QGeoCoordinate coordinate() const;
    qint32 distance() const;
    bool taken() const;

public slots:
    void setName(QString name);
    void setCoordinate(QGeoCoordinate coordinate);
    void setDistance(qint32 distance);
    void setTaken(bool taken);

signals:
    void nameChanged(QString name);
    void coordinateChanged(QGeoCoordinate coordinate);
    void distanceChanged(qint32 distance);
    void takenChanged(bool taken);

private:
    QString m_name;
    QGeoCoordinate m_coordinate;
    qint32 m_distance = -1;
    bool m_taken = false;
};
