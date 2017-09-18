#pragma once

#include "commanddialog.h"

class CommandDialogDesigner : public CommandDialog
{
public:
    CommandDialogDesigner(QWidget *parent, std::shared_ptr<DBConnection> db, CommandPtr command, bool edit, Refreshable *refreshable);
    virtual ~CommandDialogDesigner();

    virtual void setUpWindowByWorkPosition();

protected:
    virtual void updateCommand();
    virtual void acceptButtonClicked();
    virtual void rejectButtonClicked();
    virtual void designerDescriptionChanged();
    virtual void closeEvent(QCloseEvent * closeEvent);
};
