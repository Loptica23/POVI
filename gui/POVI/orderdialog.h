#pragma once

#include "dbconnection.h"
#include "order.h"
#include "refresher.h"
#include <QDialog>
#include <memory>

namespace Ui {
class OrderDialog;
}

class OrderDialog : public QDialog, public Refresher
{
    Q_OBJECT

public:
    OrderDialog(QWidget *parent, std::shared_ptr<DBConnection> db, CustomerPtr customer, Refreshable* refreshable);
    OrderDialog(QWidget *parent, std::shared_ptr<DBConnection> db, OrderPtr order, bool edit,  Refreshable* refreshable);
    ~OrderDialog();

private slots:
    void on_buttonBox_accepted();

private:
    void createOrder();
    void updateOrder();

    Ui::OrderDialog *ui;
    Refreshable* m_refreshable;
    DBConnectionPtr m_db;
    OrderPtr m_order;
    bool m_create;

    CustomerPtr m_customer;
};

