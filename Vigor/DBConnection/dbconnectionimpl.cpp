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
    return m_lastError;
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

EmployeePtr DBConnectionImpl::logIn(QString username, QString pwd)
{
    EmployeePtr result = nullptr;
    QSqlQuery query("select * from radnik");
    if(query.exec())
    {
        EmployeePtrVtr employees = Employee::createEmployeesFromQuery(query);
        for (auto iter = employees->begin(); iter != employees->end(); ++iter)
        {
            if (username == (*iter)->getUserName())
            {
                if ((*iter)->checkPWD(pwd))
                {
                    result = (*iter);
                    break;
                }
            }
        }
    }
    else
    {
        qDebug() << "nije uspeo query!";
    }
    return result;
}

EmployeePtrVtr DBConnectionImpl::getEmployees()
{
    EmployeePtrVtr employees;
    QSqlQuery query;
    query.prepare("select * from radnik");
    if(query.exec())
    {
        employees = Employee::createEmployeesFromQuery(query);
    }
    else
    {
        qDebug() << "nije uspeo query!";
    }
    return employees;
}

bool DBConnectionImpl::createNewEmployee(EmployeePtr employee)
{
    QSqlQuery query;
    query.prepare(employee->statemantForCreatingThisUser());
    if (!query.exec())
    {
        m_lastError = query.lastError().text();
        return false;
    }
    return true;
}

bool DBConnectionImpl::updateEmployee(EmployeePtr employee)
{
    QSqlQuery query;
    query.prepare(employee->statemantForUpdatingThisUser());
    if (!query.exec())
    {
        m_lastError = query.lastError().text();
        return false;
    }
    return true;
}

CustomerPtrVtr DBConnectionImpl::getCustomers()
{
    CustomerPtrVtr customers;
    QSqlQuery query;
    query.prepare("select * from klijent");
    if(query.exec())
    {
        customers = Customer::createCustomersFromQuery(query);
    }
    else
    {
        qDebug() << "nije uspeo query!";
    }
    return customers;
}

bool DBConnectionImpl::createNewCustomer(CustomerPtr customer)
{
    QSqlQuery query;
    query.prepare(customer->statemantForCreating());
    if (!query.exec())
    {
        m_lastError = query.lastError().text();
        return false;
    }
    return true;
}

bool DBConnectionImpl::updateCustomer(CustomerPtr customer)
{
    QSqlQuery query;
    query.prepare(customer->statemantForUpdating());
    if (!query.exec())
    {
        m_lastError = query.lastError().text();
        return false;
    }
    return true;
}

OrderPtrVtr DBConnectionImpl::getOrders()
{
    OrderPtrVtr orders;
    QSqlQuery query;
    query.prepare("select * from narudzbina");
    if(query.exec())
    {
        orders = Order::createOrdersFromQuery(query);
    }
    else
    {
        qDebug() << "nije uspeo query!";
    }
    return orders;
}

OrderPtrVtr DBConnectionImpl::getOrders(CustomerPtr customer)
{
    OrderPtrVtr orders;
    QSqlQuery query;
    QString stm = "select * from narudzbina where idKlijent = " + QString::number(customer->getId());
    qDebug() << stm;
    query.prepare(stm);
    if(query.exec())
    {
        orders = Order::createOrdersFromQuery(query);
    }
    else
    {
        qDebug() << "nije uspeo query!";
    }
    return orders;
}

bool DBConnectionImpl::createNewOrder(OrderPtr order)
{
    QSqlQuery query;
    query.prepare(order->statemantForCreating());
    if (!query.exec())
    {
        m_lastError = query.lastError().text();
        return false;
    }
    return true;
}

bool DBConnectionImpl::updateOrder(OrderPtr order)
{
    QSqlQuery query;
    query.prepare(order->statemantForUpdating());
    if (!query.exec())
    {
        m_lastError = query.lastError().text();
        return false;
    }
    return true;
}

CommandPtr DBConnectionImpl::getCommand(unsigned commandNumber)
{
    CommandPtr command = nullptr;
    CommandPtrVtr commands;
    QSqlQuery query;
    QString stm = "select * from nalog where BrojNaloga = " + QString::number(commandNumber) + ";";
    qDebug() << stm;
    query.prepare(stm);
    if(query.exec())
    {
        commands = Command::createCommandsFromQuery(query);
        if (!commands->empty())
        {
            command = commands->at(0);
        }
    }
    else
    {
        qDebug() << "nije uspeo query!!";
    }
    return command;
}

