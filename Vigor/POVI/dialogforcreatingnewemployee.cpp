#include "dialogforcreatingnewemployee.h"
#include "ui_dialogforcreatingnewemployee.h"
#include "dbconnection.h"
#include "QMessageBox"

DialogForCreatingNewEmployee::DialogForCreatingNewEmployee(QWidget *parent, DBConnectionPtr db) :
    QDialog(parent),
    ui(new Ui::DialogForCreatingNewEmployee),
    m_db(db)
{
    ui->setupUi(this);
}

DialogForCreatingNewEmployee::~DialogForCreatingNewEmployee()
{
    delete ui;
}

void DialogForCreatingNewEmployee::on_buttonBox_accepted()
{
    QString pos;
    switch (ui->Position->currentIndex())
    {
    case 0:
        pos = "adm";
        break;
    case 1:
        pos = "kom";
        break;
    case 2:
        pos = "pro";
        break;
    case 3:
        pos = "diz";
        break;
    case 4:
        pos = "pak";
        break;
    default:
        pos = "mag";
        break;
    }
    bool result = m_db->createNewEmployee(
                ui->FirstName->text(),
                ui->SecondName->text(),
                ui->UserName->text(),
                pos
                );
    if (!result)
    {
        QString error = m_db->getLastError();
        QMessageBox messageBox;
        messageBox.critical(0,"Error",error);
    }
}
