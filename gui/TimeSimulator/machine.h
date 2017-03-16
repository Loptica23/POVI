#pragma once
#include <memory>
#include <vector>
#include "timesimulator_global.h"
#include "types.h"

namespace TimeSimulator
{

class TIMESIMULATORSHARED_EXPORT Machine
{
public:
    Machine(unsigned id);
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

    unsigned m_id;
    CommandVtrPtr m_commandsInQueue;
    CommandPtr m_currentCommand;
};

}
