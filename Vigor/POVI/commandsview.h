#pragma once
#include <QWidget>
#include <QPushButton>
#include "order.h"
#include "command.h"
#include "dbconnection.h"

namespace Ui {
class CommandsView;
}

class CommandsView : public QWidget
{
    Q_OBJECT

public:
    CommandsView(QWidget *parent, std::shared_ptr<DBConnection> db, OrderPtr order);
    ~CommandsView();

private slots:
    void edit();
    void details();
    void createCommand();
    void on_NewCommand_clicked();
    void on_Refresh_clicked();
    void on_Back_clicked();
    void sendToProduction();

private:
    Ui::CommandsView *ui;
    std::shared_ptr<DBConnection> m_db;
    OrderPtr m_order;
    CommandPtrVtr m_commands;

    std::vector<QPushButton*> m_editButtons;
    std::vector<QPushButton*> m_detailsButtons;
    std::vector<QPushButton*> m_finishButtons;
};
