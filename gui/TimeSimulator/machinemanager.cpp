#include "machinemanager.h"
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

TimeSimulator::MachinePtr TimeSimulator::MachineManager::getMachine(QString & name)
{
    //ovde ti treba neka find funkcija
}
