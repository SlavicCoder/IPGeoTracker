#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "dbmanager.h"

//since this API_KEY is sensitive data, I would usually think of a better way to store it
const QString API_KEY = "71f113e685dc016834e0095dcdd7d22e";

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    DbManager dbman;

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/IPGeoTracker/Main.qml"_qs);
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
