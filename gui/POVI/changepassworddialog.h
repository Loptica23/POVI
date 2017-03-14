#pragma once
#include <QDialog>
#include "DBConnection/dbconnection.h"

namespace Ui {
class ChangePasswordDialog;
}

class ChangePasswordDialog : public QDialog
{
    Q_OBJECT

public:
    ChangePasswordDialog(QWidget *parent, DBConnectionPtr db);
    ~ChangePasswordDialog();

private slots:
    void on_buttonBox_accepted();
    void on_oldpassword_textChanged(const QString &arg1);
    void on_newpassword_textChanged(const QString &arg1);

    void on_confirmnewpassword_textChanged(const QString &arg1);

private:
    void setEnableToAcceptButton();

    Ui::ChangePasswordDialog *ui;
    DBConnectionPtr m_db;

    QString m_oldPassword;
    QString m_newPassword;
    QString m_confirmNewPassword;
};

