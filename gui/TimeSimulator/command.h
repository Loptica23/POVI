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
    Command();
    virtual ~Command();

    bool checkIsEverythingSetUp();
private:
    TaskVtrPtr m_tasks;
    unsigned m_priority;
    unsigned m_commandNumber;
};

}
