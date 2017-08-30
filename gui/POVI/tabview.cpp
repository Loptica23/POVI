#include "tabview.h"
#include "ui_tabview.h"
#include "mainwindow.h"
#include "machinesview.h"
#include "commandsviewisinstate.h"
#include "commandsviewwaitingontask.h"
#include "dbconnection.h"
#include "commandsonwhichiamworkingon.h"

TabView::TabView(MainWindow *mainWindow, DBConnectionPtr db) :
    QWidget(mainWindow),
    ui(new Ui::TabView),
    m_db(db)
{
    ui->setupUi(this);
    ui->tabWidget->clear();
    setUpTabViewByWorkPosition();
}

TabView::~TabView()
{
    delete ui;
}

void TabView::setUpTabViewByWorkPosition()
{
    MachinesView* machinesview;
    CommandsViewIsInState * commandsviewInProgress;
    CommandsViewIsInState * commandsviewWaitingOnProduction;

    CommandsViewWaitingOnTask * commandsViewWaitingOnTask;
    CommandsOnWhichIAmWorkingOn* commandsOnWhichIAmWorkingOn;
    auto type = m_db->getTaskTypes()->getTypeIdByString("Narucivanje materijalia");
    switch (MainWindow::getLogedUser()->getWorkPosition()) {
    case Employee::WorkPosition::SefProizvodnje:

        commandsviewInProgress = new CommandsViewIsInState(this, m_db, Command::State::InProgress);
        ui->tabWidget->addTab(commandsviewInProgress, "Nalozi u izradi:");

        commandsviewWaitingOnProduction = new CommandsViewIsInState(this, m_db, Command::State::WaitForProduction);
        ui->tabWidget->addTab(commandsviewWaitingOnProduction, "Nalozi koji cekaju na potvrdu:");

        commandsviewWaitingOnProduction = new CommandsViewIsInState(this, m_db, Command::State::Complited);
        ui->tabWidget->addTab(commandsviewWaitingOnProduction, "Zavrseni nalozi:");

        commandsviewWaitingOnProduction = new CommandsViewIsInState(this, m_db, Command::State::Stopped);
        ui->tabWidget->addTab(commandsviewWaitingOnProduction, "Stopirani nalozi:");

        machinesview = new MachinesView(this, m_db);
        ui->tabWidget->addTab(machinesview, "Masine:");

        break;
    case Employee::WorkPosition::Narucilac:

        commandsViewWaitingOnTask = new CommandsViewWaitingOnTask(this, m_db, type, false);
        ui->tabWidget->addTab(commandsViewWaitingOnTask, "Nalozi za koje treba naruciti");

        commandsOnWhichIAmWorkingOn = new CommandsOnWhichIAmWorkingOn(this, m_db);
        ui->tabWidget->addTab(commandsOnWhichIAmWorkingOn, "Nalozi na kojima radim");
    default:
        break;
    }
}
