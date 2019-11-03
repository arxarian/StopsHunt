#include <QQmlContext>
#include <QFile>

#include "application.h"

Application::Application(QObject *parent) : QObject(parent)
{
    setProxyModels();
    loadEngine();

    m_positionManager = new PositionManager(this);
    connect(m_positionManager, &PositionManager::positionUpdated, &m_stopsModel, &StopsModel::updatePosition);
    m_positionManager->start();
}

void Application::setProxyModels()
{
    m_sortByDistanceProxyModel.setSourceModel(&m_stopsModel);
    m_sortByDistanceProxyModel.setSortRole(StopsModel::DistanceRole);
    m_sortByDistanceProxyModel.sort(0, Qt::AscendingOrder);

    m_takenProxyModel.setSourceModel(&m_sortByDistanceProxyModel);
    m_takenProxyModel.setSortRole(StopsModel::TakenRole);
    m_takenProxyModel.sort(0, Qt::AscendingOrder);
}

void Application::loadEngine()
{
    qmlRegisterType<StopItem>("Datamodels", 1, 0, "StopItem");

    m_engine.rootContext()->setContextProperty("stopsModel", &m_takenProxyModel);
    m_engine.rootContext()->setContextProperty("originalModel", &m_stopsModel);

    m_engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (m_engine.rootObjects().isEmpty())
    {
        qFatal("cannot load qml engine");
    }
}
