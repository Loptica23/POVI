#include <QMessageBox>
#include "machinedialog.h"
#include "ui_machinedialog.h"
#include "mainwindow.h"

MachineDialog::MachineDialog(QWidget *parent, DBConnectionPtr db) :
    QDialog(parent),
    ui(new Ui::MachineDialog),
    m_db(db),
    m_create(true)
{
    ui->setupUi(this);
    initializeComboBox();
}

MachineDialog::MachineDialog(QWidget *parent, DBConnectionPtr db, MachinePtr machine, bool edit) :
    QDialog(parent),
    ui(new Ui::MachineDialog),
    m_db(db),
    m_create(false),
    m_machine(machine),
    m_edit(edit)
{
    ui->setupUi(this);

    ui->Name->setText(machine->getName());
    initializeComboBox();
    auto taskTypes = m_db->getTaskTypes();
    ui->comboBox->setCurrentText(taskTypes->getStringById(m_machine->getTaskTypeId()));
    ui->comboBox->setEnabled(false);

    if (!m_edit)
    {
        ui->Name->setEnabled(false);
    }
}

MachineDialog::~MachineDialog()
{
    delete ui;
}

void MachineDialog::initializeComboBox()
{
    auto taskTypes = m_db->getTaskTypes()->getTypes();
    for (auto type = taskTypes->begin(); type != taskTypes->end(); ++type)
    {
        ui->comboBox->addItem((*type).first);
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

    if (!m_db->updateMachine(m_machine))
    {
        QString error = m_db->getLastError();
        QMessageBox messageBox;
        messageBox.critical(0, "Error", error);
    }
}

void MachineDialog::createMachine()
{
    auto taskTypes = m_db->getTaskTypes();
    m_machine.reset(new Machine(0, taskTypes->getTypeIdByString(ui->comboBox->currentText())));
    m_machine->setName(ui->Name->text());

    if (!m_db->createMachine(m_machine))
    {
        QString error = m_db->getLastError();
        QMessageBox messageBox;
        messageBox.critical(0, "Error", error);
    }
}
