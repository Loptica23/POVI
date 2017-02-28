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
    m_tasks(new TaskVtr()),
    m_edit(true)
{
    ui->setupUi(this);
}

//ovaj se koristi za prikaz naloga ili njegovu izmenu
CommandDialog::CommandDialog(QWidget *parent, std::shared_ptr<DBConnection> db, CommandPtr command, bool edit) :
    QDialog(parent),
    ui(new Ui::CommandDialog),
    m_db(db),
    m_command(command),
    m_create(false),
    m_tasks(new TaskVtr()),
    m_edit(edit),
    m_deletedTasks(new TaskVtr())
{
    ui->setupUi(this);
    initializeTasks();

    ui->commandNumber->setText(QString::number(command->getCommandNumber()));
    ui->comercialistDescription->setText(command->getComercialistDescription());
    ui->designerDescription->setText(command->getDesignerDescription());
    ui->storekeeperDescription->setText(command->getStoreKeeperDescription());
    //ostali su ti taskovi

    if (!m_edit)
    {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
        ui->commandNumber->setEnabled(false);
        ui->comercialistDescription->setEnabled(false);
        ui->designerDescription->setEnabled(false);
        ui->storekeeperDescription->setEnabled(false);
        //ostali su ti taskovi
    }
}

CommandDialog::~CommandDialog()
{
    delete ui;
}

void CommandDialog::initializeTasks()
{
    //inicijalizujes taskove uz pomoc naloga
    m_tasks = m_db->getTasks(m_command);
}

void CommandDialog::removeWidget(QWidget * widget)
{
    qDeleteAll(widget->children());
    delete widget;
}

void CommandDialog::on_buttonBox_accepted()
{
    qDebug() << "prihvatanje!";
    if (m_create)
    {
        createCommand();
    }
    else
    {
        qDebug() << "pozivanje funkcije update!";
        updateCommand();
    }
}

void CommandDialog::changeTaskType(int index)
{
    QComboBox* comboBoxSender = qobject_cast<QComboBox*>(sender());
    if (std::find(m_comboBoxes.begin(), m_comboBoxes.end(), comboBoxSender) != m_comboBoxes.end())
    {
        auto row = std::find(m_comboBoxes.begin(), m_comboBoxes.end(), comboBoxSender) - m_comboBoxes.begin();
        qDebug() << row;
        ++index;
        qDebug() << index;
        m_tasks->at(row).reset(new Task(m_command, index));
        m_tasks->at(row)->setSerialNumber(row + 1);
    }
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
    else
    {
        m_command = m_db->getCommand(command->getCommandNumber());
        //ako je sve ok proslo sada kreiras zadatke koji su ti u vektoru
        auto serialNumber = 1;
        for (auto i = m_tasks->begin(); i != m_tasks->end(); ++i, ++serialNumber)
        {
            if (!m_db->createNewTask(*i, MainWindow::getLogedUser()->getId()))
            {
                QString error = m_db->getLastError();
                QMessageBox messageBox;
                messageBox.critical(0,"Error",error);
            }
        }
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
