#pragma once

#include <QWidget>
#include <QPushButton>
#include "dbconnection.h"
#include "refreshable.h"

namespace Ui {
class CommandsOnWhichIAmWorkingOn;
}

class CommandsOnWhichIAmWorkingOn : public QWidget, public Refreshable
{
    Q_OBJECT

public:
    CommandsOnWhichIAmWorkingOn(QWidget *parent, DBConnectionPtr db);
    ~CommandsOnWhichIAmWorkingOn();
    virtual void refresh();

private slots:
    void on_pushButton_clicked();
    void open();

private:
    void fillTable();
    void clearButtons();
    void insertCommandNumber(CommandPtr command, unsigned i, unsigned j);
    void insertPriority(CommandPtr command, unsigned i, unsigned j);
    void insertOpenButton(unsigned i, unsigned j);

    Ui::CommandsOnWhichIAmWorkingOn *ui;
    DBConnectionPtr m_db;
    CommandPtrVtr m_commands;

    std::vector<QPushButton *> m_openButtons;
};
