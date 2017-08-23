#pragma once

#include <QWidget>
#include<memory>
#include "dbconnection.h"
#include "refreshable.h"

class DBConnection;
class QPushButton;

namespace Ui {
class EmpoyersView;
}

class EmpoyersView : public QWidget, public Refreshable
{
    Q_OBJECT

public:
    EmpoyersView(QWidget *parent, std::shared_ptr<DBConnection> db);
    ~EmpoyersView();

    virtual void refresh();

    void clearTable();
    void insertFirstName(EmployeePtr employee, unsigned i, unsigned j);
    void insertLastName(EmployeePtr employee, unsigned i, unsigned j);
    void insertUserName(EmployeePtr employee, unsigned i, unsigned j);
    void insertWorkPosition(EmployeePtr employee, unsigned i, unsigned j);
    void insertActivation(EmployeePtr employee, unsigned i, unsigned j);
    void insertEditButton(unsigned i, unsigned j);
    void insertResetPWDButton(unsigned i, unsigned j);

private slots:
    void on_Refresh_clicked();
    void on_CreateEmployee_clicked();
    void edit();
    void resetPWD();

protected:
     void paintEvent(QPaintEvent *event);

private:
    Ui::EmpoyersView *ui;
    std::shared_ptr<DBConnection> m_db;
    std::vector<QPushButton*> m_editButtons;
    std::vector<QPushButton*> m_resetPWDButtons;
    EmployeePtrVtr m_employees;
};
