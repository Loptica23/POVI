#include <QDateTime>
#include "commandsviewisinstate.h"
#include "ui_commandsviewisinstate.h"
#include "commanddialogchieofproduction.h"
#include "TimeSimulator/timesimulator.h"
#include "TimeSimulator/timeengine.h"
#include "TimeSimulator/machine.h"
#include "TimeSimulator/command.h"
#include "TimeSimulator/task.h"
#include "TimeSimulator/types.h"
#include "machine.h"
#include "command.h"
#include "dbconnection.h"
#include "utils.h"
#include "dialogsetprediction.h"

#define timeFormat "hh:mm dd.MM.yyyy"

CommandsViewIsInState::CommandsViewIsInState(QWidget *parent, DBConnectionPtr db, Command::State state) :
    QWidget(parent),
    ui(new Ui::CommandsViewIsInState),
    m_state(state),
    m_db(db),
    m_resultMap(nullptr)
{
    ui->setupUi(this);
    refresh();
}

CommandsViewIsInState::~CommandsViewIsInState()
{
    delete ui;
}

void CommandsViewIsInState::refresh()
{
    auto commands = m_db->getCommands(m_state);
    setCommands(commands);
    fillTable();
}

void CommandsViewIsInState::on_refresh_clicked()
{
    refresh();
}

void CommandsViewIsInState::setCommands(CommandPtrVtr commands)
{
    m_commands = commands;
}

void CommandsViewIsInState::timeEngineFinish()
{
    qDebug() << "Pozvan slot! " + QString::number(m_timeSimulator->getResult()->size());
    m_resultMap = m_timeSimulator->getResult();
    fillTable();
}

void CommandsViewIsInState::details()
{
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
    if(std::find(m_detailsButtons.begin(), m_detailsButtons.end(), buttonSender) != m_detailsButtons.end())
    {
        auto index = std::find(m_detailsButtons.begin(), m_detailsButtons.end(), buttonSender) - m_detailsButtons.begin();
        qDebug() << index;
        auto commandDialog = new CommandDialogChieOfProduction(this, m_db, m_commands->at(index), false, this);
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
        auto commandDialog = new CommandDialogChieOfProduction(this, m_db, m_commands->at(index), true, this);
        commandDialog->show();
    }
}

void CommandsViewIsInState::predict()
{
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
    if(std::find(m_predictionButtons.begin(), m_predictionButtons.end(), buttonSender) != m_predictionButtons.end())
    {
        auto index = std::find(m_predictionButtons.begin(), m_predictionButtons.end(), buttonSender) - m_predictionButtons.begin();
        qDebug() << index;
        auto dialogSetPrediction = new DialogSetPrediction(this, m_db, m_commands->at(index), this);
        dialogSetPrediction->show();
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
        insertTimeSimulatorPrediction(command, i , 4);
        insertDeathLine(command, i, 5);
        insertPrediction(command, i, 6);
        insertKomercialist(command, i, 7);
        insertHealth(command, i , 8);
        insertPredictionButton(i, 9);
    }
    ui->tableWidget->resizeColumnsToContents();
}

