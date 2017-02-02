#pragma once
#include "dbconnection.h"

class QString;
class QSqlDatabase;

class DBConnectionImpl: public DBConnection
{
public:
    DBConnectionImpl();
    virtual ~DBConnectionImpl();

    virtual const QString getLastError() const;

    virtual bool conectToDb();
    virtual bool logIn(QString username, QString pwd);

private:
    QSqlDatabase m_db;
};
