#include <QQmlContext>
#include <QFile>

#include "contoller.h"

Contoller::Contoller(QObject *parent) : QObject(parent)
{
    LoadData();
    SetModel();
    LoadEngine();

    m_pPositionManager = new PositionManager(this);
    connect(m_pPositionManager, &PositionManager::PositionUpdated, &m_arrStopsModel, &StopsModel::updatePosition);
    m_pPositionManager->Start();

}

void Contoller::LoadData()
{
    QFile oFile(":/stops.csv");
    if (!oFile.open(QIODevice::ReadOnly)) {
        qDebug() << oFile.errorString();
    }

    while (oFile.isOpen() && !oFile.atEnd())
    {
        QList<QByteArray> arrLine = oFile.readLine().split(',');
        if (arrLine.count() < 3)
        {
            qDebug() << "incorrect data format" << arrLine;
        }

        QString strName { QTextCodec::codecForMib(106)->toUnicode(arrLine[0]) };
        QGeoCoordinate oCoordinate { arrLine.at(1).toDouble(), arrLine.at(2).toDouble() };

        m_arrStopsModel.add(Stop(strName, oCoordinate));
    }
}

void Contoller::SetModel()
{
    m_arrProxyModel.setSourceModel(&m_arrStopsModel);
    m_arrProxyModel.setSortRole(StopsModel::DistanceRole);
    m_arrProxyModel.sort(0, Qt::AscendingOrder);
}

void Contoller::LoadEngine()
{
    m_oEngine.rootContext()->setContextProperty("stopsModel", &m_arrProxyModel);

    m_oEngine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (m_oEngine.rootObjects().isEmpty())
    {
        qFatal("cannot load qml engine");
    }
}
