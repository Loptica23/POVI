#pragma once

#include <QWidget>
#include <QPushButton>
#include "dbconnection.h"
#include "refreshable.h"


class QPushButton;

namespace Ui {
class CustomersView;
}

class CustomersView : public QWidget, public Refreshable
{
    Q_OBJECT

public:
    CustomersView(QWidget *parent, std::shared_ptr<DBConnection> db);
    ~CustomersView();
    virtual void refresh();

private:
    void clearTable();
    bool getCustomers();
    void insertName(CustomerPtr customer, unsigned i, unsigned j);
    void insertEditButton(unsigned i, unsigned j);
    void insertNewOrderButton(unsigned i, unsigned j);
    void insertOrdersViewButton(unsigned i, unsigned j);

private slots:
    void on_AddNewCustomer_clicked();
    void on_Refresh_clicked();
    void edit();
    void showOrdersForCustomer();
    void createOrderForCustomer();

private:
    Ui::CustomersView *ui;
    std::shared_ptr<DBConnection> m_db;
    CustomerPtrVtr m_customers;
    std::vector<QPushButton*> m_editButtons;            //u ovim vektorima ima curenja memorije.. ako ih stavim da su shared onda imam problem sa utvrdjivanjem koje je dugme pritisnuto
    std::vector<QPushButton*> m_newOrderButtons;
    std::vector<QPushButton*> m_viewOrdersButtons;
};

