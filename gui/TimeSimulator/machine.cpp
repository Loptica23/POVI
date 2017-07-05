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

TimeSimulator::CommandVtrPtr TimeSimulator::Machine::decrementTime()
{
    CommandVtrPtr result (new CommandVtr());
    if (m_isVirtual)
    {
        result = decrementTimeForVirtualMachine();
    }
    else
    {
        CommandPtr command = decrementTimeForNormalMachine();
        if (command)
        {
            result->push_back(command);
        }
    }
    return result;
}

bool TimeSimulator::Machine::checkIsFinished()
{
    bool result = false;
    if (!m_currentCommand && m_commandsInQueue->empty()) result = true;
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

TimeSimulator::CommandVtrPtr TimeSimulator::Machine::decrementTimeForVirtualMachine()
{
    CommandVtrPtr result (new CommandVtr());
    /*for (auto iter = m_commandsInQueue->begin(); iter != m_commandsInQueue->end(); ++iter)
    {
        CommandPtr command = *iter;
        if (command->decrementTimeOfCurrentTask())
        {
            result->push_back(command);
            m_commandsInQueue->erase(iter);
        }
    }*/
    m_commandsInQueue->erase(std::remove_if(m_commandsInQueue->begin(), m_commandsInQueue->end(), [&](auto & command)
    {
        if (!command->decrementTimeOfCurrentTask())
        {
            result->push_back(command);
            return true;
        }
        return false;
    }), m_commandsInQueue->end());
    return result;
}

TimeSimulator::CommandPtr TimeSimulator::Machine::decrementTimeForNormalMachine()
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

TimeSimulator::CommandPtr TimeSimulator::Machine::getFirstFromQueue()
{
    CommandPtr command = nullptr;
    if (m_commandsInQueue && !m_commandsInQueue->empty())
    {
        command = m_commandsInQueue->at(0);
        m_commandsInQueue->erase(m_commandsInQueue->begin());
        qDebug() << "Nalog sa brojem: " + QString::number(command->getCommandNumber()) + " je poceo da se izvrsava na masini " + getName();
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
    qDebug() << "Nalog sa brojem: " + QString::number(command->getCommandNumber()) + " je dodat u red na masini " + getName();
    m_commandsInQueue->push_back(command);
    sortCommandsByPriority();
}

void TimeSimulator::Machine::putCurrentCommand(CommandPtr command)
{
    if (m_isVirtual)
    {
        qDebug() << "Nalog sa brojem: " + QString::number(command->getCommandNumber()) + " je dodat u red na masini " + getName();
        putCommandIntoQueue(command);
    }
    else
    {
        qDebug() << "Nalog sa brojem :" + QString::number(command->getCommandNumber()) + " je postavljen kao trenutni zadatak na masini " + getName();
        m_currentCommand = command;
    }
}

void TimeSimulator::Machine::eliminateCommandFromCalculation(CommandPtr command)
{
    auto it = std::find(m_commandsInQueue->begin(), m_commandsInQueue->end(), command);
    if(it != m_commandsInQueue->end())
        m_commandsInQueue->erase(it);
    if (m_currentCommand == command)
        m_currentCommand = nullptr;
}
