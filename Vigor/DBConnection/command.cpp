#include <QDebug>
#include <QVariant>
#include "command.h"


Command::Command(unsigned idCustomer, unsigned idOrder, unsigned idCommand):
    m_id(idCommand),
    m_idCustomer(idCustomer),
    m_idOrder(idOrder),
    m_priority(-1)
{
    resetChangeTracking();
}

Command::~Command()
{

}

//gethers
int Command::getCommandNumber() const
{
    return m_commandNumber;
}


int Command::getPriority() const
{
    return m_priority;
}

unsigned Command::getID() const
{
    return m_id;
}

const QString& Command::getComercialistDescription() const
{
    return m_comercialistDescription;
}

const QString& Command::getDesignerDescription() const
{
    return m_designerDescription;
}

const QString& Command::getStoreKeeperDescription() const
{
    return m_storeKeeperDescription;
}

//seters
void Command::setCommandNumber(int commandNumber)
{
    if (m_commandNumber != commandNumber)
    {
        m_commandNumberChanged = true;
        m_commandNumber = commandNumber;
    }
}

void Command::setPriority(int priority)
{
    if (m_priority != priority)
    {
        m_priorityChanged = true;
        m_priority = priority;
    }
}

void Command::setComercialistDescription(const QString & description)
{
    if (m_comercialistDescription != description)
    {
        m_comercialistDescriptionChanged = true;
        m_comercialistDescription = description;
    }
}

void Command::setDesignerDescription(const QString & description)
{
    if (m_designerDescription != description)
    {
        m_designerDescriptionChanged = true;
        m_designerDescription = description;
    }
}

void Command::setStoreKeeperDescription(const QString & description)
{
    if (m_storeKeeperDescription != description)
    {
        m_designerDescriptionChanged = true;
        m_designerDescription = description;
    }
}

QString Command::statemantForCreating() const
{
    QString stm = "insert into nalog (idNarudzbina, idKlijent, OpisKomercijaliste, BrojNaloga, Prioritet, "
                  "OpisDizajnera, OpisMagacionera) values (";
    stm += QString::number(m_idOrder) + ", ";
    stm += QString::number(m_idCustomer) + ", ";
    stm += "'" + m_comercialistDescription + "', ";
    stm += QString::number(m_commandNumber) + ", ";
    stm += QString::number(m_priority) + ", ";
    stm += "'" + m_designerDescription + "', ";
    stm += "'" + m_storeKeeperDescription + "')";
    qDebug() << stm;
    return stm;
}

QString Command::statemantForUpdating() const
{
    QString stm;
    if (isModified())
    {
        stm = "update nalog set ";
        if (m_comercialistDescriptionChanged)
        {
            stm += "OpisKomercijaliste = '" + getComercialistDescription() + "', ";
        }
        if (m_commandNumberChanged)
        {
            stm += "BrojNaloga = " + QString::number(getCommandNumber()) + ", ";
        }
        if (m_priorityChanged)
        {
            stm += "Prioritet = " + QString::number(getCommandNumber()) + ", ";
        }
        if (m_designerDescriptionChanged)
        {
            stm += "OpisDizajnere = '" + getDesignerDescription() + "', ";
        }
        if (m_storeKeeperDescriptionChanged)
        {
            stm += "OpisMagacionera ='" + getStoreKeeperDescription() + "', ";
        }
        stm.chop(2);
        stm += " where idNalog = " + QString::number(m_id);
        qDebug() << stm;
    }
    return stm;
}

bool Command::isModified() const
{
    return (m_priorityChanged ||
            m_comercialistDescriptionChanged ||
            m_designerDescriptionChanged ||
            m_storeKeeperDescriptionChanged ||
            m_commandNumberChanged);
}

void Command::resetChangeTracking()
{
    m_priorityChanged                   = false;
    m_commandNumberChanged              = false;
    m_comercialistDescriptionChanged    = false;
    m_designerDescriptionChanged        = false;
    m_storeKeeperDescriptionChanged     = false;
}

CommandPtrVtr Command::createCommandsFromQuery(QSqlQuery& query)
{
    CommandPtrVtr commands(new CommandVtr());
    while(query.next())
    {
        CommandPtr command(new Command(query.value("idNalog").toUInt(), query.value("idNarudzbina").toUInt() , query.value("idKlijent").toUInt()));
        command->setCommandNumber(query.value("BrojNaloga").toInt());
        command->setComercialistDescription(query.value("OpisKomercijaliste").toString());
        command->setDesignerDescription(query.value("OpisDizajnera").toString());
        command->setStoreKeeperDescription(query.value("OpisMagacionera").toString());
        commands->push_back(command);
    }
    return commands;
}
