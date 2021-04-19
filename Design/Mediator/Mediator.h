#ifndef MEDIATOR_H
#define MEDIATOR_H

#include <string>
#include <vector>

class Colleague;
//Mediator是抽象中介者，定义了同事对象到中介者对象的接口
class Mediator
{
public:
    virtual void send(std::string message,Colleague *colleague) =0;

protected:
    std::vector<Colleague *> m_Colleague;
};

//Colleague类，抽象中介者类
class Colleague
{
public:
    Colleague(Mediator *mediator);

    virtual void send(std::string message) =0;
    virtual void Notify(std::string message) =0;

protected:
    Mediator*   m_Mediator;
};

//Mediator是具体中介者
class ConcreteMediator : public Mediator
{
public:
    void addColleague(Colleague *colleague);
    // Mediator interface
public:
    void send(std::string message, Colleague *colleague);
};

class ConcreteColleague1 : public Colleague
{
    // Colleague interface
public:
    ConcreteColleague1(Mediator *mediator);

    void send(std::string message);

    void Notify(std::string message);
};

class ConcreteColleague2 : public Colleague
{
    // Colleague interface
public:
    ConcreteColleague2(Mediator *mediator);

    void send(std::string message);

    void Notify(std::string message);
};

#endif // MEDIATOR_H
