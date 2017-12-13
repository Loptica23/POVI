#include <QMessageBox>
#include <QPushButton>
#include <QListWidgetItem>
#include "machinedialog.h"
#include "ui_machinedialog.h"
#include "mainwindow.h"

MachineDialog::MachineDialog(QWidget *parent, DBConnectionPtr db, Refreshable *refreshable) :
    QDialog(parent),
    Refresher(refreshable),
    ui(new Ui::MachineDialog),
    m_db(db),
    m_create(true)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    enableOrDisableOkButton();
    enableOrDisableDeleteButton();

    ui->lineEdit->setText("00:00:00");
    ui->lineEdit_2->setText("00:00:00");
    ui->lineEdit_3->setText("1");

    initializeTaskTypesComboBox();
}

MachineDialog::MachineDialog(QWidget *parent, DBConnectionPtr db, MachinePtr machine, bool edit, Refreshable *refreshable) :
    QDialog(parent),
    Refresher(refreshable),
    ui(new Ui::MachineDialog),
    m_db(db),
    m_create(false),
    m_machine(machine),
    m_edit(edit)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    enableOrDisableOkButton();
    enableOrDisableDeleteButton();

    ui->Name->setText(machine->getName());
    //auto taskTypes = m_db->getTaskTypes();
    //ui->comboBox->setCurrentText(taskTypes->getStringById(m_machine->getTaskTypeId()));
    ui->lineEdit->setText(machine->getStartTime().toString());
    ui->lineEdit_2->setText(machine->getEndTime().toString());
    ui->lineEdit_3->setText(QString::number(machine->getWorkingDays()));
    initializeListView();
    initializeTaskTypesComboBox();
    if (!m_edit)
    {
        ui->Name->setReadOnly(true);
        ui->lineEdit->setReadOnly(true);
        ui->lineEdit_2->setReadOnly(true);
        ui->lineEdit_3->setReadOnly(true);
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    }
}

MachineDialog::~MachineDialog()
{
    delete ui;
}

void MachineDialog::initializeListView()
{
    auto taskTypes = m_db->getTaskTypes();
    auto taskTypesIds = m_db->getTasTypesIdsForMachine(m_machine);
    for (const auto taskTypeId : taskTypesIds)
    {
        QListWidgetItem *itm = new QListWidgetItem();
        itm->setText(taskTypes->getTaskTypeById(taskTypeId)->getName());
        ui->listWidget->addItem(itm);
    }
}

void MachineDialog::initializeTaskTypesComboBox()
{
    auto taskTypes = m_db->getTaskTypes()->getTypes();
    if (m_machine != nullptr)
    {
        auto taskTypesIds = m_db->getTasTypesIdsForMachine(m_machine);
        for (auto taskTypeId : taskTypesIds)
        {
            auto it = std::find_if(taskTypes->begin(), taskTypes->end(), [&](auto taskType)
                {
                    return taskType->getId() == taskTypeId;
                });
            if (it != taskTypes->end())
            {
                taskTypes->erase(it);
            }
        }
    }

    for (auto taskType : *taskTypes)
    {
        ui->comboBox->addItem(taskType->getName());
    }
}

void MachineDialog::on_buttonBox_accepted()
{
    if (m_create)
    {
        createMachine();
    }
    else
    {
        updateMachine();
    }
}

void MachineDialog::updateMachine()
{
    if (!ui->Name->text().isEmpty())
    {
        m_machine->setName(ui->Name->text());
    }

    if (!ui->lineEdit->text().isEmpty())
    {
        QTime time = time.fromString(ui->lineEdit->text(), "hh:mm:ss");
        m_machine->setStartTime(time);
    }

    if (!ui->lineEdit_2->text().isEmpty())
    {
        QTime time = QTime::fromString(ui->lineEdit_2->text(), "hh:mm:ss");
        m_machine->setEndTime(time);
    }

    if (!ui->lineEdit_3->text().isEmpty())
    {
        m_machine->setWorkingDays(ui->lineEdit_3->text().toUInt());
    }


    if (m_machine->isModified())
    {
        if (!m_db->updateMachine(m_machine))
        {
            QString error = m_db->getLastError();
            QMessageBox messageBox;
            messageBox.critical(0, "Error", error);
        }
    }
}

