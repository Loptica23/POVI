#pragma once

#include <QWidget>
#include <QPushButton>
#include "dbconnection.h"

namespace Ui {
class WorkerView;
}

class WorkerView : public QWidget
{
    Q_OBJECT

public:
    WorkerView(QWidget *parent, DBConnectionPtr db, EmployeePtr employee);
    ~WorkerView();

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void on_back_clicked();
    void on_pushButton_clicked();
    void on_refresh_clicked();

private:
    void refresh();
    void clearTabel();
    void insertTaskButton(unsigned id, unsigned column);

private:
    Ui::WorkerView *ui;
    DBConnectionPtr m_db;
    EmployeePtr m_employee;
    std::vector<QPushButton*> m_taskButtons;
    TaskTypesPtr m_taskTypes;

protected:
    static std::vector<unsigned> TaskTypeIDs;
};
