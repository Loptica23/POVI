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
    virtual void acceptButtonClicked();

    void clearButtonsAndSetHeaders();
    void insertTaskType(TaskPtr task, unsigned i, unsigned j);
    void insertTaskState(TaskPtr task, unsigned i, unsigned j);
    void insertTaskPrediction(TaskPtr task, unsigned i, unsigned j);
    void insertMachineComboBox(TaskPtr task, unsigned i, unsigned j);
    void insertWorker(TaskPtr task, unsigned i , unsigned j);
    void insertStartTime(TaskPtr task, unsigned i , unsigned j);
    void insertEndTime(TaskPtr task, unsigned i , unsigned j);

    TaskTypesPtr m_taskTypes;
    MachinePtrVtr m_machines;

    std::vector<QComboBox*> m_comboBoxes;
};
