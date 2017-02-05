#pragma once

#include <QWidget>
#include<memory>

class DBConnection;

namespace Ui {
class EmpoyersView;
}

class EmpoyersView : public QWidget
{
    Q_OBJECT

public:
    EmpoyersView(QWidget *parent, std::shared_ptr<DBConnection> db);
    ~EmpoyersView();

private slots:
    void on_Refresh_clicked();

    void on_CreateEmployee_clicked();

protected:
     void paintEvent(QPaintEvent *event);

private:
    Ui::EmpoyersView *ui;
    std::shared_ptr<DBConnection> m_db;
};
