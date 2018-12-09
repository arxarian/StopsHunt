#ifndef STOPSMODEL_H
#define STOPSMODEL_H

#include <QAbstractListModel>
#include <QGeoCoordinate>
#include <QGeoPositionInfo>
#include <QPointer>
#include <QSettings>

class Stop
{
public:
    Stop(const QString &strName, const QGeoCoordinate &oCoordinate);

    QString name() const;
    QGeoCoordinate coordinate() const;
    qint32 distance() const;
    bool taken() const;

    void setDistance(const qint32 nDistance);
    void setTaken(const bool bTaken);

private:
    QString m_strName;
    QGeoCoordinate m_oCoordinate;
    qint32 m_nDistance = 0;
    bool m_bTaken = false;

};

class StopsModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(qreal progress READ progress NOTIFY progressChanged)

public:
    enum StopsRoles
    {
        NameRole = Qt::UserRole + 1,
        CoordinateRole,
        DistanceRole,
        TakenRole
    };

    explicit StopsModel(QObject *parent = nullptr);

    void add(const Stop &oStop);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;

    void updatePosition(QGeoPositionInfo oPositionInfo);

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    qreal progress();
    qint32 m_nTaken = 0;

    QPointer<QSettings> m_pStopsData;
    QList<Stop> m_arrStops;

signals:
    void progressChanged();
};

#endif // STOPSMODEL_H
