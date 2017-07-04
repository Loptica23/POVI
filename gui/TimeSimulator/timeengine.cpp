#include <QDebug>
#include "timeengine.h"
#include "machinemanager.h"
#include "commandmanager.h"
#include "machine.h"


unsigned TimeSimulator::TimeEngine::moment = 0;

TimeSimulator::TimeEngine::TimeEngine() :
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
    //refactor: mozda ovde da isproveravas masine i naloge, da li su dati svi podaci i tako to.
    moment = 0;
    while(m_running)
    {
        qDebug() << "MOMENT: " + QString::number(moment);
        m_running = m_machineManager->decrementTime(moment);
        ++moment;
    }
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

void TimeSimulator::TimeEngine::addMachine(const QString & name, bool isVirtual)
{
    m_machineManager->addMachine(name, isVirtual);
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
