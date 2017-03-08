#include <QDebug>
#include <QVariant>
#include "command.h"


Command::Command(unsigned idCustomer, unsigned idOrder, unsigned idCommand):
    m_id(idCommand),
    m_idCustomer(idCustomer),
    m_idOrder(idOrder),
    m_priority(100)
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

unsigned Command::getIdOrder() const
{
    return m_idOrder;
}

unsigned Command::getIdCustomer() const
{
    return m_idCustomer;
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

const Command::State Command::getState() const
{
    return m_state;
}

unsigned Command::getStateInt() const
{
    switch(m_state)
    {
    case State::New:
        return 1;
    case State::InProgress:
        return 2;
    case State::Complited:
        return 3;
    case State::Stopped:
        return 4;
    default:
        qDebug() << "***************Ne postoji to stanje**********";
        return 0;
    }
}

QString Command::getStateQString() const
{
    return convertStateToString(m_state);
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

void Command::setState(const State& state)
{
    if (m_state != state)
    {
        m_stateChanged = true;
        m_state = state;
    }
}

void Command::setState(const QString &state)
{
    if (state == "nov")
        setState(State::New);
    else if (state == "izr")
        setState(State::InProgress);
    else if (state == "zav")
        setState(State::Complited);
    else if (state == "sto")
        setState((State::Stopped));
    else
        qDebug() << "!!!!!!!!!!!!Ne postoji ovo stanje!!!!!!!!!!!!!!!";
}

void Command::setState(const unsigned state)
{
    switch(state)
    {
    case 1:
        setState(State::New);
        break;
    case 2:
        setState(State::InProgress);
        break;
    case 3:
        setState(State::Complited);
        break;
    case 4:
        setState(State::Stopped);
        break;
    default:
        qDebug() << "!!!!!!nema takvog stanja!!!!!!!!!";
    }
}

QString Command::statemantForCreating() const
{
    QString stm = "insert into nalog (idNarudzbina, idKlijent, OpisKomercijaliste, BrojNaloga, Prioritet, "
                  "OpisDizajnera, OpisMagacionera, Stanje) values (";
    stm += QString::number(m_idOrder) + ", ";
    stm += QString::number(m_idCustomer) + ", ";
    stm += "'" + m_comercialistDescription + "', ";
    stm += QString::number(m_commandNumber) + ", ";
    stm += QString::number(m_priority) + ", ";
    stm += "'" + m_designerDescription + "', ";
    stm += "'" + m_storeKeeperDescription + "', ";
    stm += "'nov')";
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
            stm += "Prioritet = " + QString::number(getPriority()) + ", ";
        }
        if (m_designerDescriptionChanged)
        {
            stm += "OpisDizajnera = '" + getDesignerDescription() + "', ";
        }
        if (m_storeKeeperDescriptionChanged)
        {
            stm += "OpisMagacionera ='" + getStoreKeeperDescription() + "', ";
        }
        if (m_stateChanged)
        {
            stm += "Stanje = '" + getStateQString() + "', ";
        }
        stm.chop(2);
        stm += " where idNalog = " + QString::number(m_id);
        qDebug() << stm;
    }
    return stm;
}

QString Command::statementForDeleting() const
{
    QString stm;
    stm = "delete from nalog where idNalog = " + QString::number(m_id) + ";";
    qDebug() << stm;
    return stm;
}

bool Command::isModified() const
{
    return (m_priorityChanged ||
            m_comercialistDescriptionChanged ||
            m_designerDescriptionChanged ||
            m_storeKeeperDescriptionChanged ||
            m_stateChanged ||
            m_commandNumberChanged);
}

void Command::resetChangeTracking()
{
    m_priorityChanged                   = false;
    m_commandNumberChanged              = false;
    m_comercialistDescriptionChanged    = false;
    m_designerDescriptionChanged        = false;
    m_storeKeeperDescriptionChanged     = false;
    m_stateChanged                      = false;
}

CommandPtrVtr Command::createCommandsFromQuery(QSqlQuery& query)
{
    CommandPtrVtr commands(new CommandVtr());
    while(query.next())
    {
        CommandPtr command(new Command(query.value("idKlijent").toUInt(), query.value("idNarudzbina").toUInt(), query.value("idNalog").toUInt()));
        command->setCommandNumber(query.value("BrojNaloga").toInt());
        command->setComercialistDescription(query.value("OpisKomercijaliste").toString());
        command->setDesignerDescription(query.value("OpisDizajnera").toString());
        command->setStoreKeeperDescription(query.value("OpisMagacionera").toString());
        command->setState(query.value("Stanje").toString());
        command->setPriority(query.value("Prioritet").toInt());
        command->resetChangeTracking();
        commands->push_back(command);
    }
    return commands;
}

QString Command::convertStateToString(const State & state)
{
    QString result;
    switch(state)
    {
    case State::New:
        result = "nov";
        break;
    case State::InProgress:
        result = "izr";
        break;
    case State::Complited:
        result = "zav";
        break;
    case State::Stopped:
        result = "sto";
        break;
    default:
        qDebug() << "*****************nema takvog stanja*****************";
    }
    return result;
}
