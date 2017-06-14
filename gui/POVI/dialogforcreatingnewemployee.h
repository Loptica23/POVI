#pragma once

#include <QDialog>
#include <memory>
#include "dbconnection.h"

namespace Ui {
class DialogForCreatingNewEmployee;
}

class DBConnection;

class DialogForCreatingNewEmployee : public QDialog
{
    Q_OBJECT

public:
    DialogForCreatingNewEmployee(QWidget *parent, std::shared_ptr<DBConnection> db);
    DialogForCreatingNewEmployee(QWidget *parent, std::shared_ptr<DBConnection> db, EmployeePtr employee);
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
