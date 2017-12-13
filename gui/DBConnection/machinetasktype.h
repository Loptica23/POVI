#pragma once
#include <vector>
#include <QSqlQuery>
#include "dbconnection_global.h"


class MachineTaskType;
using MachineTaskTypePtr = std::shared_ptr<MachineTaskType>;
using MachineTaskTypeVtr = std::vector<MachineTaskTypePtr>;
using MachineTaskTypePtrVtr = std::shared_ptr<MachineTaskTypeVtr>;

class DBCONNECTIONSHARED_EXPORT MachineTaskType
{
public:
    MachineTaskType(unsigned machineID, unsigned taskTypeId);
    virtual ~MachineTaskType();

    unsigned getMachineId() const;
    unsigned getTaskTypeId() const;

    QString statemantForCreating() const;
    QString statemantForDeleting() const;

    static MachineTaskTypePtrVtr createMachineTaskTypeFromQuery(QSqlQuery& query);

private:
    unsigned m_MachineId;
    unsigned m_TaskTypeId;
};

