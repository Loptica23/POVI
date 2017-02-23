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
