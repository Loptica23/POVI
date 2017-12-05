#pragma once
#include <memory>
#include <vector>
#include <QString>
#include <QTime>
#include "types.h"

namespace TimeSimulator
{

class Machine
{
public:
    Machine(const QString & name, bool isVirtual, QTime startTime, QTime endTime, unsigned workingDays);
    virtual ~Machine();

    CommandVtrPtr decrementTime(const QDateTime& moment);
    bool checkIsFinished();

    const QString& getName() const;
    bool isVirtual() const;
    const QString & getCompareMember() const;
    bool isMachineWorking(const QDateTime& moment) const;

    void putCommandIntoQueue(CommandPtr command);
    void putCommandIntoProgress(CommandPtr command);
    void eliminateCommandFromCalculation(CommandPtr command);
    void lockNLoadMachine();

private:
    void sortCommandsByPriority();
    CommandVtrPtr getWaitingCommandsWhichShouldBegin();

    static bool compareFunction(CommandPtr command1, CommandPtr command2);

    QString m_name;
    bool m_isVirtual;
    QTime m_startTime;
    QTime m_endTime;
    unsigned m_workingDays;

    CommandVtrPtr m_commandsInQueue;
    CommandVtrPtr m_commandsInProgress;
    unsigned m_parallelism;
};

}
