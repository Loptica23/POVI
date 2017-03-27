#include "dbconnection.h"
#include <QString>
#include <QDebug>
#include <QSqlQuery>

Employee::Employee(unsigned id):
m_id(id)
{

}

Employee::~Employee()
{

}

void Employee::setFirstName(const QString& firstName)
{
    if (m_FirstName != firstName)
    {
        m_FirstName = firstName;
        m_FirstNameChanged = true;
    }
}

void Employee::setSecondName(const QString& secondName)
{
    if (m_SecondName != secondName)
    {
        m_SecondName = secondName;
        m_SecondNameChanged = true;
    }
}

void Employee::setUserName(const QString& userName)
{
    if (m_UserName != userName)
    {
        m_UserName = userName;
        m_UserNameChanged = true;
    }
}

void Employee::setPWD(const QString& pwd)
{
    if (m_pwd != pwd)
    {
        m_pwd = pwd;
        m_pwdChanged = true;
    }
}

void Employee::setWorkPosition(const WorkPosition& workPosition)
{
    if (m_WorkPosition != workPosition)
    {
        m_WorkPosition = workPosition;
        m_WorkPositionChanged = true;
    }
}

void Employee::setActivation(bool activation)
{
    if (m_Activation != activation)
    {
        m_Activation = activation;
        m_ActivationChanged = true;
    }
}


void Employee::setWorkPosition(const QString &workPosition)
{
    if (workPosition == "adm")
    {
        setWorkPosition(WorkPosition::Administrator);
    }
    else if(workPosition == "diz")
    {
        setWorkPosition(WorkPosition::Dizajner);
    }
    else if(workPosition == "mag")
    {
        setWorkPosition(WorkPosition::Magacioner);
    }
    else if(workPosition == "pro")
    {
        setWorkPosition(WorkPosition::Proizvodnja);
    }
    else if(workPosition == "pak")
    {
        setWorkPosition(WorkPosition::Pakovanje);
    }
    else if(workPosition == "kom")
    {
        setWorkPosition(WorkPosition::Komercijalista);
    }
    else if (workPosition == "spr")
    {
        setWorkPosition(WorkPosition::SefProizvodnje);
    }
    else if (workPosition == "ssm")
    {
        setWorkPosition(WorkPosition::SefSmene);
    }
    else
    {
        qDebug() << "***************************Greska ne postoji ta radna pozicija!****************************";
    }
}

void Employee::setWorkPosition(const unsigned workPosition)
{
    qDebug() << "setovana radna pozicija preko inta";
    switch(workPosition)
    {
    case 0:
        setWorkPosition(WorkPosition::Administrator);
        break;
    case 1:
        setWorkPosition(WorkPosition::Komercijalista);
        break;
    case 2:
        setWorkPosition(WorkPosition::Proizvodnja);
        break;
    case 3:
        setWorkPosition(WorkPosition::Dizajner);
        break;
    case 4:
        setWorkPosition(WorkPosition::Pakovanje);
        break;
    case 5:
        setWorkPosition(WorkPosition::Magacioner);
        break;
    case 6:
        setWorkPosition(WorkPosition::SefProizvodnje);
        break;
    case 7:
        setWorkPosition(WorkPosition::SefSmene);
        break;
    default:
        qDebug() << "**************************NE postoji ova opcija**************************";
        break;
    }
}

unsigned Employee::getId() const
{
    return m_id;
}

const QString& Employee::getFirstName() const
{
    return m_FirstName;
}

const QString& Employee::getSecondName() const
{
    return m_SecondName;
}

const QString& Employee::getUserName() const
{
    return m_UserName;
}

const QString Employee::getWorkPositionQString() const
{
    switch(m_WorkPosition)
    {
    case WorkPosition::Administrator:
        return "adm";
    case WorkPosition::Komercijalista:
        return "kom";
    case WorkPosition::Magacioner:
        return "mag";
    case WorkPosition::Proizvodnja:
        return "pro";
    case WorkPosition::Pakovanje:
        return "pak";
    case WorkPosition::Dizajner:
        return "diz";
    case WorkPosition::SefProizvodnje:
        return "spr";
    case WorkPosition::SefSmene:
        return "ssm";
    default:
        qDebug() << "***************************Greska nema tog enuma!************************";
        return "";
    }
}

