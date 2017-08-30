#pragma once

#include "dbconnection_global.h"
#include <vector>

class Employee;
typedef std::shared_ptr<Employee> EmployeePtr;
typedef std::vector<EmployeePtr> EmployeeVtr;
typedef std::shared_ptr<EmployeeVtr> EmployeePtrVtr;

class DBCONNECTIONSHARED_EXPORT Employee
{
public:
    enum class WorkPosition{
                            Administrator,
                            Komercijalista,
                            DizajnerLastis,
                            DizajnerTkanje,
                            DizajnerStampa,
                            Magacioner,
                            Proizvodnja,
                            Narucilac,
                            SefProizvodnje,
                            SefSmene,
                            KnjigovodjaFakture,
                           };
    Employee(unsigned id);
    virtual ~Employee();

    //seters
    void setFirstName(const QString& firstName);
    void setSecondName(const QString& secondName);
    void setUserName(const QString& userName);
    void setPWD(const QString& pwd);
    void setWorkPosition(const WorkPosition& workPosition);
    void setWorkPosition(const QString& workPosition);
    void setWorkPosition(const unsigned workPosition);
    void setActivation(bool activation);
    void resetPWD();

    //geters
    unsigned getId() const;
    const QString& getFirstName() const;
    const QString& getSecondName() const;
    const QString& getUserName() const;
    const WorkPosition& getWorkPosition() const;
    const QString getWorkPositionQString() const;
    const unsigned getWorkPositionQInt() const;
    bool getActivation() const;
    QString getActivationString() const;
    QString getActivationSqlString() const;

    bool checkPWD(const QString & pwd) const;

    //statemants
    QString statemantForCreatingUser() const;
    QString statemantForUpdatingUser() const;

    bool isModified() const;
    void resetChangeTracking();

    static EmployeePtrVtr createEmployeesFromQuery(QSqlQuery& query);

    static WorkPosition getWorkPositionFromQstring(const QString & workPosition);
    static WorkPosition getWorkPositionFromUint(unsigned workPosition);
    static QString getQstringFromWorkPosition(const WorkPosition workPosition);
    static unsigned getUnsignedFromWorkPosition(const WorkPosition workPosition);

private:
    unsigned m_id;

    QString m_FirstName;
    bool m_FirstNameChanged;

    QString m_SecondName;
    bool m_SecondNameChanged;

    QString m_UserName;
    bool m_UserNameChanged;

    WorkPosition m_WorkPosition;
    bool m_WorkPositionChanged;

    QString m_pwd;
    bool m_pwdChanged;

    bool m_Activation;
    bool m_ActivationChanged;
};
