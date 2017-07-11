#include <QDebug>
#include "task.h"

TimeSimulator::Task::Task(const QString & machine, unsigned serialNumber, unsigned prediction, TaskState state):
    m_machine(machine),
    m_serialNumber(serialNumber),
    m_prediction(prediction),
    m_state(state)
{

}

TimeSimulator::Task::~Task()
{

}

const QString& TimeSimulator::Task::getMachine() const
{
    return m_machine;
}

unsigned TimeSimulator::Task::getPrediction() const
{
    return m_prediction;
}

unsigned TimeSimulator::Task::getSerialNumber() const
{
    return m_serialNumber;
}

TimeSimulator::TaskState TimeSimulator::Task::getState() const
{
    return m_state;
}

void TimeSimulator::Task::setState(const TaskState & state)
{
    m_state = state;
}

void TimeSimulator::Task::setPrediction(unsigned prediction)
{
    m_prediction = prediction;
}

bool TimeSimulator::Task::checkIsEverythingSetUp()
{
    if (m_machine.isEmpty())
    {
        qDebug() << "zadatak nije lepo inicijalizovan masina: " << m_serialNumber;
        return false;
    }
    if (m_prediction == 0)
    {
        qDebug() << "zadatak nije lepo inicijalizovan predikcija: " << m_serialNumber;
        return false;
    }
    return true;
}

//ako vrati false znaci da je stigao do nule (jos u predhodnom koraku)
bool TimeSimulator::Task::decrementTime()
{
    if (m_prediction > 1)
    {
        --m_prediction;
        return true;
    }
    return false;
}

bool TimeSimulator::Task::compareFunction(TaskPtr task1, TaskPtr task2)
{
    return task1->m_serialNumber < task2->m_serialNumber;
}
