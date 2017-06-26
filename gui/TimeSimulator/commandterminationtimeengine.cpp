#include <QDebug>
#include <chrono>
#include <thread>
#include "commandterminationtimeengine.h"
#include "machine.h"
#include "command.h"
#include "types.h"

TimeSimulator::CommandTerminationTimeEngine::CommandTerminationTimeEngine():
    m_keepRunning(true)
{
    qDebug() << "konstruktor engine!";
}

TimeSimulator::CommandTerminationTimeEngine::~CommandTerminationTimeEngine()
{
    qDebug() << "destrukcija motora";
}

void TimeSimulator::CommandTerminationTimeEngine::setMachines(MachineVtrPtr machines)
{
    m_machines = machines;
}

void TimeSimulator::CommandTerminationTimeEngine::run()
{
    qDebug() << "Prediction started!";
    time = 0;
    while (m_keepRunning)
    {
        //ovde iteriras kroz masine
        for (auto iter = m_machines->begin(); iter != m_machines->end(); ++iter)
        {
            MachinePtr machine = *iter;
            CommandPtr command = machine->decrementTime();
            if (command)
            {
                //masina je vretila nalog, znaci da je taj zadatak zavrsen..
                //Izlogovati vreme i prebaciti nalog na sledecu masinu masinu
                unsigned idMachine = command->getIdOfNextMachine();
                if (idMachine)
                {
                    qDebug() << time << "  : nalog sa idjem: " + QString::number(command->getId()) +  " prelazi na masinu sa idjem: " + QString::number(idMachine);
                    MachinePtr nextMachine = getMachineWithId(idMachine);
                    nextMachine->putCommandIntoQueue(command);
                }
                else
                {
                    qDebug() << time << "  : nalog sa idjem: " + QString::number(command->getId()) + " je zavrsio!";
                }
            }
        }

        if (checkIsFinished())
        {
            break;
        }
        time++;
        //std::this_thread::sleep_for(std::chrono::milliseconds(250));
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

void TimeSimulator::CommandTerminationTimeEngine::stopEngine()
{
    m_keepRunning = false;
}
