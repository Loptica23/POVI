#pragma once
#include <QDebug>
#include <QString>
#include <vector>
#include "dbconnection_global.h"
#include "dbconnection.h"

class TaskTypes;
typedef std::pair<QString,int> taskPair;
typedef std::vector<taskPair> taskPairs;

class DBCONNECTIONSHARED_EXPORT TaskTypes
{
public:
    TaskTypes(QSqlQuery query);
    virtual ~TaskTypes();

    taskPairs getTypes() const;

private:
    taskPairs types;
};
