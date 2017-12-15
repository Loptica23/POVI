#pragma once

#include <QDialog>
#include <QListWidgetItem>
#include "dbconnection.h"
#include "refresher.h"

namespace Ui {
class MachineDialog;
}

class MachineDialog : public QDialog, public Refresher
{
    Q_OBJECT

public:
    //za kreiranje
    MachineDialog(QWidget *parent, DBConnectionPtr db, Refreshable* refreshable);
    //za izmenu i pregled
    MachineDialog(QWidget *parent, DBConnectionPtr db, MachinePtr machine, bool edit, Refreshable* refreshable);
    ~MachineDialog();

private slots:
    void on_buttonBox_accepted();
    void on_Name_textChanged(const QString &arg1);
    void on_lineEdit_textChanged(const QString &arg1);
    void on_lineEdit_2_textChanged(const QString &arg1);
    void on_lineEdit_3_textChanged(const QString &arg1);
    void on_listWidget_clicked(const QModelIndex &index);
    void on_comboBox_currentIndexChanged(const QString &tasTypeName);
    void on_addTaskType_clicked();
    void on_deleteTaskType_clicked();

private:
    void initializeListView();
    void initializeTaskTypesComboBox();
    void updateMachine();
    void createMachine();
    void enableOrDisableOkButton();
    void enableOrDisableDeleteButton();
    void enableOrDisableAddButton();
    void ifFalseShowDbError(bool b);

    Ui::MachineDialog *ui;
    DBConnectionPtr m_db;
    MachinePtr m_machine;
    bool m_edit;
    bool m_create;
};
