#include <QString>
#include <QMessageBox>
#include "commanddialogchieofproduction.h"
#include "ui_commanddialog.h"

CommandDialogChieOfProduction::CommandDialogChieOfProduction(QWidget *parent, DBConnectionPtr db, CommandPtr command, bool edit):
    CommandDialog(parent, db, command, edit)
{
    //this->showMaximized();
    m_taskTypes = m_db->getTaskTypes()->getTypes();
    fillTaskTable();
    setUpWindowByWorkPosition();
}

CommandDialogChieOfProduction::~CommandDialogChieOfProduction()
{

}

void CommandDialogChieOfProduction::setUpWindowByWorkPosition()
{
    ui->comercialistDescription->setEnabled(false);
    ui->designerDescription->setEnabled(false);
    ui->commandNumber->setEnabled(false);
    ui->storekeeperDescription->setEnabled(false);
}

void CommandDialogChieOfProduction::fillTaskTable()
{
    m_machines = m_db->getMachines();
    ui->taskTable->setRowCount(0);
    ui->taskTable->setColumnCount(4);
    QStringList headers;
    headers << "Tip zadatka" << "Stanje" << "Procena" << "Masina";
    ui->taskTable->setHorizontalHeaderLabels(headers);
    auto i = 0;
    for (auto iter = m_tasks->begin(); iter != m_tasks->end(); ++i, ++iter)
    {
        ui->taskTable->insertRow(i);
        TaskPtr task = (*iter);
        insertTaskType(task, i, 0);
        insertTaskState(task, i, 1);
        insertTaskPrediction(task, i ,2);
        insertMachineComboBox(task, i, 3);
    }

    ui->taskTable->resizeColumnsToContents();
}

void CommandDialogChieOfProduction::updateCommand()
{
    if (!ui->Priority->text().isEmpty())
    {
        m_command->setPriority(ui->Priority->text().toUInt());
    }

    if (m_command->isModified())
    {
        if (!m_db->updateCommand(m_command))
        {
            QString error = m_db->getLastError();
            QMessageBox messageBox;
            messageBox.critical(0,"Error",error);
        }
    }

    auto i = 0;
    for (auto iter = m_tasks->begin(); iter != m_tasks->end(); ++i, ++iter)
    {
        TaskPtr task = (*iter);
        QString text = ui->taskTable->item(i, 2)->text();
        if(!text.isEmpty())
        {
            task->setPrediction(text.toUInt());
            //ovde moram da postavim setovanu masinu!
            if (task->isModified())
            {
                if (!m_db->updateTask(task))
                {
                    //refactor (ovaj deo koda se stalno pojavljuje!!!) prebaci to u jednu funkciju u osnovnoj klasi
                    QString error = m_db->getLastError();
                    QMessageBox messageBox;
                    messageBox.critical(0,"Error",error);
                }
            }
        }
    }

}

void CommandDialogChieOfProduction::insertTaskType(TaskPtr task, unsigned i, unsigned j)
{
    QString str = m_taskTypes->at(task->getTaskTypeId()-1).first;
    auto *item = new QTableWidgetItem(str);
    ui->taskTable->setItem(i, j, item);
}

void CommandDialogChieOfProduction::insertTaskState(TaskPtr task, unsigned i, unsigned j)
{
    QString str = task->getStateString();
    auto *item = new QTableWidgetItem(str);
    ui->taskTable->setItem(i, j, item);
}

void CommandDialogChieOfProduction::insertTaskPrediction(TaskPtr task, unsigned i, unsigned j)
{
    QString str = QString::number(task->getPrediction());
    auto *item = new QTableWidgetItem(str);
    ui->taskTable->setItem(i, j, item);
}

void CommandDialogChieOfProduction::insertMachineComboBox(TaskPtr task, unsigned i, unsigned j)
{
    //moraces na osnovu teksta masine da dohvatas
    QComboBox* taskComboBox = new QComboBox(ui->taskTable);
    //fill combobox with machines
    for (auto iter = m_machines->begin(); iter != m_machines->end(); ++iter)
    {
        MachinePtr machine = *iter;
        if (machine->getTaskTypeId() == task->getTaskTypeId())
        {
            taskComboBox->addItem(machine->getName());
        }
    }
    ui->taskTable->setCellWidget(i, j, taskComboBox);
}
