#pragma once
#include <vector>
#include <QString>
#include <QTime>
#include "types.h"

namespace TimeSimulator
{

class MachineManager
{
public:
    MachineManager();
    virtual ~MachineManager();

    bool decrementTime(const QDateTime& moment);

    void addMachine(const QString & name, bool isVirtual, QTime startTime, QTime endTime, unsigned workingDays);
    bool isMachineExists(const QString & name);
    MachinePtr getMachine(const QString & name);
    void removeCommand(CommandPtr command);

private:
    MachineVtrPtr m_machines;
};

}
