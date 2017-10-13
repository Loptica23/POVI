#include <QDebug>
#include "timeengine.h"
#include "machinemanager.h"
#include "commandmanager.h"
#include "machine.h"

//ne sme biti staticka!!!
unsigned TimeSimulator::TimeEngine::moment = 0;

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
    //refactor: mozda ovde da isproveravas masine i naloge, da li su dati svi podaci i tako to.
    moment = 1;
    while(m_running)
    {
        qDebug() << "MOMENT: " + QString::number(moment);
        m_running = m_machineManager->decrementTime(moment);
        ++moment;
        if (moment == 2147483647)
        {
            qDebug() << "Engine timed out!!";
            break;
        }
    }

    //ovde moras da notifajerujes glavnu nit! vidi kako ces to!
    //potrebna su ti dva flega a ne jedan, kako bi znao da li je nasilno zavrsen task ili je izvrsen normalno!
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

TimeSimulator::TimeSimulatorResultMapPtr TimeSimulator::TimeEngine::getResult() const
{
    return m_commandManager->getResultMapPtr();
}