const unsigned Employee::getWorkPositionQInt() const
{
    switch(m_WorkPosition)
    {
    case WorkPosition::Administrator:
        return 0;
    case WorkPosition::Komercijalista:
        return 1;
    case WorkPosition::Proizvodnja:
        return 2;
    case WorkPosition::Dizajner:
        return 3;
    case WorkPosition::Pakovanje:
        return 4;
    case WorkPosition::Magacioner:
        return 5;
    case WorkPosition::SefProizvodnje:
        return 6;
    case WorkPosition::SefSmene:
        return 7;
    default:
        qDebug() << "***************************Greska nema tog enuma!************************";
        return 88;
    }
}

const Employee::WorkPosition& Employee::getWorkPosition() const
{
    return m_WorkPosition;
}

bool Employee::getActivation() const
{
    return m_Activation;
}

QString Employee::getActivationSqlString() const
{
    if (getActivation())
    {
        return "true";
    }
    else
    {
        return "false";
    }
}

QString Employee::getActivationString() const
{
    if (getActivation())
    {
        return "da";
    }
    else
    {
        return "ne";
    }
}

EmployeePtrVtr Employee::createEmployeesFromQuery(QSqlQuery& query)
{
    EmployeePtrVtr employees(new EmployeeVtr());
    while(query.next())
    {
        EmployeePtr emp(new Employee(query.value("idRadnik").toUInt()));
        emp->setFirstName(query.value("Ime").toString());
        emp->setSecondName(query.value("Prezime").toString());
        emp->setUserName(query.value("KorisnickoIme").toString());
        emp->setWorkPosition(query.value("Pozicija").toString());
        emp->setPWD(query.value("Sifra").toString());

        if (query.value("PristupSistemu") == true)
        {
            emp->setActivation(true);
        }
        else
        {
            emp->setActivation(false);
        }

        emp->resetChangeTracking();
        employees->push_back(emp);
    }
    return employees;
}

QString Employee::statemantForCreatingUser() const
{
    QString stm = "insert into radnik (Ime, Prezime, Sifra, KorisnickoIme, Pozicija, PristupSistemu) values ('" +
            getFirstName() + "', '" +
            getSecondName() + "', '" +
            "5555" + "', '" +
            getUserName() + "', '" +
            getWorkPositionQString() + "', " +
            getActivationSqlString() + ");";
    stm += "CREATE USER '" + getUserName() + "'@'%'  IDENTIFIED BY '5555';";
    stm += "GRANT ALL PRIVILEGES ON *.* TO '" + getUserName() + "'@'%' WITH GRANT OPTION;";
    stm += "FLUSH PRIVILEGES;";
    qDebug() << stm;
    return stm;
}

QString Employee::statemantForUpdatingUser() const
{
    QString stm;
    if (isModified())
    {
        stm = "update radnik set ";
        if (m_FirstNameChanged)
        {
            stm += "Ime = '" + getFirstName() + "' , ";
        }
        if (m_SecondNameChanged)
        {
            stm += "Prezime = '" + getSecondName() + "' , ";
        }
        if (m_UserNameChanged)
        {
            stm += "KorisnickoIme = '" + getUserName() + "' , ";
        }
        if (m_WorkPositionChanged)
        {
            stm += "Pozicija = '" + getWorkPositionQString() + "' , ";
        }
        if (m_ActivationChanged)
        {
            stm += "PristupSistemu = " + getActivationSqlString() + " , ";
        }
        if (m_pwdChanged)
        {
            stm += "Sifra = '" + m_pwd + "' , ";
        }
        stm.chop(2);
        stm += "where idRadnik = " + QString::number(m_id) + ";";
        if (m_pwdChanged)
        {
            stm += "SET PASSWORD FOR '" + m_UserName + "'@'%' = PASSWORD('" + m_pwd + "');";
        }
        qDebug() << stm;
    }
    else
    {
        qDebug() << "**************************************nema izmena**************************************";
    }
    return stm;
}

bool Employee::checkPWD(const QString & pwd) const
{
    bool result = false;
    if (m_pwd == pwd)
    {
        result = true;
    }
    return result;
}

bool Employee::isModified() const
{
    return (m_FirstNameChanged ||
            m_SecondNameChanged ||
            m_UserNameChanged ||
            m_WorkPositionChanged ||
            m_pwdChanged ||
            m_ActivationChanged);
}

void Employee::resetChangeTracking()
{
    m_FirstNameChanged      = false;
    m_SecondNameChanged     = false;
    m_UserNameChanged       = false;
    m_WorkPositionChanged   = false;
    m_ActivationChanged     = false;
    m_pwdChanged            = false;
}

