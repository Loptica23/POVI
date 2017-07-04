#include <QVariant>
#include <QDebug>
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

bool Machine::isVirtual() const
{
    return m_isVirtual;
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

QString Machine::statemantForCreating() const
{
    QString stm;
    stm = "insert into masina (Naziv, TipoviZadatka_idTipoviZadatka) values (";
    stm += "'" + getName() + "', ";
    stm += QString::number(getTaskTypeId()) + ", ";
    stm.chop(2);
    stm += ");";
    qDebug() << stm;
    return stm;
}

QString Machine::statemantForUpdating() const
{
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
    return (m_nameChanged || m_isVirtualChanged);
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
        machine->setVirtuality(query.value("Virtuelna").toBool());
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
