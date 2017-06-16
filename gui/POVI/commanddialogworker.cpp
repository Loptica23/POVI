#include <QWidget>
#include <QMessageBox>
#include "commanddialogworker.h"
#include "mainwindow.h"
#include "ui_commanddialog.h"
#include "tasktypes.h"

CommandDialogWorker::CommandDialogWorker(QWidget *parent, std::shared_ptr<DBConnection> db, CommandPtr command, bool edit):
    CommandDialog(parent, db, command, edit),
    m_haveItInvoice(false)
{
    setUpWindowByWorkPosition();
}

CommandDialogWorker::~CommandDialogWorker()
{

}

void CommandDialogWorker::setUpWindowByWorkPosition()
{
    removeWidget(ui->storekeeper);
    removeWidget(ui->tasks);
    removeWidget(ui->priorityWidget);
    removeInvoiceWidgetIfTaskDontNeedIt();

    ui->commandNumber->setEnabled(false);
    ui->comercialistDescription->setEnabled(false);
    ui->designer->setEnabled(false);
    //nalog je preuzet
    if (m_edit)
    {
        //this->showMaximized();
        ui->buttonBox->button(QDialogButtonBox::Ok)->setText("Posalji nalog u zavrseno stanje!");
        ui->buttonBox->button(QDialogButtonBox::Cancel)->setText("Ostavi nalog!");
    }

    this->repaint();

    qDebug()<< "konstruktor je zavrsio";
}

void CommandDialogWorker::acceptButtonClicked()
{
    ifFalseShowDbError(m_db->completeCurrentTask(m_command));
    if (m_haveItInvoice)
    {
        InvoicePtr invoice(new Invoice(m_currentTask, ui->invoiceDescription->toPlainText()));
        ifFalseShowDbError(m_db->createNewInvoice(invoice));
    }
}

void CommandDialogWorker::rejectButtonClicked()
{
    ifFalseShowDbError(m_db->leaveCurrentTask(m_command, MainWindow::getWorker()));
}

void CommandDialogWorker::removeInvoiceWidgetIfTaskDontNeedIt()
{
    m_haveItInvoice = true;
    if (m_currentTask)
    {
        TaskTypePtr taskType = m_db->getTaskTypes()->getTaskTypeById(m_currentTask->getTaskTypeId());
        if (!taskType->isVirtual())
        {
            removeWidget(ui->invoice);
            m_haveItInvoice = false;
        }
    }
}
