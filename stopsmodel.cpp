
#include "stopsmodel.h"
#include "dataprovider.h"

const QHash<qint32, QByteArray> RoleNames = {{StopsModel::Roles::ObjectRole, "object"},
                                             {StopsModel::Roles::DistanceRole, "distance"},
                                             {StopsModel::Roles::TakenRole, "taken"}};

StopsModel::StopsModel(QObject *parent) : QAbstractListModel(parent)
{

    beginResetModel();
    m_stopsModel.clear();
    m_stopsModel = DataProvider::loadModel();

    m_stopsPersistentData = new QSettings(this);

    for (StopItem* stopItem : m_stopsModel)
    {
        const bool taken = m_stopsPersistentData->value(QString("stops/%1").arg(stopItem->name()), false).toBool();
        stopItem->setTaken(taken);
        if (taken) ++m_taken;
    }

    endResetModel();
}

StopsModel::~StopsModel() {}

int StopsModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return m_stopsModel.count();
}

QVariant StopsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= rowCount())
    {
        return QVariant();
    }

    QPointer<StopItem> stopItem = m_stopsModel.at(index.row());
    if (role == Roles::ObjectRole)
    {
        return QVariant::fromValue(stopItem.data());
    }
    else if (role == Roles::DistanceRole)
    {
        return stopItem->distance();
    }
    else if (role == Roles::TakenRole)
    {
        return stopItem->taken();
    }

    return QVariant();
}

void StopsModel::updatePosition(const QGeoPositionInfo& positionInfo)
{
    const QGeoCoordinate& currentCoordinate = positionInfo.coordinate();

    for (qint32 i = 0; i < m_stopsModel.count(); ++i)
    {
        const QGeoCoordinate& stopCoordinate = m_stopsModel.at(i)->coordinate();
        const qint32 distance_m = static_cast<qint32>(currentCoordinate.distanceTo(stopCoordinate));

        m_stopsModel[i]->setDistance(distance_m);
    }
}

void StopsModel::setTaken(const QString &name)
{
     m_stopsPersistentData->setValue(QString("stops/%1").arg(name), true);
}

QHash<int, QByteArray> StopsModel::roleNames() const
{
    return RoleNames;
}

qreal StopsModel::progress()
{
    return static_cast<qreal>(m_taken) / m_stopsModel.count();
}
