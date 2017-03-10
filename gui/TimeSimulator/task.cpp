#include "task.h"

TimeSimulator::Task::Task(unsigned machine, unsigned prediction, State state):
    m_machine(machine),
    m_prediction(prediction),
    m_state(state)
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

bool TimeSimulator::Task::checkIsEverythingSetUp()
{
    if (m_machine == 0) return false;
    if (m_prediction == 0) return false;
    return true;
}
