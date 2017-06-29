#include <QDebug>
#include "machine.h"
#include "command.h"

TimeSimulator::Machine::Machine(const QString &name, bool isVirtual):
    m_name(name),
    m_isVirtual(isVirtual),
    m_currentCommand(nullptr),
    m_commandsInQueue(new CommandVtr())
{

}

TimeSimulator::Machine::~Machine()
{

}

TimeSimulator::CommandPtr TimeSimulator::Machine::decrementTime()
{
    CommandPtr command = nullptr;
    if (m_currentCommand && !m_currentCommand->decrementTimeOfCurrentTask())
    {
        command = m_currentCommand;
        m_currentCommand = getFirstFromQueue();
    }

    if (!m_currentCommand)
        m_currentCommand = getFirstFromQueue();

    return command;
}

bool TimeSimulator::Machine::checkIsFinished()
{
    bool result = false;
    if (!m_currentCommand) result = true;
    return  result;
}

const QString& TimeSimulator::Machine::getName() const
{
    return m_name;
}

bool TimeSimulator::Machine::isVirtual() const
{
    return m_isVirtual;
}

const QString & TimeSimulator::Machine::getCompareMember() const
{
    return getName();
}

TimeSimulator::CommandPtr TimeSimulator::Machine::getFirstFromQueue()
{
    CommandPtr command = nullptr;
    if (m_commandsInQueue && !m_commandsInQueue->empty())
    {
        command = m_commandsInQueue->at(0);
        m_commandsInQueue->erase(m_commandsInQueue->begin());
        qDebug() << "Nalog sa idjem: " + QString::number(command->getId()) + " je poceo da se izvrsava na masini ";
    }
    return command;
}

void TimeSimulator::Machine::sortCommandsByPriority()
{
    std::sort(m_commandsInQueue->begin(), m_commandsInQueue->end(), compareFunction);
}

bool TimeSimulator::Machine::compareFunction(CommandPtr command1, CommandPtr command2)
{
    return command1->getPriority() < command2->getPriority();
}

void TimeSimulator::Machine::putCommandIntoQueue(CommandPtr command)
{
    m_commandsInQueue->push_back(command);
    sortCommandsByPriority();
}

void TimeSimulator::Machine::putCurrentCommand(CommandPtr command)
{
    m_currentCommand = command;
}

void TimeSimulator::Machine::eliminateCommandFromCalculation(CommandPtr command)
{
    auto it = std::find(m_commandsInQueue->begin(), m_commandsInQueue->end(), command);
    if(it != m_commandsInQueue->end())
        m_commandsInQueue->erase(it);
    if (m_currentCommand == command)
        m_currentCommand = nullptr;
}
