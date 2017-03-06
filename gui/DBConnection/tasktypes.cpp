#include "tasktypes.h"

TaskTypes::TaskTypes(QSqlQuery query):
    m_types(new TaskPairs())
{
    while (query.next())
    {
        auto pair = std::make_pair(query.value("Naziv").toString(), query.value("idTipoviZadatka").toUInt());
        m_types->push_back(pair);
    }
}

TaskTypes::~TaskTypes()
{

}

TaskPairsPtr TaskTypes::getTypes() const
{
    return m_types;
}

unsigned TaskTypes::getTypeIdByString(QString type) const
{
    //refactor
    unsigned result = 0;
    for (auto iter = m_types->begin(); iter != m_types->end(); ++iter)
    {
        TaskPair taskPair = *iter;
        if (taskPair.first == type)
        {
            result = taskPair.second;
            break;
        }
    }
    return result;
}

QString TaskTypes::getStringById(unsigned type) const
{
    //refactor
    QString result = 0;
    for (auto iter = m_types->begin(); iter != m_types->end(); ++iter)
    {
        TaskPair taskPair = *iter;
        if (taskPair.second == type)
        {
            result = taskPair.first;
            break;
        }
    }
    return result;
}
