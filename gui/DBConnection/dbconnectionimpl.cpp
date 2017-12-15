#include <QString>
#include <QtSql/QSqlDatabase>
#include <QDebug>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include "dbconnectionimpl.h"

DBConnectionImpl::DBConnectionImpl()
    : m_machinesTaskTypes (nullptr)
{

}

DBConnectionImpl::~DBConnectionImpl()
{
    if (m_db && m_db->isOpen())
    {
        m_db->close();
    }
}

const QString DBConnectionImpl::getLastError() const
{
    return m_lastError;
}

bool DBConnectionImpl::conectToDb(QString userName, QString pwd)
{
    bool result = false;
    if (m_db && m_db->isOpen())
    {
        m_db->close();
    }
    m_db = std::make_shared<QSqlDatabase>( QSqlDatabase::addDatabase("QMYSQL"));       // ne mozes jebeno ovako
    m_db->setHostName(m_host);
    m_db->setDatabaseName(m_databaseName);
    m_db->setUserName(userName);
    m_db->setPassword("23" + pwd + "23");
    result =  m_db->open();
    if (!result)
        m_lastError = m_db->lastError().text();
    return result;
}

EmployeePtr DBConnectionImpl::logIn(QString username, QString pwd)
{
    EmployeePtr result = nullptr;
    QString stm;
    stm = "select * from radnik where KorisnickoIme = ";
    stm += "'" + username + "'";
    stm += " and Sifra = ";
    stm += "'" + pwd + "'";
    stm += ";";
    qDebug() << stm;
    QSqlQuery query(stm);
    if(query.exec())
    {
        EmployeePtrVtr employees = Employee::createEmployeesFromQuery(query);
        for (auto iter = employees->begin(); iter != employees->end(); ++iter)
        {
            result = *iter;
            break;
        }
    }
    else
    {
        m_lastError = query.lastError().text();
        qDebug() << "nije uspeo query!";
    }
    return result;
}

EmployeePtrVtr DBConnectionImpl::getEmployees()
{
    EmployeePtrVtr employees;
    QSqlQuery query;
    query.prepare("select * from radnik  order by ime;");
    if(query.exec())
    {
        employees = Employee::createEmployeesFromQuery(query);
    }
    else
    {
        m_lastError = query.lastError().text();
        qDebug() << "nije uspeo query!";
    }
    return employees;
}

EmployeePtrVtr DBConnectionImpl::getEmployees(Employee::WorkPosition workPosition)
{
    EmployeePtrVtr employees;
    QSqlQuery query;
    QString statemant = "select * from radnik where Pozicija = '" + Employee::getQstringFromWorkPosition(workPosition) + "';";
    qDebug() << statemant;
    query.prepare(statemant);
    if(query.exec())
    {
        employees = Employee::createEmployeesFromQuery(query);
    }
    else
    {
        m_lastError = query.lastError().text();
        qDebug() << "nije uspeo query!";
    }
    return employees;
}

EmployeePtr DBConnectionImpl::getEmployee(QString username)
{
    EmployeePtr employee = nullptr;
    EmployeePtrVtr employees = nullptr;
    QSqlQuery query;
    QString stm = "select * from radnik where KorisnickoIme = '" + username + "';";
    qDebug() << stm;
    query.prepare(stm);
    if(query.exec())
    {
        employees = Employee::createEmployeesFromQuery(query);
    }
    else
    {
        m_lastError = query.lastError().text();
        qDebug() << "nije uspeo query!";
        qDebug() << m_lastError;
    }
    if (employees && !employees->empty())
    {
        employee = employees->at(0);
    }

    return employee;
}

EmployeePtr DBConnectionImpl::getEmployee(unsigned id)
{
    EmployeePtr employee = nullptr;
    EmployeePtrVtr employees = nullptr;
    QSqlQuery query;
    QString stm = "select * from radnik where idRadnik = '" + QString::number(id) + "';";
    qDebug() << stm;
    query.prepare(stm);
    if(query.exec())
    {
        employees = Employee::createEmployeesFromQuery(query);
    }
    else
    {
        m_lastError = query.lastError().text();
        qDebug() << "nije uspeo query!";
        qDebug() << m_lastError;
    }
    if (employees && !employees->empty())
    {
        employee = employees->at(0);
    }

    return employee;
}

