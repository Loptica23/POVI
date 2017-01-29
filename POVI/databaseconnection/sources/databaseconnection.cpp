#include "databaseconnection.h"
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <string>

DatabaseConnection::DatabaseConnection(
        QString databaseConnectionName,
        QString host,
        QString databaseName,
        QString userName,
        QString pwd)
    :databaseConnectionName(databaseConnectionName),
     host(host),
     databaseName(databaseName),
     userName(userName),
     pwd(pwd)
{

}

DatabaseConnection::~DatabaseConnection()
{

}

bool DatabaseConnection::conectToDb()
{
    bool result;
    m_db = QSqlDatabase::addDatabase("QMYSQL");
    m_db.setHostName(host);
    m_db.setDatabaseName(databaseName);
    m_db.setUserName(userName);
    m_db.setPassword(pwd);
    result =  m_db.open();
    if (!result)
        qDebug() << m_db.lastError();
    return result;
}

bool DatabaseConnection::logIn(QString username, QString pwd)
{
    bool result = false;
    QSqlQuery query("select * from radnik");
    if(query.exec())
    {
        while (query.next())
        {
            if (username == query.value("KorisnickoIme").toString() && pwd == query.value("Sifra").toString())
            {
                result = true;
                break;
            }
        }
    }
    else
    {
        qDebug() << "nije uspeo query!";
    }
    return result;
}
