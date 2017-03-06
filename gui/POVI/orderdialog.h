#pragma once

#include "dbconnection.h"
#include "order.h"
#include <QDialog>
#include <memory>

namespace Ui {
class OrderDialog;
}

class OrderDialog : public QDialog
{
    Q_OBJECT

public:
    OrderDialog(QWidget *parent, std::shared_ptr<DBConnection> db, CustomerPtr customer);
    OrderDialog(QWidget *parent, std::shared_ptr<DBConnection> db, OrderPtr order, bool edit);
    ~OrderDialog();

private slots:
    void on_buttonBox_accepted();

private:
    void createOrder();
    void updateOrder();

    Ui::OrderDialog *ui;
    DBConnectionPtr m_db;
    OrderPtr m_order;
    bool m_create;

    CustomerPtr m_customer;
};

