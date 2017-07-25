#pragma once
#include <QWidget>
#include "dbconnection.h"
#include "qpushbutton.h"
#include "refreshable.h"

namespace Ui {
class ShiftManagerView;
}

class ShiftManagerView : public QWidget, public Refreshable
{
    Q_OBJECT

public:
    ShiftManagerView(QWidget *parent, DBConnectionPtr db);
    ~ShiftManagerView();

    virtual void refresh();

private slots:
    void on_pushButton_clicked();
    void buttonClicked();

private:
    Ui::ShiftManagerView *ui;
    DBConnectionPtr m_db;
    EmployeePtrVtr m_employees;
    std::vector<QPushButton*> m_buttons;
    EmployeePtr m_shiftMenager;
};
