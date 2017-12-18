#pragma once
#include <QWidget>
#include <QPushButton>
#include "command.h"
#include "dbconnection.h"
#include "refreshable.h"

namespace Ui {
class WhereCommandsWaiting;
}

class WhereCommandsWaiting : public QWidget, public Refreshable
{
    Q_OBJECT

public:
    WhereCommandsWaiting(QWidget *parent, std::shared_ptr<DBConnection> db);
    ~WhereCommandsWaiting();

    virtual void refresh();
private slots:
    void details();
    void on_pushButton_clicked();

private:
    void clearBuutonsAndInitializeHeaders();
    void fillTable();

    void insertCommandNumber(CommandPtr command, unsigned i, unsigned j);
    void insertPriority(CommandPtr command, unsigned i, unsigned j);
    void insertDetials(unsigned i, unsigned j);
    void insertDeadline(CommandPtr command, unsigned i, unsigned j);
    void insertPrediction(CommandPtr command, unsigned i, unsigned j);
    void insertKomercialist(CommandPtr command, unsigned i, unsigned j);
    void insertCreation(CommandPtr command, unsigned i , unsigned j);
    void insertStatus(CommandPtr command, unsigned i , unsigned j);
    void insertTaskType(CommandPtr command, unsigned i , unsigned j);

    Ui::WhereCommandsWaiting *ui;
    DBConnectionPtr m_db;
    CommandPtrVtr m_commands;
    std::vector<QPushButton*> m_detailsButtons;
};
