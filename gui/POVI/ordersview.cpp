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
    m_editButtons.clear();
    m_detailsButtons.clear();
    m_createCommandButtons.clear();
    m_viewCommands.clear();
    ui->tableWidget->setRowCount(0);
    auto orders = m_db->getOrders(m_customer);
    qDebug() << "user refreshing orders view!";
    if (!orders || orders->empty())
    {
        return;
    }
    m_orders = orders;
    auto i = 0;
    for (auto iter = orders->begin(); iter != orders->end(); ++i, ++iter)
    {
        ui->tableWidget->insertRow(i);
        {
            auto *item = new QTableWidgetItem((*iter)->getHeader());
            ui->tableWidget->setItem(i, 0,item);
        }
        {
            auto *item = new QTableWidgetItem((*iter)->getTimeLimitString());
            ui->tableWidget->setItem(i, 1,item);
        }
/*        {
            auto *item = new QTableWidgetItem(QString::number((*iter)->getPrice()));
            ui->tableWidget->setItem(i, 2,item);
        }
*/
//        {
//            auto *item = new QTableWidgetItem((*iter)->getStateQString());
//            ui->tableWidget->setItem(i, 3,item);
//        }
        {
            QPushButton* btn_details = new QPushButton();
            btn_details->setText("Detalji");
            ui->tableWidget->setIndexWidget(ui->tableWidget->model()->index(i, 2), btn_details);
            m_detailsButtons.push_back(btn_details);
            connect(btn_details, SIGNAL(clicked()), this, SLOT(details()));
        }
        {
            QPushButton* btn_edit = new QPushButton();
            btn_edit->setText("Izmeni");
            ui->tableWidget->setIndexWidget(ui->tableWidget->model()->index(i, 3), btn_edit);
            m_editButtons.push_back(btn_edit);
            connect(btn_edit, SIGNAL(clicked()), this, SLOT(edit()));
        }
        {
            QPushButton* btn_createCommand = new QPushButton();
            btn_createCommand->setText("Napravi nalog");
            ui->tableWidget->setIndexWidget(ui->tableWidget->model()->index(i, 4), btn_createCommand);
            m_createCommandButtons.push_back(btn_createCommand);
            connect(btn_createCommand, SIGNAL(clicked()), this, SLOT(createCommand()));
        }
        {
            QPushButton* btn_viewCommands = new QPushButton();
            btn_viewCommands->setText("Pregled naloga");
            ui->tableWidget->setIndexWidget(ui->tableWidget->model()->index(i, 5), btn_viewCommands);
            m_viewCommands.push_back(btn_viewCommands);
            connect(btn_viewCommands, SIGNAL(clicked()), this, SLOT(viewCommands()));
        }
    }
    ui->tableWidget->resizeColumnsToContents(); //ovo ne smes ovako da radis zato sto je mnogo karaktera u naslovu

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
