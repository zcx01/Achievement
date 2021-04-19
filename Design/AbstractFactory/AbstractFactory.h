#ifndef ABSTRACTFACTORY_H
#define ABSTRACTFACTORY_H

#include <QObject>
class User
{
public:
    User();
    void setId(int id);
    int  getId();

    void setName(QString name);
    QString getName();
private:
    int         m_Id;
    QString     m_Name;
};

class IUser
{
public:
    virtual void Insert(User *user)=0;
    virtual User* getUser(int id)=0;
};

class SqlserverUser : public IUser
{

    // IUser interface
public:
    void Insert(User *user);
    User *getUser(int id);
};

class AccessUser : public IUser
{

    // IUser interface
public:
    void Insert(User *user);
    User *getUser(int id);
};

class Department
{
public:
    Department();
    void setId(int id);
    int  getId();

    void setDeptName(QString deptName);
    QString getDeptName();
private:
    int         m_Id;
    QString     m_DeptName;
};

class IDepartment
{
public:
    virtual void Insert(Department *department) =0;
    virtual Department* GetDepartment(int id) =0;
};

class SqlserverDepartment : public IDepartment
{
public:
    void Insert(Department *department);
    Department* GetDepartment(int id);
};

class AccessDepartment : public IDepartment
{

    // IDepartment interface
public:
    void Insert(Department *department);
    Department *GetDepartment(int id);
};

class DataAccess
{
public:
    static IUser* createUser(QByteArray db);
    static IDepartment *createDepartment(QByteArray db);
};

#endif // ABSTRACTFACTORY_H
