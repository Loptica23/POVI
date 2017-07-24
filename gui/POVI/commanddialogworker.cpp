#include <QWidget>
#include <QMessageBox>
#include "commanddialogworker.h"
#include "mainwindow.h"
#include "ui_commanddialog.h"
#include "tasktypes.h"

CommandDialogWorker::CommandDialogWorker(QWidget *parent, std::shared_ptr<DBConnection> db, CommandPtr command, bool edit):
    CommandDialog(parent, db, command, edit)
{
    setUpWindowByWorkPosition();
}

CommandDialogWorker::~CommandDialogWorker()
{
    qDebug() << "Destrukcija izvede klase naloga za radnike";
}

void CommandDialogWorker::setUpWindowByWorkPosition()
{
    removeWidget(ui->storekeeper);
    removeWidget(ui->tasks);
    removeWidget(ui->priorityWidget);
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
        ui->buttonBox->button(QDialogButtonBox::Ok)->setText("Posalji nalog u zavrseno stanje!");
        ui->buttonBox->button(QDialogButtonBox::Cancel)->setText("Ostavi nalog!");
        showContinueToWorkButton();
    }

    this->repaint();

    showMaximized();

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

void CommandDialogWorker::backToDefaultScreen()
{
    if (m_edit)
    {
        auto mainWindow = MainWindow::getMainWindow();
        mainWindow->backToDefaultScreen();
    }
}
