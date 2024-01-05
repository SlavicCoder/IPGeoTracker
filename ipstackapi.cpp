#include "ipstackapi.h"

#include <QEventLoop>
#include <QTextStream>
#include <QNetworkReply>

IPStackAPI::IPStackAPI(const QString& apiKey, QObject* parent) : QObject(parent), m_apiKey(apiKey) {
    connect(&m_manager, &QNetworkAccessManager::finished, this, &IPStackAPI::onRequestFinished);
}

void IPStackAPI::processRequest(const QString& ipAddress) {
    QString apiUrl = "http://api.ipstack.com/" + ipAddress + "?access_key=" + m_apiKey;

    QUrl url(apiUrl);
    QNetworkRequest request(url);

    QSharedPointer<QNetworkReply> reply(m_manager.get(request));

    QEventLoop eventLoop;
    connect(reply.data(), &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec();

    if (reply->error() == QNetworkReply::NoError) {
        QByteArray responseData = reply->readAll();
        QString responseString = QString::fromUtf8(responseData);

        emit responseReceived(responseString);
    } else {
        emit responseReceived(reply->errorString());
    }
}

void IPStackAPI::onRequestFinished(QNetworkReply* reply) {
    // This slot is left empty intentionally.
    // The actual response handling is done in the processRequest() function.
}
