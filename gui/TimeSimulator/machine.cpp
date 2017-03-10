#include "machine.h"
#include "command.h"

TimeSimulator::Machine::Machine()
{

}

TimeSimulator::Machine::~Machine()
{

}

bool TimeSimulator::Machine::checkIsEverythingSetUp()
{
    for (auto iter = m_commands->begin(); iter != m_commands->end(); ++iter)
    {
        CommandPtr command = *iter;
        if (!command->checkIsEverythingSetUp())
            return false;
    }

    return true;
}
