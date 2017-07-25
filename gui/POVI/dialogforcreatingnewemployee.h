#pragma once

#include <QDialog>
#include <memory>
#include "dbconnection.h"
#include "refresher.h"

namespace Ui {
class DialogForCreatingNewEmployee;
}

class DBConnection;

class DialogForCreatingNewEmployee : public QDialog, public Refresher
{
    Q_OBJECT

public:
    DialogForCreatingNewEmployee(QWidget *parent, std::shared_ptr<DBConnection> db, Refreshable* refreshable);
    DialogForCreatingNewEmployee(QWidget *parent, std::shared_ptr<DBConnection> db, EmployeePtr employee, Refreshable* refreshable);
    ~DialogForCreatingNewEmployee();

private slots:
    void on_buttonBox_accepted();

private:
    void createUser();
    void updateUser();
    void initializeWorkPosition();

    Ui::DialogForCreatingNewEmployee *ui;
    std::shared_ptr<DBConnection> m_db;
    EmployeePtr m_employee;
    bool m_create;
};
