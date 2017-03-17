#include "commandsviewisinstate.h"
#include "ui_commandsviewisinstate.h"
#include "commanddialogchieofproduction.h"
#include "TimeSimulator/timesimulator.h"
#include "TimeSimulator/commandterminationtimeengine.h"
#include "TimeSimulator/machine.h"
#include "TimeSimulator/command.h"
#include "TimeSimulator/task.h"
#include "machine.h"

CommandsViewIsInState::CommandsViewIsInState(QWidget *parent, DBConnectionPtr db) :
    QWidget(parent),
    ui(new Ui::CommandsViewIsInState),
    m_state(Command::State::InProgress),
    m_db(db)
{
    ui->setupUi(this);
}

CommandsViewIsInState::~CommandsViewIsInState()
{
    delete ui;
}

void CommandsViewIsInState::on_refresh_clicked()
{
    auto commands = m_db->getCommands(m_state);
    setCommands(commands);
    fillTable();
}

void CommandsViewIsInState::setCommands(CommandPtrVtr commands)
{
    m_commands = commands;
}

void CommandsViewIsInState::details()
{
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
    if(std::find(m_detailsButtons.begin(), m_detailsButtons.end(), buttonSender) != m_detailsButtons.end())
    {
        auto index = std::find(m_detailsButtons.begin(), m_detailsButtons.end(), buttonSender) - m_detailsButtons.begin();
        qDebug() << index;
        auto commandDialog = new CommandDialogChieOfProduction(this, m_db, m_commands->at(index), false);
        commandDialog->show();
    }
}

void CommandsViewIsInState::edit()
{
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
    if(std::find(m_editButtons.begin(), m_editButtons.end(), buttonSender) != m_editButtons.end())
    {
        auto index = std::find(m_editButtons.begin(), m_editButtons.end(), buttonSender) - m_editButtons.begin();
        qDebug() << index;
        auto commandDialog = new CommandDialogChieOfProduction(this, m_db, m_commands->at(index), true);
        commandDialog->show();
    }
}

void CommandsViewIsInState::fillTable()
{
    clearBuutonsAndInitializeHeaders();
    if (!m_commands || m_commands->empty())
    {
        return;
    }
    auto i = 0;
    for (auto iter = m_commands->begin(); iter != m_commands->end(); ++i, ++iter)
    {
        CommandPtr command = *iter;
        ui->tableWidget->insertRow(i);
        insertCommandNumber(command, i, 0);
        insertPriority(command, i, 1);
        insertDetailsButton(i, 2);
        insertEditButton(i, 3);
    }
    ui->tableWidget->resizeColumnsToContents();
}

void CommandsViewIsInState::clearBuutonsAndInitializeHeaders()
{
    m_editButtons.clear();
    m_detailsButtons.clear();

    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(4);
    QStringList headers;
    headers << "Broj Naloga" << "Prioritet" << "Detalji" << "Izmeni";
    ui->tableWidget->setHorizontalHeaderLabels(headers);
}

void CommandsViewIsInState::insertCommandNumber(CommandPtr command, unsigned i, unsigned j)
{
    auto *item = new QTableWidgetItem(QString::number(command->getCommandNumber()));
    ui->tableWidget->setItem(i, j, item);
}

void CommandsViewIsInState::insertPriority(CommandPtr command, unsigned i, unsigned j)
{
    auto *item = new QTableWidgetItem(QString::number(command->getPriority()));
    ui->tableWidget->setItem(i, j, item);
}

void CommandsViewIsInState::insertDetailsButton(unsigned i, unsigned j)
{
    QPushButton* btn_details = new QPushButton();
    btn_details->setText("Detalji");
    ui->tableWidget->setIndexWidget(ui->tableWidget->model()->index(i, j), btn_details);
    m_detailsButtons.push_back(btn_details);
    connect(btn_details, SIGNAL(clicked()), this, SLOT(details()));
}

