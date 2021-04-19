#include "Mediator.h"
#include "iostream"

Colleague::Colleague(Mediator *mediator)
{
    m_Mediator =mediator;
}


void ConcreteMediator::addColleague(Colleague *colleague)
{
    m_Colleague.push_back(colleague);
}

void ConcreteMediator::send(std::string message, Colleague *colleague)
{
    for(int i = 0; i < m_Colleague.size(); i++)
    {
        Colleague *col = m_Colleague.at(i);
        if(col != colleague)
            col->Notify(message);
    }
}

ConcreteColleague1::ConcreteColleague1(Mediator *mediator) : Colleague(mediator)
{

}

void ConcreteColleague1::send(std::string message)
{
   m_Mediator->send(message,this);
}

void ConcreteColleague1::Notify(std::string message)
{
    std::cout<<std::string("同事1得到消息:")+message<<std::endl;
}

ConcreteColleague2::ConcreteColleague2(Mediator *mediator) : Colleague(mediator)
{

}

void ConcreteColleague2::send(std::string message)
{
    m_Mediator->send(message,this);
}

void ConcreteColleague2::Notify(std::string message)
{
    std::cout<<std::string("同事2得到消息:")+message<<std::endl;
}
