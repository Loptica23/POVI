#include <QString>
#include <QtSql/QSqlDatabase>
#include <QDebug>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include "dbconnectionimpl.h"

DBConnectionImpl::DBConnectionImpl()
{

}

DBConnectionImpl::~DBConnectionImpl()
{
    m_db->close();
}

const QString DBConnectionImpl::getLastError() const
{
    return "Za sada vracam ovaj string!";
}

bool DBConnectionImpl::conectToDb()
{
    bool result;
    m_db = std::make_shared<QSqlDatabase>( QSqlDatabase::addDatabase("QMYSQL"));       // ne mozes jebeno ovako
    m_db->setHostName(m_host);
    m_db->setDatabaseName(m_databaseName);
    m_db->setUserName(m_userName);
    m_db->setPassword(m_pwd);
    result =  m_db->open();
    if (!result)
        qDebug() << m_db->lastError();
    return result;
}

bool DBConnectionImpl::logIn(QString username, QString pwd)
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

std::shared_ptr<QSqlQuery> DBConnectionImpl::getEmployees()
{
    bool result = false;
    std::shared_ptr<QSqlQuery> query(new QSqlQuery("select * from radnik"));
    if(query->exec())
    {
        return query;
    }
    else
    {
        qDebug() << "nije uspeo query!";
    }
    return nullptr;
}
