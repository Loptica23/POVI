#include <QDebug>
#include <memory>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "logintab.h"
#include "waiting.h"
#include "dbconnection.h"
#include "customersview.h"
#include "empoyersview.h"
#include "tabview.h"
#include "commandsviewwaitingontask.h"
#include "changepassworddialog.h"

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
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_dbConnection = DBConnection::create();
    m_LoginTab.reset(new LoginTab(this, m_dbConnection));
    ui->ViewLayout->addWidget(m_LoginTab.get());
    m_LoginTab->setHidden(false);
    mainWindow = this;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setUpGuiByWorkPosition()
{
    unsigned type = 0;
    switch(getLogedUser()->getWorkPosition())
    {
    case Employee::WorkPosition::Komercijalista:
        qDebug() << "Komercijalista";
        setView(new CustomersView(this, m_dbConnection));
        break;
    case Employee::WorkPosition::Administrator:
        qDebug() << "Administrator";
        setView(new EmpoyersView(this, m_dbConnection));
        break;
    case Employee::WorkPosition::Dizajner:
        qDebug() << "Dizajner";
        type = m_dbConnection->getTaskTypes()->getTypeIdByString("Dizajn");
        setView(new CommandsViewWaitingOnTask(this, m_dbConnection, type));
        break;
    case Employee::WorkPosition::Magacioner:
        qDebug() << "Magacioner";
        type = m_dbConnection->getTaskTypes()->getTypeIdByString("Magacin");
        setView(new CommandsViewWaitingOnTask(this, m_dbConnection, type));
        break;
    case Employee::WorkPosition::SefProizvodnje:
        qDebug() << "Sef Proizvodnje";
        setView(new TabView(this, m_dbConnection));
        break;
    default:
        break;
    }
}

void MainWindow::setView(QWidget* view)
{
    m_defaultScreen.reset(view); //ovaj kod se duplira treba da ode u funkciju
    screenStack.push(m_defaultScreen);
    ui->ViewLayout->addWidget(m_defaultScreen.get());
    m_LoginTab->setHidden(true);
    m_defaultScreen->setHidden(false);
    this->showMaximized();
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
    qDebug() << "back";
    screenStack.top()->setHidden(true);
    screenStack.pop();
    screenStack.top()->setHidden(false);
}

void MainWindow::on_actionPromena_lozinke_triggered()
{
    //ovde moras da otvoris novi prozor za promenu passworda!
    auto changePassword = new ChangePasswordDialog(this, m_dbConnection);
    changePassword->show();
}
