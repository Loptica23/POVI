#include <QDebug>
#include "timesimulator.h"
#include "commandterminationtimeengine.h"
#include "types.h"


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

void TimeSimulator::TimeSimulator::execute(CommandTerminationTimeEngine* commandTerminationTimeEngine)
{
    //commandTerminationTimeEngine->setAutoDelete(false);
    m_threadPool->start(commandTerminationTimeEngine);
}
