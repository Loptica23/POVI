#pragma once
#include <QRunnable>
#include <atomic>
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
    void stopEngine();
private:
    bool  checkIsFinished();

    unsigned time;
    MachineVtrPtr m_machines;
    ResultVector m_resultVector;

    std::atomic_bool m_keepRunning;

};
}
