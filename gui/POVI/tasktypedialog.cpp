#include "tasktypedialog.h"
#include "ui_tasktypedialog.h"
#include <QPushButton>
#include <QMessageBox>

TaskTypeDialog::TaskTypeDialog(QWidget *parent, DBConnectionPtr db, Refreshable *refreshable) :
    QDialog(parent),
    Refresher(refreshable),
    ui(new Ui::TaskTypeDialog),
    m_db(db),
    m_create(true)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);

    ui->lineEdit_2->setText(QString::number(1));
}

TaskTypeDialog::TaskTypeDialog(QWidget *parent, DBConnectionPtr db, TaskTypePtr taskType, bool edit, Refreshable *refreshable) :
    QDialog(parent),
    Refresher(refreshable),
    ui(new Ui::TaskTypeDialog),
    m_db(db),
    m_create(false),
    m_taskType(taskType),
    m_edit(edit)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);

    ui->lineEdit->setText(taskType->getName());
    ui->lineEdit_2->setText(QString::number(taskType->getWorkersNumber()));
    if (m_taskType->isVirtual())
    {
        ui->comboBox->setCurrentText("Da");
    }
    else
    {
        ui->comboBox->setCurrentText("Ne");
    }

    initializeListView();

    if (!m_edit)
    {
        ui->lineEdit->setReadOnly(true);
        ui->lineEdit_2->setReadOnly(true);
        ui->comboBox->setEnabled(false);
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    }
}

TaskTypeDialog::~TaskTypeDialog()
{
    delete ui;
}

void TaskTypeDialog::on_buttonBox_accepted()
{
    if (m_create)
    {
        createTaskTYpoe();
    }
    else
    {
        updateTaskType();
    }
}

void TaskTypeDialog::initializeListView()
{
    auto machineIds = m_db->getMachineIdsForTaskType(m_taskType->getId());
    for (const auto machineId : machineIds)
    {
        QListWidgetItem *itm = new QListWidgetItem();
        itm->setText(m_db->getMachine(machineId)->getName());
        ui->listWidget->addItem(itm);
    }
}

void TaskTypeDialog::ifFalseShowDbError(bool b)
{
    if (!b)
    {
        QString error = m_db->getLastError();
        QMessageBox messageBox;
        messageBox.critical(0,"Error",error);
    }
}

void TaskTypeDialog::createTaskTYpoe()
{
    auto invoice = false;
    if (ui->comboBox->currentText() == "Da")
    {
        invoice = true;
    }
    m_taskType.reset(new TaskType(0, ui->lineEdit->text(), invoice, ui->lineEdit_2->text().toUInt()));
    ifFalseShowDbError(m_db->createTaskType(m_taskType));
}

void TaskTypeDialog::updateTaskType()
{
    auto invoice = false;
    if (ui->comboBox->currentText() == "Da")
    {
        invoice = true;
    }
    m_taskType->setName(ui->lineEdit->text());
    m_taskType->setInvoice(invoice);
    m_taskType->setWorkersNumber(ui->lineEdit_2->text().toUInt());
    ifFalseShowDbError(m_db->updateTaskType(m_taskType));
}
