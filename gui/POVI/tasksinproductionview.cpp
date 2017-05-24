#include "tasksinproductionview.h"
#include "ui_tasksinproductionview.h"

TasksInProductionView::TasksInProductionView(QWidget *parent, DBConnectionPtr db) :
    QWidget(parent),
    ui(new Ui::TasksInProductionView),
    m_db(db)
{
    ui->setupUi(this);
}

TasksInProductionView::~TasksInProductionView()
{
    delete ui;
}
