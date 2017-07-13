#pragma once
#include <QWidget>
#include <QPushButton>
#include <QString>
#include "dbconnection.h"
#include "TimeSimulator/types.h"
#include "TimeSimulator/timesimulator.h"

namespace Ui {
class CommandsViewIsInState;
}

class CommandsViewIsInState : public QWidget
{
    Q_OBJECT

public:
    CommandsViewIsInState(QWidget *parent, DBConnectionPtr db, Command::State state);
    virtual ~CommandsViewIsInState();

    void setCommands(CommandPtrVtr commands);
    void showTimeSimulatorResults(TimeSimulator::TimeSimulatorResultMapPtr timeSimulatorMap);

public slots:
    void timeEngineFinish();

private slots:
    void on_refresh_clicked();
    void details();
    void edit();
    void predict();

    void on_pushButton_2_clicked();

private:
    void fillTable();
    void clearBuutonsAndInitializeHeaders();
    void insertCommandNumber(CommandPtr command, unsigned i, unsigned j);
    void insertPriority(CommandPtr command, unsigned i, unsigned j);
    void insertDetailsButton(unsigned i, unsigned j);
    void insertEditButton(unsigned i, unsigned j);
    void insertTimeSimulatorPrediction(CommandPtr command, unsigned i, unsigned j);
    void insertDeathLine(CommandPtr command, unsigned i , unsigned j);
    void insertKomercialist(CommandPtr command, unsigned i, unsigned j);
    void insertHealth(CommandPtr command, unsigned i, unsigned j);
    void insertPrediction(CommandPtr command, unsigned i, unsigned j);
    void insertPredictionButton(unsigned i, unsigned j);
    void initializeTimeMachines();
    void initializeCommands();
    void initializeTasksForCommand(CommandPtr command);

    QString getMachineName(unsigned machineId);
    QDateTime getPredictionFromTimeSimulatorResult(CommandPtr command);
    QString getPredictionFromTimeSimulatorResultString(CommandPtr command);

    Ui::CommandsViewIsInState *ui;
    DBConnectionPtr m_db;
    MachinePtrVtr m_machines;
    CommandPtrVtr m_commands;
    Command::State m_state;

    std::vector<QPushButton*> m_detailsButtons;
    std::vector<QPushButton*> m_editButtons;
    std::vector<QPushButton*> m_predictionButtons;

    TimeSimulator::CommandTerminationTimeEngine* m_engine;
    std::shared_ptr<TimeSimulator::TimeSimulator> m_timeSimulator;
    TimeSimulator::MachineVtrPtr m_timeMachines;
    TimeSimulator::TimeSimulatorResultMapPtr m_resultMap;
};
