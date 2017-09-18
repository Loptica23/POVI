#include <QDebug>
#include <QMessageBox>
#include <QPushButton>
#include <QComboBox>
#include <QCloseEvent>
#include "commanddialog.h"
#include "ui_commanddialog.h"
#include "mainwindow.h"
#include "dbconnection.h"

//ovaj se koristi za kreiranje naloga
CommandDialog::CommandDialog(QWidget *parent, std::shared_ptr<DBConnection> db, OrderPtr order, Refreshable* refreshable) :
    QDialog(parent),
    Refresher(refreshable),
    ui(new Ui::CommandDialog),
    m_db(db),
    m_order(order),
    m_create(true),
    m_tasks(new TaskVtr()),
    m_deletedTasks(new TaskVtr()),
    m_edit(true),
    m_serialNumberEmpty(true),
    m_comercialistDescriptionEmpty(true),
    m_specificationEmpty(true),
    m_quantityEmpty(true),
    m_designerDescriptionEmpty(true),
    m_storeKeeperDescriptionEmpty(true),
    m_currentTask(nullptr),
    m_haveItInvoice(false)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    connectSignalsAndSlots();
}

//ovaj se koristi za prikaz naloga ili njegovu izmenu
CommandDialog::CommandDialog(QWidget *parent, std::shared_ptr<DBConnection> db, CommandPtr command, bool edit, Refreshable *refreshable) :
    QDialog(parent),
    Refresher(refreshable),
    ui(new Ui::CommandDialog),
    m_db(db),
    m_command(command),
    m_create(false),
    m_tasks(new TaskVtr()),
    m_edit(edit),
    m_deletedTasks(new TaskVtr()),
    m_serialNumberEmpty(true),
    m_comercialistDescriptionEmpty(true),
    m_specificationEmpty(true),
    m_quantityEmpty(true),
    m_designerDescriptionEmpty(true),
    m_storeKeeperDescriptionEmpty(true),
    m_currentTask(nullptr),
    m_haveItInvoice(false)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);

    m_command = m_db->getCommand(m_command->getCommandNumber());

    connectSignalsAndSlots();
    initializeTasks();

    ui->commandNumber->setText(QString::number(command->getCommandNumber()));
    ui->Priority->setText(QString::number(command->getPriority()));
    ui->comercialistDescription->setText(command->getComercialistDescription());
    ui->specification->setText(command->getSpecification());
    ui->quantity->setText(QString::number(command->getQuantity()));
    ui->designerDescription->setText(command->getDesignerDescription());
    ui->storekeeperDescription->setText(command->getStoreKeeperDescription());
    //ostali su ti taskovi

    if (!m_edit)
    {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
        ui->commandNumber->setEnabled(false);
        ui->comercialistDescription->setReadOnly(true);
        ui->specification->setReadOnly(true);
        ui->quantity->setReadOnly(true);
        ui->designerDescription->setReadOnly(true);
        ui->storekeeperDescription->setReadOnly(true);
        ui->invoiceDescription->setReadOnly(true);
        ui->lineEdit->setReadOnly(true);
        ui->Priority->setEnabled(false);
        ui->comboBox->setVisible(false);
        //ostali su ti taskovi
    }
}

CommandDialog::~CommandDialog()
{
    qDebug() << "Destrukcija naloga!";
    delete ui;
}

void CommandDialog::connectSignalsAndSlots()
{
    connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(templateChanged(int)));
    connect(ui->specification, SIGNAL(textChanged()), this, SLOT(on_specification_textChanged()));
    connect(ui->quantity, SIGNAL(textChanged(QString)), this, SLOT(on_quantity_textChanged()));
}

void CommandDialog::initializeTasks()
{
    m_tasks = m_db->getTasks(m_command);
    for (auto iter = m_tasks->begin(); iter != m_tasks->end(); ++iter)
    {
        TaskPtr task = *iter;
        if((task->getState() == Task::State::InProgress) || (task->getState() == Task::State::Waiting))
        {
            m_currentTask = task;
        }
    }
}

void CommandDialog::removeWidget(QWidget * widget)
{
    qDeleteAll(widget->children());
    delete widget;
}

