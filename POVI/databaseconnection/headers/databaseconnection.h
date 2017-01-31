#pragma once;

#include <QtSql/QSqlDatabase>
#include <string>

class DatabaseConnection
{
public:
    DatabaseConnection(
            QString databaseConnectionName = "POVI",
            QString host = "localhost",
            QString databaseName = "vigor",
            QString userName = "root",
            QString pwd = "2304"
    );

    virtual ~DatabaseConnection();

    bool conectToDb();
    bool logIn(QString username, QString pwd);

private:
    QSqlDatabase m_db;
    const QString databaseConnectionName;
    QString host;
    QString databaseName;
    QString userName;
    QString pwd;        //ovo mora da bude secure string
};
