#ifndef GEOLOCATIONDATAMANAGER_H
#define GEOLOCATIONDATAMANAGER_H

#include <QObject>
#include "dbmanager.h"
#include "ipstackapi.h"

class GeolocationDataManager : public QObject
{
    Q_OBJECT
public:
    GeolocationDataManager(const QString& apiKey, QObject* parent = nullptr);

public slots:
    void addEntry(const QString& key);
    void deleteEntry(const QString& key);
    void previewEntry(const QString& key);

private slots:
    void apiRequestFinished(const QJsonObject& responseObject);

signals:
    void actionFinished(const QJsonObject& responseObject);
    void added(const bool& success);
    void deleted(const bool& success);
    void previewed(const QJsonObject& responseObject);

private:
    IPStackAPI m_api;
    const QString m_apiKey {};
    DBManager m_dbman;
    QString m_processedInput {};

    QString sanitizeInput(const QString& input) const;
};

#endif // GEOLOCATIONDATAMANAGER_H
