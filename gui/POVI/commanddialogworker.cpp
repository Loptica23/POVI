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
}

void CommandDialogWorker::acceptButtonClicked()
{
    ifFalseShowDbError(m_db->completeCurrentTask(m_command));
}

void CommandDialogWorker::rejectButtonClicked()
{
    ifFalseShowDbError(m_db->leaveCurrentTask(m_command, MainWindow::getWorker()));
}

void CommandDialogWorker::removeInvoiceWidgetIfTaskDontNeedIt()
{
    for (auto iter = m_tasks->begin(); iter != m_tasks->end(); ++iter)
    {
        TaskPtr task = *iter;
        if(task->getState() == Task::State::InProgress)
        {
            TaskTypePtr taskType = m_db->getTaskTypes()->getTaskTypeById(task->getTaskTypeId());
            if (!taskType->isVirtual())
            {
                removeWidget(ui->storekeeper);
            }
            break;
        }
    }
}
