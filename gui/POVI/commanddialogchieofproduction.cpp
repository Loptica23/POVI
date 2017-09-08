#include <QString>
#include <QMessageBox>
#include "commanddialogchieofproduction.h"
#include "ui_commanddialog.h"

#define timeFormat "hh:mm dd.MM.yyyy"

CommandDialogChieOfProduction::CommandDialogChieOfProduction(QWidget *parent, DBConnectionPtr db, CommandPtr command, bool edit, Refreshable *refreshable):
    CommandDialog(parent, db, command, edit, refreshable),
    m_annul(false)
{
    this->showMaximized();
    m_annul = showAnnul();
    m_taskTypes = m_db->getTaskTypes();
    fillTaskTable();
    setUpWindowByWorkPosition();
    qDebug() << "Sef proizvodnje";
}

CommandDialogChieOfProduction::~CommandDialogChieOfProduction()
{

}

void CommandDialogChieOfProduction::setUpWindowByWorkPosition()
{
    ui->specification->setReadOnly(true);
    ui->quantity->setReadOnly(true);
    ui->comercialistDescription->setReadOnly(true);
    ui->designerDescription->setReadOnly(true);
    ui->commandNumber->setEnabled(false);
    ui->storekeeperDescription->setReadOnly(true);

    removeWidget(ui->invoice);
    removeWidget(ui->storekeeper);
    removeWidget(ui->comboBox);
    removeWidget(ui->label_10);
    removeWidget(ui->finishQuantity);
}

void CommandDialogChieOfProduction::fillTaskTable()
{
    clearButtonsAndSetHeaders();
    auto i = 0;
    for (auto iter = m_tasks->begin(); iter != m_tasks->end(); ++i, ++iter)
    {
        auto j = 0;
        ui->taskTable->insertRow(i);
        TaskPtr task = (*iter);
        insertTaskType(task, i, j++);
        insertTaskState(task, i, j++);
        insertTaskPrediction(task, i ,j++);
        insertMachineComboBox(task, i, j++);
        insertWorker(task, i, j++);
        insertStartTime(task, i , j++);
        insertEndTime(task, i , j++);
        insertTaskQuantity(task, i , j++);
        insertAnnulButton(task, i, j++);
    }
    taskMachineChanged();
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
        ifFalseShowDbError(m_db->updateCommand(m_command));
    }

    auto i = 0;
    for (auto iter = m_tasks->begin(); iter != m_tasks->end(); ++i, ++iter)
    {
        TaskPtr task = (*iter);
        QString text = ui->taskTable->item(i, 2)->text();
        if(!text.isEmpty())
        {
            double hours = text.toDouble();
            unsigned minutes = (unsigned)(hours*60);
            task->setPrediction(minutes);
            //ovde moram da postavim setovanu masinu!
            MachinePtr machin = Machine::getMachineByName(m_machines, m_comboBoxes.at(i)->currentText());
            if (machin)
            {
                task->setMachineId(machin->getId());
            }
            if (task->isModified())
            {
                ifFalseShowDbError(m_db->updateTask(task));
            }
        }
    }

}

void CommandDialogChieOfProduction::acceptButtonClicked()
{
    ifFalseShowDbError(m_db->completeCurrentTask(m_command, 0));
}

bool CommandDialogChieOfProduction::showAnnul()
{
    bool result = (m_command->getState() == Command::State::Stopped);
    for (auto task : *m_tasks)
    {
        if (task->getState() == Task::State::InProgress)
        {
            result = false;
            break;
        }
    }
    return result;
}

void CommandDialogChieOfProduction::clearButtonsAndSetHeaders()
{
    m_comboBoxes.clear();
    m_annulButtons.clear();

    QStringList headers;
    headers << "Tip zadatka" << "Stanje" << "Procena" << "Masina" << "Radnik" << "Poceo" << "Zavrsen" << "Kolicina";

    if (m_annul)
    {
        headers << "Storniraj";
    }

    m_machines = m_db->getMachines();
    ui->taskTable->setRowCount(0);
    ui->taskTable->setColumnCount(headers.size());
    ui->taskTable->setHorizontalHeaderLabels(headers);
}

