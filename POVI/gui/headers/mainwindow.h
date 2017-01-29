#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>
#include "databaseconnection.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void connecttodb();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    std::shared_ptr<DatabaseConnection> m_dbConnection;
};

#endif // MAINWINDOW_H
