#pragma once

#include "commanddialog.h"

class CommandDialogWorker : public CommandDialog
{
public:
    CommandDialogWorker(QWidget *parent, std::shared_ptr<DBConnection> db, CommandPtr command, bool edit, Refreshable* refreshable);
    virtual ~CommandDialogWorker();

    virtual void setUpWindowByWorkPosition();

protected:
    virtual void acceptButtonClicked();
    virtual void rejectButtonClicked();
    virtual void backToDefaultScreen();
    virtual unsigned getQuantityDone() override;

private:
    void removeQuantityIfOrderingTask();
};
