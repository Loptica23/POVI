#include <memory>
#include <vector>
#include <QDebug>
#include "ui_customersview.h"
#include "customersview.h"
#include "dbconnection.h"


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
//    auto creatingNewEmployeeDialog = new DialogForCreatingNewEmployee(this, m_db);
//    creatingNewEmployeeDialog->show();
}



void CustomersView::on_Refresh_clicked()
{
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
            m_buttons.push_back(btn_edit);
            connect(btn_edit, SIGNAL(clicked()), this, SLOT(edit()));
        }
        {
            QPushButton* btn_createOrder = new QPushButton();
            btn_createOrder->setText("Nova Porudzbina");
            ui->tableWidget->setIndexWidget(ui->tableWidget->model()->index(i, 2), btn_createOrder);
            m_buttons.push_back(btn_createOrder);
            connect(btn_createOrder, SIGNAL(clicked()), this, SLOT(edit()));  // ne sme da stoji edit!!
        }
        {
            QPushButton* btn_viewOrder = new QPushButton();
            btn_viewOrder->setText("Pregled Porudzbina");
            ui->tableWidget->setIndexWidget(ui->tableWidget->model()->index(i, 3), btn_viewOrder);
            m_buttons.push_back(btn_viewOrder);
            connect(btn_viewOrder, SIGNAL(clicked()), this, SLOT(edit()));  // ne sme da stoji edit!!
        }
    }
    ui->tableWidget->resizeColumnsToContents();
}

void CustomersView::edit()
{
    //implrementirati ovo, neophodno je napraviti novi prozor koji se otvara
}
