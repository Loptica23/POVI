#pragma once
#include <QRunnable>
#include "timesimulator_global.h"
#include "types.h"

namespace TimeSimulator
{

class TIMESIMULATORSHARED_EXPORT CommandTerminationTimeEngine : public QRunnable
{
public:
    CommandTerminationTimeEngine();
    virtual ~CommandTerminationTimeEngine();

    void setMachines(MachineVtrPtr machines);

    void run();

    bool checkIsEverythingSetUp();
private:
    MachineVtrPtr m_machines;
    ResultVector m_resultVector;
};

}