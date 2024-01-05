#include "DBManager.h"
#include <QDebug>
#include <QSqlError>

DBManager::DBManager()
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("IPGeoTracker.db");
    m_query = QSqlQuery(m_db);
    initializeDatabase();
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
    if(!connectionSuccessful())
    {
        initializeDatabase();
    }
    return m_query.exec(query);
}

QString DBManager::getLastError() const
{
    if(!connectionSuccessful())
    {
        return QString { "Database: connection with database failed" };
    }
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

void DBManager::initializeDatabase()
{
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

bool DBManager::setUpTable()
{
    QString createTableQuery = "CREATE TABLE IF NOT EXISTS GeoData ("
                               "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                               "key TEXT UNIQUE NOT NULL,"
                               "jsonData TEXT)";
    return executeQuery(createTableQuery);
}
