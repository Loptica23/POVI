#include <memory>
#include <QVariant>
#include <QDebug>
#include "task.h"
#include "command.h"


Task::Task(CommandPtr command, unsigned taskType):
    m_command(command),
    m_taskType(taskType),
    m_workerId(-1),
    m_prediction(0),
    m_machineId(-1),
    m_state(State::New)
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

//seters
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

QString Task::statemantForCreating() const
{
    QString stm;
    stm = "insert into zadatak (Nalog_idNalog, Nalog_idNarudzbina, Nalog_idKlijent,"
          "TipoviZadatka_idTipoviZadatka) values (";
    stm += QString::number(getCommand()->getID()) + ", ";
    stm += QString::number(getCommand()->getIdOrder()) + ", ";
    stm += QString::number(getCommand()->getIdCustomer()) + ", ";
    stm += QString::number(getTaskTypeId());
    stm += ")";
    return stm;
}

QString Task::statemantForUpdating() const
{
    QString stm;
    return stm;
}

bool Task::isModified() const
{
    return (m_workerIdChanged ||
            m_predictionChanged ||
            m_machineIdChanged ||
            m_stateChanged);
}

void Task::resetChangeTracking()
{
    m_workerIdChanged = false;
    m_predictionChanged = false;
    m_machineIdChanged = false;
    m_stateChanged = false;
}

TaskPtrVtr Task::createTaskFromQueryAndCommand(QSqlQuery& query, CommandPtr command)
{
    TaskPtrVtr tasks(new TaskVtr());
    while(query.next())
    {
        TaskPtr task(new Task(command, query.value("TipoviZadatka_idTipoviZadatka").toUInt()));
        task->setWorkerId(query.value("Radnik_idRadnik").toUInt()); //imaj u vidu da ova informacija ne mora da postoji
        task->setPrediction(query.value("Procena").toUInt()); //imaj u vidu da ova informacija ne mora da postoji
        task->setMachineId(query.value("Masina_idMasina").toUInt()); //imaj u vidu da ova informacija ne mora da postoji
        //ovo nije kraj ima jos setera..
        tasks->push_back(task);
    }
    return tasks;
}
