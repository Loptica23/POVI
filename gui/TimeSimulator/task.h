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

    Task(unsigned machine, unsigned prediction, State state);
    virtual ~Task();

    unsigned getMachine() const;
    unsigned getPrediction() const;
    State getState() const;

    void setState(const State & state);

    bool checkIsEverythingSetUp();
private:
    unsigned m_machine;
    unsigned m_prediction;
    State m_state;
};

}
