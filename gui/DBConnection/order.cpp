#include "order.h"
#include <QDebug>

#define dateTimeFormat "dd-MM-yyyy hh:mm:ss"
#define dateTimeFormatForDB "yyyy-MM-dd hh:mm:ss"

Order::Order(unsigned idCustomer):
    m_id((unsigned)-1),
    m_idCustomer(idCustomer),
    m_price(0)
{
    resetChangeTracking();
}

Order::Order(unsigned idOrder, unsigned idCustomer):
    m_id(idOrder),
    m_idCustomer(idCustomer),
    m_price(0)
{
    resetChangeTracking();
}

Order::~Order()
{

}

double Order::getPrice() const
{
    return m_price;
}

const QString& Order::getHeader() const
{
    return m_header;
}

const QString& Order::getDescription() const
{
    return m_description;
}

unsigned Order::getCustomerId() const
{
    return m_idCustomer;
}

//const Order::State Order::getState() const
//{
//    return m_state;
//}

//unsigned Order::getStateInt() const
//{
//    switch(m_state)
//    {
//    case State::New:
//        return 1;
//    case State::WaitingForProduction:
//        return 2;
//    case State::InProgress:
//        return 3;
//    case State::Finished:
//        return 4;
//    default:
//        qDebug() << "***************Ne postoji to stanje**********";
//        return 0;
//    }
//}

//QString Order::getStateQString() const
//{
//    switch(m_state)
//    {
//    case State::New:
//        return "nov";
//    case State::WaitingForProduction:
//        return "cek";
//    case State::InProgress:
//        return "upr";
//    case State::Finished:
//        return "zav";
//    default:
//        qDebug() << "***************Ne postoji to stanje**********";
//        return "";
//    }
//}

const QDateTime &Order::getTimeLimit() const
{
    return m_timeLimit;
}

QString Order::getTimeLimitString() const
{
    return m_timeLimit.toString(dateTimeFormat);
}

unsigned Order::getID() const
{
    return m_id;
}

void Order::setPrice(double price)
{
    if (m_price != price)
    {
        m_priceChanged = true;
        m_price = price;
    }
}

void Order::setHeader(const QString & header)
{
    if (m_header != header)
    {
        m_headerChanged = true;
        m_header = header;
    }
}

void Order::setDescription(const QString & description)
{
    if (m_description != description)
    {
        m_descriptionChanged = true;
        m_description = description;
    }
}

//void Order::setState(const State& state)
//{
//    if (m_state != state)
//    {
//        m_stateChanged = true;
//        m_state = state;
//    }
//}

//void Order::setState(const QString &state)
//{
//    if (state == "nov")
//        setState(State::New);
//    else if (state == "cek")
//        setState(State::WaitingForProduction);
//    else if (state == "upr")
//        setState(State::InProgress);
//    else if (state == "zav")
//        setState(State::Finished);
//    else
//        qDebug() << "!!!!!!!!!!!!Ne postoji ovo stanje!!!!!!!!!!!!!!!";
//}

//void Order::setState(const unsigned state)
//{
//    switch(state)
//    {
//    case 0:
//        setState(State::New);
//        break;
//    case 1:
//        setState(State::WaitingForProduction);
//        break;
//    case 2:
//        setState(State::InProgress);
//        break;
//    case 3:
//        setState(State::Finished);
//        break;
//    }
//}

void Order::setTimeLimit(const QDateTime & timeLimit)
{
    if (m_timeLimit != timeLimit)
    {
        m_timeLimit = timeLimit;
        m_timeLimitChanged = true;
    }
}

QString Order::statemantForCreating() const
{
    QString stm;
    stm = "insert into narudzbina (idKlijent, Cena, Opis, Naslov, Rok) values (";
    stm += QString::number(m_idCustomer) + ", ";
    stm += QString::number(m_price) + ", ";
    stm += "'" + m_description + "', ";
    stm += "'" + m_header + "', ";
    //stm += "'" + getStateQString() + "', ";
    stm += "'" + m_timeLimit.toString(dateTimeFormatForDB) + "')";
    qDebug() << stm;
    return stm;
}

QString Order::statemantForUpdating() const
{
    QString stm;
    if (isModified())
    {
        stm = "update narudzbina set ";
        if (m_priceChanged)
        {
            stm += "Cena = " + QString::number(getPrice()) + ", ";
        }
        if(m_headerChanged)
        {
            stm += "Naslov = '" + getHeader() + "', ";
        }
        if(m_descriptionChanged)
        {
            stm += "Opis = '" + getDescription() + "', ";
        }
        if(m_timeLimitChanged)
        {
            stm += "Rok = '" + m_timeLimit.toString(dateTimeFormatForDB) + "', ";
        }
        stm.chop(2);
        stm += "where idNarudzbina = " + QString::number(m_id);
    }
    return stm;
}

bool Order::isModified() const
{
    return (m_priceChanged ||
            m_headerChanged ||
            m_descriptionChanged ||
            m_timeLimitChanged
            );
}

void Order::resetChangeTracking()
{
    m_priceChanged = false;
    m_headerChanged = false;
    m_descriptionChanged = false;
    m_timeLimitChanged = false;
}


OrderPtrVtr Order::createOrdersFromQuery(QSqlQuery& query)
{
    OrderPtrVtr orders(new OrderVtr());
    while(query.next())
    {
        OrderPtr order(new Order(query.value("idNarudzbina").toUInt(),query.value("idKlijent").toUInt()));
        order->setHeader(query.value("Naslov").toString());
        order->setPrice((query.value("Cena").toDouble()));
        order->setDescription(query.value("Opis").toString());
        //order->setState(query.value("Stanje").toString());
        order->setTimeLimit(query.value("Rok").toDateTime());
        order->resetChangeTracking();
        orders->push_back(order);
    }
    return orders;
}
