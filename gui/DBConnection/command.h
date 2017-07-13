#pragma once
#include "dbconnection_global.h"
#include <vector>
#include <QSqlQuery>
#include <QString>
#include <QdateTime>

class Command;
typedef std::shared_ptr<Command> CommandPtr;
typedef std::weak_ptr<Command> CommandWeakPtr;
typedef std::vector<CommandPtr> CommandVtr;
typedef std::shared_ptr<CommandVtr> CommandPtrVtr;

//nalog
class DBCONNECTIONSHARED_EXPORT Command{

public:
    enum class State{New, WaitForProduction, InProgress, Complited, Stopped};

    Command(unsigned idCustomer, unsigned idOrder, unsigned idCommand, unsigned idKomercialist);
    virtual ~Command();

    //gethers
    int getCommandNumber() const;
    int getPriority() const;
    unsigned getID() const;
    unsigned getIdOrder() const;
    unsigned getIdCustomer() const;
    unsigned getKomercialistID() const;
    const QString& getSpecification() const;
    unsigned getQuantity() const;
    const QString& getComercialistDescription() const;
    const QString& getDesignerDescription() const;
    const QString& getStoreKeeperDescription() const;
    const State getState() const;
    unsigned getStateInt() const;
    QString getStateQString() const;
    const QDateTime& getDateTimePrediction() const;

    //seters
    void setCommandNumber(int commandNumber);
    void setPriority(int priority);
    void setSpecification(const QString & specification);
    void setQuantity(unsigned quantity);
    void setComercialistDescription(const QString & description);
    void setDesignerDescription(const QString & description);
    void setStoreKeeperDescription(const QString & description);
    void setState(const State& state);
    void setState(const QString& state);
    void setState(const unsigned state);
    void setDateTimePrediction(const QDateTime & prediction);

    QString statemantForCreating() const;
    QString statemantForUpdating() const;
    QString statementForDeleting() const;

    bool isModified() const;
    void resetChangeTracking();


    static CommandPtrVtr createCommandsFromQuery(QSqlQuery& query);
    static QString convertStateToString(const State &state);

private:
    unsigned m_id;
    unsigned m_idOrder;
    unsigned m_idCustomer;
    unsigned m_idKomercialist;

    State m_state;
    bool m_stateChanged;

    int m_priority;
    bool m_priorityChanged;

    int m_commandNumber;
    bool m_commandNumberChanged;

    QString m_specification;
    bool m_specificationChanged;

    unsigned m_quantity;
    bool m_quantityChanged;

    QString m_comercialistDescription;
    bool m_comercialistDescriptionChanged;

    QString m_designerDescription;
    bool m_designerDescriptionChanged;

    QString m_storeKeeperDescription;
    bool m_storeKeeperDescriptionChanged;

    QDateTime m_dateTimePrediction;
    bool m_dateTimePredictionChanged;
};
