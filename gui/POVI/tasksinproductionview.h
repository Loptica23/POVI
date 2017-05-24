#pragma once
#include <QWidget>
#include <dbconnection.h>

namespace Ui {
class TasksInProductionView;
}

class TasksInProductionView : public QWidget
{
    Q_OBJECT

public:
    TasksInProductionView(QWidget *parent, DBConnectionPtr db);
    ~TasksInProductionView();

private:
    Ui::TasksInProductionView *ui;
    DBConnectionPtr m_db;
};
