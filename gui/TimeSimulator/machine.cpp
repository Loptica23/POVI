#include <QDebug>
#include "machine.h"
#include "command.h"
#include "task.h"

TimeSimulator::Machine::Machine(const QString & name, bool isVirtual, QTime startTime, QTime endTime, unsigned workingDays):
    m_name(name),
    m_isVirtual(isVirtual),
    m_startTime(startTime),
    m_endTime(endTime),
    m_workingDays(workingDays),
    m_commandsInQueue(new CommandVtr()),
    m_commandsInProgress(new CommandVtr())
{

}

TimeSimulator::Machine::~Machine()
{

}

TimeSimulator::CommandVtrPtr TimeSimulator::Machine::decrementTime(const QDateTime &moment)
{
    CommandVtrPtr result (new CommandVtr());
    if (isMachineWorking(moment))
    {
        for (auto command : *m_commandsInProgress)
        {
            if (!command->decrementTimeOfCurrentTask())
            {
                qDebug() << "Zavrsen zadatak u nalogu: " << QString::number(command->getCommandNumber());
                result->push_back(command);
            }
        }

        for (auto command : *result)
        {
            m_commandsInProgress->erase(std::remove_if(m_commandsInProgress->begin(), m_commandsInProgress->end(),
               [command](const auto param) {
                                    return command->getCommandNumber() == param->getCommandNumber();
                                }), m_commandsInProgress->end());
        }
    }
    return result;
}

bool TimeSimulator::Machine::checkIsFinished()
{
    bool result = false;
    if (m_commandsInProgress->empty() && m_commandsInQueue->empty()) result = true;
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

bool TimeSimulator::Machine::isMachineWorking(const QDateTime &moment) const
{
    bool result = true;

    if ((m_startTime != m_endTime) && !((moment.time() < m_endTime) && (moment.time() > m_startTime)))
    {
        result = false;
    }
    else if (moment.date().dayOfWeek() > (int)m_workingDays)
    {
        result = false;
    }

    return result;
}

void TimeSimulator::Machine::lockNLoadMachine()
{
    sortCommandsByPriority();
    auto commands = getWaitingCommandsWhichShouldBegin();
    m_commandsInProgress->insert(m_commandsInProgress->begin(), commands->begin(), commands->end());
    for (auto command : *commands)
    {
        m_commandsInQueue->erase(std::remove_if(m_commandsInQueue->begin(), m_commandsInQueue->end(),
           [command](const auto param) {
                                return command->getCommandNumber() == param->getCommandNumber();
                            }), m_commandsInQueue->end());
    }
}

void TimeSimulator::Machine::sortCommandsByPriority()
{
    std::sort(m_commandsInQueue->begin(), m_commandsInQueue->end(), compareFunction);
}

TimeSimulator::CommandVtrPtr TimeSimulator::Machine::getWaitingCommandsWhichShouldBegin()
{
    CommandVtrPtr commands(new CommandVtr());
    if (m_isVirtual)
    {
        for (auto command : *m_commandsInQueue)
        {
            auto taskTypeId = command->getCurrentTask()->getTaskTypeId();
            auto numberOfCommandInProgressWithSameTaskTypeId = 0;
            for (auto inProgressCommand : *m_commandsInProgress)
            {
                if (inProgressCommand->getCurrentTask()->getTaskTypeId() == taskTypeId)
                {
                    numberOfCommandInProgressWithSameTaskTypeId++;
                }
            }
            if (numberOfCommandInProgressWithSameTaskTypeId < command->getCurrentTask()->getParallelism())
            {
                commands->push_back(command);
            }
        }
    }
    else
    {
        if (m_commandsInProgress->empty())
        {
            if (!m_commandsInQueue->empty())
            {
                commands->push_back(m_commandsInQueue->at(0));
            }
        }
    }

    return commands;
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

void TimeSimulator::Machine::putCommandIntoProgress(CommandPtr command)
{
    m_commandsInProgress->push_back(command);
}

void TimeSimulator::Machine::eliminateCommandFromCalculation(CommandPtr command)
{
    auto it = std::find(m_commandsInQueue->begin(), m_commandsInQueue->end(), command);
    if(it != m_commandsInQueue->end())
        m_commandsInQueue->erase(it);
    it = std::find(m_commandsInProgress->begin(), m_commandsInProgress->end(), command);
    if(it != m_commandsInProgress->end())
        m_commandsInProgress->erase(it);
}
