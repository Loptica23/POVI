#pragma once

#include "commanddialog.h"

class CommandDialogKomercialist : public CommandDialog
{
public:
    CommandDialogKomercialist(QWidget *parent, std::shared_ptr<DBConnection> db, OrderPtr order, Refreshable* refreshable);
    CommandDialogKomercialist(QWidget *parent, std::shared_ptr<DBConnection> db, CommandPtr command, bool edit, Refreshable* refreshable);

    virtual ~CommandDialogKomercialist();

    virtual void setUpWindowByWorkPosition();
    void fillTaskTable();

protected:
    enum class TaskTemplate{Manual, Lastis, Tkanje, Stampa};
    static const std::vector<int> LastisTemplate;
    static const std::vector<int> TkanjeTemplate;
    static const std::vector<int> StampaTemplate;

    virtual void taskTemplateChanged(int i);

    virtual void addNewTask(int index);
    virtual void up();
    virtual void down();
    virtual void deleteTask();

    virtual void updateCommand();

    void setTaskTemplateVector();
    void initializeTasksWithTaskIDs(std::vector<int> vector);
    void clearButtons();
    void insertComboBox(TaskPtr task, unsigned i, unsigned j);
    void insertUpButton(unsigned i, unsigned j);
    void insertDownButton(unsigned i, unsigned j);
    void disableFirstAndLastButtons();
    void insertDeleteButton(unsigned i, unsigned j);
    void insertNewTaskButton(unsigned i);
    void fillComboBoxWithTaskTypes(QComboBox * box);


    TaskTypesPtr m_taskTypes;
    TaskTemplate m_template;
};
