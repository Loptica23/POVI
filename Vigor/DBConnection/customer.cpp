#include "customer.h"
#include <QDebug>

Customer::Customer():
    m_id((unsigned)-1),
    m_nameChanged(false)
{

}

Customer::Customer(unsigned id):
    m_id(id),
    m_nameChanged(false)
{

}

Customer::~Customer()
{

}

const QString& Customer::getName() const
{
    return m_name;
}

unsigned Customer::getId() const
{
    return m_id;
}

void Customer::setName(const QString &name)
{
    if (m_name != name)
    {
        m_nameChanged = true;
        m_name = name;
    }
}

QString Customer::statemantForCreating() const
{
    QString stm = "insert into klijent (Ime) values (' "  + getName() +"')";
    return stm;
}

QString Customer::statemantForUpdating() const
{
    QString stm;
    if (isModified())
    {
        stm = "update klijent set ";
        if (m_nameChanged)
        {
            stm += "Ime = \"" + getName() + "\" , ";
        }
        stm.chop(2);
        stm += "where idKlijent = " + QString::number(m_id);
    }
    else
    {
        qDebug() << "**************************************nema izmena**************************************";
    }
    return stm;
}

bool Customer::isModified() const
{
    return m_nameChanged;
}

void Customer::resetChangeTracking()
{
    m_nameChanged = false;
}


CustomerPtrVtr Customer::createCustomersFromQuery(QSqlQuery& query)
{
    CustomerPtrVtr custoomers(new CustomerVtr());
    while(query.next())
    {
        CustomerPtr customer(new Customer(query.value("idKlijent").toUInt()));
        customer->setName(query.value("Ime").toString());
        customer->resetChangeTracking();
        custoomers->push_back(customer);
    }
    return custoomers;
}
