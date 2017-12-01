#include "machinemanager.h"
#include "types.h"
#include "machine.h"
#include "command.h"
#include "utils.h"
#include <QDebug>

TimeSimulator::MachineManager::MachineManager() :
    m_machines(new MachineVtr())
{

}

TimeSimulator::MachineManager::~MachineManager()
{

}

bool TimeSimulator::MachineManager::decrementTime(const QDateTime& moment)
{
    bool managerFinised = true;
    CommandVtrPtr commands(new CommandVtr());
    for (auto & machine : *m_machines)
    {
        auto temp = machine->decrementTime(moment);
        commands->insert(commands->end(), temp->begin(), temp->end());
    }

    for (auto & command : *commands)
    {
        if (command != nullptr)
        {
            qDebug() << moment.toString() << "  ----  Prelazi sa masine";
            QString machineName = command->getNextTaskMachine();
            if (!machineName.isEmpty())
            {
                MachinePtr newMachine = getMachine(machineName);
                newMachine->putCommandIntoQueue(command);
            }
            else
            {
                command->setFinishMoment(moment);
            }
        }
    }

    for (auto & machine : *m_machines)
    {
        machine->lockNLoadMachine();
        if (!machine->checkIsFinished())
        {
            managerFinised = false;
        }
    }

    return !managerFinised;
}

void TimeSimulator::MachineManager::addMachine(const QString &name, bool isVirtual, QTime startTime, QTime endTime, unsigned workingDays)
{
    if (isMachineExists(name))
    {
        qDebug() << "WARNING: Masina vec postoji!";
    }
    else
    {
        MachinePtr machine(new Machine(name, isVirtual, startTime, endTime, workingDays));
        m_machines->push_back(machine);
    }
}

bool TimeSimulator::MachineManager::isMachineExists(const QString & name)
{
    bool result = false;
    if (getMachine(name) != nullptr)
    {
        result = true;
    }
    return result;
}

TimeSimulator::MachinePtr TimeSimulator::MachineManager::getMachine(const QString &name)
{
    return Utils::findElementInVectorPtr(m_machines, name, &Machine::getName);
}

void TimeSimulator::MachineManager::removeCommand(CommandPtr command)
{
    for (auto & machine : *m_machines)
    {
        machine->eliminateCommandFromCalculation(command);
    }
}
