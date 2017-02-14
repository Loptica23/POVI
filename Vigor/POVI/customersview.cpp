#include <memory>
#include <vector>
#include <QDebug>
#include "ui_customersview.h"
#include "customersview.h"
#include "dbconnection.h"
#include "customersdialog.h"
#include "mainwindow.h"
#include "ordersview.h"
#include "orderdialog.h"


CustomersView::CustomersView(QWidget *parent, std::shared_ptr<DBConnection> db):
    QWidget(parent),
    ui(new Ui::CustomersView),
    m_db(db)
{
    ui->setupUi(this);
    ui->tableWidget->resizeColumnsToContents();
}

CustomersView::~CustomersView()
{
    delete ui;
}

void CustomersView::on_AddNewCustomer_clicked()
{
    auto customerDialog = new CustomersDialog(this, m_db);
    customerDialog->show();
}



void CustomersView::on_Refresh_clicked()
{
    m_editButtons.clear(); //*****************************************************ovde moras da dodas sve vektore dugmica
    m_viewOrdersButtons.clear();
    ui->tableWidget->setRowCount(0);
    auto customers = m_db->getCustomers();
    qDebug() << "user refreshing customers view!";
    if (!customers || customers->empty())
    {
        return;
    }
    m_customers = customers;
    auto i = 0;
    for (auto iter = customers->begin(); iter != customers->end(); ++i, ++iter)
    {
        ui->tableWidget->insertRow(i);
        {
            auto *item = new QTableWidgetItem((*iter)->getName());
            ui->tableWidget->setItem(i, 0,item);
        }
        {
            QPushButton* btn_edit = new QPushButton();
            btn_edit->setText("Izmeni");
            ui->tableWidget->setIndexWidget(ui->tableWidget->model()->index(i, 1), btn_edit);
            m_editButtons.push_back(btn_edit);
            connect(btn_edit, SIGNAL(clicked()), this, SLOT(edit()));
        }
        {
            QPushButton* btn_createOrder = new QPushButton();
            btn_createOrder->setText("Nova Porudzbina");
            ui->tableWidget->setIndexWidget(ui->tableWidget->model()->index(i, 2), btn_createOrder);
            m_newOrderButtons.push_back(btn_createOrder);
            connect(btn_createOrder, SIGNAL(clicked()), this, SLOT(createOrderForCustomer()));  // ne sme da stoji edit!!
        }
        {
            QPushButton* btn_viewOrder = new QPushButton();
            btn_viewOrder->setText("Pregled Porudzbina");
            ui->tableWidget->setIndexWidget(ui->tableWidget->model()->index(i, 3), btn_viewOrder);
            m_viewOrdersButtons.push_back(btn_viewOrder);
            connect(btn_viewOrder, SIGNAL(clicked()), this, SLOT(showOrdersForCustomer()));
        }
    }
    ui->tableWidget->resizeColumnsToContents();
}

void CustomersView::edit()
{
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
    if(std::find(m_editButtons.begin(), m_editButtons.end(), buttonSender) != m_editButtons.end())
    {
        auto index = std::find(m_editButtons.begin(), m_editButtons.end(), buttonSender) - m_editButtons.begin();
        qDebug() << index;
        auto customerDialog = new CustomersDialog(this, m_db, m_customers->at(index));
        customerDialog->show();
    }
}

void CustomersView::showOrdersForCustomer()
{
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
    if(std::find(m_viewOrdersButtons.begin(), m_viewOrdersButtons.end(), buttonSender) != m_viewOrdersButtons.end())
    {
        auto index = std::find(m_viewOrdersButtons.begin(), m_viewOrdersButtons.end(), buttonSender) - m_viewOrdersButtons.begin();
        qDebug() << index;
        auto mainWindow = MainWindow::getMainWindow();
        std::shared_ptr<QWidget> orderView(new OrdersView(mainWindow, m_db, m_customers->at(index)));
        mainWindow->forward(orderView);
    }

}

void CustomersView::createOrderForCustomer()
{
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
    if(std::find(m_newOrderButtons.begin(), m_newOrderButtons.end(), buttonSender) != m_newOrderButtons.end())
    {
        auto index = std::find(m_newOrderButtons.begin(), m_newOrderButtons.end(), buttonSender) - m_newOrderButtons.begin();
        qDebug() << index;
        auto orderdialog = new OrderDialog(this, m_db, m_customers->at(index));
        qDebug() << m_customers->at(index)->getId();
        orderdialog->show();
    }
}
