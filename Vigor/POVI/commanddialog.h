#pragma once
#include <QDialog>
#include "order.h"
#include "command.h"
#include "dbconnection.h"
#include "task.h"

namespace Ui {
class CommandDialog;
}

class CommandDialog : public QDialog
{
    Q_OBJECT

public:
    CommandDialog(QWidget *parent, std::shared_ptr<DBConnection> db, OrderPtr order);
    CommandDialog(QWidget *parent, std::shared_ptr<DBConnection> db, CommandPtr command, bool edit);
    ~CommandDialog();

    void setUpWindowByWorkPosition();

private slots:
    void on_buttonBox_accepted();
    void addNewTask(int index);
    void changeTaskType(int index);

private:
    void fillTaskTable();
    void initializeTasks();
    void removeWidget(QWidget * widget);
    void createCommand();
    void updateCommand();

    Ui::CommandDialog *ui;

    bool m_edit;
    bool m_create;
    OrderPtr m_order;
    CommandPtr m_command;
    TaskPtrVtr m_tasks;
    std::shared_ptr<DBConnection> m_db;

};
