#include "dbmanager.h"
#include <QDebug>

DbManager::DbManager()
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("IPGeoTracker.db");

    if (!m_db.open())
    {
        qDebug() << "Database: connection with database failed";
    }
    else
    {
        qDebug() << "Database: connection ok";
    }
}

DbManager::~DbManager()
{
    if(m_db.isOpen())
    {
        m_db.close();
    }
}

bool DbManager::connectionSuccessful() const
{
    return m_db.isOpen();
}

bool DbManager::executeQuery(const QString &query)
{
    QSqlQuery sqlQuery(query, m_db);
    return sqlQuery.exec();
}
