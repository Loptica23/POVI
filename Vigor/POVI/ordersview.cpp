#include "ordersview.h"
#include "ui_ordersview.h"
#include "mainwindow.h"
#include "orderdialog.h"
#include <QDebug>

OrdersView::OrdersView(QWidget *parent, std::shared_ptr<DBConnection> db, CustomerPtr customer) :
    QWidget(parent),
    ui(new Ui::OrdersView),
    m_db(db),
    m_customer(customer)
{
    ui->setupUi(this);
    ui->tableWidget->resizeColumnsToContents();
    ui->label->setText("Pregled porudzbina za klijenta " + customer->getName() + ":");
}

OrdersView::~OrdersView()
{
    delete ui;
}

void OrdersView::on_pushButton_clicked()
{
    auto orderdialog = new OrderDialog(this, m_db, m_customer);
    orderdialog->show();
}

void OrdersView::on_Refresh_clicked()
{
    m_editButtons.clear();
    m_detailsButtons.clear();
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
            auto *item = new QTableWidgetItem((*iter)->getTimeLimit());
            ui->tableWidget->setItem(i, 1,item);
        }
        {
            auto *item = new QTableWidgetItem(QString::number((*iter)->getPrice()));
            ui->tableWidget->setItem(i, 2,item);
        }
        {
            auto *item = new QTableWidgetItem((*iter)->getStateQString());
            ui->tableWidget->setItem(i, 3,item);
        }
        {
            auto *item = new QTableWidgetItem((*iter)->getDescription());
            ui->tableWidget->setItem(i, 4,item);
        }
        {
            QPushButton* btn_edit = new QPushButton();
            btn_edit->setText("Izmeni");
            ui->tableWidget->setIndexWidget(ui->tableWidget->model()->index(i, 5), btn_edit);
            m_editButtons.push_back(btn_edit);
            connect(btn_edit, SIGNAL(clicked()), this, SLOT(edit()));
        }
    }
    ui->tableWidget->resizeColumnsToContents(); //ovo ne smes ovako da radis zato sto je mnogo karaktera u naslovu
}

void OrdersView::edit()
{
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
    if(std::find(m_editButtons.begin(), m_editButtons.end(), buttonSender) != m_editButtons.end())
    {
        auto index = std::find(m_editButtons.begin(), m_editButtons.end(), buttonSender) - m_editButtons.begin();
        qDebug() << index;
        qDebug() << m_orders->size();
        auto ordersDialog = new OrderDialog(this, m_db, m_orders->at(index));
        ordersDialog->show();
    }
}

void OrdersView::on_Back_clicked()
{
    auto mainWindow = MainWindow::getMainWindow();
    mainWindow->back();
}
