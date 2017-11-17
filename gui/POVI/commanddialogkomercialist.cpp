#include <QWidget>
#include <QDialog>
#include <algorithm>
#include <QMessageBox>
#include "commanddialogkomercialist.h"
#include "commanddialog.h"
#include "ui_commanddialog.h"
#include "mainwindow.h"

const std::vector<int> CommandDialogKomercialist::LastisTemplate ({1,22,23,2,24,3,4,5,6,7});
const std::vector<int> CommandDialogKomercialist::TkanjeTemplate ({8,9,10,11,12,5,13,14,15,17,6,7});
const std::vector<int> CommandDialogKomercialist::StampaTemplate ({18,19,20,13,5,21,15,16,17,6,7});

CommandDialogKomercialist::CommandDialogKomercialist(QWidget *parent, std::shared_ptr<DBConnection> db, OrderPtr order, Refreshable *refreshable) :
    CommandDialog(parent, db, order, refreshable),
    m_recommendedCommandNumber(1000000000)
{
    this->showMaximized();
    m_template = TaskTemplate::Manual;
    setRecommendedCommandNumber();
    ui->commandNumber->setText(QString::number(m_recommendedCommandNumber));
    fillTaskTable();
    setUpWindowByWorkPosition();
}


CommandDialogKomercialist::CommandDialogKomercialist(QWidget *parent, std::shared_ptr<DBConnection> db, CommandPtr command, bool edit, Refreshable *refreshable) :
    CommandDialog(parent, db, command, edit, refreshable),
    m_recommendedCommandNumber(0)
{
    this->showMaximized();
    if (edit && m_command->getState() != Command::State::New)
    {
        close();
    }

    m_template = TaskTemplate::Manual;
    fillTaskTable();
    setUpWindowByWorkPosition();
}

CommandDialogKomercialist::~CommandDialogKomercialist()
{

}

void CommandDialogKomercialist::setUpWindowByWorkPosition()
{
    removeWidget(ui->designer);
    removeWidget(ui->storekeeper);
    removeWidget(ui->label_5);
    removeWidget(ui->Priority);
    removeWidget(ui->label_10);
    removeWidget(ui->invoice);
    removeWidget(ui->finishQuantity);
    if (!m_edit)
    {
        showPrintButton();
        ui->comboBox_2->setEnabled(false);
    }
    this->repaint();
}

void CommandDialogKomercialist::fillTaskTable()
{
    if (m_create || m_edit)
    {
        clearButtons();
        QStringList headers;
        headers << "Tip zadatka" << /*"Gore" << "Dole" <<*/ "Brisi";
        ui->taskTable->setRowCount(0);
        ui->taskTable->setColumnCount(headers.size());
        ui->taskTable->setHorizontalHeaderLabels(headers);
        auto i = 0;
        for (auto iter = m_tasks->begin(); iter != m_tasks->end(); ++i, ++iter)
        {
            //ovde se dodaju zadaci koji su vec vezani za nalog
            auto j = 0;
            ui->taskTable->insertRow(i);
            insertComboBox((*iter), i, j++);
            //insertUpButton(i, j++);
            //insertDownButton(i, j++);
            insertDeleteButton(i, j++);
        }
        disableFirstAndLastButtons();
        //insertNewTaskButton(i);
    }
    else
    {
        ui->taskTable->setRowCount(0);
        ui->taskTable->setColumnCount(2);
        QStringList headers;
        headers << "Tip zadatka" << "Stanje";
        ui->taskTable->setHorizontalHeaderLabels(headers);
        auto i = 0;
        for (auto iter = m_tasks->begin(); iter != m_tasks->end(); ++i, ++iter)
        {
            ui->taskTable->insertRow(i);
            TaskPtr task = (*iter);
            {
                QString str = m_taskTypes->getTypes()->at(task->getTaskTypeId()-1)->getName();
                qDebug() << str;
                auto *item = new QTableWidgetItem(str);
                ui->taskTable->setItem(i, 0, item);
            }
            {
                QString str = task->getStateString();
                qDebug() << str;
                auto *item = new QTableWidgetItem(str);
                ui->taskTable->setItem(i, 1, item);
            }
        }
    }
    ui->taskTable->resizeColumnsToContents();
}

