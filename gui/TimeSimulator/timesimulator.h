#pragma once
#include <QThreadPool>
#include "timesimulator_global.h"
#include "types.h"

namespace TimeSimulator
{

class TIMESIMULATORSHARED_EXPORT TimeSimulator
{
public:
    TimeSimulator();
    virtual ~TimeSimulator();

    void execute();
    bool checkIsEverythingSetUp();

    void addMachine(const QString & name, bool isVirtual);
    void addCommand(unsigned id, unsigned commandNumber, unsigned priority);
    void addTask(const QString & machine, unsigned idCommand, unsigned serilaNumber, unsigned prediction, TaskState state);

private:
    QThreadPool *m_threadPool;
    TimeEnginePtr m_timeEngine;
};

}
