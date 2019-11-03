
#pragma once

#include <QObject>
#include <QQmlApplicationEngine>
#include <QTextCodec>
#include <QGeoCoordinate>
#include <QSortFilterProxyModel>
#include <QPointer>

#include <QDebug>

#include "stopsmodel.h"
#include "positionmanager.h"

class Application : public QObject
{
    Q_OBJECT
public:
    explicit Application(QObject *parent = nullptr);

private:
    QQmlApplicationEngine m_engine;
    StopsModel m_stopsModel;
    QSortFilterProxyModel m_takenProxyModel;
    QSortFilterProxyModel m_sortByDistanceProxyModel;

    QPointer<PositionManager> m_positionManager;

    void setProxyModels();
    void loadEngine();
};
