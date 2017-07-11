#pragma once
#include <memory>
#include <vector>
#include <QString>
#include "types.h"

namespace TimeSimulator
{

class Machine
{
public:
    Machine(const QString & name, bool isVirtual);
    virtual ~Machine();

    CommandVtrPtr decrementTime();
    bool checkIsFinished();

    const QString& getName() const;
    bool isVirtual() const;
    const QString & getCompareMember() const;

    void putCommandIntoQueue(CommandPtr command);
    void putCurrentCommand(CommandPtr command);
    void eliminateCommandFromCalculation(CommandPtr command);
    void lockNLoadMachine();

private:
    CommandVtrPtr decrementTimeForVirtualMachine();
    CommandPtr decrementTimeForNormalMachine();
    CommandPtr getFirstFromQueue();
    void sortCommandsByPriority();
    static bool compareFunction(CommandPtr command1, CommandPtr command2);

    QString m_name;
    bool m_isVirtual;

    CommandVtrPtr m_commandsInQueue;
    CommandPtr m_currentCommand;
};

}
