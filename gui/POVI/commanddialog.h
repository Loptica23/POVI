#pragma once
#include <QDialog>
#include <QComboBox>
#include <QPushButton>
#include "order.h"
#include "command.h"
#include "dbconnection.h"
#include "task.h"
#include "refresher.h"

namespace Ui {
class CommandDialog;
}

class CommandDialog : public QDialog, public Refresher
{
    Q_OBJECT

public:
    CommandDialog(QWidget *parent, std::shared_ptr<DBConnection> db, OrderPtr order, Refreshable* refreshable);
    CommandDialog(QWidget *parent, std::shared_ptr<DBConnection> db, CommandPtr command, bool edit, Refreshable* refreshable);
    ~CommandDialog();

    virtual void setUpWindowByWorkPosition() = 0;

    void connectSignalsAndSlots();

protected slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

    void templateChanged(int i);

    void changeTaskType(int index);
    virtual void addNewTask(int index);
    virtual void up();
    virtual void down();
    virtual void deleteTask();

    virtual void acceptButtonClicked();
    virtual void rejectButtonClicked();
    virtual void annul();

protected:
    void fillTaskTable();
    void initializeTasks();
    void removeWidget(QWidget * widget);
    void createCommand();
    virtual void updateCommand();

    virtual void serialNumberChanged();
    virtual void comercialistDescriptionChanged();
    virtual void specificationChanged();
    virtual void quantityChanged();
    virtual void designerDescriptionChanged();
    virtual void storeKeeperDescriptionChanged();
    virtual void taskTemplateChanged(int i);
    virtual void backToDefaultScreen();

    void showContinueToWorkButton();
    void ifFalseShowDbError(bool b);
    void removeInvoiceWidgetIfTaskDontNeedIt();

    Ui::CommandDialog *ui;

    bool m_edit;
    bool m_create;
    bool m_haveItInvoice;
    OrderPtr m_order;
    CommandPtr m_command;
    TaskPtrVtr m_tasks;
    TaskPtr m_currentTask;
    TaskPtrVtr m_deletedTasks;
    std::shared_ptr<DBConnection> m_db;

    std::vector<QComboBox*> m_comboBoxes;
    std::vector<QPushButton*> m_upButtons;
    std::vector<QPushButton*> m_downButtons;
    std::vector<QPushButton*> m_deleteButtons;

    bool m_serialNumberEmpty;
    bool m_comercialistDescriptionEmpty;
    bool m_specificationEmpty;
    bool m_quantityEmpty;
    bool m_designerDescriptionEmpty;
    bool m_storeKeeperDescriptionEmpty;
private slots:
    void on_storekeeperDescription_textChanged();
    void on_specification_textChanged();
    void on_quantity_textChanged();
    void on_designerDescription_textChanged();
    void on_comercialistDescription_textChanged();
    void on_commandNumber_textChanged(const QString &arg1);
    void continueToWorkOnCommand();
};
