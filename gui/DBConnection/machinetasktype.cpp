#include "machinetasktype.h"
#include <QVariant>

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
