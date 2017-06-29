#include "tasktypes.h"
#include "utils.h"

//--------------------------------------------------------------
//TaskType

TaskType::TaskType(int id, QString name, bool isVirtual)
{
    m_id = id;
    m_name = name;
    m_isVirtual = isVirtual;
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

//--------------------------------------------------------------
//TaskTypes
TaskTypes::TaskTypes(QSqlQuery query):
    m_types(new TaskTypeVtr())
{
    while (query.next())
    {
        TaskTypePtr taskType;
        taskType.reset(new TaskType(query.value("idTipoviZadatka").toUInt(), query.value("Naziv").toString(), query.value("Faktura").toBool()));
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
