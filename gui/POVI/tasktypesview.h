#pragma once
#include <QWidget>
#include <QPushButton>
#include "refreshable.h"
#include "dbconnection.h"

namespace Ui {
class TaskTypesView;
}

class TaskTypesView : public QWidget, public Refreshable
{
    Q_OBJECT

public:
    TaskTypesView(QWidget *parent, DBConnectionPtr db);
    ~TaskTypesView();

    virtual void refresh();

private slots:
    void details();
    void edit();
    void deleteMachine();

    void on_pushButton_2_clicked();

    void on_newTaskType_clicked();

private:
    void fillTaskTypesTable();
    void clearBuutonsAndInitializeHeaders();
    void insertName(TaskTypePtr taskType, unsigned i, unsigned j);
    void insertDetailsButton(unsigned i, unsigned j);
    void insertEditButton(unsigned i, unsigned j);
    void insertDeleteButton(unsigned i, unsigned j);

    Ui::TaskTypesView *ui;
    DBConnectionPtr m_db;
    TaskTypesPtr m_tasktypes;

    std::vector<QPushButton*> m_detailsButtons;
    std::vector<QPushButton*> m_editButtons;
    std::vector<QPushButton*> m_deleteButtons;
};