void MachineDialog::createMachine()
{
    m_machine.reset(new Machine(0));
    m_machine->setName(ui->Name->text());

    {
        QTime time = time.fromString(ui->lineEdit->text(), "hh:mm:ss");
        qDebug() << time.toString();
        m_machine->setStartTime(time);
    }

    {
        QTime time = time.fromString(ui->lineEdit_2->text(), "hh:mm:ss");
        qDebug() << time.toString();
        m_machine->setEndTime(time);
    }

    m_machine->setWorkingDays(ui->lineEdit_3->text().toUInt());

    if (!m_db->createMachine(m_machine))
    {
        QString error = m_db->getLastError();
        QMessageBox messageBox;
        messageBox.critical(0, "Error", error);
    }
}

void MachineDialog::enableOrDisableOkButton()
{
    auto enable = true;

    if (ui->Name->text().isEmpty())
    {
        enable = false;
    }

    if (ui->lineEdit->text().isEmpty())
    {
        enable = false;
    }

    if (ui->lineEdit_2->text().isEmpty())
    {
        enable = false;
    }

    if (ui->lineEdit_3->text().isEmpty())
    {
        enable = false;
    }
    else
    {
        if (!(ui->lineEdit_3->text().toUInt() > 0 && ui->lineEdit_3->text().toUInt() < 8))
        {
            enable = false;
        }
    }

    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(enable);
}

void MachineDialog::enableOrDisableDeleteButton()
{
    if (m_edit)
    {
        if (ui->listWidget->currentItem() != nullptr)
        {
            ui->deleteTaskType->setEnabled(true);
        }
        else
        {
            ui->deleteTaskType->setEnabled(false);
        }
    }
}

void MachineDialog::enableOrDisableAddButton()
{
    if (m_edit)
    {
        if (ui->comboBox->currentText().isEmpty())
        {
            ui->addTaskType->setEnabled(false);
        }
        else
        {
            ui->addTaskType->setEnabled(true);
        }
    }
}

void MachineDialog::ifFalseShowDbError(bool b)
{
    if (!b)
    {
        QString error = m_db->getLastError();
        QMessageBox messageBox;
        messageBox.critical(0,"Error",error);
    }
}

void MachineDialog::on_Name_textChanged(const QString &)
{
    enableOrDisableOkButton();
}

void MachineDialog::on_lineEdit_textChanged(const QString &)
{
    enableOrDisableOkButton();
}

void MachineDialog::on_lineEdit_2_textChanged(const QString &)
{
    enableOrDisableOkButton();
}

void MachineDialog::on_lineEdit_3_textChanged(const QString &)
{
    enableOrDisableOkButton();
}

void MachineDialog::on_comboBox_currentIndexChanged(const QString &)
{
    enableOrDisableAddButton();
}

void MachineDialog::on_addTaskType_clicked()
{
    auto taskTypes = m_db->getTaskTypes();
    auto id = taskTypes->getTypeIdByString(ui->comboBox->currentText());
    ifFalseShowDbError(m_db->createMachineTaskType(m_machine, id));
    close();
}

void MachineDialog::on_listWidget_clicked(const QModelIndex &)
{
    enableOrDisableDeleteButton();
}

void MachineDialog::on_deleteTaskType_clicked()
{
    auto taskTypes = m_db->getTaskTypes();
    auto id = taskTypes->getTypeIdByString(ui->listWidget->currentItem()->text());
    ifFalseShowDbError(m_db->deleteMahineTaskType(m_machine, id));
    close();
}
