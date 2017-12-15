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
    resetChangeTracking();
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

void TaskType::setName(const QString &name)
{
    if (m_name != name)
    {
        m_nameChanged = true;
        m_name = name;
    }
}

void TaskType::setInvoice(bool invoice)
{
    if (m_isVirtual != invoice)
    {
        m_isVirtual = invoice;
        m_isVirtualChanged = true;
    }
}

void TaskType::setWorkersNumber(unsigned workersNumber)
{
    if (m_workersNumber != workersNumber)
    {
        m_workersNumber = workersNumber;
        m_workersNumberChanged = true;
    }
}

QString TaskType::statemantForCreating() const
{
    QString stm;
    stm = "insert into TipoviZadatka (Naziv, Faktura, BrojRadnika) values ('";
    stm += getName() + "', ";
    if (isVirtual())
    {
        stm += "true, ";
    }
    else
    {
        stm += "false, ";
    }
    stm += QString::number(getWorkersNumber()) + ");";
    qDebug() << stm;
    return stm;
}

QString TaskType::statemantForUpdating() const
{
    QString stm;
    if (isModified())
    {
        stm = "update TipoviZadatka set ";

        if (m_nameChanged)
        {
            stm += "Naziv = '" + getName() + "', ";
        }

        if (m_isVirtualChanged)
        {
            if (isVirtual())
            {
                stm += "Faktura = true, ";
            }
            else
            {
                stm += "Faktura = false, ";
            }
        }

        if (m_workersNumberChanged)
        {
            stm += "BrojRadnika = " + QString::number(m_workersNumber) + ", ";
        }

        stm.chop(2);
        stm += " where idTipoviZadatka = " + QString::number(m_id) + ";";
    }
    qDebug() << stm;
    return stm;
}

QString TaskType::statemantForDeleting() const
{
    QString stm;
    stm = "delete from TipoviZadatka where idTipoviZadatka = " + QString::number(m_id) + ";";
    qDebug() << stm;
    return stm;
}

bool TaskType::isModified() const
{
    return m_nameChanged || m_isVirtualChanged || m_workersNumberChanged;
}

void TaskType::resetChangeTracking()
{
    m_nameChanged = false;
    m_isVirtualChanged = false;
    m_workersNumberChanged = false;
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
