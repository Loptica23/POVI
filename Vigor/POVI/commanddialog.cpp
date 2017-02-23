#include <QDebug>
#include <QMessageBox>
#include <QPushButton>
#include <QComboBox>
#include "commanddialog.h"
#include "ui_commanddialog.h"
#include "mainwindow.h"
#include "dbconnection.h"

//ovaj se koristi za kreiranje naloga
CommandDialog::CommandDialog(QWidget *parent, std::shared_ptr<DBConnection> db, OrderPtr order) :
    QDialog(parent),
    ui(new Ui::CommandDialog),
    m_db(db),
    m_order(order),
    m_create(true),
    m_tasks(new TaskVtr())
{
    ui->setupUi(this);
    fillTaskTable();
    setUpWindowByWorkPosition();
}

//ovaj se koristi za prikaz naloga ili njegovu izmenu
CommandDialog::CommandDialog(QWidget *parent, std::shared_ptr<DBConnection> db, CommandPtr command, bool edit) :
    QDialog(parent),
    ui(new Ui::CommandDialog),
    m_db(db),
    m_command(command),
    m_create(false),
    m_tasks(new TaskVtr())
{
    ui->setupUi(this);

    ui->commandNumber->setText(QString::number(command->getCommandNumber()));
    ui->comercialistDescription->setText(command->getComercialistDescription());
    ui->designerDescription->setText(command->getDesignerDescription());
    ui->storekeeperDescription->setText(command->getStoreKeeperDescription());
    //ostali su ti taskovi

    if (!edit)
    {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
        ui->commandNumber->setEnabled(false);
        ui->comercialistDescription->setEnabled(false);
        ui->designerDescription->setEnabled(false);
        ui->storekeeperDescription->setEnabled(false);
        //ostali su ti taskovi
    }

    //ova funkcija se mora pozvati na kraju konstruktora!
    setUpWindowByWorkPosition();
}

CommandDialog::~CommandDialog()
{
    delete ui;
}

void CommandDialog::setUpWindowByWorkPosition()
{
    auto user = MainWindow::getLogedUser();
    auto username = user->getUserName();
    qDebug() << username;
    switch(user->getWorkPosition())
    {
        case Employee::WorkPosition::Komercijalista:
            removeWidget(ui->designer);
            removeWidget(ui->storekeeper);
            break;
        case Employee::WorkPosition::Dizajner:
            removeWidget(ui->storekeeper);
            removeWidget(ui->tasks);
        // nastavi dalje sa caseovima..
        default:
            break;
    }
}

void CommandDialog::fillTaskTable()
{
    if (m_create)
    {

        ui->taskTable->setRowCount(0);
        auto taskTypes = m_db->getTaskTypes()->getTypes();
        auto i = 0;
        for (auto iter = m_tasks->begin(); iter != m_tasks->end(); ++i, ++iter)
        {
            ui->taskTable->insertRow(i);
            QComboBox* taskComboBox = new QComboBox(ui->taskTable);
            for (auto type = taskTypes->begin(); type != taskTypes->end(); ++type)
            {
                taskComboBox->addItem((*type).first);
                taskComboBox->setCurrentIndex((*iter)->getTaskTypeId());
                connect(taskComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(changeTaskType(int)));
                ui->taskTable->setCellWidget(i, 0, taskComboBox);
            }
        }
        //nakon dodavanja postojecih zadataka potrebno je da dodas opciju za kreiranje
        {
            ui->taskTable->insertRow(i);
            QComboBox* add = new QComboBox(ui->taskTable);
            for (auto type = taskTypes->begin(); type != taskTypes->end(); ++type)
            {
                add->addItem((*type).first);
            }
            add->addItem("Dodaj novi zadatak");
            add->setCurrentText("Dodaj novi zadatak");
            connect(add, SIGNAL(currentIndexChanged(int)), this, SLOT(addNewTask(int)));
            add->setSizeAdjustPolicy(QComboBox::SizeAdjustPolicy::AdjustToContents);
            ui->taskTable->setCellWidget(i, 0, add);
        }
    }
    else
    {

    }
    ui->taskTable->resizeColumnsToContents();
}

void CommandDialog::initializeTasks()
{

}

void CommandDialog::removeWidget(QWidget * widget)
{
    qDeleteAll(widget->children());
    delete widget;
}

void CommandDialog::on_buttonBox_accepted()
{
    if (m_create)
    {
        createCommand();
    }
    else
    {
        updateCommand();
    }
}

void CommandDialog::addNewTask(int index)
{
    //mozda da se iskulira ako je vrednost dodaj novi zadatak;
    TaskPtr task(new Task(m_command, index));
    m_tasks->push_back(task);
    fillTaskTable();
}

void CommandDialog::changeTaskType(int index)
{
    qDebug() << index;
}

void CommandDialog::createCommand()
{
    CommandPtr command(new Command(m_order->getCustomerId(), m_order->getID(), 0));
    if (!ui->comercialistDescription->toPlainText().isEmpty())
    {
        command->setComercialistDescription(ui->comercialistDescription->toPlainText());
    }
    if (!ui->commandNumber->text().isEmpty())
    {
        command->setCommandNumber(ui->commandNumber->text().toInt());
    }

    if (!m_db->createNewCommand(command))
    {
        QString error = m_db->getLastError();
        QMessageBox messageBox;
        messageBox.critical(0,"Error",error);
    }
}

void CommandDialog::updateCommand()
{
    switch(MainWindow::getLogedUser()->getWorkPosition())
    {
    case Employee::WorkPosition::Administrator:
        if (!ui->commandNumber->text().isEmpty())
            m_command->setCommandNumber(ui->commandNumber->text().toUInt());
        if (!ui->comercialistDescription->toPlainText().isEmpty())
            m_command->setComercialistDescription(ui->comercialistDescription->toPlainText());
        if (!ui->designerDescription->toPlainText().isEmpty())
            m_command->setDesignerDescription(ui->designerDescription->toPlainText());
        if (!ui->storekeeperDescription->toPlainText().isEmpty())
            m_command->setStoreKeeperDescription(ui->storekeeperDescription->toPlainText());
        break;
    case Employee::WorkPosition::Komercijalista:
        break;
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
}
