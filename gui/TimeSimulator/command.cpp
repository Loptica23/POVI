#include <QDebug>
#include "command.h"
#include "task.h"

TimeSimulator::Command::Command(unsigned id, unsigned commandNumber, unsigned priority):
    m_id(id),
    m_commandNumber(commandNumber),
    m_priority(priority),
    m_tasks(new TaskVtr())
{

}

TimeSimulator::Command::~Command()
{

}

bool TimeSimulator::Command::checkIsEverythingSetUp()
{
    for (const auto & task : *m_tasks)
    {
        if (!task->checkIsEverythingSetUp())
            return false;
    }

    return true;
}

//ako vrati false znaci da je stigao do nule (jos u predhodnom koraku)
bool TimeSimulator::Command::decrementTimeOfCurrentTask()
{
    return getCurrentTask()->decrementTime();
}

//ako se vrati prazan string to znaci da ne postoji sledeci zadatak!
const QString TimeSimulator::Command::getNextTaskMachine()
{
    QString machine = "";
    if (changeCurrentTask())
    {
        machine = getCurrentTask()->getMachine();
    }
    return machine;
}

TimeSimulator::TaskPtr TimeSimulator::Command::getCurrentTask()
{
    return m_currentTask;
}

unsigned TimeSimulator::Command::getPriority()
{
    return m_priority;
}

unsigned TimeSimulator::Command::getId() const
{
    return m_id;
}

unsigned TimeSimulator::Command::getCommandNumber() const
{
    return m_commandNumber;
}

unsigned TimeSimulator::Command::getCompareMember() const
{
    return getId();
}

QDateTime TimeSimulator::Command::getFinishMoment() const
{
    return m_finishMoment;
}

void TimeSimulator::Command::setFinishMoment(const QDateTime& moment)
{
    m_finishMoment = moment;
    qDebug() << "Nalog sa brojem: " + QString::number(getCommandNumber()) + " je zavrsen u momentu " + moment.toString();
}

void TimeSimulator::Command::addTask(const QString & machine, unsigned serilaNumber, unsigned prediction, TaskState state)
{
    TaskPtr task(new Task(machine, serilaNumber, prediction, state));
    if ((task->getState() == TaskState::New) || (task->getState() == TaskState::Waiting) || (task->getState() == TaskState::InProgress))
    {
        m_tasks->push_back(task);
    }
    if ((task->getState() == TaskState::Waiting) || (task->getState() == TaskState::InProgress))
    {
        m_currentTask = task;
    }
}

bool TimeSimulator::Command::changeCurrentTask()
{
    //refactor
    bool result = false;
    bool  find = false;
    for (auto & task : *m_tasks)
    {
        if (find)
        {
            m_currentTask = task;
            result = true;
            break;
        }
        if (task->getSerialNumber() == m_currentTask->getSerialNumber())
        {
            find = true;
        }
    }
    return result;
}
