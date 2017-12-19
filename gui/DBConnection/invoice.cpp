#include "invoice.h"
#include "dbconnection.h"
#include <QDebug>

Invoice::Invoice(TaskPtr task, QString text):
    m_id(0),
    m_task(task),
    m_text(text),
    m_created(true)
{
    resetChangeTracking();
}

Invoice::Invoice(unsigned id, TaskPtr task, QString text):
    m_id(id),
    m_task(task),
    m_text(text),
    m_created(false)
{
    resetChangeTracking();
}

Invoice::~Invoice()
{

}

//geters
unsigned Invoice::getId() const
{
    return m_id;
}

TaskPtr Invoice::getTask() const
{
    return m_task;
}

const QString & Invoice::getText() const
{
    return m_text;
}

//seters
void Invoice::setText(const QString & text)
{
    m_text = text;
}

//statemants
QString Invoice::statemantForCreating() const
{
    QString stm;
    stm = "insert into faktura ("
          "Zadatak_idZadatak,"
          "Zadatak_Nalog_idNalog,"
          "Zadatak_Nalog_idNarudzbina,"
          "Zadatak_Nalog_idKlijent,"
          "Zadatak_TipoviZadatka_idTipoviZadatka,"
          "Zadatak_Radnik_idRadnik,"
          "Text"
          ") values (";
    stm += QString::number(m_task->getId()) + ", ";
    stm += QString::number(m_task->getCommand()->getID()) + ", ";
    stm += QString::number(m_task->getCommand()->getIdOrder()) + ", ";
    stm += QString::number(m_task->getCommand()->getIdCustomer()) + ", ";
    stm += QString::number(m_task->getTaskTypeId())+ ", ";
    stm += QString::number(m_task->getWorkerId()) + ", ";
    stm += "'" + DBConnection::escape(m_text) + "');";
    qDebug() << stm;
    return stm;
}

QString Invoice::statemantForUpdating() const
{
    QString stm;
    if (isModified())
    {
        stm = "update faktura set ";
        if (m_textChanged)
        {
            stm += "Text = '" +getText() + "', ";
        }
        stm.chop(2);
        stm += " where idFaktura = " + QString::number(m_id) + ";";
        qDebug() << stm;
    }
    return stm;
}

QString Invoice::statementForDeleting() const
{
    QString stm;
    stm = "delete from faktura where idFaktura = " + QString::number(getId()) + ";";
    return stm;
}

bool Invoice::isModified() const
{
    return m_textChanged;
}

bool Invoice::isCreated() const
{
    return m_created;
}

void Invoice::resetChangeTracking()
{
    m_textChanged = false;
}

InvoicePtrVtr Invoice::createInvoicesFromQueryAndCommand(QSqlQuery& query, TaskPtr task)
{
    InvoicePtrVtr invoices(new InvoiceVtr());
    while(query.next())
    {
        InvoicePtr invoice(new Invoice(query.value("idFaktura").toUInt(),task, query.value("text").toString()));
        invoices->push_back(invoice);
    }
    return invoices;
}
