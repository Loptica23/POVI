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


    void addMachine(QString & name, bool isVirtual);
    void addCommand(unsigned commandNumber, unsigned priority);
    void addTask(QString & machin, unsigned serilaNumber, unsigned prediction);

private:
    QThreadPool *m_threadPool;
    TimeEnginePtr m_timeEngine;
};

}
