#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "geolocationdatamanager.h"

//Since this API_KEY is sensitive data, I would usually think of a better way to store it
const QString API_KEY = "71f113e685dc016834e0095dcdd7d22e";

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    GeolocationDataManager geoDataManager(API_KEY);
    engine.rootContext()->setContextProperty("geoDataManager", &geoDataManager);

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
