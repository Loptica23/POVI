#pragma once

#include <QWidget>
#include <QLineEdit>
#include <QDebug>
#include <memory>

class MainWindow;
class DatabaseConnection;

namespace Ui {
class LoginTab;
}

class LoginTab : public QWidget
{
    Q_OBJECT

public:
    LoginTab(QWidget *parent, std::shared_ptr<DatabaseConnection> db, MainWindow* mainWindow);
    ~LoginTab();

private slots:
    void on_login_clicked();

private:
    Ui::LoginTab *ui;
    std::shared_ptr<DatabaseConnection> m_db;
    MainWindow *m_mainWindow;
};
