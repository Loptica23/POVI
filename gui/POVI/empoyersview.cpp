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
    clearTable();
    auto employees = m_db->getEmployees();
    m_employees = employees;
    qDebug() << "user refreshing employees view!";
    if (!employees || employees->empty())
    {
        return;
    }
    auto i = 0;
    for (auto iter = employees->begin(); iter != employees->end(); ++i, ++iter)
    {
        auto j = 0;
        ui->tableWidget->insertRow(i);
        EmployeePtr employee = *iter;

        insertFirstName(employee, i,  j++);
        insertLastName(employee, i, j++);
        insertUserName(employee, i, j++);
        insertWorkPosition(employee, i, j++);
        insertActivation(employee, i, j++);
        insertEditButton(i, j++);
        insertResetPWDButton(i, j++);
    }
    ui->tableWidget->resizeColumnsToContents();
}

void EmpoyersView::clearTable()
{
    m_editButtons.clear();
    m_resetPWDButtons.clear();
    ui->tableWidget->setRowCount(0);
}

void EmpoyersView::insertFirstName(EmployeePtr employee, unsigned i, unsigned j)
{
    auto *item = new QTableWidgetItem(employee->getFirstName());
    ui->tableWidget->setItem(i, j,item);
    ui->tableWidget->resizeRowToContents(j);
}

void EmpoyersView::insertLastName(EmployeePtr employee, unsigned i, unsigned j)
{
    auto *item = new QTableWidgetItem(employee->getSecondName());
    ui->tableWidget->setItem(i, j,item);
    ui->tableWidget->resizeRowToContents(j);
}

void EmpoyersView::insertUserName(EmployeePtr employee, unsigned i, unsigned j)
{
    auto *item = new QTableWidgetItem(employee->getUserName());
    ui->tableWidget->setItem(i, j,item);
    ui->tableWidget->resizeRowToContents(j);
}

void EmpoyersView::insertWorkPosition(EmployeePtr employee, unsigned i, unsigned j)
{
    auto *item = new QTableWidgetItem(employee->getWorkPositionQString());
    ui->tableWidget->setItem(i, j,item);
    ui->tableWidget->resizeRowToContents(j);
}

void EmpoyersView::insertActivation(EmployeePtr employee, unsigned i, unsigned j)
{
    if (employee->getActivation())
    {
        auto *item = new QTableWidgetItem("da");
        ui->tableWidget->setItem(i, j,item);
    }
    else
    {
        auto *item = new QTableWidgetItem("ne");
        ui->tableWidget->setItem(i, j,item);
    }
}

void EmpoyersView::insertEditButton(unsigned i, unsigned j)
{
    {
        QPushButton* btn_edit = new QPushButton();
        btn_edit->setText("Izmeni");
        ui->tableWidget->setIndexWidget(ui->tableWidget->model()->index(i, j), btn_edit);
        m_editButtons.push_back(btn_edit);
        connect(btn_edit, SIGNAL(clicked()), this, SLOT(edit()));
    }
}

void EmpoyersView::insertResetPWDButton(unsigned i, unsigned j)
{
    {
        QPushButton* btn_reset = new QPushButton();
        btn_reset->setText("Resetuj sifru");
        ui->tableWidget->setIndexWidget(ui->tableWidget->model()->index(i, j), btn_reset);
        m_resetPWDButtons.push_back(btn_reset);
        connect(btn_reset, SIGNAL(clicked()), this, SLOT(resetPWD()));
    }
}

void EmpoyersView::paintEvent(QPaintEvent *)
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
    if(std::find(m_editButtons.begin(), m_editButtons.end(), buttonSender) != m_editButtons.end())
    {
        auto index = std::find(m_editButtons.begin(), m_editButtons.end(), buttonSender) - m_editButtons.begin();
        qDebug() << index;
        auto creatingNewEmployeeDialog = new DialogForCreatingNewEmployee(this, m_db, m_employees->at(index), this);
        creatingNewEmployeeDialog->show();
    }
}

void EmpoyersView::resetPWD()
{
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
    if(std::find(m_resetPWDButtons.begin(), m_resetPWDButtons.end(), buttonSender) != m_resetPWDButtons.end())
    {
        auto index = std::find(m_resetPWDButtons.begin(), m_resetPWDButtons.end(), buttonSender) - m_resetPWDButtons.begin();
        qDebug() << index;
        EmployeePtr employee = m_employees->at(index);
        employee->resetPWD();
        m_db->updateEmployee(employee);
    }
}
