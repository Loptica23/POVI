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

    void addMachine(QString & name, bool isVirtual);
    bool isMachineExists(QString & name);
    MachinePtr getMachine(QString & name);

private:
    MachineVtrPtr m_machines;
};

}
