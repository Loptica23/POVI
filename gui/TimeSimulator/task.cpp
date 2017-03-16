#include <QDebug>
#include "task.h"

TimeSimulator::Task::Task(unsigned machine):
    m_machine(machine)
{

}

TimeSimulator::Task::~Task()
{

}

unsigned TimeSimulator::Task::getMachine() const
{
    return m_machine;
}

unsigned TimeSimulator::Task::getPrediction() const
{
    return m_prediction;
}

TimeSimulator::Task::State TimeSimulator::Task::getState() const
{
    return m_state;
}

void TimeSimulator::Task::setState(const State & state)
{
    m_state = state;
}

void TimeSimulator::Task::setPrediction(unsigned prediction)
{
    m_prediction = prediction;
}

bool TimeSimulator::Task::checkIsEverythingSetUp()
{
    if (m_machine == 0) return false;
    if (m_prediction == 0) return false;
    return true;
}

//ako vrati false znaci da je stigao do nule (jos u predhodnom koraku)
bool TimeSimulator::Task::decrementTime()
{
     qDebug() << "dekrementiranje zadatka!";
    if (m_prediction != 0)
    {
        --m_prediction;
        qDebug() << "ostalo je jos: " << m_prediction;
        return true;
    }
    return false;
}
