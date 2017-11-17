#include <QString>
#include <QSettings>
#include "dbconnection.h"
#include "dbconnectionimpl.h"

std::shared_ptr<DBConnection> DBConnection::create()
{
    DBConnectionPtr instance(new DBConnectionImpl());
    return instance;
}


DBConnection::DBConnection()
{
    QSettings settings(QString("config.ini"), QSettings::IniFormat);
    m_databaseConnectionName = settings.value("DatabaseConfiguration/connectionName", "POVI").toString();
    m_host = settings.value("DatabaseConfiguration/host", "localhost").toString();
    m_databaseName = settings.value("DatabaseConfiguration/databaseName", "Vigor").toString();
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
