#include <QMessageBox>
#include "commanddialogstorekeeper.h"
#include "ui_commanddialog.h"
#include "mainwindow.h"

CommandDialogStoreKeeper::CommandDialogStoreKeeper(QWidget *parent, std::shared_ptr<DBConnection> db, CommandPtr command, bool edit, Refreshable *refreshable) :
    CommandDialog(parent, db, command, edit, refreshable)
{
    setUpWindowByWorkPosition();
    storeKeeperDescriptionChanged();
    qDebug() << "Magacioner";
}

CommandDialogStoreKeeper::~CommandDialogStoreKeeper()
{

}

void CommandDialogStoreKeeper::setUpWindowByWorkPosition()
{
    removeWidget(ui->tasks);
    removeWidget(ui->priorityWidget);
    removeWidget(ui->finishQuantity);
    removeInvoiceWidgetIfTaskDontNeedIt();

    ui->commandNumber->setEnabled(false);
    ui->specification->setReadOnly(true);
    ui->quantity->setReadOnly(true);
    ui->comercialistDescription->setReadOnly(true);
    ui->designerDescription->setReadOnly(true);

    auto machine = m_db->getMachine(m_currentTask->getMachineId());
    if (machine)
        ui->machine->setText(machine->getName());

    if (m_edit)
    {
        this->showMaximized();
        ui->buttonBox->button(QDialogButtonBox::Ok)->setText("Posalji nalog u zavrseno stanje!");
        ui->buttonBox->button(QDialogButtonBox::Cancel)->setText("Ostavi nalog!");
    }

    this->repaint();
}

void CommandDialogStoreKeeper::updateCommand()
{
    if (!ui->storekeeperDescription->toPlainText().isEmpty())
    {
        m_command->setStoreKeeperDescription(ui->storekeeperDescription->toPlainText());
    }

    if (m_command->isModified())
    {
        ifFalseShowDbError(m_db->updateCommand(m_command));
    }
}

void CommandDialogStoreKeeper::acceptButtonClicked()
{
    ifFalseShowDbError(m_db->completeCurrentTask(m_command, m_command->getQuantity()));
    if (m_haveItInvoice)
    {
        InvoicePtr invoice(new Invoice(m_currentTask, ui->invoiceDescription->toPlainText()));
        ifFalseShowDbError(m_db->createNewInvoice(invoice));
    }
}

void CommandDialogStoreKeeper::rejectButtonClicked()
{
    ifFalseShowDbError(m_db->leaveCurrentTask(m_command, MainWindow::getWorker(), m_command->getQuantity()));
}

void CommandDialogStoreKeeper::storeKeeperDescriptionChanged()
{
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(!m_storeKeeperDescriptionEmpty);
}
