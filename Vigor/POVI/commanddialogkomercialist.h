#pragma once

#include "commanddialogkomercialist.h"
#include "commanddialog.h"

class CommandDialogKomercialist : public CommandDialog
{
public:
    CommandDialogKomercialist(QWidget *parent, std::shared_ptr<DBConnection> db, OrderPtr order);
    CommandDialogKomercialist(QWidget *parent, std::shared_ptr<DBConnection> db, CommandPtr command, bool edit);

    virtual ~CommandDialogKomercialist();

    virtual void setUpWindowByWorkPosition();
    void fillTaskTable();

protected:
    virtual void addNewTask(int index);
    virtual void up();
    virtual void down();
    virtual void deleteTask();

    virtual void updateCommand();

    void clearButtons();
    void insertComboBox(TaskPtr task, unsigned i, unsigned j);
    void insertUpButton(unsigned i, unsigned j);
    void insertDownButton(unsigned i, unsigned j);
    void disableFirstAndLastButtons();
    void insertDeleteButton(unsigned i, unsigned j);
    void insertNewTaskButton(unsigned i);
    void fillComboBoxWithTaskTypes(QComboBox * box);


    TaskPairsPtr m_taskTypes;
};