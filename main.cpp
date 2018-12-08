#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QFile>
#include <QTextCodec>
#include <QGeoCoordinate>
#include <QSortFilterProxyModel>

#include <QDebug>

#include "stopsmodel.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    StopsModel stopsModel;

    QFile oFile(":/stops.csv");
    if (!oFile.open(QIODevice::ReadOnly)) {
        qDebug() << oFile.errorString();
        return -1;
    }

    while (!oFile.atEnd())
    {
        QList<QByteArray> arrLine = oFile.readLine().split(',');
        if (arrLine.count() < 3)
        {
            qDebug() << "incorrect data format" << arrLine;
        }

        QString strName { QTextCodec::codecForMib(106)->toUnicode(arrLine[0]) };
        QGeoCoordinate oCoordinate { arrLine.at(1).toDouble(), arrLine.at(2).toDouble() };

        stopsModel.add(Stop(strName, oCoordinate));
    }

    QSortFilterProxyModel proxyModel;
    proxyModel.setSourceModel(&stopsModel);
    proxyModel.setSortRole(StopsModel::DistanceRole);
    proxyModel.sort(0, Qt::DescendingOrder);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("stopsModel", &proxyModel);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
    {
        return -1;
    }

    return app.exec();
}
