#pragma once

#include <QWidget>
#include <memory>

class MainWindow;
class DBConnection;

namespace Ui {
class AdminView;
}

class AdminView : public QWidget
{
    Q_OBJECT

public:
    AdminView(MainWindow *parent, std::shared_ptr<DBConnection> db);
    ~AdminView();

private:
    Ui::AdminView *ui;
    std::shared_ptr<DBConnection> m_db;
    MainWindow *m_mainWindow;
};
