#include <QDebug>
#include "commandsviewwaitingontask.h"
#include "ui_commandsviewwaitingontask.h"
#include "mainwindow.h"
#include "commanddialogdesigner.h"
#include "commanddialogstorekeeper.h"

CommandsViewWaitingOnTask::CommandsViewWaitingOnTask(QWidget *parent, DBConnectionPtr db, unsigned taskTypeID) :
    QWidget(parent),
    ui(new Ui::CommandsViewWaitingOnTask),
    m_db(db),
    m_taskTypeID(taskTypeID)
{
    ui->setupUi(this);
    openDialogIfThereIsTaskOnWhichUserWorkingOn();
}

CommandsViewWaitingOnTask::~CommandsViewWaitingOnTask()
{
    delete ui;
}

void CommandsViewWaitingOnTask::on_Refresh_clicked()
{
    m_commands = m_db->getCommandWhichWaitingOnTask(m_taskTypeID);
    fillTable();
}

void CommandsViewWaitingOnTask::fillTable()
{
    qDebug() << "***user refreshing commands view***";
    clearButtons();
    ui->tableWidget->setRowCount(0);

    if (!m_commands || m_commands->empty())
    {
        return;
    }

    qDebug() << "broj naloga " + QString::number(m_commands->size());

    auto i = 0;
    for (auto iter = m_commands->begin(); iter != m_commands->end(); ++i, ++iter)
    {
        ui->tableWidget->insertRow(i);
        CommandPtr command = *iter;
        insertCommandNumber(command, i, 0);
        insertDetailsButton(i, 1);
        inserTakeCommandButton(i, 2);

    }
    ui->tableWidget->resizeColumnsToContents();
}

void CommandsViewWaitingOnTask::clearButtons()
{
    m_detailsButtons.clear();
    m_takeCommandButtons.clear();
}

void CommandsViewWaitingOnTask::insertCommandNumber(CommandPtr command, unsigned i, unsigned j)
{
    auto *item = new QTableWidgetItem(QString::number(command->getCommandNumber()));
    ui->tableWidget->setItem(i, j, item);
}

void CommandsViewWaitingOnTask::insertDetailsButton(unsigned i, unsigned j)
{
    QPushButton* btn_details = new QPushButton();
    btn_details->setText("Detalji");
    ui->tableWidget->setIndexWidget(ui->tableWidget->model()->index(i, j), btn_details);
    m_detailsButtons.push_back(btn_details);
    connect(btn_details, SIGNAL(clicked()), this, SLOT(details()));
}

void CommandsViewWaitingOnTask::inserTakeCommandButton(unsigned i, unsigned j)
{
    QPushButton* btn_take = new QPushButton();
    btn_take->setText("Preuzmi nalog");
    ui->tableWidget->setIndexWidget(ui->tableWidget->model()->index(i, j), btn_take);
    m_takeCommandButtons.push_back(btn_take);
    connect(btn_take, SIGNAL(clicked()), this, SLOT(takeCommand()));
}

void CommandsViewWaitingOnTask::details()
{
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
    if(std::find(m_detailsButtons.begin(), m_detailsButtons.end(), buttonSender) != m_detailsButtons.end())
    {
        auto index = std::find(m_detailsButtons.begin(), m_detailsButtons.end(), buttonSender) - m_detailsButtons.begin();
        qDebug() << index;
        OpenCommandDialogByWorkPosition(m_commands->at(index), false);
    }
}

void CommandsViewWaitingOnTask::takeCommand()
{
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
    if(std::find(m_takeCommandButtons.begin(), m_takeCommandButtons.end(), buttonSender) != m_takeCommandButtons.end())
    {
        auto index = std::find(m_takeCommandButtons.begin(), m_takeCommandButtons.end(), buttonSender) - m_takeCommandButtons.begin();
        qDebug() << index;
        m_db->startWorkingOnWaitingTask(m_commands->at(index), MainWindow::getLogedUser());
        OpenCommandDialogByWorkPosition(m_commands->at(index), true);
    }
}

void CommandsViewWaitingOnTask::openDialogIfThereIsTaskOnWhichUserWorkingOn()
{
    EmployeePtr employee = MainWindow::getLogedUser();
    CommandPtr command = m_db->getCommandOnWhichEmployeeWorkingOn(employee);
    if (command)
    {
        OpenCommandDialogByWorkPosition(command, true);
    }
}

void CommandsViewWaitingOnTask::OpenCommandDialogByWorkPosition(CommandPtr command, bool edit)
{
    QWidget* commanddialog;
    switch(MainWindow::getLogedUser()->getWorkPosition())
    {
    case Employee::WorkPosition::Dizajner:
        commanddialog = new CommandDialogDesigner(this, m_db, command, edit);
        commanddialog->show();
        break;
    case Employee::WorkPosition::Magacioner:
        commanddialog = new CommandDialogStoreKeeper(this, m_db, command, edit);
        commanddialog->show();
        break;
    default:
        break;
    }
}