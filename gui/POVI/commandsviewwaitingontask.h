#pragma once
#include <QWidget>
#include <QPushButton>
#include "dbconnection.h"

namespace Ui {
class CommandsViewWaitingOnTask;
}

class CommandsViewWaitingOnTask : public QWidget
{
    Q_OBJECT

public:
    CommandsViewWaitingOnTask(QWidget *parent, DBConnectionPtr db, unsigned taskTypeID);
    CommandsViewWaitingOnTask(QWidget *parent, DBConnectionPtr db, std::vector<unsigned> taskTypeIDs);

    ~CommandsViewWaitingOnTask();

private slots:
    void on_Refresh_clicked();
    void details();
    void takeCommand();

    void on_Back_clicked();

private:
    void fillTable();
    void clearButtons();
    void insertCommandNumber(CommandPtr command, unsigned i, unsigned j);
    void insertDetailsButton(unsigned i, unsigned j);
    void inserTakeCommandButton(unsigned i, unsigned j);

    void openDialogIfThereIsTaskOnWhichUserWorkingOn();
    void OpenCommandDialogByWorkPosition(CommandPtr command, bool edit);


    Ui::CommandsViewWaitingOnTask *ui;
    DBConnectionPtr m_db;
    std::vector<unsigned> m_taskTypeIDs;
    CommandPtrVtr m_commands;

    std::vector<QPushButton *> m_detailsButtons;
    std::vector<QPushButton *> m_takeCommandButtons;
};
