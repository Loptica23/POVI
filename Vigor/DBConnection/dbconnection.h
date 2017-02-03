#pragma once

#include "dbconnection_global.h"
#include <memory>

class Qstring;
class DBConnection;
class QSqlQuery;

typedef std::shared_ptr<DBConnection> DBConnectionPtr;

class DBCONNECTIONSHARED_EXPORT DBConnection
{
public:
    static DBConnectionPtr create();

    virtual ~DBConnection();

    virtual bool conectToDb() = 0;
    virtual bool logIn(QString username, QString pwd) = 0;
    virtual std::shared_ptr<QSqlQuery> getEmployees() = 0;

    virtual void setDatabaseConnectionName(const QString& databaseConnectionName);
    virtual void setHost(const QString& host);
    virtual void setDatabaseName(const QString& databaseName);
    virtual void setUserName(const QString& userName);
    virtual void setPwd(const QString& pwd);

    virtual const QString getLastError() const = 0;

protected:
    DBConnection();

    QString m_databaseConnectionName;
    QString m_host;
    QString m_databaseName;
    QString m_userName;
    QString m_pwd;
};



