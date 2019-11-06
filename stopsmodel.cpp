
#include "stopsmodel.h"
#include "dataprovider.h"

const QHash<qint32, QByteArray> RoleNames = {{StopsModel::Roles::ObjectRole, "object"},
                                             {StopsModel::Roles::NameRole, "name"},
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

    connect(this, &QAbstractListModel::dataChanged, this, [this] (const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles){
        Q_UNUSED(bottomRight)
        if (roles.first() == StopsModel::TakenRole)
        {
            const QString name = data(topLeft, StopsModel::NameRole).toString();
            m_stopsPersistentData->setValue(QString("stops/%1").arg(name), true);
            ++m_taken;

            emit progressChanged(progress());
        }
    });
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
    else if (role == Roles::NameRole)
    {
        return stopItem->name();
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

bool StopsModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid() || index.row() >= rowCount())
    {
        return false;
    }

    QPointer<StopItem> stopItem = m_stopsModel[index.row()];
    if (role == Roles::TakenRole)
    {
        stopItem.data()->setTaken(value.toBool());
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }

    return false;
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

QHash<int, QByteArray> StopsModel::roleNames() const
{
    return RoleNames;
}

qreal StopsModel::progress()
{
    return static_cast<qreal>(m_taken) / m_stopsModel.count();
}
