#ifndef FACADECLIENT_H
#define FACADECLIENT_H

#include "../include/BaseClient.h"

class FacadeClient :public BaseClient
{
public:
    FacadeClient();
    ~FacadeClient();
    // BaseClient interface
public:
    void Test();
};

#endif // FACADECLIENT_H
