#include <QVariant>
#include "machine.h"

Machine::Machine():
    m_id(-1)
{
    resetChangeTracking();
}

Machine::Machine(unsigned id, unsigned taskTypeId):
    m_id(id),
    m_taskTypeId(taskTypeId)
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

unsigned Machine::getTaskTypeId() const
{
    return m_taskTypeId;
}

const QString& Machine::getName() const
{
    return m_name;
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

QString Machine::statemantForCreating() const
{
    QString stm;
    stm = "insert into maina (Naziv, TipoviZadatka_idTipoviZadatka) values (";
    stm += "'" + getName() + "', ";
    stm += QString::number(getTaskTypeId()) + ", ";
    stm.chop(2);
    stm += ")";
    return stm;
}

QString Machine::statemantForUpdating() const
{
    QString stm;
    return stm;
}

bool Machine::isModified() const
{
    return m_nameChanged;
}

void Machine::resetChangeTracking()
{
    m_nameChanged = false;
}

MachinePtrVtr Machine::createMachineFromQuery(QSqlQuery& query)
{
    MachinePtrVtr machines(new MachineVtr());
    while (query.next())
    {
        MachinePtr machine(new Machine(query.value("idMasina").toUInt(), query.value("TipoviZadatka_idTipoviZadatka").toUInt()));
        machine->setName(query.value("Naziv").toString());
        machines->push_back(machine);
    }
    return machines;
}
