#pragma once
#include <QDialog>
#include "command.h"
#include "dbconnection.h"
#include "refresher.h"

namespace Ui {
class DialogSetPrediction;
}

class DialogSetPrediction : public QDialog, public Refresher
{
    Q_OBJECT

public:
    DialogSetPrediction(QWidget *parent, DBConnectionPtr db , CommandPtr command, Refreshable* refreshable);
    ~DialogSetPrediction();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::DialogSetPrediction *ui;
    DBConnectionPtr m_db;
    CommandPtr m_command;
};
