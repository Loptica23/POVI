#include <QWidget>
#include <QDialog>
#include <algorithm>
#include <QMessageBox>
#include "commanddialogkomercialist.h"
#include "commanddialog.h"
#include "ui_commanddialog.h"
#include "mainwindow.h"

CommandDialogKomercialist::CommandDialogKomercialist(QWidget *parent, std::shared_ptr<DBConnection> db, OrderPtr order) :
    CommandDialog(parent, db, order)
{
    m_taskTypes = m_db->getTaskTypes()->getTypes();
    fillTaskTable();
    setUpWindowByWorkPosition();
}


CommandDialogKomercialist::CommandDialogKomercialist(QWidget *parent, std::shared_ptr<DBConnection> db, CommandPtr command, bool edit) :
    CommandDialog(parent, db, command, edit)
{
    m_taskTypes = m_db->getTaskTypes()->getTypes();
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
    this->repaint();
}

void CommandDialogKomercialist::fillTaskTable()
{
    if (m_create || m_edit)
    {
        clearButtons();
        ui->taskTable->setRowCount(0);
        ui->taskTable->setColumnCount(4);
        auto i = 0;
        for (auto iter = m_tasks->begin(); iter != m_tasks->end(); ++i, ++iter)
        {
            //ovde se dodaju zadaci koji su vec vezani za nalog
            ui->taskTable->insertRow(i);
            insertComboBox((*iter), i, 0);
            insertUpButton(i, 1);
            insertDownButton(i, 2);
            insertDeleteButton(i, 3);
        }
        //jo jedan red za kreiranje novog zadatka
        insertNewTaskButton(i);
    }
    else
    {
        ui->taskTable->setRowCount(0);
        ui->taskTable->setColumnCount(1);
        auto i = 0;
        for (auto iter = m_tasks->begin(); iter != m_tasks->end(); ++i, ++iter)
        {
            ui->taskTable->insertRow(i);
            TaskPtr task = (*iter);
            QString str = m_taskTypes->at(task->getTaskTypeId()-1).first;
            qDebug() << str;
            auto *item = new QTableWidgetItem(str);
            ui->taskTable->setItem(i, 0, item);
        }
    }
    ui->taskTable->resizeColumnsToContents();
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
        //oznaci ga negde da treba da se brise, vidi kako ces to..
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
    for (auto type = m_taskTypes->begin(); type != m_taskTypes->end(); ++type)
    {
        box->addItem((*type).first);
    }
}

void CommandDialogKomercialist::updateCommand()
{
    //refaktor
    if (!ui->commandNumber->text().isEmpty())
        m_command->setCommandNumber(ui->commandNumber->text().toUInt());
    if (!ui->comercialistDescription->toPlainText().isEmpty())
        m_command->setComercialistDescription(ui->comercialistDescription->toPlainText());
    if (m_command->isModified())
    {
        if (!m_db->updateCommand(m_command))
        {
            QString error = m_db->getLastError();
            QMessageBox messageBox;
            messageBox.critical(0,"Error",error);
        }
    }
    qDebug() << "taskovi dolaze na red!";

    for (auto iter = m_tasks->begin(); iter != m_tasks->end(); ++iter)
    {
        TaskPtr task = *iter;
        if (task->isCreated())
        {
            if (!m_db->createNewTask(task, MainWindow::getLogedUser()->getId()))
            {
                QString error = m_db->getLastError();
                QMessageBox messageBox;
                messageBox.critical(0,"Error",error);
            }
        }
        else if (task->isModified())
        {
            if (!m_db->updateTask(task))
            {
                //refactor (ovaj deo koda se stalno pojavljuje!!!)
                QString error = m_db->getLastError();
                QMessageBox messageBox;
                messageBox.critical(0,"Error",error);
            }
        }
    }

    qDebug() << "taskovi dolaze na red!";
    for (auto iter = m_deletedTasks->begin(); iter != m_deletedTasks->end(); ++iter)
    {
        TaskPtr task = *iter;
        if (!m_db->deleteTask(task))
        {
            QString error = m_db->getLastError();
            QMessageBox messageBox;
            messageBox.critical(0, "Error", error);
        }
    }
}
