#include <QDebug>
#include "timesimulator.h"
#include "commandterminationtimeengine.h"


TimeSimulator::TimeSimulator::TimeSimulator()
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

void TimeSimulator::TimeSimulator::execute(CommandTerminationTimeEnginePtr commandTerminationTimeEngine)
{
    m_threadPool->start(commandTerminationTimeEngine.get());
}
