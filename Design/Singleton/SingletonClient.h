#ifndef SINGLETONCLIENT_H
#define SINGLETONCLIENT_H

#include "../include/BaseClient.h"
class SingletonClient :public BaseClient
{
public:
    SingletonClient();

    // BaseClient interface
public:
    void Test();
};

#endif // SINGLETONCLIENT_H
