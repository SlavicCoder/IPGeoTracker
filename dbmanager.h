#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QSqlDatabase>
#include <QSqlQuery>

class DbManager
{
public:
    DbManager();
    ~DbManager();

    //Rule of 5
    DbManager(const DbManager&) = delete;
    DbManager& operator=(const DbManager&) = delete;
    DbManager(DbManager&&) = delete;
    DbManager& operator=(DbManager&&) = delete;

    [[nodiscard]] bool connectionSuccessful() const;
    [[nodiscard]] bool executeQuery(const QString& query);

private:
    QSqlDatabase m_db;
};

#endif // DBMANAGER_H
