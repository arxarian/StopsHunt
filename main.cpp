#include <QGuiApplication>

#include "contoller.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setOrganizationName("ArSoft");
    QCoreApplication::setOrganizationDomain("github.com/arxarian");
    QCoreApplication::setApplicationName("Stops Hunt");

    QGuiApplication app(argc, argv);

    Contoller controler;

    return app.exec();
}
