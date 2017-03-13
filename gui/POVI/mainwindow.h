#pragma once

#include <QMainWindow>
#include <memory>
#include <stack>
#include "dbconnection.h"

namespace Ui {
class MainWindow;
}
class DBConnection;
class LoginTab;
class Waiting;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void forward(std::shared_ptr<QWidget> widget);
    void back();

    void setUpGuiByWorkPosition();
    void setView(QWidget *view);

    static MainWindow* getMainWindow();

    static EmployeePtr getLogedUser();
    static void setLogedUser(EmployeePtr employee);
private slots:
    void on_actionPromena_lozinke_triggered();

private:
    Ui::MainWindow *ui;
    std::shared_ptr<DBConnection> m_dbConnection;
    std::shared_ptr<LoginTab>   m_LoginTab;
    std::shared_ptr<QWidget>    m_defaultScreen;

    std::stack<std::shared_ptr<QWidget>> screenStack;

    static MainWindow* mainWindow;
    static EmployeePtr loggedUser;
};
