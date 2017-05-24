#include "workerview.h"
#include "ui_workerview.h"
#include "mainwindow.h"

#define TASK_BUTTON_FONT_SIZE 25

std::vector<unsigned> WorkerView::TaskTypeIDs = {1, 2, 3, 4, 5, 6, 10, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21};

WorkerView::WorkerView(QWidget *parent, DBConnectionPtr db, EmployeePtr employee) :
    QWidget(parent),
    ui(new Ui::WorkerView),
    m_db(db),
    m_employee(employee)
{
    ui->setupUi(this);
    m_taskTypes = m_db->getTaskTypes();
}

WorkerView::~WorkerView()
{
    delete ui;
}

void WorkerView::refresh()
{
    clearTabel();
    auto i = 0;
    for(auto iter = TaskTypeIDs.begin(); iter != TaskTypeIDs.end(); ++iter, ++i)
    {
        unsigned id = *iter;
        ui->tableWidget->insertRow(i);
        insertTaskButton(id, i);
    }
    ui->tableWidget->resizeRowsToContents();
}

void WorkerView::clearTabel()
{
    m_taskButtons.clear();
    ui->tableWidget->setRowCount(0);
}

void WorkerView::insertTaskButton(unsigned id, unsigned column)
{
    QPushButton* taskButton = new QPushButton();
    QString taskName = m_taskTypes->getStringById(id);
    taskButton->setText(taskName);
    QFont font;
    font.setPixelSize(TASK_BUTTON_FONT_SIZE);
    font.setBold(true);
    taskButton->setFont(font);
    ui->tableWidget->setIndexWidget(ui->tableWidget->model()->index(column, 0), taskButton);
    m_taskButtons.push_back(taskButton);
    //connect(btn_details, SIGNAL(clicked()), this, SLOT(details()));
}

void WorkerView::paintEvent(QPaintEvent *event)
{
    ui->tableWidget->setColumnWidth(0, ui->tableWidget->width());
}

void WorkerView::on_back_clicked()
{
    auto mainWindow = MainWindow::getMainWindow();
    mainWindow->back();
}

void WorkerView::on_pushButton_clicked()
{
    auto mainWindow = MainWindow::getMainWindow();
    mainWindow->back();
}

void WorkerView::on_refresh_clicked()
{
    refresh();
}