void CommandDialog::on_buttonBox_accepted()
{
    if (!m_create && !m_db->canCommandBeModified(m_command))
    {
        QString error = "Akcija ne moze biti izvrsena jer je neko drugi uradio izmenu pre Vas. Pokusajte ponovo.";
        QMessageBox messageBox;
        messageBox.critical(0, "Greska", error);
    }
    else
    {
        acceptButtonClicked();

        if (m_create)
        {
            createCommand();
        }
        else
        {
            updateCommand();
        }
    }

    backToDefaultScreen();
}

void CommandDialog::on_buttonBox_rejected()
{
    rejectButtonClicked();
    backToDefaultScreen();
}

void CommandDialog::templateChanged(int i)
{
    taskTemplateChanged(i);
}

void CommandDialog::acceptButtonClicked() {}
void CommandDialog::rejectButtonClicked() {}
void CommandDialog::serialNumberChanged() {}
void CommandDialog::comercialistDescriptionChanged() {}
void CommandDialog::specificationChanged() {}
void CommandDialog::quantityChanged() {}
void CommandDialog::designerDescriptionChanged() {}
void CommandDialog::storeKeeperDescriptionChanged() {}
void CommandDialog::taskTemplateChanged(int i) {qDebug() << "Neiskorisceni parametar" << QString::number(i);}
void CommandDialog::backToDefaultScreen() {}
void CommandDialog::closeEvent(QCloseEvent * closeEvent) {closeEvent->accept();}
void CommandDialog::annul() {}
void CommandDialog::taskMachineChanged() {}

void CommandDialog::showContinueToWorkButton()
{
    auto cont = new QPushButton("Nastavi rad na nalogu!");
    ui->buttonBox->addButton(cont, QDialogButtonBox::DestructiveRole);
    connect(cont, SIGNAL(clicked(bool)), this, SLOT(continueToWorkOnCommand()));
}

void CommandDialog::changeTaskType(int index)
{
    QComboBox* comboBoxSender = qobject_cast<QComboBox*>(sender());
    if (std::find(m_comboBoxes.begin(), m_comboBoxes.end(), comboBoxSender) != m_comboBoxes.end())
    {
        auto row = std::find(m_comboBoxes.begin(), m_comboBoxes.end(), comboBoxSender) - m_comboBoxes.begin();
        qDebug() << row;
        ++index;
        qDebug() << index;
        TaskPtr oldtask = m_tasks->at(row);
        m_deletedTasks->push_back(oldtask);
        m_tasks->at(row).reset(new Task(m_command, index));
        m_tasks->at(row)->setSerialNumber(row + 1);
    }
}

void CommandDialog::addNewTask(int index)
{
    qDebug() << index;
}

void CommandDialog::up() {}
void CommandDialog::down() {}
void CommandDialog::deleteTask() {}


void CommandDialog::createCommand()
{
    CommandPtr command(new Command(m_order->getCustomerId(), m_order->getID(), 0, MainWindow::getLogedUser()->getId()));
    if (!ui->specification->toPlainText().isEmpty())
    {
        command->setSpecification(ui->specification->toPlainText());
    }
    if (!ui->quantity->text().isEmpty())
    {
        command->setQuantity(ui->quantity->text().toUInt());
    }
    if (!ui->comercialistDescription->toPlainText().isEmpty())
    {
        command->setComercialistDescription(ui->comercialistDescription->toPlainText());
    }
    if (!ui->commandNumber->text().isEmpty())
    {
        command->setCommandNumber(ui->commandNumber->text().toInt());
    }

    if (!m_db->createNewCommand(command))
    {
        QString error = m_db->getLastError();
        QMessageBox messageBox;
        messageBox.critical(0,"Error",error);
    }
    else
    {
        m_command = m_db->getCommand(command->getCommandNumber());
        //ako je sve ok proslo sada kreiras zadatke koji su ti u vektoru
        auto serialNumber = 1;
        for (auto i = m_tasks->begin(); i != m_tasks->end(); ++i, ++serialNumber)
        {
            (*i)->setCommand(m_command);
            if (!m_db->createNewTask(*i, MainWindow::getWorker()->getId()))
            {
                QString error = m_db->getLastError();
                QMessageBox messageBox;
                messageBox.critical(0,"Error",error);
            }
        }
    }
}

