#pragma once

#include <QWidget>
#include<memory>
#include "dbconnection.h"

class DBConnection;
class QPushButton;

namespace Ui {
class EmpoyersView;
}

class EmpoyersView : public QWidget
{
    Q_OBJECT

public:
    EmpoyersView(QWidget *parent, std::shared_ptr<DBConnection> db);
    ~EmpoyersView();

private slots:
    void on_Refresh_clicked();
    void on_CreateEmployee_clicked();
    void edit();

protected:
     void paintEvent(QPaintEvent *event);

private:
    Ui::EmpoyersView *ui;
    std::shared_ptr<DBConnection> m_db;
    std::vector<QPushButton*> m_buttons;
    EmployeePtrVtr m_employees;
};
