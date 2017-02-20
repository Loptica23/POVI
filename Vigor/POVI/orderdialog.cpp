#include "orderdialog.h"
#include "ui_orderdialog.h"
#include <QMessageBox>
#include <QDebug>
#include <QDate>
#include <QPushButton>

OrderDialog::OrderDialog(QWidget *parent, std::shared_ptr<DBConnection> db, CustomerPtr customer) :
    QDialog(parent),
    ui(new Ui::OrderDialog),
    m_db(db),
    m_create(true),
    m_customer(customer)
{
    ui->setupUi(this);
}

OrderDialog::OrderDialog(QWidget *parent, std::shared_ptr<DBConnection> db, OrderPtr order, bool edit) :
    QDialog(parent),
    ui(new Ui::OrderDialog),
    m_db(db),
    m_create(false),
    m_order(order)
{
    ui->setupUi(this);

    ui->Header->setText(order->getHeader());
    ui->Description->setText(order->getDescription());
    qDebug() << order->getTimeLimit();

    QString str = order->getTimeLimit().left(10);
    QDate date = QDate::fromString(str, "yyyy-MM-dd");
    ui->calendarWidget->setSelectedDate(date);

    if (!edit)
    {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    }
}

OrderDialog::~OrderDialog()
{
    delete ui;

}

void OrderDialog::createOrder()
{
    OrderPtr order(new Order(m_customer->getId()));
    if (!ui->Header->text().isEmpty())
    {
        order->setHeader(ui->Header->text());
    }
    if (!ui->Description->toPlainText().isEmpty())
    {
        order->setDescription(ui->Description->toPlainText());
    }

    QString date = ui->calendarWidget->selectedDate().toString("yyyy-MM-dd");
    QString timeLimit = date + " 00:00:00";
    order->setTimeLimit(timeLimit);

    order->setState(Order::State::New);

    if (!m_db->createNewOrder(order))
    {
        QString error = m_db->getLastError();
        QMessageBox messageBox;
        messageBox.critical(0,"Error",error);
    }
}

void OrderDialog::updateOrder()
{
    if (!ui->Header->text().isEmpty())
    {
        m_order->setHeader(ui->Header->text());
    }
    if (!ui->Description->toPlainText().isEmpty())
    {
        m_order->setDescription(ui->Description->toPlainText());
    }

    QString date = ui->calendarWidget->selectedDate().toString("yyyy-MM-dd");
    QString timeLimit = date + " 00:00:00";
    m_order->setTimeLimit(timeLimit);

    if (m_order->isModified())
    {
        if(!m_db->updateOrder(m_order))
        {
            QString error = m_db->getLastError();
            QMessageBox messageBox;
            messageBox.critical(0,"Error",error);
        }
    }
}

void OrderDialog::on_buttonBox_accepted()
{
    if (m_create)
    {
        createOrder();
    }
    else
    {
        updateOrder();
    }
}
