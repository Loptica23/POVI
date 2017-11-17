#pragma once
#include "commanddialog.h"
#include "tasktypes.h"

class CommandDialogChieOfProduction : public CommandDialog
{
public:
    CommandDialogChieOfProduction(QWidget *parent, DBConnectionPtr db, CommandPtr command, bool edit, Refreshable* refreshable);

    virtual ~CommandDialogChieOfProduction();

protected slots:
    virtual void returnToWorker() override;
    virtual void annulTask() override;
    virtual void taskMachineChanged();

protected:
    virtual void setUpWindowByWorkPosition();
    void fillTaskTable();
    virtual void updateCommand();
    virtual void acceptButtonClicked();

    bool showAnnulButtons();

    void clearButtonsAndSetHeaders();
    void insertTaskType(TaskPtr task, unsigned i, unsigned j);
    void insertTaskState(TaskPtr task, unsigned i, unsigned j);
    void insertTaskPrediction(TaskPtr task, unsigned i, unsigned j);
    void insertMachineComboBox(TaskPtr task, unsigned i, unsigned j);
    void insertWorker(TaskPtr task, unsigned i , unsigned j);
    void insertStartTime(TaskPtr task, unsigned i , unsigned j);
    void insertEndTime(TaskPtr task, unsigned i , unsigned j);
    void insertTaskQuantity(TaskPtr task, unsigned i , unsigned j);
    void insertReturnToWorkerButton(TaskPtr task, unsigned i , unsigned j);
    void insertAnnulButton(TaskPtr task, unsigned i , unsigned j);

    MachinePtrVtr m_machines;

    std::vector<QComboBox*> m_comboBoxes;
    std::vector<QPushButton*> m_returnToWorkerButtons;
    std::vector<QPushButton*> m_annulButtons;

    bool m_canBeAnnul;
    bool m_isThereTaskWithoutMachie;
};
