#pragma once
#include <memory>
#include <vector>
#include "timesimulator_global.h"
#include "types.h"

namespace TimeSimulator
{

class TIMESIMULATORSHARED_EXPORT Command
{
public:
    Command(unsigned id, unsigned priority);
    virtual ~Command();

    bool checkIsEverythingSetUp();
    bool decrementTimeOfCurrentTask();

    unsigned getIdOfNextMachine();
    TaskPtr getCurrentTask();
    unsigned getPriority();

private:
    TaskPtr changeCurrentTask();

    unsigned m_id;
    TaskVtrPtr m_tasks;
    TaskVtr::iterator m_iterator;
    unsigned m_priority;
    unsigned m_commandNumber;
};

}
