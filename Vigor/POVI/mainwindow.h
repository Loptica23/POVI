#pragma once;

#include <QMainWindow>
#include <memory>

enum class State{Izlogovan, Komercijala, Dizajner, Cekanje, Administrator};

namespace Ui {
class MainWindow;
}
class DBConnection;
class LoginTab;
class Waiting;
class AdminView;

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

    std::shared_ptr<LoginTab>   m_LoginTab;
    std::shared_ptr<Waiting>    m_WaitingTab;
    std::shared_ptr<AdminView>  m_AdminView;
};
