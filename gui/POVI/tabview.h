#pragma once
#include <QWidget>
#include "dbconnection.h"
#include "mainwindow.h"

namespace Ui {
class TabView;
}

class TabView : public QWidget
{
    Q_OBJECT

public:
    TabView(MainWindow *mainWindow, DBConnectionPtr db);
    virtual ~TabView();

private:
    void setUpTabViewByWorkPosition();

    Ui::TabView *ui;
    DBConnectionPtr m_db;
};