void CommandDialogKomercialist::taskTemplateChanged(int i)
{
    switch(i)
    {
    case 0:
        m_template = TaskTemplate::Manual;
        break;
    case 1:
        m_template = TaskTemplate::Lastis;
        m_tasks->clear();
        break;
    case 2:
        m_template = TaskTemplate::Tkanje;
        m_tasks->clear();
        break;
    case 3:
        m_template = TaskTemplate::Stampa;
        m_tasks->clear();
        break;
    default:
        qDebug() << "GRESKA: NE POSTOJI OVAKAV TASKTEMPLATE!";
    }
    setTaskTemplateVector();
    fillTaskTable();
}

void CommandDialogKomercialist::addNewTask(int index)
{
    ++index;
    qDebug() << index;
    TaskPtr task(new Task(m_command, index));
    task->setSerialNumber((unsigned)m_tasks->size());
    m_tasks->push_back(task);
    fillTaskTable();
}

void CommandDialogKomercialist::up()
{
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
    if(std::find(m_upButtons.begin(), m_upButtons.end(), buttonSender) != m_upButtons.end())
    {
        auto index = std::find(m_upButtons.begin(), m_upButtons.end(), buttonSender) - m_upButtons.begin();
        qDebug() << index;
        m_tasks->at(index)->setSerialNumber(index);
        m_tasks->at(index - 1)->setSerialNumber(index + 1);
        std::iter_swap(m_tasks->begin() + index, m_tasks->begin() + index - 1);
    }

    fillTaskTable();
}

void CommandDialogKomercialist::down()
{
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
    if(std::find(m_downButtons.begin(), m_downButtons.end(), buttonSender) != m_downButtons.end())
    {
        auto index = std::find(m_downButtons.begin(), m_downButtons.end(), buttonSender) - m_downButtons.begin();
        qDebug() << index;
        m_tasks->at(index)->setSerialNumber(index + 2);
        m_tasks->at(index + 1)->setSerialNumber(index);
        std::iter_swap(m_tasks->begin() + index, m_tasks->begin() + index + 1);
    }

    fillTaskTable();
}

void CommandDialogKomercialist::deleteTask()
{
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
    if(std::find(m_deleteButtons.begin(), m_deleteButtons.end(), buttonSender) != m_deleteButtons.end())
    {
        auto index = std::find(m_deleteButtons.begin(), m_deleteButtons.end(), buttonSender) - m_deleteButtons.begin();
        qDebug() << index;
        for (auto iter = (m_tasks->begin() + index); iter != m_tasks->end(); ++iter)
        {
            TaskPtr task = (*iter);
            task->setSerialNumber(task->getSerialNumber() - 1);
        }
        m_deletedTasks->push_back(m_tasks->at(index));
        m_tasks->erase(m_tasks->begin() + index);

    }

    fillTaskTable();
}

void CommandDialogKomercialist::setTaskTemplateVector()
{
    switch (m_template)
    {
    case TaskTemplate::Manual:
        break;
    case TaskTemplate::Lastis:
        initializeTasksWithTaskIDs(LastisTemplate);
        break;
    case TaskTemplate::Tkanje:
        initializeTasksWithTaskIDs(TkanjeTemplate);
        break;
    case TaskTemplate::Stampa:
        initializeTasksWithTaskIDs(StampaTemplate);
        break;
    }
}

void CommandDialogKomercialist::initializeTasksWithTaskIDs(std::vector<int> vector)
{
    for (auto iter = vector.begin(); iter != vector.end(); ++iter)
    {
        int id = *iter;
        TaskPtr task(new Task(m_command, id));
        task->setSerialNumber((unsigned)m_tasks->size());
        m_tasks->push_back(task);
    }
}

void CommandDialogKomercialist::clearButtons()
{
    m_comboBoxes.clear();
    m_upButtons.clear();
    m_downButtons.clear();
    m_deleteButtons.clear();
}

void CommandDialogKomercialist::insertComboBox(TaskPtr task, unsigned i, unsigned j)
{
    QComboBox* taskComboBox = new QComboBox(ui->taskTable);
    fillComboBoxWithTaskTypes(taskComboBox);
    taskComboBox->setCurrentIndex(task->getTaskTypeId()-1);
    taskComboBox->setEnabled(false);
    connect(taskComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(changeTaskType(int)));
    ui->taskTable->setCellWidget(i, j, taskComboBox);
    m_comboBoxes.push_back(taskComboBox);
}

