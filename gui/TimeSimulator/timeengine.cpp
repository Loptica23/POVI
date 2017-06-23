#include "timeengine.h"
#include "machinemanager.h"

TimeSimulator::TimeEngine::TimeEngine() :
    m_machineManager(new MachineManager())
{

}

TimeSimulator::TimeEngine::~TimeEngine()
{

}

void TimeSimulator::TimeEngine::addMachine(QString & name, bool isVirtual)
{
    m_machineManager->addMachine(name, isVirtual);
}

void TimeSimulator::TimeEngine::addCommand(unsigned commandNumber, unsigned priority)
{

}

void TimeSimulator::TimeEngine::addTask(QString & machin, unsigned serilaNumber, unsigned prediction)
{

}
