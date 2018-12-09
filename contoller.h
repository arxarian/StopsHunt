#ifndef CONTOLLER_H
#define CONTOLLER_H

#include <QObject>
#include <QQmlApplicationEngine>
#include <QTextCodec>
#include <QGeoCoordinate>
#include <QSortFilterProxyModel>
#include <QPointer>

#include <QDebug>

#include "stopsmodel.h"
#include "positionmanager.h"

class Contoller : public QObject
{
    Q_OBJECT
public:
    explicit Contoller(QObject *parent = nullptr);

signals:

public slots:

private:
    QQmlApplicationEngine m_oEngine;
    StopsModel m_arrStopsModel;
    QSortFilterProxyModel m_arrTakenModel;
    QSortFilterProxyModel m_arrSortByDistanceModel;

    QPointer<PositionManager> m_pPositionManager;

    void LoadData();
    void SetModels();
    void LoadEngine();
};

#endif // CONTOLLER_H
