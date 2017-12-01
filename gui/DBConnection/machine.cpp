#include <QVariant>
#include <QDebug>
#include "machine.h"

Machine::Machine():
    m_id(-1)
{
    resetChangeTracking();
}

Machine::Machine(unsigned id):
    m_id(id)
{
    resetChangeTracking();
}

Machine::~Machine()
{

}

//geters
unsigned Machine::getId() const
{
    return m_id;
}

const QString& Machine::getName() const
{
    return m_name;
}

bool Machine::isVirtual() const
{
    return m_isVirtual;
}

QTime Machine::getStartTime() const
{
    return m_startTime;
}

QTime Machine::getEndTime() const
{
    return m_endTime;
}

unsigned Machine::getWorkingDays() const
{
    return m_workingDays;
}

//seters
void Machine::setName(const QString &name)
{
    if (m_name != name)
    {
        m_nameChanged = true;
        m_name = name;
    }
}

void Machine::setVirtuality(bool isVirtual)
{
    if (m_isVirtual != isVirtual)
    {
        m_isVirtualChanged = true;
        m_isVirtual = isVirtual;
    }
}

void Machine::setStartTime(const QTime &time)
{
    if (m_startTime != time)
    {
        m_startTimeChanged = true;
        m_startTime = time;
    }
}

void Machine::setEndTime(const QTime &time)
{
    if (m_endTime != time)
    {
        m_endTimeChanged = true;
        m_endTime = time;
    }
}

void Machine::setWorkingDays(unsigned workingDays)
{
    if (m_workingDays != workingDays)
    {
        m_workingDaysChanged = true;
        m_workingDays = workingDays;
    }
}

QString Machine::statemantForCreating() const
{
    //TODO nije up to date
    QString stm;
    stm = "insert into masina (Naziv, TipoviZadatka_idTipoviZadatka) values (";
    stm += "'" + getName() + "', ";
    stm.chop(2);
    stm += ");";
    qDebug() << stm;
    return stm;
}

QString Machine::statemantForUpdating() const
{
    //TODO nije up to date
    QString stm;
    if (isModified())
    {
        stm = "update masina set ";
        if (m_nameChanged)
        {
            stm += "Naziv = '" + getName() + "', ";
        }
        stm.chop(2);
        stm += " where idMasina = " + QString::number(m_id) + ";";
    }
    return stm;
}

bool Machine::isModified() const
{
    return (m_nameChanged ||
            m_isVirtualChanged ||
            m_startTimeChanged ||
            m_endTimeChanged ||
            m_workingDaysChanged
            );
}

void Machine::resetChangeTracking()
{
    m_nameChanged = false;
    m_isVirtualChanged = false;
    m_startTimeChanged = false;
    m_endTimeChanged = false;
    m_workingDaysChanged = false;
}

MachinePtrVtr Machine::createMachineFromQuery(QSqlQuery& query)
{
    MachinePtrVtr machines(new MachineVtr());
    while (query.next())
    {
        MachinePtr machine(new Machine(query.value("idMasina").toUInt()));
        machine->setName(query.value("Naziv").toString());
        machine->setVirtuality(query.value("Virtuelna").toBool());
        machine->setStartTime(query.value("VremePocetka").toTime());
        machine->setEndTime(query.value("VremeKraja").toTime());
        machine->setWorkingDays(query.value("RadniDani").toUInt());
        machine->resetChangeTracking();
        machines->push_back(machine);
    }
    return machines;
}

MachinePtr Machine::getMachineByName(MachinePtrVtr machines, QString name)
{
    MachinePtr result = nullptr;
    for (auto iter = machines->begin(); iter != machines->end(); ++iter)
    {
        if (name == (*iter)->getName())
        {
            result = *iter;
            break;
        }
    }
    return result;
}

MachinePtr Machine::getMachineById(MachinePtrVtr machines, unsigned id)
{
    MachinePtr result = nullptr;
    for (auto iter = machines->begin(); iter != machines->end(); ++iter)
    {
        if (id == (*iter)->getId())
        {
            result = *iter;
            break;
        }
    }
    return result;
}
