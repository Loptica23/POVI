#pragma once
#include "commanddialog.h"

class CommandDialogInvoice : public CommandDialog
{
public:
    CommandDialogInvoice(QWidget *parent, std::shared_ptr<DBConnection> db, CommandPtr command, bool edit);
    virtual ~CommandDialogInvoice();

    virtual void setUpWindowByWorkPosition();

protected:
    virtual void updateCommand();
    virtual void acceptButtonClicked();
    virtual void rejectButtonClicked();
    virtual void showContinueToWorkButtonByWorkPosition();

    void initializeInvoiceDescription();
};
