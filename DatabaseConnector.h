#ifndef DATABASECONNECTOR_H
#define DATABASECONNECTOR_H

#include <QString>
#include <QSqlDatabase>


class DatabaseConnector
{
public:
    DatabaseConnector(QString host, QString databasePath, QString username, QString password);
    QString getHost() const;
    void setHost(const QString &value);
    QString getUsername() const;
    void setUsername(const QString &value);
    QString getPassword() const;
    void setPassword(const QString &value);
    QString getDatabasePath() const;
    void setDatabasePath(const QString &value);
    bool connect();

private:
    QString host;
    QString databasePath;
    QString username;
    QString password;
    QSqlDatabase db;
    void initTables();
};

#endif // DATABASECONNECTOR_H
