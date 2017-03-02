#pragma once

#include "commanddialog.h"

class CommandDialogDesigner : public CommandDialog
{
public:
    CommandDialogDesigner(QWidget *parent, std::shared_ptr<DBConnection> db, CommandPtr command, bool edit);
    virtual ~CommandDialogDesigner();

    virtual void setUpWindowByWorkPosition();

protected:
    virtual void addNewTask(int index);
    virtual void up();
    virtual void down();
    virtual void deleteTask();
};
