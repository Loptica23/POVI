#include "tasktypes.h"

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

int TaskType::getId() const
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
    TaskTypePtr result;

    auto it = std::find_if(m_types->begin(), m_types->end(), [&](TaskTypePtr const & taskType)
            {
                return taskType->getId() == type;
            });

    if (it != m_types->end())
    {
        result = *it;
    }
    return result;
}

unsigned TaskTypes::getTypeIdByString(QString type) const
{
    unsigned result = 0;
    auto it = std::find_if(m_types->begin(), m_types->end(), [&](TaskTypePtr const & taskType)
            {
                return taskType->getName() == type;
            });

    if (it != m_types->end())
    {
        TaskTypePtr taskType = *it;
        result = taskType->getId();
    }
    return result;
}

QString TaskTypes::getStringById(unsigned type) const
{
    QString result = 0;
    auto it = std::find_if(m_types->begin(), m_types->end(), [&](TaskTypePtr const & taskType)
            {
                return taskType->getId() == type;
            });

    if (it != m_types->end())
    {
        TaskTypePtr taskType = *it;
        result = taskType->getName();
    }
    return result;
}
