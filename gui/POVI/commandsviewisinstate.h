#pragma once
#include <QWidget>
#include <QPushButton>
#include "dbconnection.h"

namespace Ui {
class CommandsViewIsInState;
}

class CommandsViewIsInState : public QWidget
{
    Q_OBJECT

public:
    CommandsViewIsInState(QWidget *parent, DBConnectionPtr db);
    virtual ~CommandsViewIsInState();

    void setCommands(CommandPtrVtr commands);

private slots:
    void on_refresh_clicked();
    void details();
    void edit();

private:
    void fillTable();
    void clearBuutonsAndInitializeHeaders();
    void insertCommandNumber(CommandPtr command, unsigned i, unsigned j);
    void insertPriority(CommandPtr command, unsigned i, unsigned j);
    void insertDetailsButton(unsigned i, unsigned j);
    void insertEditButton(unsigned i, unsigned j);

    Ui::CommandsViewIsInState *ui;
    DBConnectionPtr m_db;
    CommandPtrVtr m_commands;
    Command::State m_state;

    std::vector<QPushButton*> m_detailsButtons;
    std::vector<QPushButton*> m_editButtons;
};
