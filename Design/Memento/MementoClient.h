#ifndef MEMENTOCLIENT_H
#define MEMENTOCLIENT_H

#include "../include/BaseClient.h"

class MementoClient : public BaseClient
{
public:
    MementoClient();
    ~MementoClient();

    // BaseClient interface
public:
    void Test();
};

#endif // MEMENTOCLIENT_H
