#include <QString>
#include "dbconnection.h"
#include "dbconnectionimpl.h"

std::shared_ptr<DBConnection> DBConnection::create()
{
    DBConnectionPtr instance(new DBConnectionImpl());
    return instance;
}


DBConnection::DBConnection()
{
    m_databaseConnectionName = "POVI";
    m_host = "localhost";
    m_databaseName = "vigor";
}

DBConnection::~DBConnection()
{

}

void DBConnection::setDatabaseConnectionName(const QString& databaseConnectionName)
{
    m_databaseConnectionName = databaseConnectionName;
}

void DBConnection::setHost(const QString& host)
{
    m_host = host;
}

void DBConnection::setDatabaseName(const QString& databaseName)
{
    m_databaseName = databaseName;
}
