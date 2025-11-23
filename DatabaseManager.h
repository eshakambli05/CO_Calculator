#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include <QString>

class DatabaseManager {
public:
    static DatabaseManager& instance();
    bool initialize();
    QSqlDatabase database() const;

private:
    DatabaseManager();
    ~DatabaseManager();
    QSqlDatabase m_db;
};

#endif // DATABASEMANAGER_H
