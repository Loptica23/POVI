#pragma once

#include <QDialog>
#include <memory>

namespace Ui {
class DialogForCreatingNewEmployee;
}

class DBConnection;

class DialogForCreatingNewEmployee : public QDialog
{
    Q_OBJECT

public:
    DialogForCreatingNewEmployee(QWidget *parent, std::shared_ptr<DBConnection> db);
    ~DialogForCreatingNewEmployee();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::DialogForCreatingNewEmployee *ui;
    std::shared_ptr<DBConnection> m_db;
};
