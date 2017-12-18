#include "wherecommandswaiting.h"
#include "ui_wherecommandswaiting.h"
#include "commanddialogchieofproduction.h"

#define DATATIMEVIEW "hh:mm dd.MM.yyyy"

WhereCommandsWaiting::WhereCommandsWaiting(QWidget *parent, std::shared_ptr<DBConnection> db) :
    QWidget(parent),
    ui(new Ui::WhereCommandsWaiting),
    m_db(db),
    m_commands(new CommandVtr())
{
    ui->setupUi(this);
    refresh();
}

WhereCommandsWaiting::~WhereCommandsWaiting()
{
    delete ui;
}

void WhereCommandsWaiting::refresh()
{
    m_commands->clear();
    TaskTypePtrVtr taskTypes =  m_db->getTaskTypes()->getTypes();
    for (auto taskType : *taskTypes)
    {
        auto commands = m_db->getCommandWhichWaitingOnTask(taskType->getId());
        if (commands != nullptr && !commands->empty())
        {
            m_commands->insert(m_commands->end(), commands->begin(), commands->end());
        }
    }

    fillTable();
}

void WhereCommandsWaiting::details()
{
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
    if(std::find(m_detailsButtons.begin(), m_detailsButtons.end(), buttonSender) != m_detailsButtons.end())
    {
        auto index = std::find(m_detailsButtons.begin(), m_detailsButtons.end(), buttonSender) - m_detailsButtons.begin();
        qDebug() << index;
        auto commanddialog = new CommandDialogChieOfProduction(this, m_db, m_commands->at(index), false, nullptr);
        commanddialog->show();
    }
}

void WhereCommandsWaiting::clearBuutonsAndInitializeHeaders()
{
    m_detailsButtons.clear();

    ui->tableWidget->setRowCount(0);
    QStringList headers;
    headers     << "Broj naloga" << "Prioritet" << "Detalji" << "Rok zavrsetka"
                << "Predvidjanje" << "Komercijalista" << "Kreiran" << "Status" << "Caka na";
    ui->tableWidget->setColumnCount(headers.size());
    ui->tableWidget->setHorizontalHeaderLabels(headers);
}

void WhereCommandsWaiting::fillTable()
{
    clearBuutonsAndInitializeHeaders();
    if (!m_commands || m_commands->empty())
    {
        return;
    }
    auto i = 0;
    for (auto iter = m_commands->begin(); iter != m_commands->end(); ++i, ++iter)
    {
        auto j = 0;
        CommandPtr command = *iter;
        ui->tableWidget->insertRow(i);
        insertCommandNumber(command, i , j++);
        insertPriority(command, i , j++);
        insertDetials(i, j++);
        insertDeadline(command, i ,j++);
        insertPrediction(command, i, j++);
        insertKomercialist(command, i, j++);
        insertCreation(command, i, j++);
        insertStatus(command, i , j++);
        insertTaskType(command, i, j++);
    }
    ui->tableWidget->resizeColumnsToContents();
}

void WhereCommandsWaiting::insertCommandNumber(CommandPtr command, unsigned i, unsigned j)
{
    auto *item = new QTableWidgetItem(QString::number(command->getCommandNumber()));
    ui->tableWidget->setItem(i, j, item);
}

void WhereCommandsWaiting::insertPriority(CommandPtr command, unsigned i, unsigned j)
{
    auto *item = new QTableWidgetItem(QString::number(command->getPriority()));
    ui->tableWidget->setItem(i, j, item);
}

void WhereCommandsWaiting::insertDetials(unsigned i, unsigned j)
{
    QPushButton* btn_details = new QPushButton();
    btn_details->setText("Detalji");
    ui->tableWidget->setIndexWidget(ui->tableWidget->model()->index(i, j), btn_details);
    m_detailsButtons.push_back(btn_details);
    connect(btn_details, SIGNAL(clicked()), this, SLOT(details()));
}

void WhereCommandsWaiting::insertDeadline(CommandPtr command, unsigned i, unsigned j)
{
    auto *item = new QTableWidgetItem(m_db->getOrder(command->getIdOrder())->getTimeLimit().toString(DATATIMEVIEW));
    ui->tableWidget->setItem(i, j, item);
}

void WhereCommandsWaiting::insertPrediction(CommandPtr command, unsigned i, unsigned j)
{
    auto *item = new QTableWidgetItem(command->getDateTimePrediction().toString(DATATIMEVIEW));
    ui->tableWidget->setItem(i, j, item);
}

void WhereCommandsWaiting::insertKomercialist(CommandPtr command, unsigned i, unsigned j)
{
    auto *item = new QTableWidgetItem(m_db->getEmployee(command->getKomercialistID())->getUserName());
    ui->tableWidget->setItem(i, j, item);
}

void WhereCommandsWaiting::insertCreation(CommandPtr command, unsigned i, unsigned j)
{
    auto *item = new QTableWidgetItem(command->getDateTimeCreation().toString(DATATIMEVIEW));
    ui->tableWidget->setItem(i, j, item);
}

void WhereCommandsWaiting::insertStatus(CommandPtr command, unsigned i, unsigned j)
{
    auto *item = new QTableWidgetItem(command->getStateQString());
    ui->tableWidget->setItem(i, j, item);
}

void WhereCommandsWaiting::insertTaskType(CommandPtr command, unsigned i, unsigned j)
{
    auto task = m_db->getCurrentTask(command);
    TaskTypePtr taskType = m_db->getTaskTypes()->getTaskTypeById(task->getTaskTypeId());
    if (taskType != nullptr)
    {
        auto *item = new QTableWidgetItem(taskType->getName());
        ui->tableWidget->setItem(i, j, item);
    }
}

void WhereCommandsWaiting::on_pushButton_clicked()
{
    refresh();
}
