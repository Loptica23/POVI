#pragma once
#include "commanddialog.h"

class CommandDialogInvoice : public CommandDialog
{
public:
    CommandDialogInvoice(QWidget *parent, std::shared_ptr<DBConnection> db, CommandPtr command, bool edit, Refreshable *refreshable);
    virtual ~CommandDialogInvoice();

    virtual void setUpWindowByWorkPosition();

protected:
    virtual void updateCommand();
    virtual void acceptButtonClicked();
    virtual void rejectButtonClicked();

    void initializeInvoiceDescription();
};
