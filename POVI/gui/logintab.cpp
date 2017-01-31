#include "logintab.h"
#include "ui_logintab.h"
#include "mainwindow.h"
#include "databaseconnection.h"

LoginTab::LoginTab(QWidget *parent, std::shared_ptr<DatabaseConnection> db, MainWindow* mainWindow) :
    QWidget(parent),
    ui(new Ui::LoginTab),
    m_db(db),
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
    if (m_db->logIn(username, pwd))
    {
        m_mainWindow->changeState(State::Cekanje);
    }
    else
    {
        qDebug() << "pogresan username ili lozinka!";
    }
}