bool DBConnectionImpl::createNewEmployee(EmployeePtr employee)
{
    QSqlQuery query;
    query.prepare(employee->statemantForCreatingUser());
    if (!query.exec())
    {
        qDebug() << "neuspelo kreiranje radnika!";
        m_lastError = query.lastError().text();
        return false;
    }
    return true;
}

bool DBConnectionImpl::updateEmployee(EmployeePtr employee)
{
    QSqlQuery query;
    query.prepare(employee->statemantForUpdatingUser());
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
    query.prepare("select * from klijent order by Ime");
    if(query.exec())
    {
        customers = Customer::createCustomersFromQuery(query);
    }
    else
    {
        m_lastError = query.lastError().text();
        qDebug() << "nije uspeo query!";
    }
    return customers;
}

CustomerPtr DBConnectionImpl::getCustomer(unsigned id)
{
    CustomerPtrVtr customers;
    CustomerPtr customer = nullptr;
    QSqlQuery query;
    query.prepare("select * from klijent where idKlijent = " + QString::number(id) + ";");
    if(query.exec())
    {
        customers = Customer::createCustomersFromQuery(query);
    }
    else
    {
        m_lastError = query.lastError().text();
        qDebug() << "nije uspeo query!";
    }
    if (!customers->empty())
    {
        customer = customers->front();
    }
    return customer;
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
        m_lastError = query.lastError().text();
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
        m_lastError = query.lastError().text();
        qDebug() << "nije uspeo query!";
    }
    return orders;
}

OrderPtr DBConnectionImpl::getOrder(unsigned id)
{
    OrderPtr order;
    OrderPtrVtr orders;
    QSqlQuery query;
    QString stm = "select * from narudzbina where idNarudzbina = " + QString::number(id);
    qDebug() << stm;
    query.prepare(stm);
    if(query.exec())
    {
        orders = Order::createOrdersFromQuery(query);
    }
    else
    {
        m_lastError = query.lastError().text();
        qDebug() << "nije uspeo query!";
    }
    if (!orders->empty())
    {
        order = *(orders->begin());

    }
    return order;
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
        m_lastError = query.lastError().text();
        qDebug() << "nije uspeo query!!";
    }
    return command;
}

CommandPtr DBConnectionImpl::getCommandOnWhichEmployeeWorkingOn(EmployeePtr employee)
{
    CommandPtr command = nullptr;
    CommandPtrVtr commands;
    commands = getCommandsOnWhichEmployeeeWorkingOn(employee);
    if (!commands->empty())
    {
        command = commands->at(0);
    }
    return command;
}

CommandPtrVtr DBConnectionImpl::getCommandsOnWhichEmployeeeWorkingOn(EmployeePtr employee)
{
    CommandPtrVtr commands(new CommandVtr());
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
        }
        else
        {
            m_lastError = queryForCommands.lastError().text();
            qDebug() << "neuspeo kveri!!";
        }
    }
    else
    {
        m_lastError = queryForTasks.lastError().text();
        qDebug() << "neuspeo kveri!!";
    }
    return commands;
}

CommandPtrVtr DBConnectionImpl::getCommands()
{
    CommandPtrVtr commands;
    QSqlQuery query;
    QString stm = "select SQL_NO_CACHE  * from nalog";
    query.prepare(stm);
    if(query.exec())
    {
        commands = Command::createCommandsFromQuery(query);
    }
    else
    {
        m_lastError = query.lastError().text();
        qDebug() << "nije uspeo query!!";
    }
    return commands;
}

