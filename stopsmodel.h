
#pragma once

#include <QAbstractListModel>
#include <QGeoCoordinate>
#include <QGeoPositionInfo>
#include <QPointer>
#include <QSettings>

#include "stopitem.h"

class StopsModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(qreal progress READ progress NOTIFY progressChanged)

public:
    enum Roles
    {
        ObjectRole = Qt::UserRole,
        NameRole,
        DistanceRole,
        TakenRole
    };

    explicit StopsModel(QObject *parent = nullptr);
    ~StopsModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;

    qreal progress();
    void updatePosition(const QGeoPositionInfo &oPositionInfo);

signals:
    void progressChanged(qreal progress);

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    qint32 m_taken = 0;

    QPointer<QSettings> m_stopsPersistentData;
    QList<QPointer<StopItem>> m_stopsModel;
    qreal m_progress;
};
