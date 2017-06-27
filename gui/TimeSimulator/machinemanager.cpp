#include "machinemanager.h"
#include "types.h"
#include "machine.h"
#include "command.h"
#include <QDebug>

TimeSimulator::MachineManager::MachineManager() :
    m_machines(new MachineVtr())
{

}

TimeSimulator::MachineManager::~MachineManager()
{

}

bool TimeSimulator::MachineManager::decrementTime()
{
    bool managerFinised = true;
    for (auto iter = m_machines->begin(); iter != m_machines->end(); ++iter)
    {
        MachinePtr machine = *iter;
        CommandPtr command = machine->decrementTime();
        if (command != nullptr)
        {
            QString machineName = command->getNextTaskMachine();
            if (!machineName.isEmpty())
            {
                MachinePtr machine = getMachine(machineName);
                machine->putCommandIntoQueue(command);
            }
        }

        if (!machine->checkIsFinished())
        {
            managerFinised = false;
        }
    }
    return !managerFinised;
}

void TimeSimulator::MachineManager::addMachine(const QString &name, bool isVirtual)
{
    if (isMachineExists(name))
    {
        qDebug() << "WARNING: Masina vec postoji!";
    }
    else
    {
        MachinePtr machine(new Machine(name, isVirtual));
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
    MachinePtr result = nullptr;
    auto iter = std::find_if(m_machines->begin(), m_machines->end(), [&](MachinePtr const& p) {
        return p->getName() == name;
    });

    if (iter != m_machines->end())
    {
        result = *iter;
    }
    return result;
}
