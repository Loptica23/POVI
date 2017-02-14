#pragma once;

#include <QMainWindow>
#include <memory>
#include <stack>

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
    enum class State{Izlogovan, Komercijala, Dizajner, Cekanje, Administrator};

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void changeState(State state);

    void forward(std::shared_ptr<QWidget> widget);
    void back();

    static MainWindow* getMainWindow();
private:
    void connecttodb();

    Ui::MainWindow *ui;
    std::shared_ptr<DBConnection> m_dbConnection;
    State m_state;

    std::shared_ptr<LoginTab>   m_LoginTab;
    std::shared_ptr<QWidget>    m_defaultScreen;

    std::stack<std::shared_ptr<QWidget>> screenStack;

    static MainWindow* mainWindow;
};
