#pragma once
#include <QString>
#include <vector>
#include <QSqlQuery>
#include <QTime>
#include "dbconnection_global.h"

class Machine;
typedef std::shared_ptr<Machine> MachinePtr;
typedef std::vector<MachinePtr> MachineVtr;
typedef std::shared_ptr<MachineVtr> MachinePtrVtr;


class DBCONNECTIONSHARED_EXPORT Machine
{
public:
    Machine();
    explicit Machine(unsigned id);
    virtual ~Machine();

    //geters
    unsigned getId() const;
    const QString& getName() const;
    bool isVirtual() const;
    QTime getStartTime() const;
    QTime getEndTime() const;
    unsigned getWorkingDays() const;

    //seters
    void setName(const QString& name);
    void setVirtuality(bool isVirtual);
    void setStartTime(const QTime & time);
    void setEndTime(const QTime & time);
    void setWorkingDays(unsigned workingDays);

    QString statemantForCreating() const;
    QString statemantForUpdating() const;
    QString statemantForDeleting() const;

    bool isModified() const;
    void resetChangeTracking();

    static MachinePtrVtr createMachineFromQuery(QSqlQuery& query);
    static MachinePtr getMachineByName(MachinePtrVtr machines, QString name);
    static MachinePtr getMachineById(MachinePtrVtr machines, unsigned id);

private:
    unsigned m_id;

    QString m_name;
    bool m_nameChanged;

    bool m_isVirtual;
    bool m_isVirtualChanged;

    QTime m_startTime;
    bool m_startTimeChanged;

    QTime m_endTime;
    bool m_endTimeChanged;

    unsigned m_workingDays;
    bool m_workingDaysChanged;
};
