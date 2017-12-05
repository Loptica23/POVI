#include "tasktypes.h"
#include "utils.h"

//--------------------------------------------------------------
//TaskType

TaskType::TaskType(int id, QString name, bool isVirtual, unsigned workerNumber)
    : m_id(id)
    , m_name(name)
    , m_isVirtual(isVirtual)
    , m_workersNumber(workerNumber)
{

}

TaskType::~TaskType()
{

}

unsigned TaskType::getId() const
{
    return m_id;
}

QString TaskType::getName() const
{
    return m_name;
}

bool TaskType::isVirtual() const
{
    return m_isVirtual;
}

unsigned TaskType::getWorkersNumber() const
{
    return m_workersNumber;
}

//--------------------------------------------------------------
//TaskTypes
TaskTypes::TaskTypes(QSqlQuery query):
    m_types(new TaskTypeVtr())
{
    while (query.next())
    {
        TaskTypePtr taskType;
        taskType.reset(new TaskType(query.value("idTipoviZadatka").toUInt(), query.value("Naziv").toString(), query.value("Faktura").toBool(), query.value("BrojRadnika").toUInt()));
        m_types->push_back(taskType);
    }
}

TaskTypes::~TaskTypes()
{

}

TaskTypePtrVtr TaskTypes::getTypes() const
{
    return m_types;
}

TaskTypePtr TaskTypes::getTaskTypeById(unsigned type) const
{
    return Utils::findElementInVectorPtr(m_types, type, &TaskType::getId);
}

unsigned TaskTypes::getTypeIdByString(const QString & type) const
{
    TaskTypePtr taskType = Utils::findElementInVectorPtr(m_types, type, &TaskType::getName);
    return taskType->getId();
}

QString TaskTypes::getStringById(unsigned type) const
{
    TaskTypePtr taskType = Utils::findElementInVectorPtr(m_types, type, &TaskType::getId);
    return taskType->getName();
}
