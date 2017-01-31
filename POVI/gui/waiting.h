#ifndef WAITING_H
#define WAITING_H

#include <QWidget>

namespace Ui {
class Waiting;
}

class Waiting : public QWidget
{
    Q_OBJECT

public:
    explicit Waiting(QWidget *parent = 0);
    ~Waiting();

private:
    Ui::Waiting *ui;
};

#endif // WAITING_H
