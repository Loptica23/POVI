#include "machinetasktype.h"
#include <QVariant>
#include <QDebug>

MachineTaskType::MachineTaskType(unsigned machineID, unsigned taskTypeId)
    : m_MachineId(machineID)
    , m_TaskTypeId(taskTypeId)
{

}

MachineTaskType::~MachineTaskType()
{

}

unsigned MachineTaskType::getMachineId() const
{
    return m_MachineId;
}

unsigned MachineTaskType::getTaskTypeId() const
{
    return m_TaskTypeId;
}

QString MachineTaskType::statemantForCreating() const
{
    QString stm;
    stm = "insert into masinatipovizadatka (Masina_idMasina, TipoviZadatka_idTipoviZadatka) values (" + QString::number(m_MachineId) + ", " + QString::number(m_TaskTypeId) + ");";
    qDebug() << stm;
    return stm;
}

QString MachineTaskType::statemantForDeleting() const
{
    QString stm;
    stm = "delete from masinatipovizadatka where Masina_idMasina = " + QString::number(m_MachineId) + " and TipoviZadatka_idTipoviZadatka = " + QString::number(m_TaskTypeId) + ";";
    qDebug() << stm;
    return stm;
}

MachineTaskTypePtrVtr MachineTaskType::createMachineTaskTypeFromQuery(QSqlQuery &query)
{
    MachineTaskTypePtrVtr machinesTaskTypes(new MachineTaskTypeVtr());
    while (query.next())
    {
        MachineTaskTypePtr machineTaskType(new MachineTaskType(query.value("Masina_idMasina").toUInt(), query.value("TipoviZadatka_idTipoviZadatka").toUInt()));
        machinesTaskTypes->push_back(machineTaskType);
    }
    return machinesTaskTypes;
}
