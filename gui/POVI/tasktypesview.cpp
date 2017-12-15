#include "tasktypesview.h"
#include "ui_tasktypesview.h"
#include "tasktypedialog.h"
#include <QMessageBox>

TaskTypesView::TaskTypesView(QWidget *parent, DBConnectionPtr db) :
    QWidget(parent),
    ui(new Ui::TaskTypesView),
    m_db(db)
{
    ui->setupUi(this);
    refresh();
}

TaskTypesView::~TaskTypesView()
{
    delete ui;
}

void TaskTypesView::refresh()
{
    m_tasktypes = m_db->getTaskTypes();
    fillTaskTypesTable();
}

void TaskTypesView::details()
{
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
    if(std::find(m_detailsButtons.begin(), m_detailsButtons.end(), buttonSender) != m_detailsButtons.end())
    {
        auto index = std::find(m_detailsButtons.begin(), m_detailsButtons.end(), buttonSender) - m_detailsButtons.begin();
        qDebug() << index;
        auto tasktypedialog = new TaskTypeDialog(this, m_db, m_tasktypes->getTypes()->at(index), false, this);
        tasktypedialog->show();
    }
}

void TaskTypesView::edit()
{
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
    if(std::find(m_editButtons.begin(), m_editButtons.end(), buttonSender) != m_editButtons.end())
    {
        auto index = std::find(m_editButtons.begin(), m_editButtons.end(), buttonSender) - m_editButtons.begin();
        qDebug() << index;
        auto tasktypedialog = new TaskTypeDialog(this, m_db, m_tasktypes->getTypes()->at(index), true, this);
        tasktypedialog->show();
    }
}

void TaskTypesView::deleteMachine()
{
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
    if(std::find(m_deleteButtons.begin(), m_deleteButtons.end(), buttonSender) != m_deleteButtons.end())
    {
        auto index = std::find(m_deleteButtons.begin(), m_deleteButtons.end(), buttonSender) - m_deleteButtons.begin();
        qDebug() << index;
        if (!m_db->deleteTaskType(m_tasktypes->getTypes()->at(index)))
        {
            QString error = m_db->getLastError();
            QMessageBox messageBox;
            messageBox.critical(0,"Error",error);
        }
        refresh();
    }
}

void TaskTypesView::fillTaskTypesTable()
{
    qDebug() << "User refreshing task types view!";
    clearBuutonsAndInitializeHeaders();
    if (!m_tasktypes || m_tasktypes->getTypes()->empty())
    {
        return;
    }
    auto taskTypes = m_tasktypes->getTypes();
    auto i = 0;
    for (auto taskType: *taskTypes)
    {
        auto j = 0;
        ui->tableWidget->insertRow(i);
        insertName(taskType, i , j++);
        insertDetailsButton(i , j++);
        insertEditButton(i, j++);
        insertDeleteButton(i, j++);
    }
    ui->tableWidget->resizeColumnsToContents();
}

void TaskTypesView::clearBuutonsAndInitializeHeaders()
{
    m_editButtons.clear();
    m_detailsButtons.clear();
    m_deleteButtons.clear();

    ui->tableWidget->setRowCount(0);
    QStringList headers;
    headers << "Naziv tipa zadatka" << "Detalji" << "Izmeni" << "Obrisi";
    ui->tableWidget->setColumnCount(headers.size());
    ui->tableWidget->setHorizontalHeaderLabels(headers);
}

void TaskTypesView::insertName(TaskTypePtr taskType, unsigned i, unsigned j)
{
    auto *item = new QTableWidgetItem(taskType->getName());
    ui->tableWidget->setItem(i, j, item);
}

void TaskTypesView::insertDetailsButton(unsigned i, unsigned j)
{
    QPushButton* btn_details = new QPushButton();
    btn_details->setText("Detalji");
    ui->tableWidget->setIndexWidget(ui->tableWidget->model()->index(i, j), btn_details);
    m_detailsButtons.push_back(btn_details);
    connect(btn_details, SIGNAL(clicked()), this, SLOT(details()));
}

void TaskTypesView::insertEditButton(unsigned i, unsigned j)
{
    QPushButton* btn_edit = new QPushButton();
    btn_edit->setText("Izmeni");
    ui->tableWidget->setIndexWidget(ui->tableWidget->model()->index(i, j), btn_edit);
    m_editButtons.push_back(btn_edit);
    connect(btn_edit, SIGNAL(clicked()), this, SLOT(edit()));
}

void TaskTypesView::insertDeleteButton(unsigned i, unsigned j)
{
    QPushButton* btn_delete = new QPushButton();
    btn_delete->setText("Obrisi");
    ui->tableWidget->setIndexWidget(ui->tableWidget->model()->index(i, j), btn_delete);
    m_deleteButtons.push_back(btn_delete);
    connect(btn_delete, SIGNAL(clicked()), this, SLOT(deleteMachine()));
}

void TaskTypesView::on_pushButton_2_clicked()
{
    refresh();
}

void TaskTypesView::on_newTaskType_clicked()
{
    auto tasktypesdialog = new TaskTypeDialog(this, m_db, this);
    tasktypesdialog->show();
}
