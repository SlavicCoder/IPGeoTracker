#ifndef DBManager_H
#define DBManager_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlResult>

class DBManager
{
public:
    DBManager();
    ~DBManager();

    DBManager(const DBManager&) = delete;
    DBManager& operator=(const DBManager&) = delete;
    DBManager(DBManager&&) = delete;
    DBManager& operator=(DBManager&&) = delete;

    [[nodiscard]] bool connectionSuccessful() const;
    [[nodiscard]] bool executeQuery(const QString& query);
    [[nodiscard]] QString getLastError() const;
    [[nodiscard]] const QSqlQuery& getLastQuery() const;
    void moveQueryToNextRow();

private:
    QSqlDatabase m_db;
    QSqlQuery m_query;

    [[nodiscard]] bool setUpTable();
};

#endif // DBManager_H
