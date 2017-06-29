#pragma once;
#include <vector>
#include <QString>
#include "types.h"

namespace TimeSimulator
{

class MachineManager
{
public:
    MachineManager();
    virtual ~MachineManager();

    bool decrementTime();

    void addMachine(const QString & name, bool isVirtual);
    bool isMachineExists(const QString & name);
    MachinePtr getMachine(const QString & name);
    void removeCommand(CommandPtr command);

private:
    MachineVtrPtr m_machines;
};

}
