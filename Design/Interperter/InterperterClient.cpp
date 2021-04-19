#include "InterperterClient.h"
#include "Interperter.h"

InterperterClient::InterperterClient()
{
}

InterperterClient::~InterperterClient()
{

}

void InterperterClient::Test()
{
    Context *context = new Context;
    QList<AbstracExpression*> list;
    list.push_back(new TerminalExpression);
    list.push_back(new NonterminalExpression);
    list.push_back(new TerminalExpression);
    list.push_back(new TerminalExpression);

    for(int i =0; i <list.size(); i++)
    {
        AbstracExpression* exp = list.at(i);
        exp->interperter(context);
    }
}
MYREGISTER(InterperterClient)
