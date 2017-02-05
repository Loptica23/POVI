#include "QSqlQuery"
#include "empoyersview.h"
#include "ui_empoyersview.h"
#include "dbconnection.h"
#include "dialogforcreatingnewemployee.h"

EmpoyersView::EmpoyersView(QWidget *parent, std::shared_ptr<DBConnection> db) :
    QWidget(parent),
    ui(new Ui::EmpoyersView),
    m_db(db)
{
    ui->setupUi(this);
}

EmpoyersView::~EmpoyersView()
{
    delete ui;
}

void EmpoyersView::paintEvent(QPaintEvent *event)
{
    on_Refresh_clicked();
}

void EmpoyersView::on_Refresh_clicked()
{
    ui->tableWidget->setRowCount(0);
    auto emp = m_db->getEmployees();
    if (!emp)
    {
        //prikazi neku gresku
        return;
    }
    auto i = 0;
    while (emp->next())
    {
        ui->tableWidget->insertRow(i);
        {
            auto *item = new QTableWidgetItem(emp->value("Ime").toString());
            ui->tableWidget->setItem(i, 0,item);
        }
        {
            auto *item = new QTableWidgetItem(emp->value("Prezime").toString());
            ui->tableWidget->setItem(i, 1,item);
        }
        {
            auto *item = new QTableWidgetItem(emp->value("KorisnickoIme").toString());
            ui->tableWidget->setItem(i, 2,item);
        }
        {
            auto *item = new QTableWidgetItem(emp->value("Pozicija").toString());
            ui->tableWidget->setItem(i, 3,item);
        }
    }
}

void EmpoyersView::on_CreateEmployee_clicked()
{
    auto creatingNewEmployeeDialog = new DialogForCreatingNewEmployee(this, m_db);
    creatingNewEmployeeDialog->show();
}
