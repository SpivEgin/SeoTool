#include "DatabaseConnector.h"
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>

DatabaseConnector::DatabaseConnector(QString host, QString databasePath, QString username, QString password)
{
    // create sqlite database
    this->db = QSqlDatabase::addDatabase("QSQLITE");
    // set hostname
    this->db.setHostName(host);
    this->setHost(host);
    // set databasename
    this->db.setDatabaseName(databasePath);
    this->setDatabasePath(databasePath);
    // set username
    this->db.setUserName(username);
    this->setUsername(username);
    // set password
    this->db.setPassword(password);
    this->setPassword(password);
}

void DatabaseConnector::initTables()
{
    QSqlQuery query("CREATE TABLE IF NOT EXISTS Domains (ID INTEGER PRIMARY KEY AUTOINCREMENT, Name TEXT)");
    if(!query.exec())
        qDebug()<<"1: "<<query.lastError().text();

    query = QSqlQuery("CREATE TABLE IF NOT EXISTS Keywords (Keyword PRIMARY KEY NOT NULL, Position INTEGER, Time TEXT,"
            "BestPosition INTEGER, BestPosTime TEXT, PositionDiff INTEGER, "
            "DomainID INTEGER)");
    if(!query.exec())
        qDebug()<<"2: "<<query.lastError().text();
}

bool DatabaseConnector::connect()
{
    bool status = this->db.open();
    if (status) {
        this->initTables();
    }
    return status;
}

QString DatabaseConnector::getPassword() const
{
    return password;
}

void DatabaseConnector::setPassword(const QString &value)
{
    password = value;
}

QString DatabaseConnector::getUsername() const
{
    return username;
}

void DatabaseConnector::setUsername(const QString &value)
{
    username = value;
}

QString DatabaseConnector::getHost() const
{
    return host;
}

void DatabaseConnector::setHost(const QString &value)
{
    host = value;
}

QString DatabaseConnector::getDatabasePath() const
{
    return databasePath;
}

void DatabaseConnector::setDatabasePath(const QString &value)
{
    databasePath = value;
}
