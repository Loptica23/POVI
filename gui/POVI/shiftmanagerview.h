#pragma once
#include <QWidget>
#include "dbconnection.h"

namespace Ui {
class ShiftManagerView;
}

class ShiftManagerView : public QWidget
{
    Q_OBJECT

public:
    ShiftManagerView(QWidget *parent, DBConnectionPtr db);
    ~ShiftManagerView();

private:
    void refreshProductionEmployees();

private slots:
    void on_pushButton_clicked();

private:
    Ui::ShiftManagerView *ui;
    DBConnectionPtr m_db;
};
