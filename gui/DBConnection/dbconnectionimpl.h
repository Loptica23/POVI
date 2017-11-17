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

    virtual bool conectToDb(QString userName, QString pwd) override;
    virtual EmployeePtr logIn(QString username, QString pwd) override;

    virtual EmployeePtrVtr getEmployees() override;              //bilo bi dobro da moze da se dohvati i kao neki predictive search
    virtual EmployeePtrVtr getEmployees(Employee::WorkPosition workPosition) override;
    virtual EmployeePtr getEmployee(QString username) override;
    virtual EmployeePtr getEmployee(unsigned id) override;
    virtual bool createNewEmployee(EmployeePtr employee) override;
    virtual bool updateEmployee(EmployeePtr employee) override;

    virtual CustomerPtrVtr getCustomers() override;          //neki search bi trebalo da postoji
    virtual CustomerPtr getCustomer(unsigned id) override;
    virtual bool createNewCustomer(CustomerPtr customer) override;
    virtual bool updateCustomer(CustomerPtr customer) override;

    virtual OrderPtrVtr getOrders() override;
    virtual OrderPtrVtr getOrders(CustomerPtr customer) override;
    virtual OrderPtr getOrder(unsigned id) override;
    virtual bool createNewOrder(OrderPtr order) override;
    virtual bool updateOrder(OrderPtr order) override;

    virtual CommandPtrVtr getCommands() override;
    virtual CommandPtr getCommand(unsigned commandNumber) override;
    virtual CommandPtr getCommandOnWhichEmployeeWorkingOn(EmployeePtr employee) override;
    virtual CommandPtrVtr getCommandsOnWhichEmployeeeWorkingOn(EmployeePtr employee) override;
    virtual CommandPtrVtr getCommands(OrderPtr order) override;
    virtual CommandPtrVtr getCommands(Command::State & state) override;
    virtual CommandPtrVtr getCommandWhichWaitingOnTask(unsigned taskTypeId) override;
    virtual CommandPtrVtr getCommandWhichWaitingOnTasks(std::vector<unsigned> taskTypeIds) override;
    virtual bool isThereCommandWhichWaitingOnTask(unsigned taskTypeId) override;
    virtual bool isCommandUpToDate(CommandPtr command) override;
    virtual bool createNewCommand(CommandPtr command) override;
    virtual bool canCommandBeModified(CommandPtr command) override;
    virtual bool updateCommand(CommandPtr command, bool noteModifiedTime=true) override;
    virtual bool deleteCommand(CommandPtr command) override;
    virtual bool sendToWaitForProduction(CommandPtr command) override;
    virtual bool sendToKomercial(CommandPtr command) override;
    virtual bool stopCommand(CommandPtr command) override;
    virtual bool sendToProduction(CommandPtr command) override;
    virtual bool completeCurrentTask(CommandPtr command, unsigned quantity) override;
    virtual bool leaveCurrentTask(CommandPtr command, EmployeePtr employee, unsigned quantity) override;
    virtual bool startWorkingOnWaitingTask(CommandPtr command, EmployeePtr employee) override;

    virtual TaskPtrVtr getTasks() override;
    virtual TaskPtrVtr getTasks(CommandPtr command) override;
    virtual TaskPtr getCurrentTask(CommandPtr command) override;
    virtual bool returnTaskToWorker(TaskPtr task, CommandPtr command, TaskPtrVtr tasks) override;
    virtual bool annulTask(TaskPtr task, CommandPtr command, TaskPtrVtr tasks) override;
    virtual bool createNewTask(TaskPtr task, unsigned employeeID) override;
    virtual bool updateTask(TaskPtr task) override;
    virtual bool updateTaskIfModyfied(TaskPtr task) override;
    virtual bool deleteTask(TaskPtr task) override;

    virtual InvoicePtrVtr getInvoices(CommandPtr command) override;
    virtual InvoicePtrVtr getInvoices(TaskPtr task) override;
    virtual bool createNewInvoice(InvoicePtr invoice) override;
    virtual bool updateInvoice(InvoicePtr invoice) override;
    virtual bool deleteInvoice(InvoicePtr invoice) override;

    virtual TaskTypesPtr getTaskTypes() override;

    virtual MachinePtrVtr getMachines() override;
    virtual MachinePtrVtr getMachines(unsigned taskTypeId) override;
    virtual MachinePtr getMachine(unsigned id) override;
    virtual bool createMachine(MachinePtr machine) override;
    virtual bool updateMachine(MachinePtr machine) override;

protected:
    EmployeePtrVtr createEmployeesFromQuery(QSqlQuery& query);

private:
    std::shared_ptr<QSqlDatabase> m_db;
    QString m_lastError;
};
