#include <QDebug>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "logintab.h"
#include "waiting.h"
#include "dbconnection.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_state(State::Izlogovan),
    ui(new Ui::MainWindow),
    m_LoginTab(new LoginTab(this, m_dbConnection, this)),
    m_WaitingTab(new Waiting(this))
{
    ui->setupUi(this);
    ui->ViewLayout->addWidget(m_LoginTab);
    ui->ViewLayout->addWidget(m_WaitingTab);
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
        break;
    case State::Cekanje:
        m_LoginTab->setHidden(true);
        break;
    case State::Dizajner:
        m_LoginTab->setHidden(true);
        break;
    case State::Komercijala:
        m_LoginTab->setHidden(true);
        break;
    default:
        break;
    }

}
