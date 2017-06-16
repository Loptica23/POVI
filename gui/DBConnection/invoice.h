#pragma once
#include "dbconnection_global.h"
#include "task.h"
#include <vector>
#include <QSqlQuery>
#include <QString>

class Invoice;
typedef std::shared_ptr<Invoice> InvoicePtr;
typedef std::vector<InvoicePtr> InvoiceVtr;
typedef std::shared_ptr<InvoiceVtr> InvoicePtrVtr;

//faktura
class DBCONNECTIONSHARED_EXPORT Invoice
{
public:

    //Ovaj konstruktor se poziva kada se kreira nova faktura
    Invoice(TaskPtr task, QString text);

    //Ovaj konstruktor se poziva kada faktura vec postoji
    Invoice(unsigned id, TaskPtr task, QString text);

    virtual ~Invoice();

    //geters
    unsigned getId() const;
    TaskPtr getTask() const;
    const QString & getText() const;

    //seters
    void setText(const QString & text);

    QString statemantForCreating() const;
    QString statemantForUpdating() const;
    QString statementForDeleting() const;

    bool isModified() const;
    bool isCreated() const;
    void resetChangeTracking();


    static InvoicePtrVtr createInvoicesFromQueryAndCommand(QSqlQuery& query, TaskPtr task);

private:
    unsigned m_id;
    bool m_created; //upravo kreiran, ne postoji u bazi podataka

    QString m_text;
    bool m_textChanged;

    TaskPtr m_task;
};
