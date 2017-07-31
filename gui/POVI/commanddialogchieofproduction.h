#pragma once
#include "commanddialog.h"
#include "tasktypes.h"

class CommandDialogChieOfProduction : public CommandDialog
{
public:
    CommandDialogChieOfProduction(QWidget *parent, DBConnectionPtr db, CommandPtr command, bool edit, Refreshable* refreshable);

    virtual ~CommandDialogChieOfProduction();

protected slots:
    virtual void annul();

protected:
    virtual void setUpWindowByWorkPosition();
    void fillTaskTable();
    virtual void updateCommand();
    virtual void acceptButtonClicked();

    bool showAnnul();

    void clearButtonsAndSetHeaders();
    void insertTaskType(TaskPtr task, unsigned i, unsigned j);
    void insertTaskState(TaskPtr task, unsigned i, unsigned j);
    void insertTaskPrediction(TaskPtr task, unsigned i, unsigned j);
    void insertMachineComboBox(TaskPtr task, unsigned i, unsigned j);
    void insertWorker(TaskPtr task, unsigned i , unsigned j);
    void insertStartTime(TaskPtr task, unsigned i , unsigned j);
    void insertEndTime(TaskPtr task, unsigned i , unsigned j);
    void insertTaskQuantity(TaskPtr task, unsigned i , unsigned j);
    void insertAnnulButton(TaskPtr task, unsigned i , unsigned j);

    TaskTypesPtr m_taskTypes;
    MachinePtrVtr m_machines;

    std::vector<QComboBox*> m_comboBoxes;
    std::vector<QPushButton*> m_annulButtons;

    bool m_annul;
};
