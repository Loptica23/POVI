#pragma once
#include <QRunnable>
#include <atomic>
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
    void stopEngine();

    bool checkIsEverythingSetUp();

    void addMachine(QString & name, bool isVirtual);
    void addCommand(unsigned id, unsigned commandNumber, unsigned priority);
    void addTask(const QString &machine, unsigned idCommand, unsigned serialNumber, unsigned prediction, TaskState state);

private:
    MachineManagerPtr m_machineManager;
    CommandManagerPtr m_commandManager;
    std::atomic<bool> m_running;
};

}
