#include <QDebug>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "logintab.h"
#include "waiting.h"
#include "dbconnection.h"
#include "adminview.h"

MainWindow* MainWindow::mainWindow;
EmployeePtr MainWindow::loggedUser;

MainWindow* MainWindow::getMainWindow()
{
    return mainWindow;
}

EmployeePtr MainWindow::getLogedUser()
{
    return loggedUser;
}

void MainWindow::setLogedUser(EmployeePtr employee)
{
    loggedUser = employee;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_state(State::Izlogovan),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_dbConnection = DBConnection::create();
    m_LoginTab.reset(new LoginTab(this, m_dbConnection));
    ui->ViewLayout->addWidget(m_LoginTab.get());
    changeState(State::Izlogovan);
    connecttodb();
    mainWindow = this;
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
    case State::Administrator:
        m_defaultScreen.reset(new AdminView(this, m_dbConnection));
        screenStack.push(m_defaultScreen);
        ui->ViewLayout->addWidget(m_defaultScreen.get());
        m_LoginTab->setHidden(true);
        m_defaultScreen->setHidden(false);
        this->showMaximized();
        break;
    default:
        break;
    }
    m_state = state;
}

void MainWindow::forward(std::shared_ptr<QWidget> widget)
{
    qDebug() << "forward";
    ui->ViewLayout->addWidget(widget.get());
    screenStack.top()->setHidden(true);
    widget->setHidden(false);
    screenStack.push(widget);
}

void MainWindow::back()
{
    //proveris da li se doslo do main windowa i ako se pokusava skidanje njega onda ispisi gresku
    qDebug() << "back";
    screenStack.top()->setHidden(true);
    screenStack.pop();
    screenStack.top()->setHidden(false);
}