void CommandDialog::closeCommandDialogAndApp(QCloseEvent * closeEvent)
{
    auto resBtn = QMessageBox::question(this, "Upozorenje",
                                        "Da li ste sigurni da zelite da zatvorite nalog i ugasite aplikaciju. Promene nece biti sacuvane!",
                                        QMessageBox::No | QMessageBox::Yes);
    if (resBtn != QMessageBox::Yes) {
        closeEvent->ignore();
    } else {
        closeEvent->accept();
        auto mainWindow = MainWindow::getMainWindow();
        mainWindow->close();
    }
}

void CommandDialog::updateCommand()
{
    //ova funkcija bi trebalo da je overajdovana! i da je ovaj kod ispod mrtav kod
    /*switch(MainWindow::getWorker()->getWorkPosition())
    {
    case Employee::WorkPosition::Administrator:
        if (!ui->commandNumber->text().isEmpty())
            m_command->setCommandNumber(ui->commandNumber->text().toUInt());
        if (!ui->comercialistDescription->toPlainText().isEmpty())
            m_command->setComercialistDescription(ui->comercialistDescription->toPlainText());
        if (!ui->designerDescription->toPlainText().isEmpty())
            m_command->setDesignerDescription(ui->designerDescription->toPlainText());
        if (!ui->storekeeperDescription->toPlainText().isEmpty())
            m_command->setStoreKeeperDescription(ui->storekeeperDescription->toPlainText());
        break;
    case Employee::WorkPosition::Komercijalista:
        break;
    }

    if (m_command->isModified())
    {
        if (!m_db->updateCommand(m_command))
        {
            QString error = m_db->getLastError();
            QMessageBox messageBox;
            messageBox.critical(0,"Error",error);
        }
    }*/
}


void CommandDialog::on_storekeeperDescription_textChanged()
{
    if (ui->storekeeperDescription->toPlainText().isEmpty())
        m_storeKeeperDescriptionEmpty = true;
    else
        m_storeKeeperDescriptionEmpty = false;

    storeKeeperDescriptionChanged();
}

void CommandDialog::on_specification_textChanged()
{
    if (ui->specification->toPlainText().isEmpty())
        m_specificationEmpty = true;
    else
        m_specificationEmpty = false;

    specificationChanged();
}

void CommandDialog::on_quantity_textChanged()
{
    if (ui->quantity->text().isEmpty())
        m_quantityEmpty = true;
    else
        m_quantityEmpty = false;

    quantityChanged();
}


void CommandDialog::on_designerDescription_textChanged()
{
    if (ui->designerDescription->toPlainText().isEmpty())
        m_designerDescriptionEmpty = true;
    else
        m_designerDescriptionEmpty = false;

    designerDescriptionChanged();
}

void CommandDialog::on_comercialistDescription_textChanged()
{
    if (ui->comercialistDescription->toPlainText().isEmpty())
        m_comercialistDescriptionEmpty = true;
    else
        m_comercialistDescriptionEmpty = false;

    comercialistDescriptionChanged();
}

void CommandDialog::on_commandNumber_textChanged(const QString &arg1)
{
    qDebug() << arg1;
    if (!ui->commandNumber->text().isEmpty())
        m_serialNumberEmpty = true;
    else
        m_serialNumberEmpty = false;

    serialNumberChanged();
}

void CommandDialog::continueToWorkOnCommand()
{
    close();
    auto mainWindow = MainWindow::getMainWindow();
    mainWindow->backToDefaultScreen();
}

void CommandDialog::ifFalseShowDbError(bool b)
{
    if (!b)
    {
        QString error = m_db->getLastError();
        QMessageBox messageBox;
        messageBox.critical(0,"Error",error);
    }
}

void CommandDialog::removeInvoiceWidgetIfTaskDontNeedIt()
{
    m_haveItInvoice = true;
    if (m_currentTask)
    {
        TaskTypePtr taskType = m_db->getTaskTypes()->getTaskTypeById(m_currentTask->getTaskTypeId());
        if (!taskType->isVirtual())
        {
            removeWidget(ui->invoice);
            m_haveItInvoice = false;
        }
    }
}
