#include "stopsmodel.h"

StopsModel::StopsModel(QObject *parent) : QAbstractListModel(parent)
{
    m_pStopsData = new QSettings();
}

void StopsModel::add(const Stop &oStop)
{
    bool bTaken = m_pStopsData->value(QString("stops/%1").arg(oStop.name()), false).toBool();

    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_arrStops << oStop;
    m_arrStops.last().setTaken(bTaken);
    endInsertRows();

    if (bTaken) ++m_nTaken;
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
            m_pStopsData->setValue(QString("stops/%1").arg(oStop.name()), true);
            ++m_nTaken;

            emit progressChanged();
        }

        emit dataChanged(index, index, QVector<int>() << role);

        return true;
    }

    return false;
}

void StopsModel::updatePosition(QGeoPositionInfo oPositionInfo)
{
    const QGeoCoordinate& oCoordinate = oPositionInfo.coordinate();

    for (qint32 nIndex = 0; nIndex < m_arrStops.count(); ++nIndex)
    {
        const QGeoCoordinate& oStopCoordinate = m_arrStops.at(nIndex).coordinate();
        const qint32 nDistance_m = static_cast<qint32>(oCoordinate.distanceTo(oStopCoordinate));

        m_arrStops[nIndex].setDistance(nDistance_m);
    }

    QModelIndex oIndexTop = createIndex(0, 0);
    QModelIndex oIndexBottom = createIndex(m_arrStops.count(), 0);

    emit dataChanged(oIndexTop, oIndexBottom, QVector<int>() << DistanceRole);
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

qreal StopsModel::progress()
{
    return static_cast<qreal>(m_nTaken) / m_arrStops.count();
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
