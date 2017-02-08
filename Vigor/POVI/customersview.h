#pragma once

#include <QWidget>
#include <QPushButton>
#include "dbconnection.h"


class QPushButton;

namespace Ui {
class CustomersView;
}

class CustomersView : public QWidget
{
    Q_OBJECT

public:
    CustomersView(QWidget *parent, std::shared_ptr<DBConnection> db);
    ~CustomersView();

private slots:
    void on_AddNewCustomer_clicked();
    void on_Refresh_clicked();
    void edit();

private:
    Ui::CustomersView *ui;
    std::shared_ptr<DBConnection> m_db;
    CustomerPtrVtr m_customers;
    std::vector<QPushButton*> m_buttons;
};

