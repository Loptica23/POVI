#include <QWidget>
#include <QMessageBox>
#include "commanddialogworker.h"
#include "mainwindow.h"
#include "ui_commanddialog.h"
#include "tasktypes.h"

CommandDialogWorker::CommandDialogWorker(QWidget *parent, std::shared_ptr<DBConnection> db, CommandPtr command, bool edit, Refreshable *refreshable):
    CommandDialog(parent, db, command, edit, refreshable)
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
    removeQuantityIfOrderingTask();

    ui->commandNumber->setEnabled(false);
    ui->specification->setReadOnly(true);
    ui->quantity->setReadOnly(true);
    ui->comboBox_2->setEnabled(false);
    ui->comercialistDescription->setReadOnly(true);
    ui->designerDescription->setReadOnly(true);
    ui->Priority->setReadOnly(true);
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
    completeCurrentTask();
}

void CommandDialogWorker::rejectButtonClicked()
{
    leaveCurrentTask();
}

void CommandDialogWorker::backToDefaultScreen()
{
    if (m_edit)
    {
        auto mainWindow = MainWindow::getMainWindow();
        mainWindow->backToDefaultScreen();
    }
}

unsigned CommandDialogWorker::getQuantityDone()
{
    unsigned doneQuantity;
    if (ui->lineEdit->text().isEmpty())
    {
        doneQuantity = m_command->getQuantity();
    }
    else
    {
        doneQuantity = ui->lineEdit->text().toUInt();
    }

    return doneQuantity;
}

void CommandDialogWorker::removeQuantityIfOrderingTask()
{
    if (MainWindow::getLogedUser()->getWorkPosition() == Employee::WorkPosition::Narucilac)
    {
        removeWidget(ui->finishQuantity);
    }
}
