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
    m_timeEngine->stopEngine();
    m_threadPool->waitForDone();
}

void TimeSimulator::TimeSimulator::execute()
{
    m_timeEngine->setAutoDelete(false);
    m_threadPool->start(m_timeEngine.get());
}

bool TimeSimulator::TimeSimulator::checkIsEverythingSetUp()
{
    return m_timeEngine->checkIsEverythingSetUp();
}

void TimeSimulator::TimeSimulator::addMachine(const QString & name, bool isVirtual, QTime startTime, QTime endTime, unsigned workingDays)
{
    m_timeEngine->addMachine(name, isVirtual, startTime, endTime, workingDays);
}

void TimeSimulator::TimeSimulator::addCommand(unsigned id, unsigned commandNumber, unsigned priority)
{
    m_timeEngine->addCommand(id, commandNumber, priority);
}

void TimeSimulator::TimeSimulator::addTask(const QString & machine, unsigned idCommand, unsigned serilaNumber, unsigned prediction, TaskState state)
{
    m_timeEngine->addTask(machine, idCommand, serilaNumber, prediction, state);
}


const TimeSimulator::TimeEngine* TimeSimulator::TimeSimulator::getSender() const
{
    return m_timeEngine.get();
}

TimeSimulator::TimeSimulatorResultMapPtr TimeSimulator::TimeSimulator::getResult() const
{
    return m_timeEngine->getResult();
}
