#include <QWidget>
#include "commanddialogdesigner.h"
#include "ui_commanddialog.h"

CommandDialogDesigner::CommandDialogDesigner(QWidget *parent, std::shared_ptr<DBConnection> db, CommandPtr command, bool edit) :
    CommandDialog(parent, db, command, edit)
{
    setUpWindowByWorkPosition();
}

CommandDialogDesigner::~CommandDialogDesigner()
{

}

void CommandDialogDesigner::setUpWindowByWorkPosition()
{
    removeWidget(ui->storekeeper);
    removeWidget(ui->tasks);
    this->repaint();
}


//implementation of pure virtual functions
void CommandDialogDesigner::addNewTask(int index)
{

}

void CommandDialogDesigner::up()
{

}

void CommandDialogDesigner::down()
{

}

void CommandDialogDesigner::deleteTask()
{

}
