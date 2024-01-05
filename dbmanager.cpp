#include "DBManager.h"
#include <QDebug>
#include <QSqlError>

DBManager::DBManager()
{


    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("IPGeoTracker.db");

    m_query = QSqlQuery(m_db);

    if (!m_db.open())
    {
        qDebug() << "Database: connection with database failed";
    }
    else
    {
        qDebug() << "Database: connection ok";
        if (setUpTable())
        {
            qDebug() << "GeoData table created successfully!";
        }
        else
        {
            qDebug() << "Error creating GeoData table:" << getLastError();
        }
    }
}

DBManager::~DBManager()
{
    if(m_db.isOpen())
    {
        m_db.close();
    }
}

bool DBManager::connectionSuccessful() const
{
    return m_db.isOpen();
}

bool DBManager::executeQuery(const QString &query)
{
    qDebug() << query;
    const auto success = m_query.exec(query);
    return success;
}

QString DBManager::getLastError() const
{
    return m_query.lastError().text();
}

const QSqlQuery &DBManager::getLastQuery() const
{
    return m_query;
}

void DBManager::moveQueryToNextRow()
{
    m_query.next();
}

bool DBManager::setUpTable()
{
    QString createTableQuery = "CREATE TABLE IF NOT EXISTS GeoData ("
                               "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                               "key TEXT UNIQUE NOT NULL,"
                               "jsonData TEXT)";
    return executeQuery(createTableQuery);
}
