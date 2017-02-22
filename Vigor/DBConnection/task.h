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
    Task(CommandPtr command, unsigned taskType);
    virtual ~Task();

    //geters
    CommandPtr getCommand() const;
    unsigned getTaskTypeId() const;

    //seters


    QString statemantForCreating() const;
    QString statemantForUpdating() const;

    bool isModified() const;
    void resetChangeTracking();


    static TaskPtrVtr createTaskFromQueryAndCommand(QSqlQuery& query, CommandPtr command);

private:
    CommandWeakPtr m_command;
    unsigned m_taskType;
};