CommandPtrVtr DBConnectionImpl::getCommands()
{
    CommandPtrVtr commands;
    QSqlQuery query;
    query.prepare("select * from nalog");
    if(query.exec())
    {
        commands = Command::createCommandsFromQuery(query);
    }
    else
    {
        qDebug() << "nije uspeo query!!";
    }
    return commands;
}

CommandPtrVtr DBConnectionImpl::getCommands(OrderPtr order)
{
    CommandPtrVtr commands;
    QSqlQuery query;
    query.prepare("select * from nalog where idNarudzbina = " + QString::number(order->getID()));
    if(query.exec())
    {
        commands = Command::createCommandsFromQuery(query);
    }
    else
    {
        qDebug() << "nije uspeo query!";
    }
    return commands;
}

bool DBConnectionImpl::createNewCommand(CommandPtr command)
{
    QSqlQuery query;
    query.prepare(command->statemantForCreating());
    if (!query.exec())
    {
        m_lastError = query.lastError().text();
        return false;
    }
    return true;
}

bool DBConnectionImpl::updateCommand(CommandPtr command)
{
    QSqlQuery query;
    query.prepare(command->statemantForUpdating());
    if (!query.exec())
    {
        m_lastError = query.lastError().text();
        return false;
    }
    return true;
}

bool DBConnectionImpl::completeCurrentTask(CommandPtr command)
{
    //refactor
    qDebug() << "zavrsen zadatak";
    TaskPtrVtr tasks = getTasks(command);
    qDebug() << "dohvaceni zadacai!";
    if (tasks->empty())
    {
        qDebug() << "Nalog nema zadatke!";
        return false;
    }
    for (auto iter = tasks->begin(); iter != tasks->end(); ++iter)
    {
        qDebug() << "Nalog je verovatno iz stanja New presao u in progress";
        TaskPtr task = *iter;
        if (task->getState() == Task::State::New)
        {
            task->setState(Task::State::Waiting);
            command->setState(Command::State::InProgress);
            if (task->isModified())
            {
                if (!updateTask(task))
                {
                    return false;
                }
            }
            if (command->isModified())
            {
                if (!updateCommand(command))
                {
                    return false;
                }
            }
            return true;
        }

        if (task->getState() == Task::State::InProgress)
        {
            task->setState(Task::State::Complited);
            if (task->isModified())
            {
                if (!updateTask(task))
                {
                    return false;
                }
            }
            ++iter;
            if (iter == tasks->end())
            {
                command->setState(Command::State::Complited);
            }
            else
            {
                task = *iter;
                task->setState(Task::State::Waiting);
                if (task->isModified())
                {
                    if (!updateTask(task))
                    {
                        return false;
                    }
                }
                if (command->isModified())
                {
                    if (!updateCommand(command))
                    {
                        return false;
                    }
                }
            }
            return true;
        }
    }

    return false;
}

TaskPtrVtr DBConnectionImpl::getTasks()
{
    //ova metoda ne bi trebala da se poziva.. zasto bi neko pravio pregled svih taskova?
    TaskPtrVtr tasks;
    return tasks;
}

TaskPtrVtr DBConnectionImpl::getTasks(CommandPtr command)
{
    TaskPtrVtr tasks;
    QSqlQuery query;
    QString stm("select * from zadatak where Nalog_idNalog = ");
    stm += QString::number(command->getID());
    stm += " order by RedniBroj;";
    query.prepare(stm);
    qDebug() << stm;
    if (query.exec())
    {
        tasks = Task::createTaskFromQueryAndCommand(query, command);
    }
    else
    {
        qDebug() << "nije uspeo query!";
    }
    return tasks;
}

bool DBConnectionImpl::createNewTask(TaskPtr task, unsigned employeeID)
{
    QSqlQuery query;
    query.prepare(task->statemantForCreating(employeeID));
    if (!query.exec())
    {
        m_lastError = query.lastError().text();
        return false;
    }
    return true;
}

bool DBConnectionImpl::updateTask(TaskPtr task)
{
    QSqlQuery query;
    query.prepare(task->statemantForUpdating());
    if (!query.exec())
    {
        m_lastError = query.lastError().text();
        return false;
    }
    return true;
}

bool DBConnectionImpl::deleteTask(TaskPtr task)
{
    QSqlQuery query;
    query.prepare(task->statementForDeleting());
    if (!query.exec())
    {
        m_lastError = query.lastError().text();
        return false;
    }
    return true;
}

TaskTypesPtr DBConnectionImpl::getTaskTypes() const
{
    TaskTypesPtr tasktypes = nullptr;
    QSqlQuery query;
    query.prepare("select * from TipoviZadatka order by idTipoviZadatka");
    if(query.exec())
    {
        tasktypes.reset(new TaskTypes(query));
    }
    return tasktypes;
}

