#include "orderdialog.h"
#include "ui_orderdialog.h"
#include <QMessageBox>
#include <QDebug>
#include <QDate>
#include <QPushButton>

OrderDialog::OrderDialog(QWidget *parent, std::shared_ptr<DBConnection> db, CustomerPtr customer, Refreshable *refreshable) :
    QDialog(parent),
    Refresher(refreshable),
    ui(new Ui::OrderDialog),
    m_db(db),
    m_create(true),
    m_customer(customer)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
}

OrderDialog::OrderDialog(QWidget *parent, std::shared_ptr<DBConnection> db, OrderPtr order, bool edit, Refreshable *refreshable) :
    QDialog(parent),
    Refresher(refreshable),
    ui(new Ui::OrderDialog),
    m_db(db),
    m_create(false),
    m_order(order)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);

    ui->Header->setText(order->getHeader());
    ui->Description->setText(order->getDescription());
    qDebug() << order->getTimeLimit();

    ui->calendarWidget->setSelectedDate(order->getTimeLimit().date());

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

    QDateTime dateTime;
    dateTime.setDate(ui->calendarWidget->selectedDate());
    order->setTimeLimit(dateTime);

    //order->setState(Order::State::New);

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

    QDateTime dateTime;
    dateTime.setDate(ui->calendarWidget->selectedDate());
    m_order->setTimeLimit(dateTime);

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
