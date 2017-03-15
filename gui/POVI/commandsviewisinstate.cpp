#include "commandsviewisinstate.h"
#include "ui_commandsviewisinstate.h"
#include "commanddialogchieofproduction.h"
#include "TimeSimulator/timesimulator.h"
#include "TimeSimulator/commandterminationtimeengine.h"
#include "TimeSimulator/machine.h"
#include "TimeSimulator/command.h"
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
    //ovde moras da setujes simulator
    TimeSimulator::TimeSimulator* timesimulator = new TimeSimulator::TimeSimulator();
    //ocigledno je da ne smes da budes odogovoran za zivot engina
    engine.reset(new TimeSimulator::CommandTerminationTimeEngine());
    //sada inicijalizujes simulator

    //pravim masine
    TimeSimulator::MachineVtrPtr timeMachines(new TimeSimulator::MachineVtr());
    MachinePtrVtr AllMachines = m_db->getMachines();
    for (auto iter = AllMachines->begin(); iter != AllMachines->end(); ++iter)
    {
        MachinePtr machine = *iter;
        TimeSimulator::MachinePtr newTimeMachine(new TimeSimulator::Machine(machine->getId()));
        timeMachines->push_back(newTimeMachine);
    }
    //setujem masine simulatoru
    engine->setMachines(timeMachines);

    //dohvatanje komandi
    auto commands = m_db->getCommands(m_state);
    setCommands(commands);

    for (auto iter = m_commands->begin(); iter != m_commands->end(); ++iter)
    {
        CommandPtr command = *iter;
        TimeSimulator::CommandPtr timeCommand(new TimeSimulator::Command(command->getID()));
        TaskPtrVtr tasks = m_db->getTasks(command);

        //moram da prodjem kroz taskove
        //da li su ovi taskovi u po rednom broju
        for (auto taskIter = tasks->begin(); taskIter != tasks->end(); ++iter)
        {
            TaskPtr task = *taskIter;
            switch(task->getState())
            {
            case Task::State::Complited:
                //ne radis nista
                break;
            case Task::State::Leaved:
                //ne radis nista
                break;
            case Task::State::InProgress:
                //ovde moras da radis oduzimanje
                //dodas komandi
                break;
            case Task::State::Waiting:
                //ubacujes u listu cekanja za masinu
                //dodas komandi
                break;
            case Task::State::New:
                //ne radis nista
                //dodaj komandi
                break;
            case Task::State::Stopped:
                //nemam pojma sta u ovoj situaciji, najbolje je da ga ne racunas
                //to jest nekako da preskocis tu komandu
                break;
            }
        }
    }

    //startovanje motora
    timesimulator->execute(engine);
}
