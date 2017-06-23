#pragma once
#include <QString>
#include "types.h"

namespace TimeSimulator
{

class TimeEngine
{
public:
    TimeEngine();
    virtual ~TimeEngine();

    void addMachine(QString & name, bool isVirtual);
    void addCommand(unsigned commandNumber, unsigned priority);
    void addTask(QString & machin, unsigned serilaNumber, unsigned prediction);

private:
    MachineManagerPtr m_machineManager;
};

}
