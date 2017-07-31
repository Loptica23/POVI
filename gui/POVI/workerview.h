#pragma once

#include <QWidget>
#include <QPushButton>
#include "dbconnection.h"
#include "refreshable.h"

namespace Ui {
class WorkerView;
}

class WorkerView : public QWidget, public Refreshable
{
    Q_OBJECT

public:
    WorkerView(QWidget *parent, DBConnectionPtr db, EmployeePtr employee);
    ~WorkerView();

    virtual void refresh();
protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void on_back_clicked();
    void on_refresh_clicked();
    void on_task_clicked();

private:
    void clearTable();
    void insertTaskButton(unsigned id, unsigned column);
    bool isThereCommandWhichWaitingOnTask(unsigned id);

private:
    Ui::WorkerView *ui;
    DBConnectionPtr m_db;
    EmployeePtr m_employee;
    std::vector<QPushButton*> m_taskButtons;
    std::vector<unsigned> m_tasksIDs;
    TaskTypesPtr m_taskTypes;
    CommandPtrVtr m_commands;

protected:
    static std::vector<unsigned> TaskTypeIDs;
};
