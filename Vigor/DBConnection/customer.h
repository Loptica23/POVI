#pragma once

#include "dbconnection_global.h"
#include <memory>
#include <vector>
#include <QString>
#include <QSqlQuery>

class Customer;
typedef std::shared_ptr<Customer> CustomerPtr;
typedef std::vector<CustomerPtr> CustomerVtr;
typedef std::shared_ptr<CustomerVtr> CustomerPtrVtr;

//sve ove kalse bi trebale biti izvedene iz jedne, to za sada ne bi imalo nikakve benificije,
//ali bi mozda bilo korisno za kaznije
class DBCONNECTIONSHARED_EXPORT Customer
{
public:
    Customer();
    Customer(unsigned id);
    virtual ~Customer();

    //gethers
    const QString& getName() const;
    unsigned getId() const;

    //seters
    void setName(const QString & name);

    QString statemantForCreating() const;
    QString statemantForUpdating() const;

    bool isModified() const;
    void resetChangeTracking();


    static CustomerPtrVtr createCustomersFromQuery(QSqlQuery& query);

private:
    unsigned m_id;

    bool m_nameChanged;
    QString m_name;
};
