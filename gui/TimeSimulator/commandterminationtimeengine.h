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

    void eliminateCommandFromCalculation(CommandPtr command);
    MachinePtr getMachineWithId(unsigned id);
private:
    bool  checkIsFinished();

    unsigned time;
    MachineVtrPtr m_machines;
    ResultVector m_resultVector;
};

}
