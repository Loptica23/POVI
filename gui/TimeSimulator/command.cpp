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
    for (auto iter = m_tasks->begin(); iter != m_tasks->end(); ++iter)
    {
        TaskPtr task = *iter;
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
const QString TimeSimulator::Command::getCurrentTaskMachine()
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

void TimeSimulator::Command::setTasks(TaskVtrPtr tasks)
{
    m_tasks = tasks;
    std::sort(m_tasks->begin(), m_tasks->end(), Task::compareFunction);
    m_iterator = m_tasks->begin();
    m_currentTask = *m_iterator;
}

void TimeSimulator::Command::addTask(const QString & machine, unsigned serilaNumber, unsigned prediction, TaskState state)
{

}

bool TimeSimulator::Command::changeCurrentTask()
{
    ++m_iterator;
    if (m_iterator != m_tasks->end())
    {
        m_currentTask = *m_iterator;
        return true;
    }
    return false;
}
