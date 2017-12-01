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

    ui->Name->setText(machine->getName());
    //auto taskTypes = m_db->getTaskTypes();
    //ui->comboBox->setCurrentText(taskTypes->getStringById(m_machine->getTaskTypeId()));
    ui->lineEdit->setText(machine->getStartTime().toString());
    ui->lineEdit_2->setText(machine->getEndTime().toString());
    ui->lineEdit_3->setText(QString::number(machine->getWorkingDays()));
    initializeListView();
    if (!m_edit)
    {
        ui->Name->setEnabled(false);
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

    if (!m_db->createMachine(m_machine))
    {
        QString error = m_db->getLastError();
        QMessageBox messageBox;
        messageBox.critical(0, "Error", error);
    }
}
