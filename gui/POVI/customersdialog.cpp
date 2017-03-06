#include <QMessageBox>
#include "customersdialog.h"
#include "ui_customersdialog.h"
#include "dbconnection.h"
#include "customer.h"

CustomersDialog::CustomersDialog(QWidget *parent, DBConnectionPtr db):
    QDialog(parent),
    ui(new Ui::CustomersDialog),
    m_db(db),
    m_create(true)
{
    ui->setupUi(this);
}

CustomersDialog::CustomersDialog(QWidget *parent, DBConnectionPtr db, CustomerPtr customer):
    QDialog(parent),
    ui(new Ui::CustomersDialog),
    m_db(db),
    m_customer(customer),
    m_create(false)
{
    ui->setupUi(this);

    ui->Name->setText(m_customer->getName());

    m_customer->resetChangeTracking();
}

CustomersDialog::~CustomersDialog()
{
    delete ui;
}

void CustomersDialog::createCustomer()
{
    CustomerPtr customer(new Customer((unsigned)-1));
    if (!ui->Name->text().isEmpty())
    {
        customer->setName(ui->Name->text());
    }

    if (!m_db->createNewCustomer(customer))
    {
        QString error = m_db->getLastError();
        QMessageBox messageBox;
        messageBox.critical(0,"Error",error);
    }
}

void CustomersDialog::updateCustomer()
{
    if (!ui->Name->text().isEmpty())
    {
        m_customer->setName(ui->Name->text());
    }

    if (m_customer->isModified())
    {
        if (!m_db->updateCustomer(m_customer))
        {
            QString error = m_db->getLastError();
            QMessageBox messageBox;
            messageBox.critical(0,"Error",error);
        }
    }
}

void CustomersDialog::on_buttonBox_accepted()
{
    if (m_create)
    {
        createCustomer();
    }
    else
    {
        updateCustomer();
    }
}
