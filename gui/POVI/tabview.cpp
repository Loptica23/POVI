#include "tabview.h"
#include "ui_tabview.h"
#include "mainwindow.h"
#include "machinesview.h"

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
    switch (MainWindow::getLogedUser()->getWorkPosition()) {
    case Employee::WorkPosition::SefProizvodnje:
        machinesview = new MachinesView(this, m_db);
        ui->tabWidget->addTab(machinesview, "Masine");
        break;
    default:
        break;
    }
}
