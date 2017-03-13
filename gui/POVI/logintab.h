#pragma once

#include <QWidget>
#include <QLineEdit>
#include <QDebug>
#include <memory>

class MainWindow;
class DBConnection;

namespace Ui {
class LoginTab;
}

class LoginTab : public QWidget
{
    Q_OBJECT

public:
    LoginTab(MainWindow *mainWindow, std::shared_ptr<DBConnection> db);
    ~LoginTab();

private slots:
    void on_login_clicked();

private:
    bool connectToDB(QString userName, QString pwd);

    Ui::LoginTab *ui;
    std::shared_ptr<DBConnection> m_dbConnection;
    MainWindow *m_mainWindow;
};
