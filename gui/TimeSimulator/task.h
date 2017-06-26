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
    Task(const QString & machine, unsigned serilaNumber, unsigned prediction, TaskState state);
    virtual ~Task();

    const QString &getMachine() const;
    unsigned getPrediction() const;

    TaskState getState() const;
    void setState(const TaskState & state);
    void setPrediction(unsigned prediction);

    bool checkIsEverythingSetUp();
    bool decrementTime();

    static bool compareFunction(TaskPtr task1, TaskPtr task2);
private:

    QString m_machine;
    unsigned m_serialNumber;
    unsigned m_prediction;
    TaskState m_state;
};

}
