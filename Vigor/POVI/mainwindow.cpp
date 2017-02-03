#include <QDebug>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "logintab.h"
#include "waiting.h"
#include "dbconnection.h"
#include "adminview.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_state(State::Izlogovan),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_dbConnection = DBConnection::create();
    m_LoginTab.reset(new LoginTab(this, m_dbConnection));
    m_WaitingTab.reset(new Waiting(this));
    m_AdminView.reset(new AdminView(this, m_dbConnection));
    ui->ViewLayout->addWidget(m_LoginTab.get());
    ui->ViewLayout->addWidget(m_WaitingTab.get());
    ui->ViewLayout->addWidget(m_AdminView.get());
    changeState(State::Izlogovan);
    connecttodb();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::connecttodb()
{
    if(m_dbConnection->conectToDb())
    {
        qDebug() << "uspesno konektovanje na bazu podataka!";
    }
    else
    {
        qDebug() << "nije uspelo konektovanje na bazu podataka, proveriti port i IP adresu!";
    }
}

void MainWindow::changeState(State state)
{
    if (m_LoginTab->hasHeightForWidth())
    {
        m_LoginTab->setHidden(true);
    }
    switch(state)
    {
    case State::Izlogovan:
        m_LoginTab->setHidden(false);
        m_AdminView->setHidden(true);
        break;
    case State::Cekanje:
        m_LoginTab->setHidden(true);
        m_AdminView->setHidden(true);
        break;
    case State::Dizajner:
        m_LoginTab->setHidden(true);
        m_AdminView->setHidden(true);
        break;
    case State::Komercijala:
        m_LoginTab->setHidden(true);
        m_AdminView->setHidden(true);
        break;
    case State::Administrator:
        m_LoginTab->setHidden(true);
        m_AdminView->setHidden(false);
        break;
    default:
        break;
    }
    m_state = state;
}
