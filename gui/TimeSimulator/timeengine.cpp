#include <QDebug>
#include "timeengine.h"
#include "machinemanager.h"
#include "commandmanager.h"
#include "machine.h"


TimeSimulator::TimeEngine::TimeEngine(QObject* parent) :
    QObject(parent),
    m_machineManager(new MachineManager()),
    m_commandManager(new CommandManager()),
    m_running(true)
{

}

TimeSimulator::TimeEngine::~TimeEngine()
{

}

void TimeSimulator::TimeEngine::run()
{
    m_moment = QDateTime::currentDateTime();
    auto timedOut = m_moment.addYears(1);
    while(m_running)
    {
        m_running = m_machineManager->decrementTime(m_moment);
        m_moment = m_moment.addSecs(60);
        if (m_moment == timedOut)
        {
            qDebug() << "Engine timed out!!";
            break;
        }
    }
    emit sendResult();
}

void TimeSimulator::TimeEngine::stopEngine()
{
    m_running = false;
}

bool TimeSimulator::TimeEngine::checkIsEverythingSetUp()
{
    bool result = true;
    CommandVtrPtr commandsForRemoving = m_commandManager->checkIsEverythingSetUp();
    for (auto & command : *commandsForRemoving)
    {
        m_machineManager->removeCommand(command);
    }
    return result;
}

void TimeSimulator::TimeEngine::addMachine(const QString & name, bool isVirtual, QTime startTime, QTime endTime, unsigned workingDays)
{
    m_machineManager->addMachine(name, isVirtual, startTime, endTime, workingDays);
}

void TimeSimulator::TimeEngine::addCommand(unsigned id, unsigned commandNumber, unsigned priority)
{
    m_commandManager->addCommand(id,commandNumber, priority);
}

void TimeSimulator::TimeEngine::addTask(const QString & machine, unsigned idCommand, unsigned serialNumber, unsigned prediction, TaskState state)
{
    if (m_machineManager->isMachineExists(machine))
    {
        m_commandManager->addTask(machine, idCommand, serialNumber, prediction, state);
        CommandPtr command = m_commandManager->getCommand(idCommand);
        switch(state)
        {
        case TaskState::InProgress:
            m_machineManager->getMachine(machine)->putCurrentCommand(command);
            break;
        case TaskState::Waiting:
            m_machineManager->getMachine(machine)->putCommandIntoQueue(command);
            break;
        default :
            break;
        }

    }
    else
    {
        qDebug() << "WARNING: Ne postoji takva masina!" + machine;
    }
}

TimeSimulator::TimeSimulatorResultMapPtr TimeSimulator::TimeEngine::getResult() const
{
    return m_commandManager->getResultMapPtr();
}
