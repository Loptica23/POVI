#pragma once

#include "dbconnection_global.h"
#include <memory>

class Qstring;

class DBCONNECTIONSHARED_EXPORT DBConnection
{
public:
    static std::shared_ptr<DBConnection> createDBConnection();

    virtual ~DBConnection();

    virtual bool conectToDb() = 0;
    virtual bool logIn(QString username, QString pwd) = 0;

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

