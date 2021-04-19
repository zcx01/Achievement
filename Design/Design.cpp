#include "Design.h"
#include "./ObjectFactory/ObjectFactory.h"
#include "./include/BaseClient.h"

Design::Design()
{

}

BaseClient *Design::getClient(QByteArray funName)
{
    BaseClient *client = static_cast<BaseClient *>(ObjectFactory::createObject(funName));
    if(client)
        client->Test();
    return client;
}
