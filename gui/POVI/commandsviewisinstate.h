#pragma once
#include <QWidget>
#include <QPushButton>
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
    CommandsViewIsInState(QWidget *parent, DBConnectionPtr db);
    virtual ~CommandsViewIsInState();

    void setCommands(CommandPtrVtr commands);

private slots:
    void on_refresh_clicked();
    void details();
    void edit();

    void on_pushButton_2_clicked();

private:
    void fillTable();
    void clearBuutonsAndInitializeHeaders();
    void insertCommandNumber(CommandPtr command, unsigned i, unsigned j);
    void insertPriority(CommandPtr command, unsigned i, unsigned j);
    void insertDetailsButton(unsigned i, unsigned j);
    void insertEditButton(unsigned i, unsigned j);

    void initializeTimeEngine();
    void initializeTimeMachines();
    void initializeTimeTasksForCommand(CommandPtr command);

    Ui::CommandsViewIsInState *ui;
    DBConnectionPtr m_db;
    CommandPtrVtr m_commands;
    Command::State m_state;

    std::vector<QPushButton*> m_detailsButtons;
    std::vector<QPushButton*> m_editButtons;

    TimeSimulator::CommandTerminationTimeEngine* m_engine;
    std::shared_ptr<TimeSimulator::TimeSimulator> m_timeSimulator;
    TimeSimulator::MachineVtrPtr m_timeMachines;
};
