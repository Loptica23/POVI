#pragma once
#include <memory>
#include "dbconnection.h"

class QString;
class QSqlDatabase;
class QSqlQuery;
//class DBConnection;

class DBConnectionImpl: public DBConnection
{
public:
    DBConnectionImpl();
    virtual ~DBConnectionImpl();

    virtual const QString getLastError() const;

    virtual bool conectToDb();
    virtual bool logIn(QString username, QString pwd);
    virtual EmployeePtrVtr getEmployees();              //bilo bi dobro da moze da se dohvati i kao neki predictive search
    virtual bool createNewEmployee(EmployeePtr employee);
    virtual bool updateEmployee(EmployeePtr employee);

protected:
    EmployeePtrVtr createEmployeesFromQuery(QSqlQuery& query);

private:
    std::shared_ptr<QSqlDatabase> m_db;
    QString m_lastError;
};
