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
    enum class State{New, InProgress, Complited, Leaved, Stopped};

    Task(CommandPtr command, unsigned taskType);
    virtual ~Task();

    //geters
    CommandPtr getCommand() const;
    unsigned getTaskTypeId() const;
    unsigned getWorkerId() const;
    unsigned getPrediction() const;
    unsigned getMachineId() const;
    const State& getState() const;
    QString getStateString() const;

    //seters
    void setWorkerId(const unsigned workerId);
    void setPrediction(const unsigned prediction);
    void setMachineId(const unsigned machineId);
    void setState(const State& state);
    void setState(const QString& state);


    QString statemantForCreating() const;
    QString statemantForUpdating() const;

    bool isModified() const;
    void resetChangeTracking();


    static TaskPtrVtr createTaskFromQueryAndCommand(QSqlQuery& query, CommandPtr command);

private:
    CommandWeakPtr m_command;

    unsigned m_taskType;
    bool m_taskTypeChanged;

    unsigned m_workerId;
    bool m_workerIdChanged;

    unsigned m_prediction;
    bool m_predictionChanged;

    unsigned m_machineId;
    bool m_machineIdChanged;

    State m_state;
    bool m_stateChanged;
};
