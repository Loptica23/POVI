#include <QDebug>
#include "commandsview.h"
#include "ui_commandsview.h"
#include "command.h"
#include "mainwindow.h"
#include "commanddialog.h"

CommandsView::CommandsView(QWidget *parent, std::shared_ptr<DBConnection> db, OrderPtr order) :
    QWidget(parent),
    ui(new Ui::CommandsView),
    m_db(db),
    m_order(order)
{
    ui->setupUi(this);
}

CommandsView::~CommandsView()
{
    delete ui;
}

void CommandsView::on_NewCommand_clicked()
{
    qDebug() << "otvaranje prozora za kreiranje naloga!";
    auto commanddialog = new CommandDialog(this, m_db, m_order);
    commanddialog->show();
}

void CommandsView::on_Refresh_clicked()
{
    m_editButtons.clear();
    m_detailsButtons.clear();
    qDebug() << "user refreshing commands view!";
    ui->tableWidget->setRowCount(0);
    auto commands = m_db->getCommands(m_order);
    if (!commands || commands->empty())
    {
        return;
    }
    m_commands = commands;
    qDebug() << "broj naloga " + QString::number(commands->size());
    auto i = 0;
    for (auto iter = commands->begin(); iter != commands->end(); ++i, ++iter)
    {
        ui->tableWidget->insertRow(i);
        {
            auto *item = new QTableWidgetItem(QString::number((*iter)->getCommandNumber()));
            ui->tableWidget->setItem(i, 0,item);
        }
        {
            QPushButton* btn_details = new QPushButton();
            btn_details->setText("Detalji");
            ui->tableWidget->setIndexWidget(ui->tableWidget->model()->index(i, 1), btn_details);
            m_detailsButtons.push_back(btn_details);
            connect(btn_details, SIGNAL(clicked()), this, SLOT(details()));
        }
    }
    ui->tableWidget->resizeColumnsToContents();
}

void CommandsView::on_Back_clicked()
{
    auto mainWindow = MainWindow::getMainWindow();
    mainWindow->back();
}

void CommandsView::edit()
{

}

void CommandsView::details()
{
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
    if(std::find(m_detailsButtons.begin(), m_detailsButtons.end(), buttonSender) != m_detailsButtons.end())
    {
        auto index = std::find(m_detailsButtons.begin(), m_detailsButtons.end(), buttonSender) - m_detailsButtons.begin();
        qDebug() << index;
        QWidget* commanddialog(new CommandDialog(this, m_db, m_commands->at(index), false));
        commanddialog->show();
    }
}

void CommandsView::createCommand()
{

}
