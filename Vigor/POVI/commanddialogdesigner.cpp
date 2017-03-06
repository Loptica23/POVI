#include <QWidget>
#include <QMessageBox>
#include "commanddialogdesigner.h"
#include "ui_commanddialog.h"
#include "mainwindow.h"

CommandDialogDesigner::CommandDialogDesigner(QWidget *parent, std::shared_ptr<DBConnection> db, CommandPtr command, bool edit) :
    CommandDialog(parent, db, command, edit)
{
    setUpWindowByWorkPosition();
    designerDescriptionChanged();
}

CommandDialogDesigner::~CommandDialogDesigner()
{

}

void CommandDialogDesigner::setUpWindowByWorkPosition()
{
    removeWidget(ui->storekeeper);
    removeWidget(ui->tasks);

    ui->commandNumber->setEnabled(false);
    ui->comercialistDescription->setEnabled(false);
    //nalog je preuzet
    if (m_edit)
    {
        this->showMaximized();
        ui->buttonBox->button(QDialogButtonBox::Ok)->setText("Posalji nalog u zavrseno stanje!");
        ui->buttonBox->button(QDialogButtonBox::Cancel)->setText("Ostavi nalog!");
    }

    this->repaint();
}

void CommandDialogDesigner::updateCommand()
{
    if (!ui->designerDescription->toPlainText().isEmpty())
    {
        m_command->setDesignerDescription(ui->designerDescription->toPlainText());
    }

    if (m_command->isModified())
    {
        if (!m_db->updateCommand(m_command))
        {
            QString error = m_db->getLastError();
            QMessageBox messageBox;
            messageBox.critical(0,"Error",error);
        }
    }
}

void CommandDialogDesigner::acceptButtonClicked()
{
    if (!m_db->completeCurrentTask(m_command))
    {
        qDebug() << "neuspelo zavrsavanje zadatka!";
        QString error = m_db->getLastError();
        QMessageBox messageBox;
        messageBox.critical(0,"Error",error);
    }
}

void CommandDialogDesigner::rejectButtonClicked()
{
    if (!m_db->leaveCurrentTask(m_command, MainWindow::getLogedUser()))
    {
        qDebug() << "neuspelo ostavljanje zadatka!";
        QString error = m_db->getLastError();
        QMessageBox messageBox;
        messageBox.critical(0,"Error",error);
    }
}

void CommandDialogDesigner::designerDescriptionChanged()
{
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(!m_designerDescriptionEmpty);
}
