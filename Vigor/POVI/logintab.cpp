#include "logintab.h"
#include "ui_logintab.h"
#include "mainwindow.h"
#include "dbconnection.h"

LoginTab::LoginTab(MainWindow* mainWindow, std::shared_ptr<DBConnection> db) :
    QWidget(mainWindow),
    ui(new Ui::LoginTab),
    m_dbConnection(db),
    m_mainWindow(mainWindow)
{
    ui->setupUi(this);
    ui->username->setFocus();
}

LoginTab::~LoginTab()
{
    delete ui;
}

void LoginTab::on_login_clicked()
{
    auto username = ui->username->text();
    auto pwd = ui->pwd->text();
    if (m_dbConnection->logIn(username, pwd))
    {
        m_mainWindow->changeState(State::Administrator);
    }
    else
    {
        qDebug() << "pogresan username ili lozinka!";
    }
}
