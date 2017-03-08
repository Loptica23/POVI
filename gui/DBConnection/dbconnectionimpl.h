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
    virtual EmployeePtr logIn(QString username, QString pwd);

    virtual EmployeePtrVtr getEmployees();              //bilo bi dobro da moze da se dohvati i kao neki predictive search
    virtual bool createNewEmployee(EmployeePtr employee);
    virtual bool updateEmployee(EmployeePtr employee);

    virtual CustomerPtrVtr getCustomers();          //neki search bi trebalo da postoji
    virtual bool createNewCustomer(CustomerPtr customer);
    virtual bool updateCustomer(CustomerPtr customer);

    virtual OrderPtrVtr getOrders();
    virtual OrderPtrVtr getOrders(CustomerPtr customer);
    virtual bool createNewOrder(OrderPtr order);
    virtual bool updateOrder(OrderPtr order);

    virtual CommandPtrVtr getCommands();
    virtual CommandPtr getCommand(unsigned commandNumber);
    virtual CommandPtr getCommandOnWhichEmployeeWorkingOn(EmployeePtr employee);
    virtual CommandPtrVtr getCommands(OrderPtr order);
    virtual CommandPtrVtr getCommands(Command::State & state);
    virtual CommandPtrVtr getCommandWhichWaitingOnTask(unsigned taskTypeId);
    virtual bool createNewCommand(CommandPtr command);
    virtual bool updateCommand(CommandPtr command);
    virtual bool deleteCommand(CommandPtr command);
    virtual bool completeCurrentTask(CommandPtr command);
    virtual bool leaveCurrentTask(CommandPtr command, EmployeePtr employee);
    virtual bool startWorkingOnWaitingTask(CommandPtr command, EmployeePtr employee);

    virtual TaskPtrVtr getTasks();
    virtual TaskPtrVtr getTasks(CommandPtr command);
    virtual bool createNewTask(TaskPtr task, unsigned employeeID);
    virtual bool updateTask(TaskPtr task);
    virtual bool deleteTask(TaskPtr task);

    virtual TaskTypesPtr getTaskTypes() const;

    virtual MachinePtrVtr getMachines();
    virtual bool createMachine(MachinePtr machine);
    virtual bool updateMachine(MachinePtr machine);

protected:
    EmployeePtrVtr createEmployeesFromQuery(QSqlQuery& query);

private:
    std::shared_ptr<QSqlDatabase> m_db;
    QString m_lastError;
};
