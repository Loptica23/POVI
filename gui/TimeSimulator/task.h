#pragma once
#include <memory>
#include <vector>
#include "timesimulator_global.h"
#include "types.h"

namespace TimeSimulator
{

class TIMESIMULATORSHARED_EXPORT Task
{
public:
    enum class State{New, InProgress, Complited};

    Task(unsigned machine, unsigned serialNumber);
    virtual ~Task();

    unsigned getMachine() const;
    unsigned getPrediction() const;

    State getState() const;
    void setState(const State & state);
    void setPrediction(unsigned prediction);

    bool checkIsEverythingSetUp();
    bool decrementTime();

    static bool compareFunction(TaskPtr task1, TaskPtr task2);
private:

    unsigned m_machine;
    unsigned m_prediction;
    unsigned m_serialNumber;
    State m_state;
};

}
