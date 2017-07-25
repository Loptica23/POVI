#pragma once
#include <QWidget>
#include <QPushButton>
#include "customer.h"
#include "dbconnection.h"
#include "refreshable.h"

namespace Ui {
class OrdersView;
}

class OrdersView : public QWidget, public Refreshable
{
    Q_OBJECT

public:
    OrdersView(QWidget *parent, std::shared_ptr<DBConnection> db, CustomerPtr customer);
    ~OrdersView();

    virtual void refresh();

private slots:
    void on_pushButton_clicked();
    void on_Refresh_clicked();
    void edit();
    void details();
    void createCommand();
    void viewCommands();
    void on_Back_clicked();

private:
    Ui::OrdersView *ui;
    std::shared_ptr<DBConnection> m_db;
    CustomerPtr m_customer;
    OrderPtrVtr m_orders;

    std::vector<QPushButton*> m_editButtons;
    std::vector<QPushButton*> m_detailsButtons;
    std::vector<QPushButton*> m_createCommandButtons;
    std::vector<QPushButton*> m_viewCommands;
};
