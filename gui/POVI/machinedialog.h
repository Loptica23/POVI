#pragma once

#include <QDialog>
#include "dbconnection.h"

namespace Ui {
class MachineDialog;
}

class MachineDialog : public QDialog
{
    Q_OBJECT

public:
    //za kreiranje
    MachineDialog(QWidget *parent, DBConnectionPtr db);
    //za izmenu i pregled
    MachineDialog(QWidget *parent, DBConnectionPtr db, MachinePtr machine, bool edit);
    ~MachineDialog();

private slots:
    void on_buttonBox_accepted();

private:
    void initializeComboBox();
    void updateMachine();
    void createMachine();

    Ui::MachineDialog *ui;
    DBConnectionPtr m_db;
    MachinePtr m_machine;
    bool m_edit;
    bool m_create;
};
