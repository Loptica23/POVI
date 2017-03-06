#pragma once
#include <QDialog>
#include "dbconnection.h"
#include "customer.h"

namespace Ui {
class CustomersDialog;
}

class CustomersDialog : public QDialog
{
    Q_OBJECT

public:
    CustomersDialog(QWidget *parent, std::shared_ptr<DBConnection> db);
    CustomersDialog(QWidget *parent, std::shared_ptr<DBConnection> db, CustomerPtr customer);
    ~CustomersDialog();

private slots:
    void on_buttonBox_accepted();

private:
    void createCustomer();
    void updateCustomer();

    Ui::CustomersDialog *ui;
    std::shared_ptr<DBConnection> m_db;
    CustomerPtr m_customer;
    bool m_create;
};

