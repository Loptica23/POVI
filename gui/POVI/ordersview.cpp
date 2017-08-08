#include <QDebug>
#include "ordersview.h"
#include "ui_ordersview.h"
#include "mainwindow.h"
#include "orderdialog.h"
#include "commandsview.h"

OrdersView::OrdersView(QWidget *parent, std::shared_ptr<DBConnection> db, CustomerPtr customer) :
    QWidget(parent),
    ui(new Ui::OrdersView),
    m_db(db),
    m_customer(customer)
{
    ui->setupUi(this);
    ui->tableWidget->resizeColumnsToContents();
    ui->label->setText("Pregled porudzbina za klijenta " + customer->getName() + ":");
    refresh();
}

OrdersView::~OrdersView()
{
    delete ui;
}

void OrdersView::refresh()
{
    clearTable();
    if (!getOrders())
    {
        return;
    }
    auto i = 0;
    for (auto iter = m_orders->begin(); iter != m_orders->end(); ++i, ++iter)
    {
        auto j = 0;
        ui->tableWidget->insertRow(i);
        OrderPtr order = *iter;

        insertHeader(order, i, j++);
        insertTimeLimmit(order, i, j++);
        insertDetailsButton(i, j++);
        insertEditButton(i, j++);
        insertCommandsViewButton(i, j++);
    }
    ui->tableWidget->resizeColumnsToContents(); //ovo ne smes ovako da radis zato sto je mnogo karaktera u naslovu

}

void OrdersView::clearTable()
{
    m_editButtons.clear();
    m_detailsButtons.clear();
    m_createCommandButtons.clear();
    m_viewCommands.clear();
    ui->tableWidget->setRowCount(0);
}

bool OrdersView::getOrders()
{
    auto orders = m_db->getOrders(m_customer);
    qDebug() << "user refreshing orders view!";
    if (!orders || orders->empty())
    {
        return false;
    }
    m_orders = orders;
    return true;
}

void OrdersView::insertHeader(OrderPtr order, unsigned i, unsigned j)
{
    auto *item = new QTableWidgetItem(order->getHeader());
    ui->tableWidget->setItem(i, j, item);
}

void OrdersView::insertTimeLimmit(OrderPtr order, unsigned i, unsigned j)
{
    auto *item = new QTableWidgetItem(order->getTimeLimitString());
    ui->tableWidget->setItem(i, j,item);
}

void OrdersView::insertDetailsButton(unsigned i, unsigned j)
{
    QPushButton* btn_details = new QPushButton();
    btn_details->setText("Detalji");
    ui->tableWidget->setIndexWidget(ui->tableWidget->model()->index(i, j), btn_details);
    m_detailsButtons.push_back(btn_details);
    connect(btn_details, SIGNAL(clicked()), this, SLOT(details()));
}

void OrdersView::insertEditButton(unsigned i, unsigned j)
{
    QPushButton* btn_edit = new QPushButton();
    btn_edit->setText("Izmeni");
    ui->tableWidget->setIndexWidget(ui->tableWidget->model()->index(i, j), btn_edit);
    m_editButtons.push_back(btn_edit);
    connect(btn_edit, SIGNAL(clicked()), this, SLOT(edit()));
}

void OrdersView::insertCommandsViewButton(unsigned i, unsigned j)
{
    QPushButton* btn_viewCommands = new QPushButton();
    btn_viewCommands->setText("Pregled naloga");
    ui->tableWidget->setIndexWidget(ui->tableWidget->model()->index(i, j), btn_viewCommands);
    m_viewCommands.push_back(btn_viewCommands);
    connect(btn_viewCommands, SIGNAL(clicked()), this, SLOT(viewCommands()));
}

void OrdersView::on_pushButton_clicked()
{
    auto orderdialog = new OrderDialog(this, m_db, m_customer, this);
    orderdialog->show();
}

void OrdersView::on_Refresh_clicked()
{
    refresh();
}

void OrdersView::edit()
{
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
    if(std::find(m_editButtons.begin(), m_editButtons.end(), buttonSender) != m_editButtons.end())
    {
        auto index = std::find(m_editButtons.begin(), m_editButtons.end(), buttonSender) - m_editButtons.begin();
        qDebug() << index;
        qDebug() << m_orders->size();
        auto ordersDialog = new OrderDialog(this, m_db, m_orders->at(index), true, this);
        ordersDialog->show();
    }
}


void OrdersView::details()
{
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
    if(std::find(m_detailsButtons.begin(), m_detailsButtons.end(), buttonSender) != m_detailsButtons.end())
    {
        auto index = std::find(m_detailsButtons.begin(), m_detailsButtons.end(), buttonSender) - m_detailsButtons.begin();
        qDebug() << index;
        qDebug() << m_orders->size();
        auto ordersDialog = new OrderDialog(this, m_db, m_orders->at(index), false, this);
        ordersDialog->show();
    }
}

void OrdersView::createCommand()
{
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
    if(std::find(m_createCommandButtons.begin(), m_createCommandButtons.end(), buttonSender) != m_createCommandButtons.end())
    {
        auto index = std::find(m_createCommandButtons.begin(), m_createCommandButtons.end(), buttonSender) - m_createCommandButtons.begin();
        qDebug() << index;
        qDebug() << m_orders->size();
//        auto ordersDialog = new OrderDialog(this, m_db, m_orders->at(index), false);
//        ordersDialog->show();
    }
}

void OrdersView::viewCommands()
{
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
    if(std::find(m_viewCommands.begin(), m_viewCommands.end(), buttonSender) != m_viewCommands.end())
    {
        auto index = std::find(m_viewCommands.begin(), m_viewCommands.end(), buttonSender) - m_viewCommands.begin();
        qDebug() << index;
        qDebug() << m_orders->size();
        auto mainWindow = MainWindow::getMainWindow();
        std::shared_ptr<QWidget> commandsView(new CommandsView(mainWindow, m_db, m_orders->at(index)));
        mainWindow->forward(commandsView);
        //ordersDialog->show();
    }
}

void OrdersView::on_Back_clicked()
{
    auto mainWindow = MainWindow::getMainWindow();
    mainWindow->back();
}
