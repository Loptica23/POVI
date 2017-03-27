#include "shiftmanagerview.h"
#include "ui_shiftmanagerview.h"
#include "dbconnection.h"

ShiftManagerView::ShiftManagerView(QWidget *parent, DBConnectionPtr db) :
    QWidget(parent),
    ui(new Ui::ShiftManagerView),
    m_db(db)
{
    ui->setupUi(this);
}

ShiftManagerView::~ShiftManagerView()
{
    delete ui;
}
