#include "CommandClient.h"
#include "Command.h"

CommandClient::CommandClient()
{
}

CommandClient::~CommandClient()
{

}

void CommandClient::Test()
{
    Receiver r;
    Command *c = new ConcreteCommand(&r);
    Invoker i;

    i.setCommand(c);
}
MYREGISTER(CommandClient)
