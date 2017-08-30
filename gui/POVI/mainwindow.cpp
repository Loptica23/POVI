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
#include "shiftmanagerview.h"

MainWindow* MainWindow::mainWindow;
EmployeePtr MainWindow::loggedUser;
EmployeePtr MainWindow::worker;

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
    worker = employee;
}

EmployeePtr MainWindow::getWorker()
{
    return worker;
}

void MainWindow::setWorker(EmployeePtr employee)
{
    worker = employee;
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
    std::vector<unsigned> types;
    ui->menuKorisnik->setEnabled(true);
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
    case Employee::WorkPosition::DizajnerLastis:
        qDebug() << "Dizajner";
        type = m_dbConnection->getTaskTypes()->getTypeIdByString("Dizajn Lastis");
        setView(new CommandsViewWaitingOnTask(this, m_dbConnection, type));
        break;
    case Employee::WorkPosition::DizajnerTkanje:
        qDebug() << "Dizajner";
        type = m_dbConnection->getTaskTypes()->getTypeIdByString("Dizajn Tkanje");
        setView(new CommandsViewWaitingOnTask(this, m_dbConnection, type));
        break;
    case Employee::WorkPosition::DizajnerStampa:
        qDebug() << "Dizajner";
        type = m_dbConnection->getTaskTypes()->getTypeIdByString("Dizajn Stampa");
        setView(new CommandsViewWaitingOnTask(this, m_dbConnection, type));
        break;
    case Employee::WorkPosition::Magacioner:
        qDebug() << "Magacioner";
        type = m_dbConnection->getTaskTypes()->getTypeIdByString("Magacin Zaduzivanje");
        types.push_back(type);
        type = m_dbConnection->getTaskTypes()->getTypeIdByString("Magacin Razduzivanje");
        types.push_back(type);
        setView(new CommandsViewWaitingOnTask(this, m_dbConnection, types));
        break;
    case Employee::WorkPosition::SefProizvodnje:
        qDebug() << "Sef Proizvodnje";
        setView(new TabView(this, m_dbConnection));
        break;
    case Employee::WorkPosition::SefSmene:
        qDebug() << "Sef smene";
        setView(new ShiftManagerView(this, m_dbConnection));
        break;
    case Employee::WorkPosition::KnjigovodjaFakture:
        qDebug() << "Knjigovodja fakture";
        type = m_dbConnection->getTaskTypes()->getTypeIdByString("Faktura");
        setView(new CommandsViewWaitingOnTask(this, m_dbConnection, type));
        break;
    case Employee::WorkPosition::Narucilac:
        qDebug() << "Narucilac";
        setView(new TabView(this, m_dbConnection));
        break;
    default:
        break;
    }
}

void MainWindow::setView(QWidget* view)
{
    m_defaultScreen.reset(view);
    m_screenStack.push(m_defaultScreen);
    ui->ViewLayout->addWidget(m_defaultScreen.get());
    m_LoginTab->setHidden(true);
    m_defaultScreen->setHidden(false);
    this->showMaximized();
}

void MainWindow::forward(std::shared_ptr<QWidget> widget)
{
    qDebug() << "forward";
    ui->ViewLayout->addWidget(widget.get());
    m_screenStack.top()->setHidden(true);
    widget->setHidden(false);
    m_screenStack.push(widget);
}

void MainWindow::back()
{
    qDebug() << "back";
    if (m_screenStack.size()>1)
    {
        m_screenStack.top()->setHidden(true);
        m_screenStack.pop();
        m_screenStack.top()->setHidden(false);
    }
}

void MainWindow::backToDefaultScreen()
{
    qDebug() << "back to default screen";
    m_screenStack.top()->setHidden(true);
    while (m_screenStack.size() > 1)
    {
        m_screenStack.pop();
    }
    m_screenStack.top()->setHidden(false);
}

void MainWindow::on_actionPromena_lozinke_triggered()
{
    auto changePassword = new ChangePasswordDialog(this, m_dbConnection);
    changePassword->show();
}
