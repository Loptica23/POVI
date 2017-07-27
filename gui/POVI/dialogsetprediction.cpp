#include "dialogsetprediction.h"
#include "ui_dialogsetprediction.h"

DialogSetPrediction::DialogSetPrediction(QWidget *parent, DBConnectionPtr db , CommandPtr command, Refreshable *refreshable) :
    QDialog(parent),
    Refresher(refreshable),
    ui(new Ui::DialogSetPrediction),
    m_db(db),
    m_command(command)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);

    QDateTime dateTime = command->getDateTimePrediction();
    if (!dateTime.isNull())
    {
        ui->calendarWidget->setSelectedDate(dateTime.date());
    }
}

DialogSetPrediction::~DialogSetPrediction()
{
    delete ui;
}

void DialogSetPrediction::on_buttonBox_accepted()
{
    QDateTime dateTime;
    dateTime.setDate(ui->calendarWidget->selectedDate());
    m_command->setDateTimePrediction(dateTime);
    m_db->updateCommand(m_command);
}
