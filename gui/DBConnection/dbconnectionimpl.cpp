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

CommandPtr DBConnectionImpl::getCommandOnWhichEmployeeWorkingOn(EmployeePtr employee)
{
    CommandPtr command = nullptr;
    CommandPtrVtr commands;
    QSqlQuery queryForTasks;
    QSqlQuery queryForCommands;
    QString stm;
    stm = "select Nalog_idNalog from zadatak where Radnik_idRadnik = " + QString::number(employee->getId());
    stm += " and Stanje = 'izr';";
    qDebug() << stm;
    queryForTasks.prepare(stm);

    stm = "select * from nalog where idNalog in (";
    if(queryForTasks.exec())
    {
        while(queryForTasks.next())
        {
            stm += queryForTasks.value("Nalog_idNalog").toString() + ",";
        }
        stm.chop(1);
        stm += ");";

        queryForCommands.prepare(stm);
        if(queryForCommands.exec())
        {
            commands = Command::createCommandsFromQuery(queryForCommands);
            if (!commands->empty())
            {
                command = commands->at(0);
            }
        }
        else
        {
            qDebug() << "neuspeo kveri!!";
        }
    }
    else
    {
        qDebug() << "neuspeo kveri!!";
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

CommandPtrVtr DBConnectionImpl::getCommandWhichWaitingOnTask(unsigned taskTypeId)
{
    CommandPtrVtr commands;
    QSqlQuery queryGetTasks;
    QSqlQuery queryGetCommands;
    QString stm("select Nalog_idNalog from zadatak where TipoviZadatka_idTipoviZadatka = ");
    stm += QString::number(taskTypeId);
    stm += " and Stanje = 'cek';";
    qDebug() << stm;

    queryGetTasks.prepare(stm);
    if (!queryGetTasks.exec())
    {
        qDebug() << "neuspesno!";
        m_lastError = queryGetTasks.lastError().text();
        return commands;
    }

    stm = "select * from Nalog where idNalog in (";
    while (queryGetTasks.next())
    {
        stm += queryGetTasks.value("Nalog_idNalog").toString() + ",";
    }
    stm.chop(1);
    stm += ");";
    qDebug() << stm;

    queryGetCommands.prepare(stm);
    if (!queryGetCommands.exec())
    {
        qDebug() << "neuspesno!";
        m_lastError = queryGetCommands.lastError().text();
        return commands;
    }

    commands = Command::createCommandsFromQuery(queryGetCommands);
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

bool DBConnectionImpl::deleteCommand(CommandPtr command)
{
    QSqlQuery query;
    query.prepare(command->statementForDeleting());
    if (!query.exec())
    {
        m_lastError = query.lastError().text();
        return false;
    }
    return true;
}

bool DBConnectionImpl::completeCurrentTask(CommandPtr command)
{
    TaskPtrVtr tasks = getTasks(command);
    TaskPtr task;
    TaskPtr task1;
    if (tasks->empty())
    {
        qDebug() << "Nalog nema zadatke!";
        return false;
    }

    for (auto iter = tasks->begin(); iter != tasks->end(); ++iter)
    {
        task = *iter;
        //ako je ovaj uslov ispunjen radi se o prvom zadatku
        if (task->getState() == Task::State::New)
        {
            qDebug() << "postavljnje zadatka na cekanje!";
            task->setState(Task::State::Waiting);
            command->setState(Command::State::InProgress);
            break;
        }

        //nije rec o prvom zadatku!
        if (task->getState() == Task::State::InProgress)
        {
            qDebug() << "postavljnje zadatka na zavrseno!";
            task->setState(Task::State::Complited);
            task->setCurrentTimeForComplited();
            ++iter;
            if (iter == tasks->end())
            {
                command->setState(Command::State::Complited);
            }
            else
            {
                task1 = *iter;
                task1->setState(Task::State::Waiting);
            }
            break;
        }
    }

    //refactor (ovaj kod dole se stalno ponavlja!!)
    if (task->isModified())
    {
        if (!updateTask(task))
        {
            qDebug() << "update task nije uspeo!";
            return false;
        }
    }
    if (command->isModified())
    {
        if (!updateCommand(command))
        {
            qDebug() << "update command nije uspeo!";
            return false;
        }
    }
    if (task1 && task1->isModified())
    {
        if (!updateTask(task1))
        {
            qDebug() << "update task1 nije uspeo!";
            return false;
        }
    }
    return true;
}

bool DBConnectionImpl::leaveCurrentTask(CommandPtr command, EmployeePtr employee)
{
    TaskPtrVtr tasks = getTasks(command);
    TaskPtr task;
    TaskPtr newTask;
    auto serialNumber = 150;
    for (auto iter = tasks->begin(); iter != tasks->end(); ++iter)
    {
        task = *iter;
        if (serialNumber == 150)
        {
            if (task->getState() == Task::State::InProgress)
            {
                qDebug() << "postavljnje zadatka u ostavljeno stanje!";
                serialNumber = task->getSerialNumber();
                task->setState(Task::State::Leaved);
                task->setCurrentTimeForComplited();
                newTask.reset(new Task(command, task->getTaskTypeId()));
                newTask->setSerialNumber(++serialNumber);
                newTask->setState(Task::State::Waiting);
                if (!createNewTask(newTask, employee->getId()))
                {
                    return false;
                }
                if (!updateTask(task))
                {
                    return false;
                }
                qDebug() << "postavljnje zadatka u ostavljeno stanje!";
            }
        }
        else
        {
            //znaci da smo sada u stanju inkrementiranja rednog broja zadatka
            qDebug() << "uvecavanje rednog broja zadatka!!";
            task->setSerialNumber(++serialNumber);
            if (!updateTask(task)) return false;
        }
    }

    return true;
}

bool DBConnectionImpl::startWorkingOnWaitingTask(CommandPtr command, EmployeePtr employee)
{
    TaskPtrVtr tasks = getTasks(command);
    if (tasks->empty())
    {
        qDebug() << "Nalog nema zadatke!";
        return false;
    }
    for (auto iter = tasks->begin(); iter != tasks->end(); ++iter)
    {
        TaskPtr task = *iter;
        if (task->getState() == Task::State::Waiting)
        {
            task->setState(Task::State::InProgress);
            task->setWorkerId(employee->getId());
            task->setCurrentTimeForStarted();
            updateTask(task);
        }
    }

    qDebug() << "nije nadjen ni jedan zadatak u waiting stanju!";
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

