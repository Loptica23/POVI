#pragma once
#include <QString>
#include "types.h"


namespace TimeSimulator
{

class CommandManager
{
public:
    CommandManager();
    virtual ~CommandManager();

    void addCommand(unsigned id, unsigned commandNumber, unsigned priority);
    void addTask(const QString & machine, unsigned idCommand, unsigned serialNumber, unsigned prediction, TaskState state);
    bool isCommandExists(unsigned id);
    CommandPtr getCommand(unsigned id);
    CommandVtrPtr checkIsEverythingSetUp();

private:
    CommandVtrPtr m_commands;
};

}
