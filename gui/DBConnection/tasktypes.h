#pragma once
#include <QDebug>
#include <QString>
#include <vector>
#include <QSqlQuery>
#include "dbconnection_global.h"

class TaskType;
typedef std::shared_ptr<TaskType> TaskTypePtr;
typedef std::vector<TaskTypePtr> TaskTypeVtr;
typedef std::shared_ptr<TaskTypeVtr> TaskTypePtrVtr;

class TaskTypes;
typedef std::shared_ptr<TaskTypes> TaskTypesPtr;

class DBCONNECTIONSHARED_EXPORT TaskType
{
public:
    TaskType(int id, QString name, bool isVirtual, unsigned workerNumber);
    virtual ~TaskType();

    unsigned getId() const;
    QString getName() const;
    bool isVirtual() const;
    unsigned getWorkersNumber() const;

private:
    unsigned        m_id;
    QString         m_name;
    bool            m_isVirtual;
    unsigned        m_workersNumber;
};

class DBCONNECTIONSHARED_EXPORT TaskTypes
{    
public:
    TaskTypes(QSqlQuery query);
    virtual ~TaskTypes();

    TaskTypePtrVtr getTypes() const;
    TaskTypePtr getTaskTypeById(unsigned type) const;
    unsigned getTypeIdByString(const QString & type) const;
    QString getStringById(unsigned type) const;

private:
    TaskTypePtrVtr m_types;
};
