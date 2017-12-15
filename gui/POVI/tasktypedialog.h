#pragma once

#include <QDialog>
#include "dbconnection.h"
#include "refresher.h"

namespace Ui {
class TaskTypeDialog;
}

class TaskTypeDialog : public QDialog, public Refresher
{
    Q_OBJECT

public:
    //for creating
    TaskTypeDialog(QWidget *parent, DBConnectionPtr db, Refreshable * refreshable);
    //for editing and overview
    TaskTypeDialog(QWidget *parent, DBConnectionPtr db, TaskTypePtr taskType, bool edit, Refreshable * refreshable);
    ~TaskTypeDialog();

private slots:
    void on_buttonBox_accepted();

private:
    void initializeListView();
    void ifFalseShowDbError(bool b);
    void createTaskTYpoe();
    void updateTaskType();

    Ui::TaskTypeDialog *ui;
    DBConnectionPtr m_db;
    TaskTypePtr m_taskType;
    bool m_create;
    bool m_edit;
};

