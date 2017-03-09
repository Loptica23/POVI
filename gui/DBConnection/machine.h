#pragma once
#include <QString>
#include <vector>
#include <QSqlQuery>
#include "dbconnection_global.h"

class Machine;
typedef std::shared_ptr<Machine> MachinePtr;
typedef std::vector<MachinePtr> MachineVtr;
typedef std::shared_ptr<MachineVtr> MachinePtrVtr;


class DBCONNECTIONSHARED_EXPORT Machine
{
public:
    Machine();
    explicit Machine(unsigned id, unsigned taskTypeId);
    virtual ~Machine();

    //geters
    unsigned getId() const;
    unsigned getTaskTypeId() const;
    const QString& getName() const;

    //seters
    void setName(const QString& name);

    QString statemantForCreating() const;
    QString statemantForUpdating() const;

    bool isModified() const;
    void resetChangeTracking();


    static MachinePtrVtr createMachineFromQuery(QSqlQuery& query);
    static MachinePtr getMachineByName(MachinePtrVtr machines, QString name);
    static MachinePtr getMachineById(MachinePtrVtr machines, unsigned id);

private:
    unsigned m_id;
    unsigned m_taskTypeId;

    QString m_name;
    bool m_nameChanged;
};
