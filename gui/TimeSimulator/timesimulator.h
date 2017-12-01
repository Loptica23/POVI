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

    void addMachine(const QString & name, bool isVirtual, QTime startTime, QTime endTime, unsigned workingDays);
    void addCommand(unsigned id, unsigned commandNumber, unsigned priority);
    void addTask(const QString & machine, unsigned idCommand, unsigned serilaNumber, unsigned prediction, TaskState state);

    const TimeEngine *getSender() const;
    TimeSimulatorResultMapPtr getResult() const;
private:
    QThreadPool *m_threadPool;
    TimeEnginePtr m_timeEngine;
};

}
