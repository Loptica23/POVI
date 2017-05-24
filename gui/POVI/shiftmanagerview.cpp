#include "shiftmanagerview.h"
#include "ui_shiftmanagerview.h"
#include "dbconnection.h"
#include "employee.h"
#include "mainwindow.h"
#include "workerview.h"

#define NUMBER_OF_COLUMN 4

ShiftManagerView::ShiftManagerView(QWidget *parent, DBConnectionPtr db) :
    QWidget(parent),
    ui(new Ui::ShiftManagerView),
    m_db(db)
{
    ui->setupUi(this);
    ui->pushButton->setFocus();
    m_shiftMenager = MainWindow::getLogedUser();
}

ShiftManagerView::~ShiftManagerView()
{
    delete ui;
}

void ShiftManagerView::refreshProductionEmployees()
{
    //refactor - moras ovo da sredis! Pogotovu ove velicine celjija!
    m_buttons.clear();
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);

    ui->tableWidget->setColumnCount(NUMBER_OF_COLUMN);
    m_employees = m_db->getEmployees(Employee::WorkPosition::Proizvodnja);
    qDebug() << "User refreshing employees ShiftManagerView!";
    if (!m_employees || m_employees->empty())
    {
        return;
    }
    m_employees;
    auto i = 0;
    for (auto iter = m_employees->begin(); iter != m_employees->end(); ++i, ++iter)
    {
        EmployeePtr employee = *iter;
        if ((i%4)==0)
        {
            ui->tableWidget->insertRow(i/4);
        }
        {
            QPushButton* btn_edit = new QPushButton();
            btn_edit->setText(employee->getFirstName() + " " + employee->getSecondName());
            ui->tableWidget->setIndexWidget(ui->tableWidget->model()->index(i/4, i%4), btn_edit);
            m_buttons.push_back(btn_edit);
            connect(btn_edit, SIGNAL(clicked()), this, SLOT(buttonClicked()));
        }
    }
    ui->tableWidget->resizeColumnsToContents();

    auto width = (ui->tableWidget->frameSize().width()-NUMBER_OF_COLUMN)/NUMBER_OF_COLUMN;
    for(auto j = 0; j != NUMBER_OF_COLUMN; ++j)
    {
        ui->tableWidget->setColumnWidth(j, width);
    }
    qDebug() << width;

}

void ShiftManagerView::on_pushButton_clicked()
{
    //refresh
    refreshProductionEmployees();
}

void ShiftManagerView::buttonClicked()
{
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
    if(std::find(m_buttons.begin(), m_buttons.end(), buttonSender) != m_buttons.end())
    {
        auto index = std::find(m_buttons.begin(), m_buttons.end(), buttonSender) - m_buttons.begin();
        qDebug() << index;
        //imas indeks zaposlenog, znaci imas zaposlenog..
        //postavis ga da je on logovan i u zavisnosti od toga da li ima dodeljen zadatak prikazuje nalog ili listu zadataka koje treba izvrsiti...
        auto mainWindow = MainWindow::getMainWindow();
        std::shared_ptr<QWidget> workerView(new WorkerView(this, m_db, m_employees->at(index)));
        mainWindow->forward(workerView);
    }
}
