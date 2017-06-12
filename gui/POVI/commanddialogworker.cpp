#include <QWidget>
#include <QMessageBox>
#include "commanddialogworker.h"
#include "ui_commanddialog.h"

CommandDialogWorker::CommandDialogWorker(QWidget *parent, std::shared_ptr<DBConnection> db, CommandPtr command, bool edit):
    CommandDialog(parent, db, command, edit)
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

    ui->commandNumber->setEnabled(false);
    ui->comercialistDescription->setEnabled(false);
    //nalog je preuzet
    if (m_edit)
    {
        //this->showMaximized();
        ui->buttonBox->button(QDialogButtonBox::Ok)->setText("Posalji nalog u zavrseno stanje!");
        ui->buttonBox->button(QDialogButtonBox::Cancel)->setText("Ostavi nalog!");
    }

    this->repaint();
}

void CommandDialogWorker::acceptButtonClicked()
{

}

void CommandDialogWorker::rejectButtonClicked()
{

}
