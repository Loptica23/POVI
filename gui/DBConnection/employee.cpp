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
    setWorkPosition(Employee::getWorkPositionFromQstring(workPosition));
}

void Employee::setWorkPosition(const unsigned workPosition)
{
    setWorkPosition(Employee::getWorkPositionFromUint(workPosition));
    qDebug() << "setovana radna pozicija preko inta";
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
    return Employee::getQstringFromWorkPosition(m_WorkPosition);
}

const unsigned Employee::getWorkPositionQInt() const
{
    return Employee::getUnsignedFromWorkPosition(m_WorkPosition);
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

Employee::WorkPosition Employee::getWorkPositionFromQstring(const QString & workPosition)
{
    Employee::WorkPosition result;
    if (workPosition == "adm")
    {
        result = WorkPosition::Administrator;
    }
    else if(workPosition == "diz")
    {
        result = WorkPosition::Dizajner;
    }
    else if(workPosition == "mag")
    {
        result = WorkPosition::Magacioner;
    }
    else if(workPosition == "pro")
    {
        result = WorkPosition::Proizvodnja;
    }
    else if(workPosition == "pak")
    {
        result = WorkPosition::Pakovanje;
    }
    else if(workPosition == "kom")
    {
        result = WorkPosition::Komercijalista;
    }
    else if (workPosition == "spr")
    {
        result = WorkPosition::SefProizvodnje;
    }
    else if (workPosition == "ssm")
    {
        result = WorkPosition::SefSmene;
    }
    else
    {
        qDebug() << "***************************Greska ne postoji ta radna pozicija!****************************";
    }
    return result;
}
Employee::WorkPosition Employee::getWorkPositionFromUint(unsigned workPosition)
{
    Employee::WorkPosition result;
    switch(workPosition)
    {
    case 0:
        result = WorkPosition::Administrator;
        break;
    case 1:
        result = WorkPosition::Komercijalista;
        break;
    case 2:
        result = WorkPosition::Proizvodnja;
        break;
    case 3:
        result = WorkPosition::Dizajner;
        break;
    case 4:
        result = WorkPosition::Pakovanje;
        break;
    case 5:
        result = WorkPosition::Magacioner;
        break;
    case 6:
        result = WorkPosition::SefProizvodnje;
        break;
    case 7:
        result = WorkPosition::SefSmene;
        break;
    default:
        qDebug() << "**************************NE postoji ova opcija**************************";
        break;
    }
    return result;
}

QString Employee::getQstringFromWorkPosition(const Employee::WorkPosition &workPosition)
{
    QString result = "";
    switch(workPosition)
    {
    case WorkPosition::Administrator:
        result = "adm";
    case WorkPosition::Komercijalista:
        result = "kom";
    case WorkPosition::Magacioner:
        result = "mag";
    case WorkPosition::Proizvodnja:
        result = "pro";
    case WorkPosition::Pakovanje:
        result = "pak";
    case WorkPosition::Dizajner:
        result = "diz";
    case WorkPosition::SefProizvodnje:
        result = "spr";
    case WorkPosition::SefSmene:
        result = "ssm";
    default:
        qDebug() << "***************************Greska nema tog enuma!************************";
        result = "";
    }
    return result;
}

unsigned Employee::getUnsignedFromWorkPosition(const Employee::WorkPosition & workPosition)
{
    unsigned result = 88;
    switch(workPosition)
    {
    case WorkPosition::Administrator:
        result = 0;
    case WorkPosition::Komercijalista:
        result = 1;
    case WorkPosition::Proizvodnja:
        result = 2;
    case WorkPosition::Dizajner:
        result = 3;
    case WorkPosition::Pakovanje:
        result = 4;
    case WorkPosition::Magacioner:
        result = 5;
    case WorkPosition::SefProizvodnje:
        result = 6;
    case WorkPosition::SefSmene:
        result = 7;
    default:
        qDebug() << "***************************Greska nema tog enuma!************************";
        result = 88;
    }
    return result;
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

