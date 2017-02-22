#pragma once
#include <QDebug>
#include <QString>
#include <vector>
#include <QSqlQuery>
#include "dbconnection_global.h"

class TaskTypes;
typedef std::shared_ptr<TaskTypes> TaskTypesPtr;
typedef std::pair<QString,int> taskPair;
typedef std::vector<taskPair> taskPairs;

class DBCONNECTIONSHARED_EXPORT TaskTypes
{
public:
    TaskTypes(QSqlQuery query);
    virtual ~TaskTypes();

    taskPairs getTypes() const;

private:
    taskPairs m_types;
};
