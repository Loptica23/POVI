#include <QDateTime>
#include <QLabel>
#include <QBrush>
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
    ui->pushButton_2->setEnabled(false);
    if (state == Command::State::InProgress)
    {
        ui->pushButton_2->setEnabled(true);
    }
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
    ui->pushButton_2->setEnabled(true);
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

void CommandsViewIsInState::stopCommand()
{
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
    if(std::find(m_stopContinueButons.begin(), m_stopContinueButons.end(), buttonSender) != m_stopContinueButons.end())
    {
        auto index = std::find(m_stopContinueButons.begin(), m_stopContinueButons.end(), buttonSender) - m_stopContinueButons.begin();
        qDebug() << index;
        m_db->stopCommand(m_commands->at(index));
        refresh();
    }
}

void CommandsViewIsInState::continueCommand()
{
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
    if(std::find(m_stopContinueButons.begin(), m_stopContinueButons.end(), buttonSender) != m_stopContinueButons.end())
    {
        auto index = std::find(m_stopContinueButons.begin(), m_stopContinueButons.end(), buttonSender) - m_stopContinueButons.begin();
        qDebug() << index;
        m_db->sendToProduction(m_commands->at(index));
        refresh();
    }
}

void CommandsViewIsInState::sendBackToKomercialists()
{
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
    if(std::find(m_sendBackToKomercialistsButtons.begin(), m_sendBackToKomercialistsButtons.end(), buttonSender) != m_sendBackToKomercialistsButtons.end())
    {
        auto index = std::find(m_sendBackToKomercialistsButtons.begin(), m_sendBackToKomercialistsButtons.end(), buttonSender) - m_sendBackToKomercialistsButtons.begin();
        qDebug() << index;
        m_db->sendToKomercial(m_commands->at(index));
        refresh();
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
        auto j = 0;
        ui->tableWidget->insertRow(i);
        insertCommandNumber(command, i, j++);
        insertPriority(command, i, j++);
        insertDetailsButton(i, j++);
        insertEditButton(i, j++);
        insertTimeSimulatorPrediction(command, i , j++);
        insertDeathLine(command, i, j++);
        insertPrediction(command, i, j++);
        insertKomercialist(command, i, j++);
        insertDateTimeCreation(command, i, j++);
        insertHealth(command, i , j++);
        insertPredictionButton(i, j++);
        insertStopContinueButton(command, i, j++);
        insertSendBackToKomercialist(command, i, j++);
    }
    ui->tableWidget->resizeColumnsToContents();
}

void CommandsViewIsInState::clearBuutonsAndInitializeHeaders()
{
    m_editButtons.clear();
    m_detailsButtons.clear();
    m_predictionButtons.clear();
    m_stopContinueButons.clear();
    m_sendBackToKomercialistsButtons.clear();

    QStringList headers;
    headers << "Broj Naloga"
            << "Prioritet"
            << "Detalji"
            << "Izmeni"
            << "Izracunato vreme"
            << "Rok Zavrsetka"
            << "Predvidjanje"
            << "Komercijalista"
            << "Kreiran"
            << "Status"
            << "Predvidi"
            << "Stopiraj/Nastavi"
            << "Vrati komercijali";
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

void CommandsViewIsInState::insertDateTimeCreation(CommandPtr command, unsigned i, unsigned j)
{
    QDateTime creation = command->getDateTimeCreation();
    if (!creation.isNull())
    {
        auto *item = new QTableWidgetItem(creation.toString(timeFormat));
        ui->tableWidget->setItem(i, j, item);
    }
}

void CommandsViewIsInState::insertHealth(CommandPtr command, unsigned i, unsigned j)
{
    QDateTime predictedTime = getPredictionFromTimeSimulatorResult(command);
    QDateTime deatheLine = m_db->getOrder(command->getIdOrder())->getTimeLimit();
    auto *item = new QTableWidgetItem();
    QBrush brush;
    if (!predictedTime.isNull())
    {
        if (deatheLine < predictedTime)
        {
            item->setText("Kasni");
            brush.setColor(QColor("red"));
        }
        else if (deatheLine < predictedTime.addDays(3))
        {
            item->setText("Paznja");
            brush.setColor(QColor("yellow"));
        }
        else
        {
            item->setText("U redu");
            brush.setColor(QColor("green"));
        }
    }
    item->setForeground(brush);
    ui->tableWidget->setItem(i, j, item);
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

void CommandsViewIsInState::insertStopContinueButton(CommandPtr command, unsigned i, unsigned j)
{
    QPushButton* btn = new QPushButton();
    btn->setEnabled(false);
    if (command->getState() == Command::State::InProgress)
    {
        btn->setText("Stopiraj");
        btn->setEnabled(true);
        connect(btn, SIGNAL(clicked()), this, SLOT(stopCommand()));
    }
    if (command->getState() == Command::State::Stopped)
    {
        btn->setText("Nastavi");
        btn->setEnabled(true);
        connect(btn, SIGNAL(clicked()), this, SLOT(continueCommand()));
    }
    m_stopContinueButons.push_back(btn);
    ui->tableWidget->setIndexWidget(ui->tableWidget->model()->index(i, j), btn);
}

void CommandsViewIsInState::insertSendBackToKomercialist(CommandPtr command, unsigned i, unsigned j)
{
    QPushButton* btn = new QPushButton();
    auto enable = false;
    btn->setText("Vrati komercijali");
    connect(btn, SIGNAL(clicked()), this, SLOT(sendBackToKomercialists()));
    if ((command->getState() == Command::State::Stopped) || (command->getState() == Command::State::WaitForProduction))
    {
        auto task = m_db->getCurrentTask(command);
        if ((task != nullptr) && (task->getState() != Task::State::InProgress))
        {
            enable = true;
        }
    }
    btn->setEnabled(enable);
    m_sendBackToKomercialistsButtons.push_back(btn);
    ui->tableWidget->setIndexWidget(ui->tableWidget->model()->index(i, j), btn);
}

void CommandsViewIsInState::on_pushButton_2_clicked()
{
    ui->pushButton_2->setEnabled(false);
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
        unsigned prediction = task->getPrediction();
        auto msec = task->getStartTime().msecsTo(QDateTime::currentDateTime());
        unsigned minutes = 0;
        QString machineName = getMachineName(task->getMachineId());
        TimeSimulator::TaskState state;
        switch(task->getState())
        {
        case Task::State::Complited:
            state = TimeSimulator::TaskState::Complited;
            break;
        case Task::State::InProgress:
            state = TimeSimulator::TaskState::InProgress;
            minutes = msec/(1000*60);
            if (prediction > minutes)
                prediction -= minutes;
            else
                prediction = 0;
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
        m_timeSimulator->addTask(machineName, command->getID(), task->getSerialNumber(), prediction, state);
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