void CommandsViewIsInState::clearBuutonsAndInitializeHeaders()
{
    m_editButtons.clear();
    m_detailsButtons.clear();
    m_predictionButtons.clear();

    QStringList headers;
    headers << "Broj Naloga" << "Prioritet" << "Detalji" << "Izmeni" << "Izracunato vreme" << "Rok Zavrsetka" << "Predvidjanje" << "Komercijalista" << "Status" << "Predvidi";
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(headers.size());
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

void CommandsViewIsInState::insertTimeSimulatorPrediction(CommandPtr command, unsigned i, unsigned j)
{
    auto *item = new QTableWidgetItem(getPredictionFromTimeSimulatorResultString(command));
    ui->tableWidget->setItem(i, j, item);
}

void CommandsViewIsInState::insertDeathLine(CommandPtr command, unsigned i , unsigned j)
{
    OrderPtr order = m_db->getOrder(command->getIdOrder());
    auto *item = new QTableWidgetItem(order->getTimeLimit().toString(timeFormat));
    ui->tableWidget->setItem(i, j, item);
}

void CommandsViewIsInState::insertKomercialist(CommandPtr command, unsigned i, unsigned j)
{
    EmployeePtr employee = m_db->getEmployee(command->getKomercialistID());
    auto *item = new QTableWidgetItem(employee->getUserName());
    ui->tableWidget->setItem(i, j, item);
}

void CommandsViewIsInState::insertHealth(CommandPtr command, unsigned i, unsigned j)
{
    QDateTime predictedTime = getPredictionFromTimeSimulatorResult(command);
    QDateTime deatheLine = m_db->getOrder(command->getIdOrder())->getTimeLimit();
    if (!predictedTime.isNull())
    {
        QLabel* label = new QLabel();
        if (deatheLine < predictedTime) // kasni
        {
            label->setText("Kasni");
        }
        else if (deatheLine < predictedTime.addDays(3))
        {
            label->setText("Paznja");
        }
        else
        {
            label->setText("U redu");
        }
        ui->tableWidget->setIndexWidget(ui->tableWidget->model()->index(i, j), label);
    }
}

void CommandsViewIsInState::insertPrediction(CommandPtr command, unsigned i, unsigned j)
{
    QDateTime prediction = command->getDateTimePrediction();
    if (!prediction.isNull())
    {
        auto *item = new QTableWidgetItem(prediction.toString(timeFormat));
        ui->tableWidget->setItem(i, j, item);
    }
}

void CommandsViewIsInState::insertPredictionButton(unsigned i, unsigned j)
{
    QPushButton* btn_predict = new QPushButton();
    btn_predict->setText("Predvidi");
    ui->tableWidget->setIndexWidget(ui->tableWidget->model()->index(i, j), btn_predict);
    m_predictionButtons.push_back(btn_predict);
    connect(btn_predict, SIGNAL(clicked()), this, SLOT(predict()));
}

void CommandsViewIsInState::on_pushButton_2_clicked()
{
    m_timeSimulator.reset(new TimeSimulator::TimeSimulator());
    connect(  m_timeSimulator->getSender()
            , SIGNAL(sendResult())
            , this
            , SLOT(timeEngineFinish()));
    initializeTimeMachines();
    initializeCommands();
    qDebug() << "initialization is finished!";
    if (m_timeSimulator->checkIsEverythingSetUp())
    {
        qDebug() << "starting engine from main thread!";
        m_timeSimulator->execute();
    }
}

void CommandsViewIsInState::initializeTimeMachines()
{
    m_machines = m_db->getMachines();
    for (auto & machine : *m_machines)
    {
        m_timeSimulator->addMachine(machine->getName(), machine->isVirtual());
    }
}

void CommandsViewIsInState::initializeCommands()
{
    Command::State state = Command::State::InProgress;
    CommandPtrVtr commands = m_db->getCommands(state);
    for (auto iter = commands->begin(); iter != commands->end(); ++iter)
    {
        CommandPtr command = *iter;
        m_timeSimulator->addCommand(command->getID(), command->getCommandNumber(), command->getPriority());
        initializeTasksForCommand(command);
    }
}

void CommandsViewIsInState::initializeTasksForCommand(CommandPtr command)
{
    TaskPtrVtr tasks = m_db->getTasks(command);
    for (auto iter = tasks->begin(); iter != tasks->end(); ++iter)
    {
        TaskPtr task = *iter;
        QString machineName = getMachineName(task->getMachineId());
        TimeSimulator::TaskState state;
        switch(task->getState())
        {
        case Task::State::Complited:
            state = TimeSimulator::TaskState::Complited;
            break;
        case Task::State::InProgress:
            state = TimeSimulator::TaskState::InProgress;
            break;
        case Task::State::Leaved:
            state = TimeSimulator::TaskState::Leaved;
            break;
        case Task::State::New:
            state = TimeSimulator::TaskState::New;
            break;
        case Task::State::Stopped:
            state = TimeSimulator::TaskState::Stopped;
            break;
        case Task::State::Waiting:
            state = TimeSimulator::TaskState::Waiting;
            break;
        }
        m_timeSimulator->addTask(machineName, command->getID(), task->getSerialNumber(), task->getPrediction(), state);
    }
}

QString CommandsViewIsInState::getMachineName(unsigned machineId)
{
    QString result = "";
    MachinePtr machine = Utils::findElementInVectorPtr(m_machines, machineId, &Machine::getId);
    if (machine != nullptr)
    {
        result = machine->getName();
    }
    return result;
}

QDateTime CommandsViewIsInState::getPredictionFromTimeSimulatorResult(CommandPtr command)
{
    QDateTime result;
    QDateTime currentDateTime = QDateTime::currentDateTime();
    if (m_resultMap != nullptr)
    {
        auto prediction = m_resultMap->find(command->getID());
        if (prediction != m_resultMap->end())
            if (prediction->second != 0)
            {
                qint64 seconds = prediction->second * 60;
                result = currentDateTime.addSecs(seconds);
            }
    }
    return result;
}

QString CommandsViewIsInState::getPredictionFromTimeSimulatorResultString(CommandPtr command)
{
    QString result;
    QDateTime dateTime = getPredictionFromTimeSimulatorResult(command);
    if (!dateTime.isNull())
    {
        result = dateTime.toString("hh:mm dd.MM.yyyy");
    }
    return result;
}
