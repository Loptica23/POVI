#include <QDebug>
#include "commandterminationtimeengine.h"
#include "machine.h"
#include "command.h"
#include "types.h"

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
    qDebug() << "Prediction started!";
    time = 0;
    while (true)
    {
        qDebug() << "TIME: " << time++;
        //ovde iteriras kroz masine
        for (auto iter = m_machines->begin(); iter != m_machines->end(); ++iter)
        {
            MachinePtr machine = *iter;
            CommandPtr command = machine->decrementTime();
            if (command)
            {
                //masina je vretila nalog, znaci da je taj zadatak zavrsen..
                //Izlogovati vreme i prebaciti nalog na sledecu masinu masinu
                qDebug() << time << "  : nalog sa Idjem prelazi na masinu sa";
                MachinePtr nextMachine = getMachineWithId(command->getIdOfNextMachine());
                nextMachine->putCommandIntoQueue(command);
            }
        }

        if (checkIsFinished())
        {
            break;
        }
    }
    qDebug() << "Prediction finished!";
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

void TimeSimulator::CommandTerminationTimeEngine::eliminateCommandFromCalculation(TimeSimulator::CommandPtr command)
{
    for (auto iter = m_machines->begin(); iter != m_machines->end(); ++iter)
    {
        MachinePtr machine = *iter;
        machine->eliminateCommandFromCalculation(command);
    }
}

bool TimeSimulator::CommandTerminationTimeEngine::checkIsFinished()
{
    bool result = true;
    for (auto iter = m_machines->begin(); iter != m_machines->end(); ++iter)
    {
        MachinePtr machine = *iter;
        if (!machine->checkIsFinished())
        {
            result = false;
            break;
        }
    }
    return result;
}

TimeSimulator::MachinePtr TimeSimulator::CommandTerminationTimeEngine::getMachineWithId(unsigned id)
{
    MachinePtr resultMachine = nullptr;
    //refactor ovo zameni funkcijom stdfind!
    for (auto iter = m_machines->begin(); iter != m_machines->end(); ++iter)
    {
        MachinePtr machine = *iter;
        if (machine->getId() == id)
        {
            resultMachine = machine;
            break;
        }
    }

    return resultMachine;
}
