#include "commandsonwhichiamworkingon.h"
#include "ui_commandsonwhichiamworkingon.h"
#include "mainwindow.h"
#include "commanddialogworker.h"

CommandsOnWhichIAmWorkingOn::CommandsOnWhichIAmWorkingOn(QWidget *parent, DBConnectionPtr db) :
    QWidget(parent),
    ui(new Ui::CommandsOnWhichIAmWorkingOn),
    m_db(db)
{
    ui->setupUi(this);
    refresh();
}

CommandsOnWhichIAmWorkingOn::~CommandsOnWhichIAmWorkingOn()
{
    delete ui;
}

void CommandsOnWhichIAmWorkingOn::refresh()
{
    m_commands = m_db->getCommandsOnWhichEmployeeeWorkingOn(MainWindow::getLogedUser());
    fillTable();
}

void CommandsOnWhichIAmWorkingOn::on_pushButton_clicked()
{
    refresh();
}

void CommandsOnWhichIAmWorkingOn::open()
{
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
    if(std::find(m_openButtons.begin(), m_openButtons.end(), buttonSender) != m_openButtons.end())
    {
        auto index = std::find(m_openButtons.begin(), m_openButtons.end(), buttonSender) - m_openButtons.begin();
        qDebug() << index;
        auto commanddialog = new CommandDialogWorker(this, m_db, m_commands->at(index), true, this);
        commanddialog->show();
    }
}

void CommandsOnWhichIAmWorkingOn::fillTable()
{
    qDebug() << "***user refreshing commands view***";
    clearButtons();

    if (!m_commands || m_commands->empty())
    {
        return;
    }

    qDebug() << "broj naloga " + QString::number(m_commands->size());

    auto i = 0;
    for (auto iter = m_commands->begin(); iter != m_commands->end(); ++i, ++iter)
    {
        auto j = 0;
        ui->tableWidget->insertRow(i);
        CommandPtr command = *iter;
        insertCommandNumber(command, i, j++);
        insertPriority(command, i, j++);
        insertOpenButton(i, j++);

    }
    ui->tableWidget->resizeColumnsToContents();
}

void CommandsOnWhichIAmWorkingOn::clearButtons()
{
    ui->tableWidget->setRowCount(0);
    m_openButtons.clear();
}

void CommandsOnWhichIAmWorkingOn::insertCommandNumber(CommandPtr command, unsigned i, unsigned j)
{
    auto *item = new QTableWidgetItem(QString::number(command->getCommandNumber()));
    ui->tableWidget->setItem(i, j, item);
}

void CommandsOnWhichIAmWorkingOn::insertPriority(CommandPtr command, unsigned i, unsigned j)
{
    auto *item = new QTableWidgetItem(QString::number(command->getPriority()));
    ui->tableWidget->setItem(i, j, item);
}

void CommandsOnWhichIAmWorkingOn::insertOpenButton(unsigned i, unsigned j)
{
    QPushButton* btn_open = new QPushButton();
    btn_open->setText("Otvori");
    ui->tableWidget->setIndexWidget(ui->tableWidget->model()->index(i, j), btn_open);
    m_openButtons.push_back(btn_open);
    connect(btn_open, SIGNAL(clicked()), this, SLOT(open()));
}
