#include <QDebug>
#include "types.h"
#include "timesimulator.h"
#include "timeengine.h"


TimeSimulator::TimeSimulator::TimeSimulator() :
    m_timeEngine(new TimeEngine())
{
    m_threadPool = QThreadPool::globalInstance();
    if (!m_threadPool)
        qDebug() << "null ptr!";
}

TimeSimulator::TimeSimulator::~TimeSimulator()
{
    //vidi kako ces da stopiras zadatke
}

void TimeSimulator::TimeSimulator::execute()
{
    //commandTerminationTimeEngine->setAutoDelete(false);
    m_threadPool->start(m_timeEngine.get());
}

void TimeSimulator::TimeSimulator::addMachine(QString & name, bool isVirtual)
{
    m_timeEngine->addMachine(name, isVirtual);
}

void TimeSimulator::TimeSimulator::addCommand(unsigned id, unsigned commandNumber, unsigned priority)
{
    m_timeEngine->addCommand(id, commandNumber, priority);
}

void TimeSimulator::TimeSimulator::addTask(QString & machine, unsigned idCommand, unsigned serilaNumber, unsigned prediction, TaskState state)
{
    m_timeEngine->addTask(machine, idCommand, serilaNumber, prediction, state);
}
