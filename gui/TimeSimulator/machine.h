#pragma once
#include <memory>
#include <vector>
#include "timesimulator_global.h"
#include "types.h"

namespace TimeSimulator
{

class TIMESIMULATORSHARED_EXPORT Machine
{
public:
    Machine();
    virtual ~Machine();
    MachinePtr mp;

    bool checkIsEverythingSetUp();

private:
    CommandVtrPtr m_commands;
};

}
