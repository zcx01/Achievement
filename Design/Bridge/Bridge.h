#ifndef BRIDGE_H
#define BRIDGE_H

#include <QObject>

class Implement
{
public:
    virtual void Operation() = 0;
};

class ConcreteImplementA : public Implement
{
    // Implement interface
public:
    void Operation();
};

class ConcreteImplementB : public Implement
{
    // Implement interface
public:
    void Operation();
};

class Abstraction
{
public:
    Abstraction();
    void setImplementor(Implement *implement);

    virtual void Operation();

protected:
    Implement *m_Implement;
};

class RefinedAbstraction :public Abstraction
{

    // Abstraction interface
public:
    void Operation();
};

#endif // BRIDGE_H
