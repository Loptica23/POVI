#include <QDebug>
#include "commandterminationtimeengine.h"
#include "machine.h"

TimeSimulator::CommandTerminationTimeEngine::CommandTerminationTimeEngine()
{
    qDebug() << "konstruktor engine!";
}

TimeSimulator::CommandTerminationTimeEngine::~CommandTerminationTimeEngine()
{

}

void TimeSimulator::CommandTerminationTimeEngine::setMachines(MachineVtrPtr machines)
{
    m_machines = machines;
}

void TimeSimulator::CommandTerminationTimeEngine::run()
{
    qDebug() << "run method!";
}

bool TimeSimulator::CommandTerminationTimeEngine::checkIsEverythingSetUp()
{
    for (auto iter = m_machines->begin(); iter != m_machines->end(); ++iter)
    {
        MachinePtr machine = *iter;
        if (!machine->checkIsEverythingSetUp())
            return false;
    }

    return true;
}