void CommandsViewIsInState::insertEditButton(unsigned i, unsigned j)
{
    QPushButton* btn_edit = new QPushButton();
    btn_edit->setText("Izmeni");
    ui->tableWidget->setIndexWidget(ui->tableWidget->model()->index(i, j), btn_edit);
    m_editButtons.push_back(btn_edit);
    connect(btn_edit, SIGNAL(clicked()), this, SLOT(edit()));
}

void CommandsViewIsInState::on_pushButton_2_clicked()
{
    m_timeSimulator.reset(new TimeSimulator::TimeSimulator());

    initializeTimeEngine();

    qDebug() << "initialization is finished!";
    if (m_engine->checkIsEverythingSetUp())
    {
        qDebug() << "starting engine from main thread!";
        m_timeSimulator->execute(m_engine);
    }
}

void CommandsViewIsInState::initializeTimeEngine()
{
    m_engine = new TimeSimulator::CommandTerminationTimeEngine();
    initializeTimeMachines();

    //dohvatanje komandi
    auto commands = m_db->getCommands(m_state);
    setCommands(commands);

    for (auto iter = m_commands->begin(); iter != m_commands->end(); ++iter)
    {
        CommandPtr command = *iter;
        initializeTimeTasksForCommand(command);
    }
}

void CommandsViewIsInState::initializeTimeMachines()
{
    //pravim masine
    m_timeMachines.reset(new TimeSimulator::MachineVtr());
    MachinePtrVtr AllMachines = m_db->getMachines();
    for (auto iter = AllMachines->begin(); iter != AllMachines->end(); ++iter)
    {
        MachinePtr machine = *iter;
        TimeSimulator::MachinePtr newTimeMachine(new TimeSimulator::Machine(machine->getId()));
        m_timeMachines->push_back(newTimeMachine);
    }
    //setujem masine simulatoru
    m_engine->setMachines(m_timeMachines);
}

void CommandsViewIsInState::initializeTimeTasksForCommand(CommandPtr command)
{
    bool wrongCommand = false;
    TimeSimulator::CommandPtr timeCommand(new TimeSimulator::Command(command->getID(), command->getPriority()));
    TaskPtrVtr tasks = m_db->getTasks(command);
    TimeSimulator::TaskVtrPtr timeTasks(new TimeSimulator::TaskVtr());
    for (auto taskIter = tasks->begin(); taskIter != tasks->end(); ++taskIter)
    {
        TaskPtr task = *taskIter;
        TimeSimulator::TaskPtr timeTask(new TimeSimulator::Task(task->getMachineId(), task->getSerialNumber()));
        TimeSimulator::MachinePtr timeMachine = m_engine->getMachineWithId(task->getMachineId());
        switch(task->getState())
        {
        case Task::State::Complited:
            break;
        case Task::State::Leaved:
            break;
        case Task::State::InProgress:
            timeTask->setPrediction(task->getPrediction());
            timeMachine->putCurrentCommand(timeCommand);
            timeTasks->push_back(timeTask);
            if (!task->getMachineId())
            {
                wrongCommand = true;
            }
            break;
        case Task::State::Waiting:
            timeTask->setPrediction(task->getPrediction());
            timeMachine->putCommandIntoQueue(timeCommand);
            timeTasks->push_back(timeTask);
            if (!task->getMachineId())
            {
                wrongCommand = true;
            }
            break;
        case Task::State::New:
            timeTask->setPrediction(task->getPrediction());
            timeTasks->push_back(timeTask);
            if (!task->getMachineId())
            {
                wrongCommand = true;
            }
            break;
        case Task::State::Stopped:
            wrongCommand = true;
            break;
        }
    }

    if (wrongCommand)
    {
        qDebug() << "nalog id = " << command->getID() << "nema sve informacije za izracunavanje i zbog toga ispada iz kalkulacije!";
        m_engine->eliminateCommandFromCalculation(timeCommand);
    }
    else
    {
        qDebug() << "setting tasks";
        timeCommand->setTasks(timeTasks);
    }
}
