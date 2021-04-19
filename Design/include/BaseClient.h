#ifndef BASECLIENT_H
#define BASECLIENT_H

#include "../ObjectFactory/ObjectFactory.h"
class BaseClient
{
public:
    BaseClient(){}
    virtual ~BaseClient(){}

    virtual void Test() = 0;
};

#endif // BASECLIENT_H
