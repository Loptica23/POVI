#include <algorithm>
#include <vector>
#include <QSqlQuery>
#include <QDebug>
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
    ui->tableWidget->resizeColumnsToContents();
    refresh();
}

EmpoyersView::~EmpoyersView()
{
    delete ui;
}

void EmpoyersView::refresh()
{
    m_buttons.clear();
    ui->tableWidget->setRowCount(0);
    auto employees = m_db->getEmployees();
    qDebug() << "user refreshing employees view!";
    if (!employees || employees->empty())
    {
        return;
    }
    m_employees = employees;
    auto i = 0;
    for (auto iter = employees->begin(); iter != employees->end(); ++i, ++iter)
    {
        ui->tableWidget->insertRow(i);
        {
            auto *item = new QTableWidgetItem((*iter)->getFirstName());
            ui->tableWidget->setItem(i, 0,item);
            ui->tableWidget->resizeRowToContents(0);
        }
        {
            auto *item = new QTableWidgetItem((*iter)->getSecondName());
            ui->tableWidget->setItem(i, 1,item);
            ui->tableWidget->resizeRowToContents(1);
        }
        {
            auto *item = new QTableWidgetItem((*iter)->getUserName());
            ui->tableWidget->setItem(i, 2,item);
            ui->tableWidget->resizeRowToContents(2);
        }
        {
            auto *item = new QTableWidgetItem((*iter)->getWorkPositionQString());
            ui->tableWidget->setItem(i, 3,item);
            ui->tableWidget->resizeRowToContents(3);
        }
        {
            if ((*iter)->getActivation())
            {
                auto *item = new QTableWidgetItem("da");
                ui->tableWidget->setItem(i, 4,item);
            }
            else
            {
                auto *item = new QTableWidgetItem("ne");
                ui->tableWidget->setItem(i, 4,item);
            }
        }
        {
            QPushButton* btn_edit = new QPushButton();
            btn_edit->setText("Izmeni");
            ui->tableWidget->setIndexWidget(ui->tableWidget->model()->index(i, 5), btn_edit);
            m_buttons.push_back(btn_edit);
            connect(btn_edit, SIGNAL(clicked()), this, SLOT(edit()));
        }
    }
    ui->tableWidget->resizeColumnsToContents();
}

void EmpoyersView::paintEvent(QPaintEvent *event)
{

}

void EmpoyersView::on_Refresh_clicked()
{
    refresh();
}

void EmpoyersView::on_CreateEmployee_clicked()
{
    auto creatingNewEmployeeDialog = new DialogForCreatingNewEmployee(this, m_db, this);
    creatingNewEmployeeDialog->show();
}

void EmpoyersView::edit()
{
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
    if(std::find(m_buttons.begin(), m_buttons.end(), buttonSender) != m_buttons.end())
    {
        auto index = std::find(m_buttons.begin(), m_buttons.end(), buttonSender) - m_buttons.begin();
        qDebug() << index;
        auto creatingNewEmployeeDialog = new DialogForCreatingNewEmployee(this, m_db, m_employees->at(index), this);
        creatingNewEmployeeDialog->show();
    }
}
