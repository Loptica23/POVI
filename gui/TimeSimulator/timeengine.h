#pragma once
#include <QRunnable>
#include <QString>
#include "types.h"

namespace TimeSimulator
{

class TimeEngine : public QRunnable
{
public:
    TimeEngine();
    virtual ~TimeEngine();

    void run();

    bool checkIsEverythingSetUp();

    void addMachine(QString & name, bool isVirtual);
    void addCommand(unsigned id, unsigned commandNumber, unsigned priority);
    void addTask(QString & machin, unsigned idCommand, unsigned serilaNumber, unsigned prediction, TaskState state);

private:
    MachineManagerPtr m_machineManager;
    CommandManagerPtr m_commandManager;
};

}
