#include <QMessageBox>
#include "commanddialogstorekeeper.h"
#include "ui_commanddialog.h"
#include "mainwindow.h"

CommandDialogStoreKeeper::CommandDialogStoreKeeper(QWidget *parent, std::shared_ptr<DBConnection> db, CommandPtr command, bool edit) :
    CommandDialog(parent, db, command, edit)
{
    setUpWindowByWorkPosition();
    storeKeeperDescriptionChanged();
}

CommandDialogStoreKeeper::~CommandDialogStoreKeeper()
{

}

void CommandDialogStoreKeeper::setUpWindowByWorkPosition()
{
    removeWidget(ui->tasks);
    removeWidget(ui->priorityWidget);

    ui->commandNumber->setEnabled(false);
    ui->comercialistDescription->setEnabled(false);
    ui->designerDescription->setEnabled(false);

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
    ifFalseShowDbError(m_db->completeCurrentTask(m_command));
}

void CommandDialogStoreKeeper::rejectButtonClicked()
{
    ifFalseShowDbError(m_db->leaveCurrentTask(m_command, MainWindow::getLogedUser()));
}

void CommandDialogStoreKeeper::storeKeeperDescriptionChanged()
{
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(!m_storeKeeperDescriptionEmpty);
}
