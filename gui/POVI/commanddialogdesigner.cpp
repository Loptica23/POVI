#include <QWidget>
#include <QMessageBox>
#include <QCloseEvent>
#include "commanddialogdesigner.h"
#include "ui_commanddialog.h"
#include "mainwindow.h"

CommandDialogDesigner::CommandDialogDesigner(QWidget *parent, std::shared_ptr<DBConnection> db, CommandPtr command, bool edit, Refreshable* refreshable) :
    CommandDialog(parent, db, command, edit, refreshable)
{
    setUpWindowByWorkPosition();
    designerDescriptionChanged();
    qDebug() << "Dizajner";
}

CommandDialogDesigner::~CommandDialogDesigner()
{

}

void CommandDialogDesigner::setUpWindowByWorkPosition()
{
    removeWidget(ui->storekeeper);
    removeWidget(ui->tasks);
    removeWidget(ui->priorityWidget);
    removeWidget(ui->invoice);
    removeWidget(ui->finishQuantity);
    removeWidget(ui->Priority);
    removeWidget(ui->label_5);

    ui->commandNumber->setEnabled(false);
    ui->specification->setReadOnly(true);
    ui->quantity->setReadOnly(true);
    ui->comboBox_2->setEnabled(false);
    ui->comercialistDescription->setReadOnly(true);
    //nalog je preuzet

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

void CommandDialogDesigner::updateCommand()
{
    if (!ui->designerDescription->toPlainText().isEmpty())
    {
        m_command->setDesignerDescription(ui->designerDescription->toPlainText());
    }

    if (m_command->isModified())
    {
        ifFalseShowDbError(m_db->updateCommand(m_command));
    }
}

void CommandDialogDesigner::acceptButtonClicked()
{
    completeCurrentTask();
}

void CommandDialogDesigner::rejectButtonClicked()
{
    leaveCurrentTask();
    updateCommand();
}

void CommandDialogDesigner::designerDescriptionChanged()
{
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(!m_designerDescriptionEmpty);
}

void CommandDialogDesigner::closeEvent(QCloseEvent * closeEvent)
{
    if (m_edit)
    {
        closeCommandDialogAndApp(closeEvent);
    }
}
