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

    virtual bool conectToDb(QString userName, QString pwd);
    virtual EmployeePtr logIn(QString username, QString pwd);

    virtual EmployeePtrVtr getEmployees();              //bilo bi dobro da moze da se dohvati i kao neki predictive search
    virtual EmployeePtrVtr getEmployees(Employee::WorkPosition workPosition);
    virtual EmployeePtr getEmployee(QString username);
    virtual EmployeePtr getEmployee(unsigned id);
    virtual bool createNewEmployee(EmployeePtr employee);
    virtual bool updateEmployee(EmployeePtr employee);

    virtual CustomerPtrVtr getCustomers();          //neki search bi trebalo da postoji
    virtual bool createNewCustomer(CustomerPtr customer);
    virtual bool updateCustomer(CustomerPtr customer);

    virtual OrderPtrVtr getOrders();
    virtual OrderPtrVtr getOrders(CustomerPtr customer);
    virtual OrderPtr getOrder(unsigned id);
    virtual bool createNewOrder(OrderPtr order);
    virtual bool updateOrder(OrderPtr order);

    virtual CommandPtrVtr getCommands();
    virtual CommandPtr getCommand(unsigned commandNumber);
    virtual CommandPtr getCommandOnWhichEmployeeWorkingOn(EmployeePtr employee);
    virtual CommandPtrVtr getCommandsOnWhichEmployeeeWorkingOn(EmployeePtr employee);
    virtual CommandPtrVtr getCommands(OrderPtr order);
    virtual CommandPtrVtr getCommands(Command::State & state);
    virtual CommandPtrVtr getCommandWhichWaitingOnTask(unsigned taskTypeId);
    virtual CommandPtrVtr getCommandWhichWaitingOnTasks(std::vector<unsigned> taskTypeIds);
    virtual bool isThereCommandWhichWaitingOnTask(unsigned taskTypeId);
    virtual bool isCommandUpToDate(CommandPtr command);
    virtual bool createNewCommand(CommandPtr command);
    virtual bool canCommandBeModified(CommandPtr command);
    virtual bool updateCommand(CommandPtr command);
    virtual bool deleteCommand(CommandPtr command);
    virtual bool sendToWaitForProduction(CommandPtr command);
    virtual bool sendToKomercial(CommandPtr command);
    virtual bool stopCommand(CommandPtr command);
    virtual bool sendToProduction(CommandPtr command);
    virtual bool completeCurrentTask(CommandPtr command, unsigned quantity);
    virtual bool leaveCurrentTask(CommandPtr command, EmployeePtr employee, unsigned quantity);
    virtual bool startWorkingOnWaitingTask(CommandPtr command, EmployeePtr employee);

    virtual TaskPtrVtr getTasks();
    virtual TaskPtrVtr getTasks(CommandPtr command);
    virtual TaskPtr getCurrentTask(CommandPtr command);
    virtual bool annulTask(TaskPtr task, CommandPtr command, TaskPtrVtr tasks);
    virtual bool createNewTask(TaskPtr task, unsigned employeeID);
    virtual bool updateTask(TaskPtr task);
    virtual bool deleteTask(TaskPtr task);

    virtual InvoicePtrVtr getInvoices(CommandPtr command);
    virtual InvoicePtrVtr getInvoices(TaskPtr task);
    virtual bool createNewInvoice(InvoicePtr invoice);
    virtual bool updateInvoice(InvoicePtr invoice);
    virtual bool deleteInvoice(InvoicePtr invoice);

    virtual TaskTypesPtr getTaskTypes();

    virtual MachinePtrVtr getMachines();
    virtual MachinePtrVtr getMachines(unsigned taskTypeId);
    virtual MachinePtr getMachine(unsigned id);
    virtual bool createMachine(MachinePtr machine);
    virtual bool updateMachine(MachinePtr machine);

protected:
    EmployeePtrVtr createEmployeesFromQuery(QSqlQuery& query);

private:
    std::shared_ptr<QSqlDatabase> m_db;
    QString m_lastError;
};
