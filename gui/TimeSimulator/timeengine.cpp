#include <QDebug>
#include "timeengine.h"
#include "machinemanager.h"
#include "commandmanager.h"

TimeSimulator::TimeEngine::TimeEngine() :
    m_machineManager(new MachineManager()),
    m_commandManager(new CommandManager())

{

}

TimeSimulator::TimeEngine::~TimeEngine()
{

}

void TimeSimulator::TimeEngine::run()
{

}

bool TimeSimulator::TimeEngine::checkIsEverythingSetUp()
{
    bool result = false;
    return result;
}

void TimeSimulator::TimeEngine::addMachine(QString & name, bool isVirtual)
{
    m_machineManager->addMachine(name, isVirtual);
}

void TimeSimulator::TimeEngine::addCommand(unsigned id, unsigned commandNumber, unsigned priority)
{
    m_commandManager->addCommand(id,commandNumber, priority);
}

void TimeSimulator::TimeEngine::addTask(QString & machin, unsigned idCommand, unsigned serilaNumber, unsigned prediction, TaskState state)
{
    if (m_machineManager->isMachineExists(machin))
    {
        m_commandManager->addTask(machin, idCommand, serilaNumber, prediction, state);
    }
    else
    {
        qDebug() << "WARNING: Ne postoji takva masina!";
    }
}
