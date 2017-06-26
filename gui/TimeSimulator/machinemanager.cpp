#include "machinemanager.h"
#include "types.h"
#include "machine.h"
#include <QDebug>

TimeSimulator::MachineManager::MachineManager() :
    m_machines(new MachineVtr())
{

}

TimeSimulator::MachineManager::~MachineManager()
{

}

void TimeSimulator::MachineManager::addMachine(QString &name, bool isVirtual)
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

bool TimeSimulator::MachineManager::isMachineExists(QString & name)
{
    bool result = false;
    if (getMachine(name) != nullptr)
    {
        result = true;
    }
    return result;
}

TimeSimulator::MachinePtr TimeSimulator::MachineManager::getMachine(QString & name)
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
