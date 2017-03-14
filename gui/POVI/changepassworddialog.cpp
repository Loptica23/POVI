#include <QPushButton>
#include <QMessageBox>
#include "changepassworddialog.h"
#include "ui_changepassworddialog.h"
#include "mainwindow.h"

ChangePasswordDialog::ChangePasswordDialog(QWidget *parent, DBConnectionPtr db) :
    QDialog(parent),
    ui(new Ui::ChangePasswordDialog),
    m_db(db)
{
    ui->setupUi(this);
    setEnableToAcceptButton();
}

ChangePasswordDialog::~ChangePasswordDialog()
{
    delete ui;
}

void ChangePasswordDialog::on_buttonBox_accepted()
{
    QString username = MainWindow::getLogedUser()->getUserName();
    EmployeePtr employee = m_db->getEmployee(username);
    if (!employee)
    {
        qDebug() << "greska ne moze se naci logovani korisnik u bazi!";
        return;
    }
    if (employee->checkPWD(ui->oldpassword->text()))
    {
        employee->setPWD(ui->newpassword->text());
        if (!m_db->updateEmployee(employee))
        {
            QString error = m_db->getLastError();
            QMessageBox messageBox;
            messageBox.critical(this, "Greska", error);
        }
        else
        {
            //uspesno je zamenjen password
        }
    }
    else
    {
        QString error = "Uneli ste pogresnu lozinku!";
        QMessageBox messageBox;
        messageBox.critical(this, "Greska", error);
    }
}

void ChangePasswordDialog::on_oldpassword_textChanged(const QString &arg1)
{
    m_oldPassword = arg1;
    setEnableToAcceptButton();
}

void ChangePasswordDialog::on_newpassword_textChanged(const QString &arg1)
{
    m_newPassword = arg1;
    setEnableToAcceptButton();
}

void ChangePasswordDialog::setEnableToAcceptButton()
{
    if (!m_oldPassword.isEmpty() && !m_confirmNewPassword.isEmpty() && !m_newPassword.isEmpty() && (m_confirmNewPassword == m_newPassword))
    {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
    }
    else
    {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    }
}

void ChangePasswordDialog::on_confirmnewpassword_textChanged(const QString &arg1)
{
    m_confirmNewPassword = arg1;
    setEnableToAcceptButton();
}
