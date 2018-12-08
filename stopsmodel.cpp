#include "stopsmodel.h"

StopsModel::StopsModel(QObject *parent) : QAbstractListModel(parent)
{
    //
}

void StopsModel::add(const Stop &oStop)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_arrStops << oStop;
    endInsertRows();
}

int StopsModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_arrStops.count();
}

QVariant StopsModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_arrStops.count())
    {
        return QVariant();
    }

    const Stop &oStop = m_arrStops[index.row()];
    if (role == NameRole)
    {
        return oStop.name();
    }
    else if (role == CoordinateRole)
    {
        return QVariant::fromValue(oStop.coordinate());
    }
    else if (role == DistanceRole)
    {
        return oStop.distance();
    }
    else if (role == TakenRole)
    {
        return oStop.taken();
    }

    return QVariant();
}

bool StopsModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.row() < 0 || index.row() > m_arrStops.size() - 1)
    {
        return false;
    }

    if (role == DistanceRole || role == TakenRole)
    {
        Stop &oStop = m_arrStops[index.row()];

        if (role == DistanceRole)
        {
            oStop.setDistance(value.toInt());
        }
        else if (role == TakenRole)
        {
            oStop.setTaken(value.toBool());
        }

        emit dataChanged(index, index, QVector<int>() << role);

        return true;
    }

    return false;
}

QHash<int, QByteArray> StopsModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[CoordinateRole] = "coordinate";
    roles[DistanceRole] = "distance";
    roles[TakenRole] = "taken";
    return roles;
}

Stop::Stop(const QString &strName, const QGeoCoordinate &oCoordinate)
    : m_strName(strName), m_oCoordinate(oCoordinate)
{
    //
}

QString Stop::name() const
{
    return m_strName;
}

QGeoCoordinate Stop::coordinate() const
{
    return m_oCoordinate;
}

qint32 Stop::distance() const
{
    return m_nDistance;
}

bool Stop::taken() const
{
    return m_bTaken;
}

void Stop::setDistance(const qint32 nDistance)
{
    m_nDistance = nDistance;
}

void Stop::setTaken(const bool bTaken)
{
    m_bTaken = bTaken;
}
