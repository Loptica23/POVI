#include "command.h"
#include "task.h"

TimeSimulator::Command::Command(unsigned id):
    m_id(id)
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

//ako se vrati 0 to znaci da ne postoji sledeci zadatak!
unsigned TimeSimulator::Command::getIdOfNextMachine()
{
    unsigned id = 0;
    if (changeCurrentTask())
    {
        id = getCurrentTask()->getMachine();
    }
    return id;
}

TimeSimulator::TaskPtr TimeSimulator::Command::getCurrentTask()
{
    TaskPtr task = *m_iterator;
    return task;
}

TimeSimulator::TaskPtr TimeSimulator::Command::changeCurrentTask()
{
    TaskPtr task = nullptr;
    ++m_iterator;
    if (m_iterator != m_tasks->end())
    {
        task = *m_iterator;
    }
    return task;
}
