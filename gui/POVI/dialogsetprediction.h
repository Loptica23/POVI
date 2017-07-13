#pragma once
#include <QDialog>
#include "command.h"
#include "dbconnection.h"

namespace Ui {
class DialogSetPrediction;
}

class DialogSetPrediction : public QDialog
{
    Q_OBJECT

public:
    DialogSetPrediction(QWidget *parent, DBConnectionPtr db , CommandPtr command);
    ~DialogSetPrediction();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::DialogSetPrediction *ui;
    DBConnectionPtr m_db;
    CommandPtr m_command;
};
