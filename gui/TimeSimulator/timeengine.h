#pragma once
#include <QRunnable>
#include <atomic>
#include <QString>
#include <QObject>
#include <QDateTime>
#include "types.h"
#include "timesimulator_global.h"

namespace TimeSimulator
{

class TIMESIMULATORSHARED_EXPORT TimeEngine : public QObject, public QRunnable
{

    Q_OBJECT

public:
    TimeEngine(QObject *parent = 0);
    virtual ~TimeEngine();

    void run();
    void stopEngine();

    bool checkIsEverythingSetUp();

    void addMachine(const QString & name, bool isVirtual, QTime startTime, QTime endTime, unsigned workingDays);
    void addCommand(unsigned id, unsigned commandNumber, unsigned priority);
    void addTask(const QString &machine, unsigned idCommand, unsigned serialNumber, unsigned prediction, TaskState state);

    TimeSimulatorResultMapPtr getResult() const;

    QDateTime m_moment;

signals:
    void sendResult();

private:
    MachineManagerPtr m_machineManager;
    CommandManagerPtr m_commandManager;
    std::atomic<bool> m_running;
};

}