void CommandDialogKomercialist::insertUpButton(unsigned i, unsigned j)
{
    QPushButton* btn_up = new QPushButton();
    QPixmap pix(":/resources/resource/img/arrow-up.png");
    QIcon icon(pix);
    btn_up->setIcon(icon);
    btn_up->setIconSize(QSize(70, 70));
    ui->taskTable->setIndexWidget(ui->taskTable->model()->index(i, j), btn_up);
    m_upButtons.push_back(btn_up);
    connect(btn_up, SIGNAL(clicked()), this, SLOT(up()));
}

void CommandDialogKomercialist::insertDownButton(unsigned i, unsigned j)
{
    QPushButton* btn_down = new QPushButton();
    QPixmap pix(":/resources/resource/img/arrow-down.png");
    QIcon icon(pix);
    btn_down->setIcon(icon);
    btn_down->setIconSize(QSize(70, 70));
    ui->taskTable->setIndexWidget(ui->taskTable->model()->index(i, j), btn_down);
    m_downButtons.push_back(btn_down);
    connect(btn_down, SIGNAL(clicked()), this, SLOT(down()));
}

void CommandDialogKomercialist::disableFirstAndLastButtons()
{
    if (!m_upButtons.empty())
    {
        m_upButtons.at(0)->setEnabled(false);
    }
    if (!m_downButtons.empty())
    {
        m_downButtons.at(m_downButtons.size() - 1)->setEnabled(false);
    }
}

void CommandDialogKomercialist::insertDeleteButton(unsigned i, unsigned j)
{
    QPushButton* btn_down = new QPushButton();
    QPixmap pix(":/resources/resource/img/brisi.png");
    QIcon icon(pix);
    btn_down->setIcon(icon);
    btn_down->setIconSize(QSize(25, 25));
    ui->taskTable->setIndexWidget(ui->taskTable->model()->index(i, j), btn_down);
    m_deleteButtons.push_back(btn_down);
    connect(btn_down, SIGNAL(clicked()), this, SLOT(deleteTask()));
}

void CommandDialogKomercialist::insertNewTaskButton(unsigned i)
{
    ui->taskTable->insertRow(i);
    QComboBox* add = new QComboBox(ui->taskTable);
    fillComboBoxWithTaskTypes(add);
    add->addItem("Dodaj novi zadatak");
    add->setCurrentText("Dodaj novi zadatak");
    connect(add, SIGNAL(currentIndexChanged(int)), this, SLOT(addNewTask(int)));
    add->setSizeAdjustPolicy(QComboBox::SizeAdjustPolicy::AdjustToContents);
    ui->taskTable->setCellWidget(i, 0, add);
}

void CommandDialogKomercialist::fillComboBoxWithTaskTypes(QComboBox * box)
{
    for (auto type = m_taskTypes->getTypes()->begin(); type != m_taskTypes->getTypes()->end(); ++type)
    {
        box->addItem((*type)->getName());
    }
}

void CommandDialogKomercialist::setRecommendedCommandNumber()
{
    unsigned numberOfCommands = m_db->getCommands(m_order)->size();
    m_recommendedCommandNumber += m_order->getCustomerId() * 100000;
    m_recommendedCommandNumber += m_order->getID() * 100;
    m_recommendedCommandNumber += numberOfCommands;
}

void CommandDialogKomercialist::updateCommand()
{
    //refaktor
    if (!ui->commandNumber->text().isEmpty())
        m_command->setCommandNumber(ui->commandNumber->text().toUInt());
    if (!ui->quantity->text().isEmpty())
        m_command->setQuantity(ui->quantity->text().toUInt());
    if (!ui->specification->toPlainText().isEmpty())
        m_command->setSpecification(ui->specification->toPlainText());
    if (!ui->comercialistDescription->toPlainText().isEmpty())
        m_command->setComercialistDescription(ui->comercialistDescription->toPlainText());
    m_command->setUnitOfQuantity(ui->comboBox_2->currentText());

    if (m_command->isModified())
    {
        ifFalseShowDbError(m_db->updateCommand(m_command));
    }


    for (auto iter = m_tasks->begin(); iter != m_tasks->end(); ++iter)
    {
        TaskPtr task = *iter;
        if (task->isCreated())
        {
            ifFalseShowDbError(m_db->createNewTask(task, MainWindow::getWorker()->getId()));
        }
        else if (task->isModified())
        {
            ifFalseShowDbError(m_db->updateTask(task));
        }
    }

    for (auto iter = m_deletedTasks->begin(); iter != m_deletedTasks->end(); ++iter)
    {
        TaskPtr task = *iter;
        ifFalseShowDbError(m_db->deleteTask(task));
    }
}
