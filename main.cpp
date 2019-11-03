#include <QGuiApplication>

#include "application.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setOrganizationName("ArSoft");
    QCoreApplication::setOrganizationDomain("github.com/arxarian");
    QCoreApplication::setApplicationName("Stops Hunt");

    QGuiApplication app(argc, argv);

    Application application;

    return QGuiApplication::exec();
}
