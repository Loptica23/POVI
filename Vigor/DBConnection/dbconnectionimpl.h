#pragma once
#include <memory>
#include "dbconnection.h"

class QString;
class QSqlDatabase;
//class DBConnection;

class DBConnectionImpl: public DBConnection
{
public:
    DBConnectionImpl();
    virtual ~DBConnectionImpl();

    virtual const QString getLastError() const;

    virtual bool conectToDb();
    virtual bool logIn(QString username, QString pwd);
    virtual std::shared_ptr<QSqlQuery> getEmployees();


private:
    std::shared_ptr<QSqlDatabase> m_db;
};
