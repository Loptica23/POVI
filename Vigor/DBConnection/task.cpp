#include <memory>
#include <QVariant>
#include <QDebug>
#include "task.h"
#include "command.h"

//ovaj konstruktor se poziva kada se kreira novi task
Task::Task(CommandPtr command, unsigned taskType):
    m_command(command),
    m_taskType(taskType),
    m_workerId(-1),
    m_prediction(0),
    m_machineId(-1),
    m_state(State::New),
    m_serialNumber(0),
    m_id(-1),
    m_created(true)
{
    resetChangeTracking();
}

//ovaj konstruktor se poziva kada task vec postoji
Task::Task(unsigned id, CommandPtr command, unsigned taskType):
    m_command(command),
    m_taskType(taskType),
    m_workerId(-1),
    m_prediction(0),
    m_machineId(-1),
    m_state(State::New),
    m_serialNumber(0),
    m_id(id),
    m_created(false)
{
    resetChangeTracking();
}

Task::~Task()
{

}

//geters
CommandPtr Task::getCommand() const
{
    CommandPtr command;
    if (!(command = m_command.lock()))
    {
        qDebug() << "ne moze da zakljuca";
        command = nullptr;
    }
    return command;
}

unsigned Task::getTaskTypeId() const
{
    return m_taskType;
}

unsigned Task::getWorkerId() const
{
    return m_workerId;
}

unsigned Task::getPrediction() const
{
    return m_prediction;
}

unsigned Task::getMachineId() const
{
    return m_machineId;
}

const Task::State& Task::getState() const
{
    return m_state;
}

QString Task::getStateString() const
{
    QString st;
    switch(m_state)
    {
    case State::New:
        st = "nov";
        break;
    case State::InProgress:
        st = "izr";
        break;
    case State::Complited:
        st = "zav";
        break;
    case State::Stopped:
        st = "sto";
        break;
    case State::Leaved:
        st = "ost";
        break;
    default:
        qDebug() << "*************NEPOSTOJECE STANJE************";
    }
    return st;
}

unsigned Task::getSerialNumber() const
{
    return m_serialNumber;
}

//seters
void Task::setCommand(CommandPtr command)
{
    m_command = command;
}

void Task::setWorkerId(const unsigned workerId)
{
    if (m_workerId != workerId)
    {
        m_workerIdChanged = true;
        m_workerId = workerId;
    }
}

void Task::setPrediction(const unsigned prediction)
{
    if (m_prediction != prediction)
    {
        m_predictionChanged = true;
        m_prediction = prediction;
    }
}

void Task::setMachineId(const unsigned machineId)
{
    if (m_machineId != machineId)
    {
        m_machineIdChanged = true;
        m_machineId = machineId;
    }
}

void Task::setState(const Task::State &state)
{
    if (m_state != state)
    {
        m_stateChanged = true;
        m_state = state;
    }
}

void Task::setState(const QString &state)
{
    if (state == "nov")
        setState(State::New);
    else if (state == "izr")
        setState(State::InProgress);
    else if (state == "zav")
        setState(State::Complited);
    else if (state == "sto")
        setState(State::Stopped);
    else if (state == "ost")
        setState(State::Leaved);
    else
        qDebug() << "NE MOZE SE SETOVATI NEPOSTOJECE STANJE!";
}

void Task::setSerialNumber(unsigned serialNumber)
{
    if (m_serialNumber != serialNumber)
    {
        m_serialNumberChanged = true;
        m_serialNumber = serialNumber;
    }
}

QString Task::statemantForCreating(unsigned employeeID) const
{
    QString stm;
    stm = "insert into zadatak (Nalog_idNalog, Nalog_idNarudzbina, Nalog_idKlijent,"
          "TipoviZadatka_idTipoviZadatka, Radnik_idRadnik, Stanje, RedniBroj) values (";
    stm += QString::number(getCommand()->getID()) + ", ";
    stm += QString::number(getCommand()->getIdOrder()) + ", ";
    stm += QString::number(getCommand()->getIdCustomer()) + ", ";
    stm += QString::number(getTaskTypeId()) + ", ";
    stm += QString::number(employeeID) + ", ";
    stm += "'" + getStateString() + "', ";
    stm += QString::number(getSerialNumber());
    stm += ");";
    qDebug() << stm;
    return stm;
}

QString Task::statemantForUpdating() const
{
    QString stm;
    return stm;
}

QString Task::statementForDeleting() const
{
    QString stm;
    stm = "delete from zadatak where idZadatak = ";
    stm += QString::number(m_id);
    return stm;
}

bool Task::isModified() const
{
    return (m_workerIdChanged ||
            m_predictionChanged ||
            m_machineIdChanged ||
            m_serialNumberChanged ||
            m_stateChanged);
}

bool Task::isCreated() const
{
    return m_created;
}

void Task::resetChangeTracking()
{
    m_workerIdChanged = false;
    m_predictionChanged = false;
    m_machineIdChanged = false;
    m_stateChanged = false;
    m_serialNumberChanged = false;
}

TaskPtrVtr Task::createTaskFromQueryAndCommand(QSqlQuery& query, CommandPtr command)
{
    TaskPtrVtr tasks(new TaskVtr());
    while(query.next())
    {
        TaskPtr task(new Task(query.value("idZadatak").toUInt(), command, query.value("TipoviZadatka_idTipoviZadatka").toUInt()));
        task->setWorkerId(query.value("Radnik_idRadnik").toUInt()); //imaj u vidu da ova informacija ne mora da postoji
        task->setPrediction(query.value("Procena").toUInt()); //imaj u vidu da ova informacija ne mora da postoji
        task->setMachineId(query.value("Masina_idMasina").toUInt()); //imaj u vidu da ova informacija ne mora da postoji
        task->setState(query.value("Stanje").toString());
        task->setSerialNumber(query.value("RedniBroj").toUInt());
        tasks->push_back(task);
    }
    return tasks;
}
