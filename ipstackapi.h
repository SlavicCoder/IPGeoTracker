#ifndef IPSTACKAPI_H
#define IPSTACKAPI_H

#include <QObject>
#include <QNetworkAccessManager>

class IPStackAPI : public QObject {
    Q_OBJECT
public:
    IPStackAPI(QObject* parent = nullptr);

    void processRequest(const QString& apiKey, const QString& ipAddress);

signals:
    void responseReceived(const QJsonObject& responseObject);

private slots:
    void onRequestFinished(QNetworkReply* reply);

private:
    QNetworkAccessManager m_manager;
};

#endif // IPSTACKAPI_H
