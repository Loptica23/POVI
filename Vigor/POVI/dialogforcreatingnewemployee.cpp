#include <QDebug>
#include "dialogforcreatingnewemployee.h"
#include "ui_dialogforcreatingnewemployee.h"
#include "dbconnection.h"
#include "QMessageBox"

DialogForCreatingNewEmployee::DialogForCreatingNewEmployee(QWidget *parent, DBConnectionPtr db, EmployeePtr employee) :
    QDialog(parent),
    ui(new Ui::DialogForCreatingNewEmployee),
    m_db(db),
    m_employee(employee),
    m_create(false)
{
    ui->setupUi(this);
    ui->FirstName->setText(m_employee->getFirstName());
    ui->SecondName->setText(m_employee->getSecondName());
    ui->UserName->setText(m_employee->getUserName());
    ui->Position->setCurrentIndex(m_employee->getWorkPositionQInt());
    if (m_employee->getActivation())
        ui->PristupSistemu->setCurrentIndex(0);
    else
        ui->PristupSistemu->setCurrentIndex(1);
    employee->resetChangeTracking();
}

DialogForCreatingNewEmployee::DialogForCreatingNewEmployee(QWidget *parent, DBConnectionPtr db) :
    QDialog(parent),
    ui(new Ui::DialogForCreatingNewEmployee),
    m_db(db),
    m_create(true)
{
    ui->setupUi(this);
}

DialogForCreatingNewEmployee::~DialogForCreatingNewEmployee()
{
    delete ui;
}

void DialogForCreatingNewEmployee::on_buttonBox_accepted()
{
    if (m_create)
    {
        createUser();
    }
    else
    {
        updateUser();
    }
}

void DialogForCreatingNewEmployee::createUser()
{
    EmployeePtr employee(new Employee(0));
    employee->setWorkPosition(ui->Position->currentIndex());
    if (ui->PristupSistemu->currentIndex() == 0)
    {
        employee->setActivation(true);
    }
    else
    {
        employee->setActivation(false);
    }
    employee->setFirstName(ui->FirstName->text());
    employee->setSecondName(ui->SecondName->text());
    employee->setUserName(ui->UserName->text());
    bool result = m_db->createNewEmployee(employee);
    if (!result)
    {
        QString error = m_db->getLastError();
        QMessageBox messageBox;
        messageBox.critical(0,"Error",error);
    }
}

void DialogForCreatingNewEmployee::updateUser()
{
    m_employee->setWorkPosition(ui->Position->currentIndex());
    if (ui->PristupSistemu->currentIndex() == 0)
    {
        m_employee->setActivation(true);
    }
    else
    {
        m_employee->setActivation(false);
    }
    m_employee->setFirstName(ui->FirstName->text());
    m_employee->setSecondName(ui->SecondName->text());
    m_employee->setUserName(ui->UserName->text());
    if (m_employee->isModified())
    {
        if (!m_db->updateEmployee(m_employee))
        {
            QString error = m_db->getLastError();
            QMessageBox messageBox;
            messageBox.critical(0,"Error",error);
        }
    }
}
