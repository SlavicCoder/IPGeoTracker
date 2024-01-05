#include "geolocationdatamanager.h"
#include <QJsonObject>
#include <QJsonDocument>

GeolocationDataManager::GeolocationDataManager(const QString& apiKey, QObject* parent) : QObject(parent), m_apiKey(apiKey)
{
    connect(&m_api, &IPStackAPI::responseReceived, this, &GeolocationDataManager::apiRequestFinished);
}

void GeolocationDataManager::addEntry(const QString &key)
{
    m_processedInput = sanitizeInput(key);
    m_api.processRequest(m_apiKey, m_processedInput);
}

void GeolocationDataManager::deleteEntry(const QString &key)
{
    m_processedInput = sanitizeInput(key);
    const auto query = QString("DELETE FROM GeoData WHERE key = '%1'").arg(m_processedInput);

    const auto success = m_dbman.executeQuery(query);

    QJsonObject returnObject;
    returnObject["query"] = query;
    returnObject["lastQueryError"] = m_dbman.getLastError();

    emit deleted(success);
    emit actionFinished(returnObject);
}

void GeolocationDataManager::previewEntry(const QString &key)
{
    m_processedInput = sanitizeInput(key);
    const auto query = QString("SELECT jsonData FROM GeoData WHERE key = '%1' LIMIT 1").arg(m_processedInput);

    const auto success = m_dbman.executeQuery(query);

    QJsonObject returnObject;
    returnObject["query"] = query;
    returnObject["lastQueryError"] = m_dbman.getLastError();

    if(success)
    {
        const auto& result = m_dbman.getLastQuery();
        m_dbman.moveQueryToNextRow();
        const auto jsonVariant = result.value(0);
        if(jsonVariant.canConvert<QString>())
        {
            const auto jsonString = jsonVariant.toString();
            QJsonParseError jsonError;
            QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonString.toUtf8(), &jsonError);

            if (jsonError.error == QJsonParseError::NoError && jsonDoc.isObject())
            {
                returnObject = jsonDoc.object();
            }
        }
    }
    emit previewed(returnObject);
    emit actionFinished(returnObject);
}

void GeolocationDataManager::apiRequestFinished(const QJsonObject& responseObject)
{
    if (responseObject.contains("success") && !responseObject["success"].toBool())
    {
        emit added(false);
        emit actionFinished(responseObject);
        return;
    }

    const QString jsonData = QJsonDocument(responseObject).toJson(QJsonDocument::Compact).toStdString().c_str();
    const QString query = QString("INSERT OR REPLACE INTO GeoData (key, jsonData) VALUES ('%1', '%2')")
                              .arg(m_processedInput)
                              .arg(jsonData);
    const auto success = m_dbman.executeQuery(query);
    emit added(success);

    QJsonObject returnObject = responseObject;
    returnObject["query"] = query;
    returnObject["lastQueryError"] = m_dbman.getLastError();
    emit actionFinished(returnObject);
}

QString GeolocationDataManager::sanitizeInput(const QString &input) const
{
    //Now, I only prevent SQL Injection, but more input sanitizing can be done to handle edge cases
    QString sanitizedInput = input;
    sanitizedInput.replace("'", "''");
    return sanitizedInput;
}