void CommandDialogChieOfProduction::insertTaskType(TaskPtr task, unsigned i, unsigned j)
{
    QString str = m_taskTypes->getTypes()->at(task->getTaskTypeId()-1)->getName();
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
    unsigned minutes = task->getPrediction();
    double hours = ((double)minutes/(double)60);
    QString str = QString::number(hours, 'f', 2);
    auto *item = new QTableWidgetItem(str);
    ui->taskTable->setItem(i, j, item);
}

void CommandDialogChieOfProduction::insertMachineComboBox(TaskPtr task, unsigned i, unsigned j)
{
    //moraces na osnovu teksta masine da dohvatas
    QComboBox* taskComboBox = new QComboBox(ui->taskTable);
    //fill combobox with machines
    taskComboBox->addItem("");
    //refactor -- ovo treba da se baci na backend
    MachinePtrVtr machines = m_db->getMachines(task->getTaskTypeId());
    for (auto iter = machines->begin(); iter != machines->end(); ++iter)
    {
        MachinePtr machine = *iter;
        taskComboBox->addItem(machine->getName());
    }
    ui->taskTable->setCellWidget(i, j, taskComboBox);
    MachinePtr machine = Machine::getMachineById(m_machines, task->getMachineId());

    if (machine)
    {
        taskComboBox->setCurrentText(machine->getName());
    }
    else if (machines->size() == 1)
    {
        machine = *(machines->begin());
        taskComboBox->setCurrentText(machine->getName());
    }
    else
    {
        m_isThereTaskWithoutMachie = true;
    }

    if (!m_edit)
    {
        taskComboBox->setEnabled(false);
    }
    m_comboBoxes.push_back(taskComboBox);
    connect(taskComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(taskMachineChanged()));
}

void CommandDialogChieOfProduction::insertWorker(TaskPtr task, unsigned i , unsigned j)
{
    QString str = m_db->getEmployee(task->getWorkerId())->getUserName();
    auto *item = new QTableWidgetItem(str);
    ui->taskTable->setItem(i, j, item);
}

void CommandDialogChieOfProduction::insertStartTime(TaskPtr task, unsigned i , unsigned j)
{
    QString str = task->getStartTime().toString(timeFormat);
    auto *item = new QTableWidgetItem(str);
    ui->taskTable->setItem(i, j, item);
}

void CommandDialogChieOfProduction::insertEndTime(TaskPtr task, unsigned i , unsigned j)
{
    QString str = task->getEndTime().toString(timeFormat);
    auto *item = new QTableWidgetItem(str);
    ui->taskTable->setItem(i, j, item);
}

void CommandDialogChieOfProduction::insertTaskQuantity(TaskPtr task, unsigned i , unsigned j)
{
    QString str = QString::number(task->getQuantity());
    auto *item = new QTableWidgetItem(str);
    ui->taskTable->setItem(i, j, item);
}

void CommandDialogChieOfProduction::insertAnnulButton(TaskPtr task, unsigned i , unsigned j)
{
    if (m_annul)
    {
        QPushButton* btn = new QPushButton();
        m_annulButtons.push_back(btn);
        connect(btn, SIGNAL(clicked()), this, SLOT(annul()));
        btn->setEnabled(false);
        btn->setText("Storniraj");
        if (((task->getState() == Task::State::Complited) || (task->getState() == Task::State::Leaved)) && m_edit)
        {
            btn->setEnabled(true);
        }
        ui->taskTable->setIndexWidget(ui->taskTable->model()->index(i, j), btn);
    }
}

void CommandDialogChieOfProduction::annul()
{
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
    if(std::find(m_annulButtons.begin(), m_annulButtons.end(), buttonSender) != m_annulButtons.end())
    {
        auto index = std::find(m_annulButtons.begin(), m_annulButtons.end(), buttonSender) - m_annulButtons.begin();
        qDebug() << index;
        m_db->annulTask(m_tasks->at(index), m_command, m_tasks);
        close();
    }
}

void CommandDialogChieOfProduction::taskMachineChanged()
{
    auto showOKButton = true;
    for (QComboBox* combo : m_comboBoxes)
    {
        if (combo->currentText() == "")
        {
            showOKButton = false;
            break;
        }
    }

    if (showOKButton)
    {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
    }
    else
    {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    }
}
