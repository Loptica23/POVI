#include <QDebug>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_dbConnection(new DatabaseConnection()),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::connecttodb()
{

}

void MainWindow::on_pushButton_clicked()
{
    if(m_dbConnection->conectToDb())
    {
        qDebug() << "uspelo";
    }
    else
    {
        qDebug() << "nije";
    }
    if(m_dbConnection->logIn("milos.pajkic", "1234"))
    {
        qDebug() << "uspelo";
    }
    else
    {
        qDebug() << "nije";
    }
}
