#pragma once

#include <QPushButton>
#include <QWidget>
#include "dbconnection.h"
#include "machine.h"
#include "tasktypes.h"
#include "refreshable.h"

namespace Ui {
class MachinesView;
}

class MachinesView : public QWidget, public Refreshable
{
    Q_OBJECT

public:
    MachinesView(QWidget *parent, DBConnectionPtr db);
    ~MachinesView();

    virtual void refresh();
private slots:
    void on_NewMachine_clicked();
    void on_refresh_clicked();
    void details();
    void edit();

private:
    void fillMachinesTable();
    void clearBuutonsAndInitializeHeaders();
    void insertName(MachinePtr machine, unsigned i, unsigned j);
    void insertType(MachinePtr machine, unsigned i, unsigned j);
    void insertDetailsButton(unsigned i, unsigned j);
    void insertEditButton(unsigned i, unsigned j);

    Ui::MachinesView *ui;
    DBConnectionPtr m_db;
    MachinePtrVtr m_machines;
    TaskTypesPtr m_tasktypes;

    std::vector<QPushButton*> m_detailsButtons;
    std::vector<QPushButton*> m_editButtons;
};
