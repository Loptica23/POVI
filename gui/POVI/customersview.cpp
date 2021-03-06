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
    refresh();
}

CustomersView::~CustomersView()
{
    delete ui;
}

void CustomersView::refresh()
{
    qDebug() << "user refreshing customers view!";
    clearTable();
    if (!getCustomers())
    {
        return;
    }
    auto i = 0;
    for (auto iter = m_customers->begin(); iter != m_customers->end(); ++i, ++iter)
    {
        auto j = 0;
        CustomerPtr customer = *iter;
        ui->tableWidget->insertRow(i);
        insertName(customer, i, j++);
        insertEditButton(i, j++);
        insertNewOrderButton(i, j++);
        insertOrdersViewButton(i, j++);
    }
    ui->tableWidget->resizeColumnsToContents();
}

void CustomersView::clearTable()
{
    m_editButtons.clear();
    m_viewOrdersButtons.clear();
    m_newOrderButtons.clear();
    ui->tableWidget->setRowCount(0);
}

bool CustomersView::getCustomers()
{
    auto customers = m_db->getCustomers();
    if (!customers || customers->empty())
    {
        return false;
    }
    m_customers = customers;
    return true;
}

void CustomersView::insertName(CustomerPtr customer, unsigned i, unsigned j)
{
    auto *item = new QTableWidgetItem(customer->getName());
    ui->tableWidget->setItem(i, j, item);
}

void CustomersView::insertEditButton(unsigned i, unsigned j)
{
    QPushButton* btn_edit = new QPushButton();
    btn_edit->setText("Izmeni");
    ui->tableWidget->setIndexWidget(ui->tableWidget->model()->index(i, j), btn_edit);
    m_editButtons.push_back(btn_edit);
    connect(btn_edit, SIGNAL(clicked()), this, SLOT(edit()));
}

void CustomersView::insertNewOrderButton(unsigned i, unsigned j)
{
    QPushButton* btn_createOrder = new QPushButton();
    btn_createOrder->setText("Nova Porudzbina");
    ui->tableWidget->setIndexWidget(ui->tableWidget->model()->index(i, j), btn_createOrder);
    m_newOrderButtons.push_back(btn_createOrder);
    connect(btn_createOrder, SIGNAL(clicked()), this, SLOT(createOrderForCustomer()));
}

void CustomersView::insertOrdersViewButton(unsigned i, unsigned j)
{
    QPushButton* btn_viewOrder = new QPushButton();
    btn_viewOrder->setText("Pregled Porudzbina");
    ui->tableWidget->setIndexWidget(ui->tableWidget->model()->index(i, j), btn_viewOrder);
    m_viewOrdersButtons.push_back(btn_viewOrder);
    connect(btn_viewOrder, SIGNAL(clicked()), this, SLOT(showOrdersForCustomer()));
}

void CustomersView::on_AddNewCustomer_clicked()
{
    auto customerDialog = new CustomersDialog(this, m_db, this);
    customerDialog->show();
}

void CustomersView::on_Refresh_clicked()
{
    refresh();
}

void CustomersView::edit()
{
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
    if(std::find(m_editButtons.begin(), m_editButtons.end(), buttonSender) != m_editButtons.end())
    {
        auto index = std::find(m_editButtons.begin(), m_editButtons.end(), buttonSender) - m_editButtons.begin();
        qDebug() << index;
        auto customerDialog = new CustomersDialog(this, m_db, m_customers->at(index), this);
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
        auto orderdialog = new OrderDialog(this, m_db, m_customers->at(index), this);
        qDebug() << m_customers->at(index)->getId();
        orderdialog->show();
    }
}
