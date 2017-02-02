#pragma once;

#include <QMainWindow>
#include <memory>

enum class State{Izlogovan, Komercijala, Dizajner, Cekanje};

namespace Ui {
class MainWindow;
}
class DBConnection;
class LoginTab;
class Waiting;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void changeState(State state);

private:
    void connecttodb();

    Ui::MainWindow *ui;
    std::shared_ptr<DBConnection> m_dbConnection;
    State m_state;

    LoginTab* m_LoginTab;       //ne znam koliko je pametno ovako
    Waiting* m_WaitingTab;
};