CommandPtrVtr DBConnectionImpl::getCommands(OrderPtr order)
{
    CommandPtrVtr commands;
    QSqlQuery query;
    QString stm = "select * from nalog where idNarudzbina = " + QString::number(order->getID());
    qDebug() << stm;
    query.prepare(stm);
    if(query.exec())
    {
        commands = Command::createCommandsFromQuery(query);
    }
    else
    {
        m_lastError = query.lastError().text();
        qDebug() << "nije uspeo query!";
    }
    return commands;
}

CommandPtrVtr DBConnectionImpl::getCommands(Command::State & state)
{
    CommandPtrVtr commands;
    QSqlQuery query;
    QString stm = "select * from nalog where Stanje = '" + Command::convertStateToString(state) + "';";
    qDebug() << stm;
    query.prepare(stm);
    if(query.exec())
    {
        commands = Command::createCommandsFromQuery(query);
    }
    else
    {
        m_lastError = query.lastError().text();
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
    stm += ")";
    stm += " and Stanje = 'izr';";
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

CommandPtrVtr DBConnectionImpl::getCommandWhichWaitingOnTasks(std::vector<unsigned> taskTypeIds)
{
    CommandPtrVtr commands(new CommandVtr());
    QSqlQuery queryGetTasks;
    QSqlQuery queryGetCommands;
    QString stm("select Nalog_idNalog from zadatak where (TipoviZadatka_idTipoviZadatka = ");
    for (auto iter = taskTypeIds.begin(); iter != taskTypeIds.end(); ++iter)
    {
        QString id = QString::number(*iter);
        stm += id;
        stm += " or TipoviZadatka_idTipoviZadatka = ";
    }
    stm.chop(36);
    stm += ") and Stanje = 'cek';";
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
    stm += ")";
    stm += " and Stanje = 'izr' ";
    stm += "order by prioritet;";
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

bool DBConnectionImpl::isThereCommandWhichWaitingOnTask(unsigned taskTypeId)
{
    QSqlQuery queryGetTasks;
    QString stm("select Nalog_idNalog from zadatak where TipoviZadatka_idTipoviZadatka = ");
    stm += QString::number(taskTypeId);
    stm += " and Stanje = 'cek';";
    qDebug() << stm;
    queryGetTasks.prepare(stm);
    if (!queryGetTasks.exec())
    {
        qDebug() << "neuspesno!";
        m_lastError = queryGetTasks.lastError().text();
        return false;
    }

    if (queryGetTasks.next())
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool DBConnectionImpl::isCommandUpToDate(CommandPtr command)
{
    bool result = false;
    CommandPtr dbCommand = getCommand(command->getCommandNumber());
    if (dbCommand->getDateTimeLastUpdated() == command->getDateTimeLastUpdated())
    {
        result = true;
    }
    return result;
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

bool DBConnectionImpl::canCommandBeModified(CommandPtr command)
{
    bool result = false;
    CommandPtr original = getCommand(command->getCommandNumber());
    if (original->getDateTimeLastUpdated() == command->getDateTimeLastUpdated())
    {
        result = true;
    }
    return result;
}

bool DBConnectionImpl::updateCommand(CommandPtr command, bool noteModifiedTime)
{
    QSqlQuery query;
    query.prepare(command->statemantForUpdating(noteModifiedTime));
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

bool DBConnectionImpl::sendToWaitForProduction(CommandPtr command)
{
    if (command->getState() != Command::State::New)
    {
        m_lastError = "Komanda mora biti u stanju NEW da bi mogla da se prebaci u WAITFORPRODUCTION stanje.";
        qDebug() << m_lastError;
        return false;
    }
    command->setState(Command::State::WaitForProduction);
    return updateCommand(command);
}

bool DBConnectionImpl::sendToKomercial(CommandPtr command)
{
    if (!((command->getState() == Command::State::Stopped) || (command->getState() == Command::State::WaitForProduction)))
    {
        m_lastError = "Komanda mora biti u stanju Stopped ili WaitForProduction da bi mogla da se prebaci u New stanje.";
        qDebug() << m_lastError;
        return false;
    }
    command->setState(Command::State::New);
    return updateCommand(command);
}

bool DBConnectionImpl::stopCommand(CommandPtr command)
{
    if (command->getState() != Command::State::InProgress)
    {
        m_lastError = "Komanda mora biti u stanju InProgress da bi mogla da se prebaci u Stopped stanje.";
        qDebug() << m_lastError;
        return false;
    }
    command->setState(Command::State::Stopped);
    return updateCommand(command);
}

bool DBConnectionImpl::sendToProduction(CommandPtr command)
{
    if (!((command->getState() == Command::State::Stopped) || (command->getState() == Command::State::WaitForProduction)))
    {
        m_lastError = "Komanda mora biti u stanju Stopped ili WaitForProduction da bi mogla da se prebaci u InProgress stanje.";
        qDebug() << m_lastError;
        return false;
    }
    command->setState(Command::State::InProgress);
    auto tasks = getTasks(command);
    auto task = (*tasks->begin());
    if (task->getState() == Task::State::New)
    {
        //command is new and first task state must be changed to Waiting
        task->setState(Task::State::Waiting);
    }
    return updateCommand(command) && updateTaskIfModyfied(task);
}

bool DBConnectionImpl::completeCurrentTask(CommandPtr command, unsigned quantity)
{
    TaskPtrVtr tasks = getTasks(command);
    TaskPtr task;
    TaskPtr task1;
    if (tasks == nullptr || tasks->empty())
    {
        qDebug() << "Nalog nema zadatke!";
        return false;
    }
    if (!((command->getState() == Command::State::Stopped) || (command->getState() == Command::State::InProgress)))
    {
        m_lastError = "Da bi se zadatak mogao poslati u stanje complete potrebno je da nalog bude u stanju stopped ili u stanju inProgress.";
        qDebug() << m_lastError;
        return false;
    }
    //refactor -- izmeni ovu petlju na dve funkcije tipa dohvati trenutni zadatak, poslaji prvi nov zadatak u waiting stanje
    //         -- i na kraju treca funkcija ako su svi zadaci u zavrsenom stanju possalji ceo nalog u zavrseno stanje
    for (auto iter = tasks->begin(); iter != tasks->end(); ++iter)
    {
        task = *iter;
        if (task->getState() == Task::State::InProgress)
        {
            qDebug() << "postavljnje zadatka na zavrseno!";
            task->setState(Task::State::Complited);
            task->setCurrentTimeForComplited();
            task->setQuantity(quantity);
            while (++iter != tasks->end())
            {
                task1 = *iter;
                if (task1->getState() == Task::State::New)
                {
                    task1->setState(Task::State::Waiting);
                    break;
                }
            }
            if (iter == tasks->end())
            {
                command->setState(Command::State::Complited);
            }
            break;
        }
    }

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

bool DBConnectionImpl::leaveCurrentTask(CommandPtr command, EmployeePtr employee, unsigned quantity)
{
    qDebug() << "leave current task";
    //new code same function
    auto tasks = getTasks(command);

    //setting up leaved task
    auto task = getCurrentTask(command);
    if (task == nullptr)
        return false;
    task->setState(Task::State::Leaved);
    task->setCurrentTimeForComplited();
    task->setQuantity(quantity);
    auto serialNumber = task->getSerialNumber();
    if (!updateTask(task))
    {
        return false;
    }

    //setting up new Task
    auto newTask = std::make_shared<Task>(command, task->getTaskTypeId());
    newTask->setSerialNumber(++serialNumber);
    newTask->setState(Task::State::Waiting);
    newTask->setMachineId(task->getMachineId());
    auto msecconds = task->getStartTime().msecsTo(QDateTime::currentDateTime());
    unsigned minutes = msecconds/(1000*60);
    int leftPredictedTime = task->getPrediction();
    leftPredictedTime -= minutes;
    if (leftPredictedTime > 0)
        newTask->setPrediction(leftPredictedTime);

    for (auto t: *tasks)
    {
        if (t->getSerialNumber() == serialNumber)
        {
            t->setSerialNumber(++serialNumber);
            if (!updateTask(t)) return false;
        }
    }


    if (!createNewTask(newTask, employee->getId()))
    {
        return false;
    }

    return true;
}

bool DBConnectionImpl::startWorkingOnWaitingTask(CommandPtr command, EmployeePtr employee)
{
    if (!isCommandUpToDate(command))
    {
        return false;
    }
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
            return true;
        }
    }

    qDebug() << "nije nadjen ni jedan zadatak u waiting stanju!";
    return false;
}

TaskPtrVtr DBConnectionImpl::getTasks()
{
    //ova metoda ne bi trebala da se poziva.. zasto bi neko pravio pregled svih taskova?
    TaskPtrVtr tasks;
    qDebug() << "***************pozvana je ne implementirana metoda ****************";
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

TaskPtr DBConnectionImpl::getCurrentTask(CommandPtr command)
{
    TaskPtrVtr tasks = getTasks(command);
    TaskPtr currentTask = nullptr;

    for(const auto& task: *tasks)
    {
        if ((task->getState() == Task::State::Waiting) || (task->getState() == Task::State::InProgress))
        {
            currentTask = task;
        }
    }

    return currentTask;
}

bool DBConnectionImpl::returnTaskToWorker(TaskPtr task, CommandPtr command, TaskPtrVtr tasks)
{
    TaskPtr currentTask = nullptr;
    for (auto t: *tasks)
    {
        if (t->getState() == Task::State::Waiting)
        {
            currentTask = t;
        }
    }

    if (currentTask == nullptr)
        return false;

    currentTask->setState(Task::State::New);
    task->setState(Task::State::InProgress);

    InvoicePtrVtr invoices = getInvoices(task);
    for (auto inv : *invoices)
    {
        deleteInvoice(inv);
    }


    if (!updateTask(currentTask))
    {
        return false;
    }

    if (!updateTask(task))
    {
        return false;
    }

    //paiz kako komplitujes zadatak.. moras da stavis na cekanje prvi koji je u stanju nov..
    //to ne znaci da je u pitanju sledeci zadatak
    //cakk se moze desiti da je rec o poslednjem zadatku, u tom slucaju treba setovati ceo nalog u stanje zav
    return true;
}

bool DBConnectionImpl::annulTask(TaskPtr task, CommandPtr command, TaskPtrVtr tasks)
{
    TaskPtr currentTask = nullptr;
    for (auto t: *tasks)
    {
        if (t->getState() == Task::State::Waiting)
        {
            currentTask = t;
        }
    }

    if (currentTask == nullptr)
        return false;

    currentTask->setState(Task::State::New);
    task->setState(Task::State::Waiting);

    InvoicePtrVtr invoices = getInvoices(task);
    for (auto inv : *invoices)
    {
        deleteInvoice(inv);
    }


    if (!updateTask(currentTask))
    {
        return false;
    }

    if (!updateTask(task))
    {
        return false;
    }

    //paiz kako komplitujes zadatak.. moras da stavis na cekanje prvi koji je u stanju nov..
    //to ne znaci da je u pitanju sledeci zadatak
    //cakk se moze desiti da je rec o poslednjem zadatku, u tom slucaju treba setovati ceo nalog u stanje zav
    return true;
}

bool DBConnectionImpl::createNewTask(TaskPtr task, unsigned employeeID)
{
    QSqlQuery query;
    QString stm = task->statemantForCreating(employeeID);
    qDebug() << stm;
    query.prepare(stm);
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

//return false only if query fails
bool DBConnectionImpl::updateTaskIfModyfied(TaskPtr task)
{
    auto result = true;
    if (task->isModified())
    {
        result = updateTask(task);
    }
    return result;
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

InvoicePtrVtr DBConnectionImpl::getInvoices(CommandPtr command)
{
    InvoicePtrVtr invoices(new InvoiceVtr());
    auto tasks = getTasks(command);
    for (auto task: (*tasks))
    {
        auto invs = getInvoices(task);
        invoices->insert(invoices->end(), invs->begin(), invs->end());
    }
    return invoices;
}

InvoicePtrVtr DBConnectionImpl::getInvoices(TaskPtr task)
{
    InvoicePtrVtr invoices(new InvoiceVtr());
    QSqlQuery query;
    QString stm("select * from faktura where Zadatak_idZadatak = ");
    stm += QString::number(task->getId()) + ";";
    query.prepare(stm);
    qDebug() << stm;
    if (query.exec())
    {
        invoices = Invoice::createInvoicesFromQueryAndCommand(query, task);
    }
    else
    {
        qDebug() << "nije uspeo query!";
    }
    return invoices;
}

bool DBConnectionImpl::createNewInvoice(InvoicePtr invoice)
{
    QSqlQuery query;
    query.prepare(invoice->statemantForCreating());
    if (!query.exec())
    {
        m_lastError = query.lastError().text();
        return false;
    }
    return true;
}

bool DBConnectionImpl::updateInvoice(InvoicePtr invoice)
{
    QSqlQuery query;
    query.prepare(invoice->statemantForUpdating());
    if (!query.exec())
    {
        m_lastError = query.lastError().text();
        return false;
    }
    return true;
}

bool DBConnectionImpl::deleteInvoice(InvoicePtr invoice)
{
    QSqlQuery query;
    query.prepare(invoice->statementForDeleting());
    if (!query.exec())
    {
        m_lastError = query.lastError().text();
        return false;
    }
    return true;
}

TaskTypesPtr DBConnectionImpl::getTaskTypes()
{
    TaskTypesPtr tasktypes = nullptr;
    QSqlQuery query;
    query.prepare("select * from TipoviZadatka order by idTipoviZadatka");
    if(query.exec())
    {
        tasktypes.reset(new TaskTypes(query));
    }
    else
    {
        qDebug() << "nije uspeo query!";
        m_lastError = query.lastError().text();
    }
    return tasktypes;
}

bool DBConnectionImpl::createTaskType(TaskTypePtr taskType)
{
    QSqlQuery query;
    query.prepare(taskType->statemantForCreating());
    if (!query.exec())
    {
        m_lastError = query.lastError().text();
        return false;
    }
    return true;
}

bool DBConnectionImpl::updateTaskType(TaskTypePtr taskType)
{
    QSqlQuery query;
    query.prepare(taskType->statemantForUpdating());
    if (!query.exec())
    {
        m_lastError = query.lastError().text();
        return false;
    }
    return true;
}

bool DBConnectionImpl::deleteTaskType(TaskTypePtr taskType)
{
    QSqlQuery query;
    query.prepare(taskType->statemantForDeleting());
    if (!query.exec())
    {
        m_lastError = query.lastError().text();
        return false;
    }
    return true;
}

MachinePtrVtr DBConnectionImpl::getMachines()
{
    MachinePtrVtr machines = nullptr;
    QSqlQuery query;
    query.prepare("select * from masina;");
    if(query.exec())
    {
        machines = Machine::createMachineFromQuery(query);
    }
    else
    {
        qDebug() << "nije uspeo query!";
        m_lastError = query.lastError().text();
    }
    return machines;
}

MachinePtrVtr DBConnectionImpl::getMachines(unsigned taskTypeId)
{
    MachinePtrVtr machines = nullptr;
    QSqlQuery query;
    QString stm = "select * from masina where ";    
    auto machineIds = getMachineIdsForTaskType(taskTypeId);
    for (auto machineId : machineIds)
    {
        stm += "idMasina = " + QString::number(machineId) + " or ";
    }
    stm.chop(4);
    stm += ";";
    qDebug() << stm;
    query.prepare(stm);
    if(query.exec())
    {
        machines = Machine::createMachineFromQuery(query);
    }
    else
    {
        qDebug() << "nije uspeo query!";
        m_lastError = query.lastError().text();
    }
    return machines;
}

MachinePtr DBConnectionImpl::getMachine(unsigned id)
{
    MachinePtr result = nullptr;
    MachinePtrVtr machines = nullptr;
    QSqlQuery query;
    QString stm = "select * from masina where idMasina = " + QString::number(id) + ";";
    qDebug() << stm;
    query.prepare(stm);
    if(query.exec())
    {
        machines = Machine::createMachineFromQuery(query);
    }
    else
    {
        qDebug() << "nije uspeo query!";
        m_lastError = query.lastError().text();
    }
    if (machines && machines->size() > 0)
    {
        result = *(machines->begin());
    }
    return result;
}

bool DBConnectionImpl::createMachine(MachinePtr machine)
{
    QSqlQuery query;
    query.prepare(machine->statemantForCreating());
    if (!query.exec())
    {
        m_lastError = query.lastError().text();
        return false;
    }
    return true;
}

bool DBConnectionImpl::updateMachine(MachinePtr machine)
{
    QSqlQuery query;
    query.prepare(machine->statemantForUpdating());
    if (!query.exec())
    {
        m_lastError = query.lastError().text();
        return false;
    }
    return true;
}

bool DBConnectionImpl::deleteMachine(MachinePtr machine)
{
    QSqlQuery query;
    query.prepare(machine->statemantForDeleting());
    if (!query.exec())
    {
        m_lastError = query.lastError().text();
        return false;
    }
    return true;
}

MachineTaskTypePtrVtr DBConnectionImpl::getMachineTaskTypes()
{
    MachineTaskTypePtrVtr result = m_machinesTaskTypes;
    if (result == nullptr)
    {
        QSqlQuery query;
        QString stm = "select * from MasinaTipoviZadatka;";
        qDebug() << stm;
        query.prepare(stm);
        if (query.exec())
        {
            result = MachineTaskType::createMachineTaskTypeFromQuery(query);
        }
        else
        {
            qDebug() << "nije uspeo query!";
            m_lastError = query.lastError().text();
        }
    }
    m_machinesTaskTypes = result;
    return result;
}

std::vector<unsigned> DBConnectionImpl::getTasTypesIdsForMachine(MachinePtr machine)
{
    std::vector<unsigned> ids;
    auto machinesTaskTypes = getMachineTaskTypes();
    for (const auto machineTaskType : *machinesTaskTypes)
    {
        if (machine->getId() == machineTaskType->getMachineId())
        {
            ids.push_back(machineTaskType->getTaskTypeId());
        }
    }
    return ids;
}

std::vector<unsigned> DBConnectionImpl::getMachineIdsForTaskType(unsigned taskTypeId)
{
    std::vector<unsigned> ids;
    auto machinesTaskTypes = getMachineTaskTypes();
    for (const auto machineTaskType : *machinesTaskTypes)
    {
        if (taskTypeId == machineTaskType->getTaskTypeId())
        {
            ids.push_back(machineTaskType->getMachineId());
        }
    }
    return ids;
}

bool DBConnectionImpl::createMachineTaskType(MachinePtr machine, unsigned taskTypeId)
{
    QSqlQuery query;
    MachineTaskTypePtr machineTaskType(new MachineTaskType(machine->getId(), taskTypeId));
    query.prepare(machineTaskType->statemantForCreating());
    if (!query.exec())
    {
        m_lastError = query.lastError().text();
        return false;
    }

    m_machinesTaskTypes = nullptr;
    getMachineTaskTypes();
    return true;
}

bool DBConnectionImpl::deleteMahineTaskType(MachinePtr machine, unsigned taskTypeId)
{
    auto machinesTaskTypes = getMachineTaskTypes();
    for (auto it = machinesTaskTypes->begin(); it != machinesTaskTypes->end(); ++it)
    {
        auto machineTaskType = *it;
        if (taskTypeId == machineTaskType->getTaskTypeId() && machine->getId() == machineTaskType->getMachineId())
        {
            QSqlQuery query;
            query.prepare(machineTaskType->statemantForDeleting());
            if (!query.exec())
            {
                m_lastError = query.lastError().text();
                return false;
            }
            machinesTaskTypes->erase(it);
            return true;
        }
    }
    return false;
}
