#pragma once

#include "dbconnection_global.h"
#include <QString>
#include <QSqlQuery>
#include <memory>
#include <vector>

class Order;
typedef std::shared_ptr<Order> OrderPtr;
typedef std::vector<OrderPtr> OrderVtr;
typedef std::shared_ptr<OrderVtr> OrderPtrVtr;

//Narudzbina
class DBCONNECTIONSHARED_EXPORT Order
{
public:
    //enum class State{New, WaitingForProduction, InProgress, Finished};

    Order(unsigned idCustomer);
    Order(unsigned idCustomer, unsigned idOrder);
    virtual ~Order();

    //gethers
    double getPrice() const;
    const QString& getHeader() const;
    const QString& getDescription() const;
    unsigned getCustomerId() const;
    //const State getState() const;
    //unsigned getStateInt() const;
    //QString getStateQString() const;
    QString getTimeLimit() const;
    unsigned getID() const;

    //seters
    void setPrice(double price);
    void setHeader(const QString & header);
    void setDescription(const QString & description);
    //void setState(const State& state);
    //void setState(const QString& state);
    //void setState(const unsigned state);
    void setTimeLimit(const QString & timeLimit);

    QString statemantForCreating() const;
    QString statemantForUpdating() const;

    bool isModified() const;
    void resetChangeTracking();


    static OrderPtrVtr createOrdersFromQuery(QSqlQuery& query);

private:
    unsigned m_id;
    unsigned m_idCustomer;

    double m_price;
    bool m_priceChanged;
    QString m_header;
    bool m_headerChanged;
    QString m_description;
    bool m_descriptionChanged;
    //State m_state;
    //bool m_stateChanged;
    QString m_timeLimit;
    bool m_timeLimitChanged;
};
