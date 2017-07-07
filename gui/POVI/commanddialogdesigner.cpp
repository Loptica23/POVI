#include <QWidget>
#include <QMessageBox>
#include "commanddialogdesigner.h"
#include "ui_commanddialog.h"
#include "mainwindow.h"

CommandDialogDesigner::CommandDialogDesigner(QWidget *parent, std::shared_ptr<DBConnection> db, CommandPtr command, bool edit) :
    CommandDialog(parent, db, command, edit)
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

    ui->commandNumber->setEnabled(false);
    ui->specification->setReadOnly(true);
    ui->quantity->setReadOnly(true);
    ui->comercialistDescription->setReadOnly(true);
    //nalog je preuzet
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
    ifFalseShowDbError(m_db->completeCurrentTask(m_command));
}

void CommandDialogDesigner::rejectButtonClicked()
{
    ifFalseShowDbError(m_db->leaveCurrentTask(m_command, MainWindow::getWorker()));
}

void CommandDialogDesigner::designerDescriptionChanged()
{
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(!m_designerDescriptionEmpty);
}
