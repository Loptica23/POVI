#include "dbconnection_global.h"
#include <vector>
#include <QSqlQuery>
#include <QString>
#pragma once

class Command;
typedef std::shared_ptr<Command> CommandPtr;
typedef std::vector<CommandPtr> CommandVtr;
typedef std::shared_ptr<CommandVtr> CommandPtrVtr;

//nalog
class DBCONNECTIONSHARED_EXPORT Command{

public:
    enum class State{New, Complited};

    Command(unsigned idCustomer, unsigned idOrder, unsigned idCommand);

    virtual ~Command();

    //gethers
    int getCommandNumber() const;
    int getPriority() const;
    unsigned getID() const;
    const QString& getComercialistDescription() const;
    const QString& getDesignerDescription() const;
    const QString& getStoreKeeperDescription() const;

    //seters
    void setCommandNumber(int commandNumber);
    void setPriority(int priority);
    void setComercialistDescription(const QString & description);
    void setDesignerDescription(const QString & description);
    void setStoreKeeperDescription(const QString & description);

    QString statemantForCreating() const;
    QString statemantForUpdating() const;

    bool isModified() const;
    void resetChangeTracking();


    static CommandPtrVtr createCommandsFromQuery(QSqlQuery& query);

private:
    unsigned m_id;
    unsigned m_idOrder;
    unsigned m_idCustomer;

    int m_priority;
    bool m_priorityChanged;

    int m_commandNumber;
    bool m_commandNumberChanged;

    QString m_comercialistDescription;
    bool m_comercialistDescriptionChanged;

    QString m_designerDescription;
    bool m_designerDescriptionChanged;

    QString m_storeKeeperDescription;
    bool m_storeKeeperDescriptionChanged;
};
