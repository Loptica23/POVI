#pragma once

#include "commanddialog.h"

class CommandDialogStoreKeeper : public CommandDialog
{
public:
    CommandDialogStoreKeeper(QWidget *parent, std::shared_ptr<DBConnection> db, CommandPtr command, bool edit);
    virtual ~CommandDialogStoreKeeper();

    virtual void setUpWindowByWorkPosition();
protected:
    virtual void updateCommand();

    virtual void acceptButtonClicked();
    virtual void rejectButtonClicked();
    virtual void storeKeeperDescriptionChanged();
};
