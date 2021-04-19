#include "AbstractFactory.h"
#include <QDebug>
#include "../ObjectFactory/ObjectFactory.h"
User::User()
{

}

void User::setId(int id)
{
    m_Id = id;
}

int User::getId()
{
    return m_Id;
}

void User::setName(QString name)
{
    m_Name = name;
}

QString User::getName()
{
    return m_Name;
}

void SqlserverUser::Insert(User *user)
{
    qDebug()<<"在SQL Server中给User表增加一条记录";
}

User *SqlserverUser::getUser(int id)
{
    qDebug()<<"在SQL Server中根据ID得到User表一条记录";
    return NULL;
}
MYREGISTER(SqlserverUser)

void AccessUser::Insert(User *user)
{
    qDebug()<<"在Access中给User表增加一条记录";
}

User *AccessUser::getUser(int id)
{
    qDebug()<<"在Access中根据ID得到User表一条记录";
    return NULL;
}
MYREGISTER(AccessUser)

Department::Department()
{

}

void Department::setId(int id)
{
    m_Id =id;
}

int Department::getId()
{
    return m_Id;
}

void Department::setDeptName(QString deptName)
{
    m_DeptName =deptName;
}

QString Department::getDeptName()
{
    return m_DeptName;
}


void SqlserverDepartment::Insert(Department *department)
{
    qDebug()<<"在SQL Server中给department表增加一条记录";
}

Department *SqlserverDepartment::GetDepartment(int id)
{
    qDebug()<<"在SQL Server中根据ID得到department表一条记录";
    return NULL;
}
MYREGISTER(SqlserverDepartment)

void AccessDepartment::Insert(Department *department)
{
    qDebug()<<"在Access中给department表增加一条记录";
}

Department *AccessDepartment::GetDepartment(int id)
{
    qDebug()<<"在Access中根据ID得到department表一条记录";
    return NULL;
}
MYREGISTER(AccessDepartment)

IUser *DataAccess::createUser(QByteArray db)
{
    IUser *result = static_cast<IUser*>(ObjectFactory::createObject(db));
    return result;
}

IDepartment *DataAccess::createDepartment(QByteArray db)
{
    IDepartment *result = static_cast<IDepartment*>(ObjectFactory::createObject(db));
    return result;
}
