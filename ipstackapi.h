#ifndef IPSTACKAPI_H
#define IPSTACKAPI_H

#include <QObject>
#include <QNetworkAccessManager>

class IPStackAPI : public QObject {
    Q_OBJECT
public:
    IPStackAPI(const QString& apiKey, QObject* parent = nullptr);

    void processRequest(const QString& ipAddress);

signals:
    void responseReceived(const QString& response);

private slots:
    void onRequestFinished(QNetworkReply* reply);

private:
    QNetworkAccessManager m_manager;
    QString m_apiKey;
};

#endif // IPSTACKAPI_H
