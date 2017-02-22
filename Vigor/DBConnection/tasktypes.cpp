#include "tasktypes.h"

TaskTypes::TaskTypes(QSqlQuery query)
{
    while (query.next())
    {
        auto pair = std::make_pair(query.value("Naziv").toString(), query.value("idTipoviZadatka").toUInt());
        m_types.push_back(pair);
    }
}

TaskTypes::~TaskTypes()
{

}

taskPairs TaskTypes::getTypes() const
{
    return m_types;
}
