#include <memory>
#include <QVariant>
#include "task.h"
#include "command.h"


Task::Task(CommandPtr command, unsigned taskType):
    m_command(command),
    m_taskType(taskType)
{

}

Task::~Task()
{

}

//geters
CommandPtr Task::getCommand() const
{
    CommandPtr command;
    if (!(command = m_command.lock()))
    {
        command = nullptr;
    }
    return command;
}

unsigned Task::getTaskTypeId() const
{
    return m_taskType;
}

//seters


QString Task::statemantForCreating() const
{
    QString stm;
    stm = "insert into zadatak (Nalog_idNalog, Nalog_idNarudzbina, Nalog_idKlijent,"
          "TipoviZadatka_idTipoviZadatka) values (";
    stm += QString::number(getCommand()->getID()) + ", ";
    stm += QString::number(getCommand()->getIdOrder()) + ", ";
    stm += QString::number(getCommand()->getIdCustomer()) + ", ";
    stm += QString::number(getTaskTypeId());
    stm += ")";
    return stm;
}

QString Task::statemantForUpdating() const
{
    QString stm;
    return stm;
}

bool Task::isModified() const
{
    return false;
}

void Task::resetChangeTracking()
{

}

TaskPtrVtr Task::createTaskFromQueryAndCommand(QSqlQuery& query, CommandPtr command)
{
    TaskPtrVtr tasks(new TaskVtr());
    while(query.next())
    {
        TaskPtr task(new Task(command, query.value("TipoviZadatka_idTipoviZadatka").toUInt()));

        tasks->push_back(task);
    }
    return tasks;
}
