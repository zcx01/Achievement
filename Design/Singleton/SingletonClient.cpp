#include "SingletonClient.h"
#include "Singleton.h"

SingletonClient::SingletonClient()
{

}


void SingletonClient::Test()
{
    Singleton::getInstance();
    qDebug()<<"单利";
}
MYREGISTER(SingletonClient)
