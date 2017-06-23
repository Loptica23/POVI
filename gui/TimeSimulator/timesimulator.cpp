#include <QDebug>
#include "timesimulator.h"
#include "types.h"


TimeSimulator::TimeSimulator::TimeSimulator() :
    m_timeEngine(new TimeEngine)
{
    m_threadPool = QThreadPool::globalInstance();
    if (!m_threadPool)
        qDebug() << "null ptr!";
}

TimeSimulator::TimeSimulator::~TimeSimulator()
{

}

TimeSimulator::CommandTerminationTimeEnginePtr TimeSimulator::TimeSimulator::getCommandTerminationTimeEngine()
{
    CommandTerminationTimeEnginePtr result;
    return result;
}

void TimeSimulator::TimeSimulator::execute()
{
    //commandTerminationTimeEngine->setAutoDelete(false);
    m_threadPool->start(m_timeEngine);
}
