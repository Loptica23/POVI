#pragma once
#include <QDebug>
#include <QString>
#include <vector>
#include <QSqlQuery>
#include "dbconnection_global.h"

class TaskTypes;
typedef std::shared_ptr<TaskTypes> TaskTypesPtr;
typedef std::pair<QString,int> TaskPair;
typedef std::vector<TaskPair> TaskPairs;
typedef std::shared_ptr<TaskPairs> TaskPairsPtr;

class DBCONNECTIONSHARED_EXPORT TaskTypes
{
public:
    TaskTypes(QSqlQuery query);
    virtual ~TaskTypes();

    TaskPairsPtr getTypes() const;
    unsigned getTypeIdByString(QString type) const;
    QString getStringById(unsigned type) const;

private:
    TaskPairsPtr m_types;
};
