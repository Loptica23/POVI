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

    CommandTerminationTimeEnginePtr getCommandTerminationTimeEngine();
    void execute(CommandTerminationTimeEnginePtr commandTerminationTimeEngine);

private:
    QThreadPool *m_threadPool;
};

}
