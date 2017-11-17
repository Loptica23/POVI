#include <QDebug>
#include <QVariant>
#include "command.h"


Command::Command(unsigned idCustomer, unsigned idOrder, unsigned idCommand, unsigned idKomercialist):
    m_id(idCommand),
    m_idCustomer(idCustomer),
    m_idOrder(idOrder),
    m_idKomercialist(idKomercialist),
    m_quantity(00),
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

unsigned Command::getKomercialistID() const
{
    return m_idKomercialist;
}

const QString& Command::getSpecification() const
{
    return m_specification;
}

unsigned Command::getQuantity() const
{
    return m_quantity;
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

Command::State Command::getState() const
{
    return m_state;
}

unsigned Command::getStateInt() const
{
    switch(m_state)
    {
    case State::New:
        return 1;
    case State::WaitForProduction:
        return 2;
    case State::InProgress:
        return 3;
    case State::Complited:
        return 4;
    case State::Stopped:
        return 5;
    default:
        qDebug() << "***************Ne postoji to stanje**********";
        return 0;
    }
}

QString Command::getStateQString() const
{
    return convertStateToString(m_state);
}

const QDateTime& Command::getDateTimePrediction() const
{
    return m_dateTimePrediction;
}

const QDateTime& Command::getDateTimeCreation() const
{
    return m_dateTimeCreation;
}

const QDateTime& Command::getDateTimeLastUpdated() const
{
    return m_dateTimeLastupdated;
}

Command::UnitOfQuantity Command::getUnitOfQuantity() const
{
    return m_unitOfQuantity;
}

QString Command::getUnitOfQuantityStr() const
{
    return unitOfQuantityEnumToStr(m_unitOfQuantity);
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

void Command::setSpecification(const QString & specification)
{
    if (m_specification != specification)
    {
        m_specificationChanged = true;
        m_specification = specification;
    }
}

void Command::setQuantity(unsigned quantity)
{
    if (m_quantity != quantity)
    {
        m_quantityChanged = true;
        m_quantity = quantity;
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
        m_storeKeeperDescriptionChanged = true;
        m_storeKeeperDescription = description;
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
    else if (state == "cek")
        setState(State::WaitForProduction);
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
        setState(State::WaitForProduction);
        break;
    case 3:
        setState(State::InProgress);
        break;
    case 4:
        setState(State::Complited);
        break;
    case 5:
        setState(State::Stopped);
        break;
    default:
        qDebug() << "!!!!!!nema takvog stanja!!!!!!!!!";
    }
}

void Command::setDateTimePrediction(const QDateTime & prediction)
{
    if (m_dateTimePrediction != prediction)
    {
        m_dateTimePredictionChanged = true;
        m_dateTimePrediction = prediction;
    }
}

void Command::setUnitOfQuantity(Command::UnitOfQuantity unitOfQuantity)
{
    if (m_unitOfQuantity != unitOfQuantity)
    {
        m_unitOfQuantityChanged = true;
        m_unitOfQuantity =  unitOfQuantity;
    }
}

void Command::setUnitOfQuantity(const QString& unitOfQuantity)
{
    if (m_unitOfQuantity != unitOfQuantityStrToEnum(unitOfQuantity))
    {
        m_unitOfQuantityChanged = true;
        m_unitOfQuantity = unitOfQuantityStrToEnum(unitOfQuantity);
    }
}

QString Command::statemantForCreating() const
{
    QString stm = "insert into nalog (idNarudzbina, idKlijent, Radnik_idRadnik, OpisKomercijaliste, BrojNaloga, Prioritet, "
                  "OpisDizajnera, OpisMagacionera, Stanje, Specifikacija, Kolicina, Kreiran, PoslednjaPromena, MeraKolicine) values (";
    stm += QString::number(m_idOrder) + ", ";
    stm += QString::number(m_idCustomer) + ", ";
    stm += QString::number(m_idKomercialist) + ", ";
    stm += "'" + m_comercialistDescription + "', ";
    stm += QString::number(m_commandNumber) + ", ";
    stm += QString::number(m_priority) + ", ";
    stm += "'" + m_designerDescription + "', ";
    stm += "'" + m_storeKeeperDescription + "', ";
    stm += "'nov', ";
    stm += "'" + m_specification + "', ";
    stm += QString::number(m_quantity) + ", ";
    stm += "NOW(), ";
    stm += "NOW(), ";
    stm += "'" + getUnitOfQuantityStr() + "'";
    stm += ");";
    qDebug() << stm;
    return stm;
}

QString Command::statemantForUpdating(bool noteModifiedTime) const
{
    QString stm;
    if (isModified())
    {
        stm = "update nalog set ";
        if (m_specificationChanged)
        {
            stm += "Specifikacija = '" + getSpecification() + "', ";
        }
        if (m_quantityChanged)
        {
            stm += "Kolicina = " + QString::number(getQuantity()) + ", ";
        }
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
        if (m_dateTimePredictionChanged)
        {
            stm += "Predvidjanje = '" + getDateTimePrediction().toString("yyyy-MM-dd hh:mm:ss") + "', ";
        }
        if (m_unitOfQuantityChanged)
        {
            stm += "MeraKolicine = '" + getUnitOfQuantityStr() + "', ";
        }
        if (noteModifiedTime)
        {
            stm += "PoslednjaPromena = NOW(), ";
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
            m_commandNumberChanged ||
            m_specificationChanged ||
            m_quantityChanged ||
            m_dateTimePredictionChanged ||
            m_unitOfQuantityChanged);
}

void Command::resetChangeTracking()
{
    m_priorityChanged                   = false;
    m_commandNumberChanged              = false;
    m_comercialistDescriptionChanged    = false;
    m_designerDescriptionChanged        = false;
    m_storeKeeperDescriptionChanged     = false;
    m_stateChanged                      = false;
    m_specificationChanged              = false;
    m_quantityChanged                   = false;
    m_dateTimePredictionChanged         = false;
    m_unitOfQuantityChanged             = false;
}

CommandPtrVtr Command::createCommandsFromQuery(QSqlQuery& query)
{
    CommandPtrVtr commands(new CommandVtr());
    while(query.next())
    {
        CommandPtr command(new Command(query.value("idKlijent").toUInt(), query.value("idNarudzbina").toUInt(), query.value("idNalog").toUInt(), query.value("Radnik_idRadnik").toUInt()));
        command->setCommandNumber(query.value("BrojNaloga").toInt());
        command->setSpecification(query.value("Specifikacija").toString());
        command->setQuantity(query.value("Kolicina").toInt());
        command->setComercialistDescription(query.value("OpisKomercijaliste").toString());
        command->setDesignerDescription(query.value("OpisDizajnera").toString());
        command->setStoreKeeperDescription(query.value("OpisMagacionera").toString());
        command->setState(query.value("Stanje").toString());
        command->setPriority(query.value("Prioritet").toInt());
        command->setDateTimePrediction(query.value("Predvidjanje").toDateTime());
        command->m_dateTimeCreation = query.value("Kreiran").toDateTime();
        command->m_dateTimeLastupdated = query.value("PoslednjaPromena").toDateTime();
        command->setUnitOfQuantity(query.value("MeraKolicine").toString());
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
    case State::WaitForProduction:
        result = "cek";
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

QString Command::unitOfQuantityEnumToStr(UnitOfQuantity unitQuantity)
{
    QString result;
    switch (unitQuantity)
    {
    case UnitOfQuantity::M:
        result = "m";
        break;
    case UnitOfQuantity::KG:
        result = "kg";
        break;
    case UnitOfQuantity::KOM:
        result = "kom";
        break;
    default:
        break;
    }
    return result;
}

Command::UnitOfQuantity Command::unitOfQuantityStrToEnum(const QString &unitQuantity)
{
    UnitOfQuantity result;
    if (unitQuantity == "m")
    {
        result = UnitOfQuantity::M;
    }
    else if (unitQuantity == "kg")
    {
        result = UnitOfQuantity::KG;
    }
    else if (unitQuantity == "kom")
    {
        result = UnitOfQuantity::KOM;
    }
    else
    {
        qDebug() << "GRESKA: ne postoji ta jedinica";
    }
    return result;
}
