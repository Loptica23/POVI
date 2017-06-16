#pragma once
#include <QSqlQuery>
#include <QString>
#include <vector>
#include "dbconnection_global.h"
#include "command.h"

class Task;
typedef std::shared_ptr<Task> TaskPtr;
typedef std::vector<TaskPtr> TaskVtr;
typedef std::shared_ptr<TaskVtr> TaskPtrVtr;

//zadatak
class DBCONNECTIONSHARED_EXPORT Task
{
public:
    enum class State{New, Waiting, InProgress, Complited, Leaved, Stopped};

    //ovaj konstruktor se poziva kada se kreira novi task
    Task(CommandPtr command, unsigned taskType);

    //ovaj konstruktor se poziva kada task vec postoji
    Task(unsigned id, CommandPtr command, unsigned taskType);

    virtual ~Task();

    //geters
    unsigned getId() const;
    CommandPtr getCommand() const;
    unsigned getTaskTypeId() const;
    unsigned getWorkerId() const;
    unsigned getPrediction() const;
    unsigned getMachineId() const;
    const State& getState() const;
    QString getStateString() const;
    unsigned getSerialNumber() const;

    //seters
    void setCommand(CommandPtr command);
    void setWorkerId(const unsigned workerId);
    void setPrediction(const unsigned prediction);
    void setMachineId(const unsigned machineId);
    void setState(const State& state);
    void setState(const QString& state);
    void setSerialNumber(unsigned serialNumber);
    void setCurrentTimeForStarted();
    void setCurrentTimeForComplited();


    QString statemantForCreating(unsigned employeeID) const;
    QString statemantForUpdating() const;
    QString statementForDeleting() const;

    bool isModified() const;
    bool isCreated() const;
    void resetChangeTracking();


    static TaskPtrVtr createTaskFromQueryAndCommand(QSqlQuery& query, CommandPtr command);

private:
    unsigned m_id;
    bool m_created; //task je upravo kreiran; ne postoji u bazi podataka;

    CommandWeakPtr m_command;

    unsigned m_taskType;
    bool m_taskTypeChanged;

    unsigned m_workerId;
    bool m_workerIdChanged;

    unsigned m_prediction;
    bool m_predictionChanged;

    unsigned m_machineId;
    bool m_machineIdChanged;

    unsigned m_serialNumber;
    bool m_serialNumberChanged;

    State m_state;
    bool m_stateChanged;

    bool m_setStartedTime;
    bool m_setComplitedTime;
};
