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
    Machine(QString & name, bool isVirtual);
    virtual ~Machine();

    bool checkIsEverythingSetUp();
    CommandPtr decrementTime();
    bool checkIsFinished();

    unsigned getId() const;

    void putCommandIntoQueue(CommandPtr command);
    void putCurrentCommand(CommandPtr command);
    void eliminateCommandFromCalculation(CommandPtr command);

private:
    CommandPtr getFirstFromQueue();
    void sortCommandsByPriority();
    static bool compareFunction(CommandPtr command1, CommandPtr command2);

    QString m_name;
    bool m_isVirtual;

    CommandVtrPtr m_commandsInQueue;
    CommandPtr m_currentCommand;
};

}
