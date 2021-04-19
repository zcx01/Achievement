#ifndef ABSTRACTFACTORYCLIENT_H
#define ABSTRACTFACTORYCLIENT_H

#include "../include/BaseClient.h"

class AbstractFactoryClient : public BaseClient
{
public:
    AbstractFactoryClient();
    ~AbstractFactoryClient();

    void Test();
};

#endif // ABSTRACTFACTORYCLIENT_H
