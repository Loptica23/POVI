#include "command.h"
#include "task.h"

TimeSimulator::Command::Command()
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
