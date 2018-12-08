#include <QGuiApplication>

#include "contoller.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    Contoller controler;

    return app.exec();
}
