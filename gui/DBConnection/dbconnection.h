#pragma once

#include "dbconnection_global.h"
#include <memory>
#include <vector>
#include <QString>
#include "customer.h"
#include "order.h"
#include "command.h"
#include "tasktypes.h"
#include "task.h"
#include "machine.h"
#include "employee.h"
#include "invoice.h"

class QString;
class DBConnection;
class Employee;
class QSqlQuery;

typedef std::shared_ptr<DBConnection> DBConnectionPtr;

class DBCONNECTIONSHARED_EXPORT DBConnection
{
public:
    static DBConnectionPtr create();

    virtual ~DBConnection();

    virtual bool conectToDb(QString userName, QString pwd) = 0;
    virtual EmployeePtr logIn(QString username, QString pwd) = 0;

    virtual EmployeePtrVtr getEmployees() = 0;
    virtual EmployeePtrVtr getEmployees(Employee::WorkPosition workPosition) = 0;
    virtual EmployeePtr getEmployee(QString username) = 0;
    virtual bool createNewEmployee(EmployeePtr employee) = 0;
    virtual bool updateEmployee(EmployeePtr employee) = 0;

    virtual CustomerPtrVtr getCustomers() = 0;
    virtual bool createNewCustomer(CustomerPtr customer) = 0;
    virtual bool updateCustomer(CustomerPtr customer) = 0;

    virtual OrderPtrVtr getOrders() = 0;
    virtual OrderPtrVtr getOrders(CustomerPtr customer) = 0;
    virtual bool createNewOrder(OrderPtr order) = 0;
    virtual bool updateOrder(OrderPtr order) = 0;

    virtual CommandPtrVtr getCommands() = 0;
    virtual CommandPtr getCommand(unsigned commandNumber) = 0;
    virtual CommandPtr getCommandOnWhichEmployeeWorkingOn(EmployeePtr employee) = 0;
    virtual CommandPtrVtr getCommands(OrderPtr order) = 0;
    virtual CommandPtrVtr getCommands(Command::State & state) = 0;
    virtual CommandPtrVtr getCommandWhichWaitingOnTask(unsigned taskTypeId) = 0;
    virtual bool isThereCommandWhichWaitingOnTask(unsigned taskTypeId) = 0;
    virtual bool createNewCommand(CommandPtr command) = 0;
    virtual bool updateCommand(CommandPtr command) = 0;
    virtual bool deleteCommand(CommandPtr command) = 0;
    virtual bool sendToProduction(CommandPtr command) = 0;
    virtual bool completeCurrentTask(CommandPtr command) = 0;
    virtual bool leaveCurrentTask(CommandPtr command, EmployeePtr employee) = 0;
    virtual bool startWorkingOnWaitingTask(CommandPtr command, EmployeePtr employee) = 0;

    virtual TaskPtrVtr getTasks() = 0;
    virtual TaskPtrVtr getTasks(CommandPtr command) = 0;
    virtual bool createNewTask(TaskPtr task, unsigned employeeID) = 0;
    virtual bool updateTask(TaskPtr task) = 0;
    virtual bool deleteTask(TaskPtr task) = 0;

    virtual InvoicePtrVtr getInvoices(CommandPtr command) = 0;
    virtual InvoicePtrVtr getInvoices(TaskPtr task) = 0;
    virtual bool createNewInvoice(InvoicePtr invoice) = 0;
    virtual bool updateInvoice(InvoicePtr invoice) = 0;
    virtual bool deleteInvoice(InvoicePtr invoice) = 0;

    virtual TaskTypesPtr getTaskTypes() = 0;

    virtual MachinePtrVtr getMachines() = 0;
    virtual bool createMachine(MachinePtr machine) = 0;
    virtual bool updateMachine(MachinePtr machine) = 0;

    virtual void setDatabaseConnectionName(const QString& databaseConnectionName);
    virtual void setHost(const QString& host);
    virtual void setDatabaseName(const QString& databaseName);

    virtual const QString getLastError() const = 0;

protected:
    DBConnection();

    QString m_databaseConnectionName;
    QString m_host;
    QString m_databaseName;
};
