#include "adminview.h"
#include "ui_adminview.h"
#include "mainwindow.h"
#include "empoyersview.h"
#include "customersview.h"

AdminView::AdminView(MainWindow *mainWindow, std::shared_ptr<DBConnection> db) :
    QWidget(mainWindow),
    ui(new Ui::AdminView),
    m_db(db)
{
    ui->setupUi(this);
    m_mainWindow =  mainWindow; 
    auto employersview = new EmpoyersView(mainWindow, db);
    auto customers = new CustomersView(mainWindow, db);
    ui->tabWidget->clear();
    ui->tabWidget->addTab(employersview, "Zaposleni");
    ui->tabWidget->addTab(customers, "Klijenti");
}

AdminView::~AdminView()
{
    delete ui;
}
