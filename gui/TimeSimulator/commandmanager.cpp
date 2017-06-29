#include "commandmanager.h"
#include "command.h"
#include "utils.h"
#include <QDebug>

TimeSimulator::CommandManager::CommandManager() :
    m_commands(new CommandVtr())
{

}

TimeSimulator::CommandManager::~CommandManager()
{

}

void TimeSimulator::CommandManager::addCommand(unsigned id, unsigned commandNumber, unsigned priority)
{
    if (isCommandExists(id))
    {
        qDebug () << "WARNING: Command exists!";
    }
    else
    {
        CommandPtr command(new Command(id, commandNumber, priority));
        m_commands->push_back(command);
    }
}

void TimeSimulator::CommandManager::addTask(const QString & machine, unsigned idCommand, unsigned serialNumber, unsigned prediction, TaskState state)
{
    if (isCommandExists(idCommand))
    {
        CommandPtr command = getCommand(idCommand);
        command->addTask(machine, serialNumber, prediction, state);
    }
    else
    {
        qDebug() << "WARNING Ne postoji trazen nalog!";
    }
}

bool TimeSimulator::CommandManager::isCommandExists(unsigned id)
{
    bool result = false;
    if (getCommand(id) != nullptr)
    {
        result = true;
    }
    return result;
}

TimeSimulator::CommandPtr TimeSimulator::CommandManager::getCommand(unsigned id)
{
    return Utils::findElementInVectorPtr(m_commands, id, &Command::getId);
}

TimeSimulator::CommandVtrPtr TimeSimulator::CommandManager::checkIsEverythingSetUp()
{
    CommandVtrPtr commandsWhichIsNotSetUp(new CommandVtr());
    for (const auto & command: *m_commands)
    {
        if (!command->checkIsEverythingSetUp())
        {
            commandsWhichIsNotSetUp->push_back(command);
        }
    }
    return commandsWhichIsNotSetUp;
}
