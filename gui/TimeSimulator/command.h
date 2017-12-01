#pragma once
#include <memory>
#include <vector>
#include <QDateTime>
#include "timesimulator_global.h"
#include "types.h"

namespace TimeSimulator
{

class TIMESIMULATORSHARED_EXPORT Command
{
public:
    Command(unsigned id, unsigned commandNumber, unsigned priority);
    virtual ~Command();

    bool checkIsEverythingSetUp();
    bool decrementTimeOfCurrentTask();

    const QString getNextTaskMachine();
    TaskPtr getCurrentTask();
    unsigned getPriority();
    unsigned getId() const;
    unsigned getCommandNumber() const;
    unsigned getCompareMember() const;
    QDateTime getFinishMoment() const;

    void setFinishMoment(const QDateTime& moment);
    void addTask(const QString & machine, unsigned serilaNumber, unsigned prediction, TaskState state);

private:
    bool changeCurrentTask();

    unsigned m_id;
    unsigned m_commandNumber;
    unsigned m_priority;
    QDateTime m_finishMoment;
    TaskVtrPtr m_tasks;
    TaskPtr m_currentTask;
};

}
