#include <QDebug>
#include <QMessageBox>
#include "commandsview.h"
#include "ui_commandsview.h"
#include "command.h"
#include "mainwindow.h"
#include "commanddialog.h"
#include "commanddialogkomercialist.h"

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
    auto commanddialog = new CommandDialogKomercialist(this, m_db, m_order);
    commanddialog->show();
}

void CommandsView::on_Refresh_clicked()
{
    //refaktorisi malo ovu funkciju
    m_editButtons.clear();
    m_detailsButtons.clear();
    m_finishButtons.clear();
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
            auto *item = new QTableWidgetItem((*iter)->getStateQString());
            ui->tableWidget->setItem(i, 1,item);
        }
        {
            QPushButton* btn_details = new QPushButton();
            btn_details->setText("Detalji");
            ui->tableWidget->setIndexWidget(ui->tableWidget->model()->index(i, 2), btn_details);
            m_detailsButtons.push_back(btn_details);
            connect(btn_details, SIGNAL(clicked()), this, SLOT(details()));
        }
        {
            QPushButton* btn_edit = new QPushButton();
            btn_edit->setText("Izmeni");
            ui->tableWidget->setIndexWidget(ui->tableWidget->model()->index(i, 3), btn_edit);
            m_editButtons.push_back(btn_edit);
            connect(btn_edit, SIGNAL(clicked()), this, SLOT(edit()));
            if ((*iter)->getState() != Command::State::New)
            {
                btn_edit->setEnabled(false);
            }
        }
        {
            QPushButton* btn_finis = new QPushButton();
            btn_finis->setText("Posalji u proizvodnju");
            ui->tableWidget->setIndexWidget(ui->tableWidget->model()->index(i, 4), btn_finis);
            m_finishButtons.push_back(btn_finis);
            connect(btn_finis, SIGNAL(clicked()), this, SLOT(sendToProduction()));
            if ((*iter)->getState() != Command::State::New)
            {
                btn_finis->setEnabled(false);
            }
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
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
    if(std::find(m_editButtons.begin(), m_editButtons.end(), buttonSender) != m_editButtons.end())
    {
        auto index = std::find(m_editButtons.begin(), m_editButtons.end(), buttonSender) - m_editButtons.begin();
        qDebug() << index;
        QWidget* commanddialog(new CommandDialogKomercialist(this, m_db, m_commands->at(index), true));
        commanddialog->show();
    }
}

void CommandsView::details()
{
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
    if(std::find(m_detailsButtons.begin(), m_detailsButtons.end(), buttonSender) != m_detailsButtons.end())
    {
        auto index = std::find(m_detailsButtons.begin(), m_detailsButtons.end(), buttonSender) - m_detailsButtons.begin();
        qDebug() << index;
        QWidget* commanddialog(new CommandDialogKomercialist(this, m_db, m_commands->at(index), false));
        commanddialog->show();
    }
}

void CommandsView::createCommand()
{
    auto commanddialog = new CommandDialogKomercialist(this, m_db, m_order);
    commanddialog->show();
}

void CommandsView::sendToProduction()
{
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
    if(std::find(m_finishButtons.begin(), m_finishButtons.end(), buttonSender) != m_finishButtons.end())
    {
        auto index = std::find(m_finishButtons.begin(), m_finishButtons.end(), buttonSender) - m_finishButtons.begin();
        qDebug() << index;
        if (!m_db->completeCurrentTask(m_commands->at(index)))
        {
            QString error = m_db->getLastError();
            QMessageBox messageBox;
            messageBox.critical(0,"Error",error);
        }
    }
}
