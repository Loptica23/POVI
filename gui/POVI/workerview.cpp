#include "workerview.h"
#include "ui_workerview.h"
#include "mainwindow.h"
#include "commandsviewwaitingontask.h"
#include "mainwindow.h"
#include "utils/utils.h"

#define TASK_BUTTON_FONT_SIZE 25

std::vector<unsigned> WorkerView::TaskTypeIDs = {2, 3, 4, 5, 6, 10, 12, 13, 14, 15, 16, 17, 19, 20, 21, 22, 23, 24};

WorkerView::WorkerView(QWidget *parent, DBConnectionPtr db, EmployeePtr employee) :
    QWidget(parent),
    ui(new Ui::WorkerView),
    m_db(db),
    m_employee(employee)
{
    ui->setupUi(this);
    m_taskTypes = m_db->getTaskTypes();
    MainWindow::setWorker(employee);
    refresh();
}

WorkerView::~WorkerView()
{
    delete ui;
}

void WorkerView::refresh()
{
    clearTable();
    auto i = 0;
    m_commands = m_db->getCommandWhichWaitingOnTasks(TaskTypeIDs);
    for(auto id : TaskTypeIDs)
    {
        if (isThereCommandWhichWaitingOnTask(id))
        {
            ui->tableWidget->insertRow(i);
            insertTaskButton(id, i);
            ++i;
        }
    }

    ui->tableWidget->resizeRowsToContents();
}

void WorkerView::clearTable()
{
    m_taskButtons.clear();
    m_tasksIDs.clear();
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
    m_tasksIDs.push_back(id);
    connect(taskButton, SIGNAL(clicked()), this, SLOT(on_task_clicked()));
}

bool WorkerView::isThereCommandWhichWaitingOnTask(unsigned id)
{
    for (const auto & command : *m_commands)
    {
        if (m_db->getCurrentTask(command)->getTaskTypeId() == id)
        {
            return true;
        }
    }
    return false;
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

void WorkerView::on_refresh_clicked()
{
    refresh();
}

void WorkerView::on_task_clicked()
{
    //refaktor -- za sada neka ostane ovako.. ali nije dobro, dva puta je pozvano find, pa bi bilo dobro da se kod ne ponavlja
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
    if(std::find(m_taskButtons.begin(), m_taskButtons.end(), buttonSender) != m_taskButtons.end())
    {
        auto index = std::find(m_taskButtons.begin(), m_taskButtons.end(), buttonSender) - m_taskButtons.begin();
        qDebug() << index;
        auto mainWindow = MainWindow::getMainWindow();
        std::shared_ptr<QWidget> workerView(new CommandsViewWaitingOnTask(this, m_db, m_tasksIDs.at(index)));
        mainWindow->forward(workerView);
    }
}
