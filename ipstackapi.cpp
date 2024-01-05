#include "ipstackapi.h"

#include <QEventLoop>
#include <QTextStream>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>

IPStackAPI::IPStackAPI( QObject* parent) : QObject(parent) {
    connect(&m_manager, &QNetworkAccessManager::finished, this, &IPStackAPI::onRequestFinished);
}

void IPStackAPI::processRequest(const QString& apiKey, const QString& ipAddress) {
    QString apiUrl = "http://api.ipstack.com/" + ipAddress + "?access_key=" + apiKey;

    QUrl url(apiUrl);
    QNetworkRequest request(url);

    QSharedPointer<QNetworkReply> reply(m_manager.get(request));

    QEventLoop eventLoop;
    connect(reply.data(), &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec();

    if (reply->error() == QNetworkReply::NoError) {
        QByteArray responseData = reply->readAll();

        // Parse the JSON data directly into a QJsonObject
        QJsonParseError jsonError;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData, &jsonError);

        if (jsonError.error == QJsonParseError::NoError) {
            QJsonObject jsonObject = jsonDoc.object();
            emit responseReceived(jsonObject);
        } else {
            QJsonObject errorObject;
            errorObject["error"] = "JSON parse error: " + jsonError.errorString();
            emit responseReceived(errorObject);
        }
    } else {
        QJsonObject errorObject;
        errorObject["error"] = reply->errorString();
        emit responseReceived(errorObject);
    }
}

void IPStackAPI::onRequestFinished(QNetworkReply* reply) {
    // This slot is left empty intentionally.
    // The actual response handling is done in the processRequest() function.
}
