#include "tabview.h"
#include "ui_tabview.h"
#include "mainwindow.h"
#include "machinesview.h"
#include "commandsviewisinstate.h"

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
    switch (MainWindow::getLogedUser()->getWorkPosition()) {
    case Employee::WorkPosition::SefProizvodnje:

        commandsviewInProgress = new CommandsViewIsInState(this, m_db, Command::State::InProgress);
        ui->tabWidget->addTab(commandsviewInProgress, "Nalozi u izradi:");

        commandsviewWaitingOnProduction = new CommandsViewIsInState(this, m_db, Command::State::WaitForProduction);
        ui->tabWidget->addTab(commandsviewWaitingOnProduction, "Nalozi koji cekaju na potvrdu:");

        machinesview = new MachinesView(this, m_db);
        ui->tabWidget->addTab(machinesview, "Masine:");

        break;
    default:
        break;
    }
}
