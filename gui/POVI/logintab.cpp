#include <QMessageBox>
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

bool LoginTab::connectToDB(QString userName, QString pwd)
{
    if(m_dbConnection->conectToDb(userName, pwd))
    {
        qDebug() << "uspesno konektovanje na bazu podataka!";
        return true;
    }
    else
    {
        qDebug() << "nije uspelo konektovanje na bazu podataka, proveriti port i IP adresu!";
        return false;
    }
}

void LoginTab::on_login_clicked()
{
    auto username = ui->username->text();
    auto pwd = ui->pwd->text();

    if (!connectToDB(username, pwd))
    {
        QString error = m_dbConnection->getLastError();
        qDebug() << error;
        QMessageBox messageBox;
        messageBox.critical(this,"Error",error);
        return;
    }

    auto loggeduser = m_dbConnection->logIn(username, pwd);

    if (loggeduser != nullptr)
    {
        MainWindow::setLogedUser(loggeduser);
        m_mainWindow->setUpGuiByWorkPosition();
        qDebug() << "User loged in!";
    }
    else
    {
        qDebug() << "pogresan username ili lozinka!";
    }
}
