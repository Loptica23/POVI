#include "commanddialoginvoice.h"
#include "ui_commanddialog.h"
#include "mainwindow.h"

CommandDialogInvoice::CommandDialogInvoice(QWidget *parent, std::shared_ptr<DBConnection> db, CommandPtr command, bool edit) :
    CommandDialog(parent, db, command, edit)
{
    setUpWindowByWorkPosition();
}

CommandDialogInvoice::~CommandDialogInvoice()
{
}

void CommandDialogInvoice::setUpWindowByWorkPosition()
{
    removeWidget(ui->storekeeper);
    removeWidget(ui->tasks);
    removeWidget(ui->priorityWidget);

    ui->commandNumber->setEnabled(false);
    ui->comercialistDescription->setEnabled(false);
    ui->designer->setEnabled(false);
    ui->invoiceDescription->setEnabled(false);

    if (m_edit)
    {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setText("Posalji nalog u zavrseno stanje!");
        ui->buttonBox->button(QDialogButtonBox::Cancel)->setText("Ostavi nalog!");
    }

    initializeInvoiceDescription();

    showMaximized();
}

void CommandDialogInvoice::updateCommand()
{

}

void CommandDialogInvoice::acceptButtonClicked()
{
    ifFalseShowDbError(m_db->completeCurrentTask(m_command));
}

void CommandDialogInvoice::rejectButtonClicked()
{
    ifFalseShowDbError(m_db->leaveCurrentTask(m_command, MainWindow::getWorker()));
}

void CommandDialogInvoice::showContinueToWorkButtonByWorkPosition()
{
    auto cont = new QPushButton("Nastavi rad na nalogu!");
    ui->buttonBox->addButton(cont, QDialogButtonBox::DestructiveRole);
    connect(cont, SIGNAL(clicked(bool)), this, SLOT(continueToWorkOnCommand()));
}

void CommandDialogInvoice::initializeInvoiceDescription()
{
    QString text = "";
    TaskTypesPtr taskTypes = m_db->getTaskTypes();
    for (auto iter = m_tasks->begin(); iter != m_tasks->end(); ++iter)
    {
        TaskPtr task = *iter;
        if (taskTypes->getTaskTypeById(task->getTaskTypeId())->isVirtual())
        {
            InvoicePtrVtr invoices = m_db->getInvoices(task);
            InvoicePtr invoice;
            if (invoices != nullptr && invoices->size()>0)
            {
                invoice = *(invoices->begin());
                text += taskTypes->getStringById(task->getTaskTypeId());
                text += "\n\n";
                text += invoice->getText();
                text += "\n";
            }
        }
    }

    ui->invoiceDescription->setText(text);
}
