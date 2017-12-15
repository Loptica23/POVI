#include "machinesview.h"
#include "ui_machinesview.h"
#include "tasktypes.h"
#include "machinedialog.h"
#include <QMessageBox>

MachinesView::MachinesView(QWidget *parent, DBConnectionPtr db) :
    QWidget(parent),
    ui(new Ui::MachinesView),
    m_db(db),
    m_machines(new MachineVtr())
{
    m_tasktypes = m_db->getTaskTypes();
    ui->setupUi(this);
    refresh();
}

MachinesView::~MachinesView()
{
    delete ui;
}

void MachinesView::refresh()
{
    m_machines = m_db->getMachines();
    fillMachinesTable();
}

void MachinesView::on_NewMachine_clicked()
{
    auto machinedialog = new MachineDialog(this, m_db, this);
    machinedialog->show();
}

void MachinesView::on_refresh_clicked()
{
    refresh();
}

void MachinesView::fillMachinesTable()
{
    qDebug() << "user refreshing machines view!";
    clearBuutonsAndInitializeHeaders();
    if (!m_machines || m_machines->empty())
    {
        return;
    }
    auto i = 0;
    for (auto iter = m_machines->begin(); iter != m_machines->end(); ++i, ++iter)
    {
        auto j = 0;
        MachinePtr machine = *iter;
        ui->tableWidget->insertRow(i);
        insertName(machine, i, j++);
        //insertType(machine, i, j++);
        insertDetailsButton(i, j++);
        insertEditButton(i, j++);
        insertDeleteButton(i, j++);
    }
    ui->tableWidget->resizeColumnsToContents();
}

void MachinesView::clearBuutonsAndInitializeHeaders()
{
    m_editButtons.clear();
    m_detailsButtons.clear();
    m_deleteButtons.clear();

    ui->tableWidget->setRowCount(0);
    QStringList headers;
    headers << "Naziv Masine" << "Detalji" << "Izmeni" << "Obrisi";
    ui->tableWidget->setColumnCount(headers.size());
    ui->tableWidget->setHorizontalHeaderLabels(headers);
}

void MachinesView::insertName(MachinePtr machine, unsigned i, unsigned j)
{
    auto *item = new QTableWidgetItem(machine->getName());
    ui->tableWidget->setItem(i, j, item);
}

/*
void MachinesView::insertType(MachinePtr machine, unsigned i, unsigned j)
{
    QString type = m_tasktypes->getStringById(machine->getTaskTypeId());
    auto *item = new QTableWidgetItem(type);
    ui->tableWidget->setItem(i, j, item);
}
*/

void MachinesView::insertDetailsButton(unsigned i, unsigned j)
{
    QPushButton* btn_details = new QPushButton();
    btn_details->setText("Detalji");
    ui->tableWidget->setIndexWidget(ui->tableWidget->model()->index(i, j), btn_details);
    m_detailsButtons.push_back(btn_details);
    connect(btn_details, SIGNAL(clicked()), this, SLOT(details()));
}

void MachinesView::insertEditButton(unsigned i, unsigned j)
{
    QPushButton* btn_edit = new QPushButton();
    btn_edit->setText("Izmeni");
    ui->tableWidget->setIndexWidget(ui->tableWidget->model()->index(i, j), btn_edit);
    m_editButtons.push_back(btn_edit);
    connect(btn_edit, SIGNAL(clicked()), this, SLOT(edit()));
}

void MachinesView::insertDeleteButton(unsigned i, unsigned j)
{
    QPushButton* btn_delete = new QPushButton();
    btn_delete->setText("Obrisi");
    ui->tableWidget->setIndexWidget(ui->tableWidget->model()->index(i, j), btn_delete);
    m_deleteButtons.push_back(btn_delete);
    connect(btn_delete, SIGNAL(clicked()), this, SLOT(deleteMachine()));
}

void MachinesView::details()
{
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
    if(std::find(m_detailsButtons.begin(), m_detailsButtons.end(), buttonSender) != m_detailsButtons.end())
    {
        auto index = std::find(m_detailsButtons.begin(), m_detailsButtons.end(), buttonSender) - m_detailsButtons.begin();
        qDebug() << index;
        auto machinesdialog = new MachineDialog(this, m_db, m_machines->at(index), false, this);
        machinesdialog->show();
    }
}

void MachinesView::edit()
{
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
    if(std::find(m_editButtons.begin(), m_editButtons.end(), buttonSender) != m_editButtons.end())
    {
        auto index = std::find(m_editButtons.begin(), m_editButtons.end(), buttonSender) - m_editButtons.begin();
        qDebug() << index;
        auto machinesdialog = new MachineDialog(this, m_db, m_machines->at(index), true, this);
        machinesdialog->show();
    }
}

void MachinesView::deleteMachine()
{
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
    if(std::find(m_deleteButtons.begin(), m_deleteButtons.end(), buttonSender) != m_deleteButtons.end())
    {
        auto index = std::find(m_deleteButtons.begin(), m_deleteButtons.end(), buttonSender) - m_deleteButtons.begin();
        qDebug() << index;
        if (!m_db->deleteMachine(m_machines->at(index)))
        {
            QString error = m_db->getLastError();
            QMessageBox messageBox;
            messageBox.critical(0,"Error",error);
        }
        refresh();
    }
}
