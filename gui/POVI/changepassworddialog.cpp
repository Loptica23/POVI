#include <QPushButton>
#include "changepassworddialog.h"
#include "ui_changepassworddialog.h"

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
    if (!m_oldPassword.isEmpty() && !m_newPassword.isEmpty() && (m_oldPassword == m_newPassword))
    {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
    }
    else
    {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    }
}
