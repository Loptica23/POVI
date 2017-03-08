#pragma once
#include "commanddialog.h"
#include "tasktypes.h"

class CommandDialogChieOfProduction : public CommandDialog
{
public:
    CommandDialogChieOfProduction(QWidget *parent, DBConnectionPtr db, CommandPtr command, bool edit);

    virtual ~CommandDialogChieOfProduction();

protected:
    virtual void setUpWindowByWorkPosition();
    void fillTaskTable();
    virtual void updateCommand();

    void insertTaskType(TaskPtr task, unsigned i, unsigned j);
    void insertTaskState(TaskPtr task, unsigned i, unsigned j);
    void insertTaskPrediction(TaskPtr task, unsigned i, unsigned j);
    void insertMachineComboBox(TaskPtr task, unsigned i, unsigned j);

    TaskPairsPtr m_taskTypes;
    MachinePtrVtr m_machines;
};
